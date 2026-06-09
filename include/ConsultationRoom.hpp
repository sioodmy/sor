#pragma once

#include "Doctor.hpp"
#include "Patient.hpp"
#include "Room.hpp"

class ConsultationRoom : public Room {
private:
  int roomNumber;
  Doctor *assignedDoctor;
  Patient *currentPatient;

public:
  ConsultationRoom(int capacity, int roomNumber);

  void assignDoctor(Doctor *d);

  bool isFree() const;

  void assignPatient(Patient *p);

  Patient *processTreatment(int minutes);

  bool hasDoctor() const;
};
