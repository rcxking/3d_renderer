/*
 * Tuple.cpp
 *
 * Class implementation of a 3D Tuple object.  Can represent both a point and a
 * vector.
 */
#include "Tuple.h"

#include <cmath>

Tuple Point(const double x, const double y, const double z) {
  return Tuple(x, y, z, 1.0);
}

Tuple Vector(const double x, const double y, const double z) {
  return Tuple(x, y, z, 0.0);
}

double Magnitude(const Tuple& vec) {
  return sqrt(vec.X() * vec.X() +
              vec.Y() * vec.Y() +
              vec.Z() * vec.Z() +
              vec.W() * vec.W());
}

Tuple Normalize(const Tuple& vec) {
  const double mag = Magnitude(vec);
  return Tuple(vec.X() / mag,
               vec.Y() / mag,
               vec.Z() / mag,
               vec.W() / mag);
}

double Dot(const Tuple& vec1, const Tuple& vec2) {
  return vec1.X() * vec2.X() +
         vec1.Y() * vec2.Y() +
         vec1.Z() * vec2.Z() +
         vec1.W() * vec2.W();
}

Tuple Cross(const Tuple &vec1, const Tuple &vec2) {
  return Vector(vec1.Y() * vec2.Z() - vec1.Z() * vec2.Y(),
                vec1.Z() * vec2.X() - vec1.X() * vec2.Z(),
                vec1.X() * vec2.Y() - vec1.Y() * vec2.X());
}
