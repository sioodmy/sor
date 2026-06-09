#pragma once

#include "Patient.hpp"

class CardiacPatient : public Patient {
public:
  CardiacPatient(std::string id, std::string firstName, std::string lastName,
                 int healthStatus, long arrivalTime, int requiredTreatmentTime);

  bool performWaitingStep() override;
  std::string getDiagnosis() const override;
};
