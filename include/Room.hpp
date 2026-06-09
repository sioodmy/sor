#pragma once

class Room {
protected:
  int capacity;

public:
  Room(int capacity);

  virtual ~Room() = default;

  int getCapacity() const;
};
