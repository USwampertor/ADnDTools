#include "aMoney.h"

namespace ADND {

  Map<MONEY_UNIT::E, float> 
  conversionRates = {
  { MONEY_UNIT::E::PLATINUM,  5.0f },
  { MONEY_UNIT::E::GOLD,      1.0f },
  { MONEY_UNIT::E::ELECTRUM,  0.5f },
  { MONEY_UNIT::E::SILVER,    0.05f },
  { MONEY_UNIT::E::COPPER,    0.005f }
};


}