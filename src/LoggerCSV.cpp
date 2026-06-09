#include "LoggerCSV.hpp"

LoggerCSV::LoggerCSV(const std::string &filename) {
  file.open(filename);
  if (file.is_open()) {
    file << "Minute,OccupiedRooms,WaitingPatients,TotalTreated\n";
  }
}

LoggerCSV::~LoggerCSV() {
  if (file.is_open()) {
    file.close();
  }
}

void LoggerCSV::logStep(int minute, int occupiedRooms, int waitingPatients,
                        int totalTreated) {
  if (file.is_open()) {
    file << minute << "," << occupiedRooms << "," << waitingPatients << ","
         << totalTreated << "\n";
  }
}
