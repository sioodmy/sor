#include "EmergencyDepartment.hpp"
#include "CardiacPatient.hpp"
#include "ConfigParser.hpp"
#include "ConsultationRoom.hpp"
#include "Doctor.hpp"
#include "Employee.hpp"
#include "LoggerCSV.hpp"
#include "Nurse.hpp"
#include "StandardPatient.hpp"
#include "TraumaPatient.hpp"
#include "WaitingRoom.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

EmergencyDepartment::EmergencyDepartment(const ConfigParser &config)
    : currentMinute(0), patientsTreated(0), idCounter(1) {

  totalSimulationTime = config.getInt("total_time", 60);
  stepDuration = config.getInt("step_duration", 5);
  spawnChance = config.getInt("spawn_chance", 50);
  int numRooms = config.getInt("num_rooms", 3);

  waitingRoom = new WaitingRoom(100);
  for (int i = 0; i < numRooms; ++i) {
    consultRooms.push_back(new ConsultationRoom(1, i + 1));
  }
  logger = new LoggerCSV("output/simulation.csv");

  std::srand(std::time(nullptr));
}

EmergencyDepartment::~EmergencyDepartment() {
  delete waitingRoom;
  for (auto room : consultRooms) {
    delete room;
  }
  delete logger;
}

void EmergencyDepartment::addStaff(Employee *emp) { staff.push_back(emp); }

void EmergencyDepartment::assignDoctorToRoom(int roomIdx, Doctor *doc) {
  if (roomIdx >= 0 && roomIdx < static_cast<int>(consultRooms.size())) {
    consultRooms[roomIdx]->assignDoctor(doc);
  }
}

void EmergencyDepartment::spawnRandomPatient() {
  if ((std::rand() % 100) < spawnChance) {
    int health = std::rand() % 100;
    int treatmentTime = 10 + (std::rand() % 20);
    std::string id = "PAT" + std::to_string(idCounter++);

    Patient *p = nullptr;
    int type = std::rand() % 100;
    if (type < 50) {
      p = new StandardPatient(id, "John", "Doe", health, currentMinute,
                              treatmentTime);
    } else if (type < 80) {
      p = new CardiacPatient(id, "John", "Doe", health, currentMinute,
                             treatmentTime);
    } else {
      p = new TraumaPatient(id, "John", "Doe", health, currentMinute,
                            treatmentTime);
    }

    admitPatient(p);
  }
}

void EmergencyDepartment::admitPatient(Patient *p) {
  Nurse *triageNurse = nullptr;
  for (Employee *emp : staff) {
    triageNurse = dynamic_cast<Nurse *>(emp);
    if (triageNurse) {
      break;
    }
  }

  if (triageNurse) {
    triageNurse->performTriage(p);
    std::cout << "[Minute " << currentMinute << "] Patient " << p->getId()
              << " triaged by " << triageNurse->getFullName()
              << " with Priority " << static_cast<int>(p->getPriority())
              << ".\n";
    waitingRoom->addPatient(p);
  } else {
    std::cerr << "No nurse available for triage!\n";
    delete p;
  }
}

void EmergencyDepartment::runSimulation() {
  std::cout << "Starting Simulation for " << totalSimulationTime
            << " minutes.\n";

  while (currentMinute < totalSimulationTime) {
    spawnRandomPatient();

    waitingRoom->updateWaitingPatients();

    int occupiedRooms = 0;
    for (auto room : consultRooms) {
      if (!room->isFree()) {
        Patient *finished = room->processTreatment(stepDuration);
        if (finished) {
          std::cout << "[Minute " << currentMinute << "] Patient "
                    << finished->getId() << " treated completely.\n";
          patientsTreated++;
          delete finished;
        } else {
          occupiedRooms++;
        }
      }
    }

    for (auto room : consultRooms) {
      if (room->isFree() && room->hasDoctor() && !waitingRoom->isEmpty()) {
        Patient *nextP = waitingRoom->getNextPatient();
        if (nextP) {
          room->assignPatient(nextP);
          std::cout << "[Minute " << currentMinute << "] Patient "
                    << nextP->getId() << " entered a consultation room.\n";
          occupiedRooms++;
        }
      }
    }

    logger->logStep(currentMinute, occupiedRooms,
                    waitingRoom->getWaitingCount(), patientsTreated);
    currentMinute += stepDuration;
  }

  std::cout << "Simulation Complete. Total patients treated: "
            << patientsTreated << "\n";
}
