#pragma once
#include "aDnDPrerequisites.h"

namespace ADND
{

  namespace MONEY_UNIT
  {
    BETTER_ENUM(E, uint32, 
                COPPER,
                SILVER,
                GOLD,
                PLATINUM,
                ELECTRUM);
  }

struct Money
{
  const static Map<MONEY_UNIT::E, float> conversionRates;


  uint32 convert(const uint32 value, const MONEY_UNIT::E& from, const MONEY_UNIT::E& to)
  {
    if (from == to) {
      return value;
    }
    if (conversionRates.find(from) == conversionRates.end() || conversionRates.find(to) == conversionRates.end()) {
      throw std::invalid_argument("Invalid money unit");
    }
    // Convert to gold pieces (gp) first for standardization
    double valueInGP = value * conversionRates.at(from);

    // Convert from gp to the target unit
    double convertedAmount = valueInGP / conversionRates.at(to);

    // Round to avoid floating-point precision issues (optional)
    convertedAmount = std::round(convertedAmount * 100) / 100;  // Rounds to 2 decimal places

    return convertedAmount;
  }
};


}