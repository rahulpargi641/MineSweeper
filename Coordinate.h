#pragma once
#include <iostream>
#include <initializer_list>
#include <tuple> // for tie()
#include <assert.h>

struct Coordinate
{
int X, Y;

Coordinate()
{}

Coordinate(int x, int y) : X(x), Y(y)
{}

Coordinate& operator= (const std::initializer_list<int>& values)
{
  assert(values.size() == 2);
  
  auto it = values.begin();
  std::tie(X, Y) = std::make_pair(*it, *(it+1));
  return *this;
}

bool operator== (const Coordinate& other) const
{ return (X == other.X && Y == other.Y); }

};

// std::ostream& operator<< (std::ostream& stream, const Coordinate& other)
// { return stream << other.X << ", " << other.Y; }

