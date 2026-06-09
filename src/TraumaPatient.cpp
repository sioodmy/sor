#include "TraumaPatient.hpp"

TraumaPatient::TraumaPatient(std::string id, std::string firstName,
                             std::string lastName, int healthStatus,
                             long arrivalTime, int requiredTreatmentTime)
    : Patient(id, firstName, lastName, healthStatus, arrivalTime,
              requiredTreatmentTime) {}

bool TraumaPatient::performWaitingStep() {
  if (priority == TriagePriority::RED) {
    healthStatus -= 2;
    return false;
  }

  healthStatus -= 5;

  if (healthStatus < 30) {
    priority = TriagePriority::RED;
    return true;
  }
  return false;
}

std::string TraumaPatient::getDiagnosis() const { return "Physical Trauma"; }
