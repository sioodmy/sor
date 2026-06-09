#include "WaitingRoom.hpp"
#include <iostream>

WaitingRoom::WaitingRoom(int capacity) : Room(capacity) {}

void WaitingRoom::addPatient(Patient *p) {
  if (p) {
    pq.push(p);
  }
}

Patient *WaitingRoom::getNextPatient() {
  if (pq.empty()) {
    return nullptr;
  }
  Patient *p = pq.top();
  pq.pop();
  return p;
}

bool WaitingRoom::isEmpty() const { return pq.empty(); }

int WaitingRoom::getWaitingCount() const { return pq.size(); }

void WaitingRoom::updateWaitingPatients() {
  if (pq.empty())
    return;

  bool needsResort = false;
  std::vector<Patient *> temp;

  while (!pq.empty()) {
    Patient *p = pq.top();
    pq.pop();

    if (p->performWaitingStep()) {
      std::cout << ">>> CRITICAL: Patient " << p->getId() << " ("
                << p->getDiagnosis() << ") has deteriorated! "
                << "Priority escalated to RED.\n";
      needsResort = true;
    }

    temp.push_back(p);
  }

  for (Patient *p : temp) {
    pq.push(p);
  }
}
