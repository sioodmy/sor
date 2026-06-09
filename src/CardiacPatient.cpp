#include "CardiacPatient.hpp"
#include <cstdlib>

CardiacPatient::CardiacPatient(std::string id, std::string firstName,
                               std::string lastName, int healthStatus,
                               long arrivalTime, int requiredTreatmentTime)
    : Patient(id, firstName, lastName, healthStatus, arrivalTime,
              requiredTreatmentTime) {}

bool CardiacPatient::performWaitingStep() {
  if (priority == TriagePriority::RED) {
    return false;
  }

  if ((std::rand() % 100) < 5) {
    healthStatus = 10;
    priority = TriagePriority::RED;
    return true;
  }
  return false;
}

std::string CardiacPatient::getDiagnosis() const {
  return "Cardiac Abnormalities";
}
