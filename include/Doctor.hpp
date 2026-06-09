#pragma once

#include "Employee.hpp"
#include "Patient.hpp"

class Doctor : public Employee {
private:
  std::string specialty;
  bool busy;

public:
  Doctor(std::string id, std::string firstName, std::string lastName,
         std::string employeeId, std::string specialty);

  bool isBusy() const override;

  void setBusy();

  void setAvailable();
};
