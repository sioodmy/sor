#pragma once

#include "Employee.hpp"
#include "Patient.hpp"

class Nurse : public Employee {
public:
  Nurse(std::string id, std::string firstName, std::string lastName,
        std::string employeeId);

  bool isBusy() const override;

  void performTriage(Patient *p);
};
