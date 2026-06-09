#pragma once

#include "ConfigParser.hpp"
#include "ConsultationRoom.hpp"
#include "Doctor.hpp"
#include "Employee.hpp"
#include "LoggerCSV.hpp"
#include "Nurse.hpp"
#include "WaitingRoom.hpp"
#include <string>
#include <vector>

class EmergencyDepartment {
private:
  int totalSimulationTime;
  int stepDuration;
  int currentMinute;
  int patientsTreated;
  int spawnChance;
  int idCounter;

  WaitingRoom *waitingRoom;
  std::vector<ConsultationRoom *> consultRooms;
  std::vector<Employee *> staff;
  LoggerCSV *logger;

  void spawnRandomPatient();

public:
  EmergencyDepartment(const ConfigParser &config);

  ~EmergencyDepartment();

  void addStaff(Employee *emp);

  void assignDoctorToRoom(int roomIdx, Doctor *doc);

  void runSimulation();

  void admitPatient(Patient *p);
};
