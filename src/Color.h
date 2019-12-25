/*
 * Color.h
 *
 * Class implementation of a RGB-Color representation.
 *
 * Bryant Pong
 * 9/10/18
 */

#ifndef _COLOR_H_
#define _COLOR_H_

#include "Tuple.h"

// Color is built on top of a Tuple 
class Color : public Tuple
{
public:
  // Default Constructor (defaults to black)
  Color() : Tuple(0.0, 0.0, 0.0, 0.0) {
  }
 
  Color(const float red, const float green, const float blue) :
    Tuple(red, green, blue, 0.0) {
  }

  // Accessors/Modifiers.  We don't need the m_w parameter.
  inline float Red()   const { return x_; }
  inline float Green() const { return y_; }
  inline float Blue()  const { return z_; }

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
  Color &operator*=(const float scalar) {
    Tuple::operator*=(scalar);
    return *this;
  }

  // Operator * (Scalar multiplication)
  Color operator*(const float scalar) const {
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
