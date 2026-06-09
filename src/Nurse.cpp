#include "Nurse.hpp"

Nurse::Nurse(std::string id, std::string firstName, std::string lastName,
             std::string employeeId)
    : Employee(id, firstName, lastName, employeeId) {}

bool Nurse::isBusy() const {
  return false;
}

void Nurse::performTriage(Patient *p) {
  if (!p)
    return;

  int health = p->getHealthStatus();
  if (health < 30) {
    p->setPriority(TriagePriority::RED);
  } else if (health < 70) {
    p->setPriority(TriagePriority::YELLOW);
  } else {
    p->setPriority(TriagePriority::GREEN);
  }
}
