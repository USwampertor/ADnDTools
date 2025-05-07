#pragma once
#include "aDnDPrerequisites.h"

#include "aCRace.h"
#include "aCClass.h"

namespace ADND
{

  namespace CH_ABILITIES
  {
    BETTER_ENUM(E, uint32, 
                STRENGTH, 
                INTELLIGENCE, 
                WISDOM, 
                DEXTERITY, 
                CONSTITUTION, 
                CHARISMA);
  }

class Character : public CRace, public CClass
{
public:


  Character() = default;
  ~Character() = default;


  void
  load();

  void
  save();

  void
  create();

  void
  setName(const String& name) {
    this->name = name;
  }

public:

  String name;

  uint32 gold;
  uint32 silver;
  uint32 copper;
  uint32 platinum;
  uint32 electrum;

  uint32 experience;
  
  uint32 level;

  uint32 age;

  float height;

  float weight;

  uint32 speed;

  uint32 currentHitPoints;

  uint32 armorClass;

  uint32 initiative;

  uint32 proficiencyBonus;

  uint32 maxHitPoints;



  Map<CH_ABILITIES::E, uint32> abilities;

};

}

