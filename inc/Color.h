/*
 * Color.h
 *
 * Class implementation of a RGB-Color representation.
 *
 * Bryant Pong
 * 9/10/18
 */

#ifndef __COLOR_H__
#define __COLOR_H__

#include "Tuple.h"

// Color is built on top of a Tuple
class Color : public Tuple
{
public:
  // Default Constructor (defaults to black)
  Color() : Tuple(0.0, 0.0, 0.0, 0.0) {
  }

  Color(const double red, const double green, const double blue) :
    Tuple(red, green, blue, 0.0) {
  }

  // Accessors/Modifiers.  We don't need the m_w parameter.
  double Red()   const { return x_; }
  double Green() const { return y_; }
  double Blue()  const { return z_; }

  // Comparison operator ==
  bool operator==(const Color &rhs) const {
    return IsEqual(x_, rhs.x_) &&
           IsEqual(y_, rhs.y_) &&
           IsEqual(z_, rhs.z_);
  }

  // Operator +=
  Color &operator+=(const Color &rhs) {
    Tuple::operator+=(rhs);
    return *this;
  }

  // Operator +
  Color operator+(const Color &rhs) const {
    return Color(*this) += rhs;
  }

  // Operator -=
  Color &operator-=(const Color &rhs) {
    Tuple::operator-=(rhs);
    return *this;
  }

  // Operator -
  Color operator-(const Color &rhs) const {
    return Color(*this) -= rhs;
  }

  // Operator *= (Scalar multiplication)
  Color &operator*=(const double scalar) {
    Tuple::operator*=(scalar);
    return *this;
  }

  // Operator * (Scalar multiplication)
  Color operator*(const double scalar) const {
    return Color(*this) *= scalar;
  }

  // Operator *= (Hadamard product)
  Color &operator*=(const Color &rhs) {
    x_ *= rhs.x_;
    y_ *= rhs.y_;
    z_ *= rhs.z_;
    return *this;
  }

  // Operator * (Hadamard product)
  Color operator*(const Color &rhs) const {
    return Color(*this) *= rhs;
  }
};
#endif
