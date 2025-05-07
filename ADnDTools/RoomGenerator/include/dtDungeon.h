#pragma once

#include "dtPrerequisites.h"
#include "dtRoom.h"

class Dungeon
{
public:
  Dungeon() = default;

  ~Dungeon() = default;

  void
  tableI();

  void
  tableII();

  void
  tableIII();

  void
  tableIV();

  void
  tableV();

  void
  printRoom() const;

public:

  std::vector<Room> m_rooms;

  Room* m_activeRoom;

};

