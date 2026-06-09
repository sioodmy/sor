#include "Doctor.hpp"

Doctor::Doctor(std::string id, std::string firstName, std::string lastName,
               std::string employeeId, std::string specialty)
    : Employee(id, firstName, lastName, employeeId), specialty(specialty),
      busy(false) {}

bool Doctor::isBusy() const { return busy; }

void Doctor::setBusy() { busy = true; }

void Doctor::setAvailable() { busy = false; }
