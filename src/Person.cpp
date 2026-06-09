#include "Person.hpp"

Person::Person(std::string id, std::string firstName, std::string lastName)
    : id(id), firstName(firstName), lastName(lastName) {}

std::string Person::getFullName() const { return firstName + " " + lastName; }

std::string Person::getId() const { return id; }
