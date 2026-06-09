#include "StandardPatient.hpp"

StandardPatient::StandardPatient(std::string id, std::string firstName,
                                 std::string lastName, int healthStatus,
                                 long arrivalTime, int requiredTreatmentTime)
    : Patient(id, firstName, lastName, healthStatus, arrivalTime,
              requiredTreatmentTime) {}

bool StandardPatient::performWaitingStep() {
  return false;
}

std::string StandardPatient::getDiagnosis() const { return "Standard Illness"; }
