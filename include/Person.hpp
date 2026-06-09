#pragma once

#include <string>

class Person {
protected:
  std::string id;
  std::string firstName;
  std::string lastName;

public:
  Person(std::string id, std::string firstName, std::string lastName);

  virtual ~Person() = default;

  std::string getFullName() const;

  std::string getId() const;
};
