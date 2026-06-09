#pragma once

#include "Patient.hpp"

class TraumaPatient : public Patient {
public:
  TraumaPatient(std::string id, std::string firstName, std::string lastName,
                int healthStatus, long arrivalTime, int requiredTreatmentTime);

  bool performWaitingStep() override;
  std::string getDiagnosis() const override;
};
