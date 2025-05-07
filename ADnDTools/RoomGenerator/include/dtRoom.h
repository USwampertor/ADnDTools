#pragma once

#include "dtPrerequisites.h"


enum eSHAPE {
  REGULAR,
  IRREGULAR,
};

class Room
{
  Vector2D m_size;
  eSHAPE m_shape;
};

