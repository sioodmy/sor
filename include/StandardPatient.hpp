#pragma once

#include "Patient.hpp"

class StandardPatient : public Patient {
public:
  StandardPatient(std::string id, std::string firstName, std::string lastName,
                  int healthStatus, long arrivalTime,
                  int requiredTreatmentTime);

  bool performWaitingStep() override;
  std::string getDiagnosis() const override;
};
