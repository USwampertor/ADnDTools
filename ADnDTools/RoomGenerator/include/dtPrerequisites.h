#pragma once

#include <string> // String is a type of container that stores text dynamically
#include <vector> // Vector is a type of container that works like an array but is dynamic

struct Vector2D
{
  Vector2D() = default;
  ~Vector2D() = default; // Default constructor and destructor
  Vector2D(int x, int y) : x(x), y(y) {} // Constructor to initialize the vector
  const int
  getArea() const
  {
    return x * y; // Function to calculate the area of the vector
  }
  
  int x;
  int y;
};
