#pragma once

#include "Patient.hpp"
#include "Room.hpp"
#include <queue>
#include <vector>

struct ComparePatients {
  bool operator()(const Patient *p1, const Patient *p2) const {
    return static_cast<int>(p1->getPriority()) <
           static_cast<int>(p2->getPriority());
  }
};

class WaitingRoom : public Room {
private:
  std::priority_queue<Patient *, std::vector<Patient *>, ComparePatients> pq;

public:
  WaitingRoom(int capacity);

  void addPatient(Patient *p);

  Patient *getNextPatient();

  bool isEmpty() const;

  int getWaitingCount() const;

  void updateWaitingPatients();
};
