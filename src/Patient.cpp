#include "Patient.hpp"

Patient::Patient(std::string id, std::string firstName, std::string lastName,
                 int healthStatus, long arrivalTime, int requiredTreatmentTime)
    : Person(id, firstName, lastName), healthStatus(healthStatus),
      priority(TriagePriority::GREEN), arrivalTime(arrivalTime),
      requiredTreatmentTime(requiredTreatmentTime) {}

void Patient::setPriority(TriagePriority p) { priority = p; }

TriagePriority Patient::getPriority() const { return priority; }

void Patient::reduceTreatmentTime(int minutes) {
  requiredTreatmentTime -= minutes;
  if (requiredTreatmentTime < 0) {
    requiredTreatmentTime = 0;
  }
}

bool Patient::isTreated() const { return requiredTreatmentTime <= 0; }

int Patient::getHealthStatus() const { return healthStatus; }
