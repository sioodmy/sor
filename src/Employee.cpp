#include "Employee.hpp"

Employee::Employee(std::string id, std::string firstName, std::string lastName,
                   std::string employeeId)
    : Person(id, firstName, lastName), employeeId(employeeId) {}

std::string Employee::getEmployeeId() const { return employeeId; }
