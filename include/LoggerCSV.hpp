#pragma once

#include <fstream>
#include <string>

class LoggerCSV {
private:
  std::ofstream file;

public:
  LoggerCSV(const std::string &filename);

  ~LoggerCSV();

  void logStep(int minute, int occupiedRooms, int waitingPatients,
               int totalTreated);
};
