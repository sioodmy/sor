#include "ConsultationRoom.hpp"

ConsultationRoom::ConsultationRoom(int capacity, int roomNumber)
    : Room(capacity), roomNumber(roomNumber), assignedDoctor(nullptr),
      currentPatient(nullptr) {}

void ConsultationRoom::assignDoctor(Doctor *d) { assignedDoctor = d; }

bool ConsultationRoom::isFree() const { return currentPatient == nullptr; }

void ConsultationRoom::assignPatient(Patient *p) {
  currentPatient = p;
  if (assignedDoctor) {
    assignedDoctor->setBusy();
  }
}

Patient *ConsultationRoom::processTreatment(int minutes) {
  if (currentPatient) {
    currentPatient->reduceTreatmentTime(minutes);
    if (currentPatient->isTreated()) {
      Patient *treated = currentPatient;
      currentPatient = nullptr;
      if (assignedDoctor) {
        assignedDoctor->setAvailable();
      }
      return treated;
    }
  }
  return nullptr;
}

bool ConsultationRoom::hasDoctor() const { return assignedDoctor != nullptr; }
