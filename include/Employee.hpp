#pragma once

#include "Person.hpp"

class Employee : public Person {
protected:
  std::string employeeId;

public:
  Employee(std::string id, std::string firstName, std::string lastName,
           std::string employeeId);

  virtual ~Employee() = default;

  virtual bool isBusy() const = 0;

  std::string getEmployeeId() const;
};
