#pragma once

#include "Person.hpp"
#include "TriagePriority.hpp"

class Patient : public Person {
protected:
  int healthStatus;
  TriagePriority priority;
  long arrivalTime;
  int requiredTreatmentTime;

public:
  Patient(std::string id, std::string firstName, std::string lastName,
          int healthStatus, long arrivalTime, int requiredTreatmentTime);

  virtual ~Patient() = default;

  void setPriority(TriagePriority p);

  TriagePriority getPriority() const;

  void reduceTreatmentTime(int minutes);

  bool isTreated() const;

  int getHealthStatus() const;

  virtual bool performWaitingStep() = 0;

  virtual std::string getDiagnosis() const = 0;
};
