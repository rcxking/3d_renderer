/*
 * Tuple.h
 *
 * Class definition of a 3D Tuple object. Can represent both a point and a
 * vector.
 *
 * Bryant Pong
 * 9/7/18
 */ 

#ifndef _TUPLE_H_
#define _TUPLE_H_

#include <cmath>
#include <limits>

class Tuple
{
public:
    // Default Constructor.  Tuple is initialized to (0.0, 0.0, 0.0, 0.0)
    Tuple() : x_(0.0),
              y_(0.0),
              z_(0.0),
              w_(0.0) {
    }

    // Constructor with arguments
    Tuple(const float x, const float y, const float z, const float w) :
      x_(x),
      y_(y),
      z_(z),
      w_(w) {
    }

    // Copy Constructor
    Tuple(const Tuple& rhs) :
      x_(rhs.x_),
      y_(rhs.y_),
      z_(rhs.z_),
      w_(rhs.w_) {
    }

    // Destructor
    ~Tuple() {
    }

    // Assignment operator=
    Tuple& operator=(const Tuple& rhs) {
      // Check for self-referencing:
      if(this != &rhs) {
        x_ = rhs.x_;
        y_ = rhs.y_;
        z_ = rhs.z_;
        w_ = rhs.w_;
      }
      return *this;
    }

    // Comparison operator==
    bool operator==(const Tuple &rhs) const {
      return IsEqual(x_, rhs.x_) &&
             IsEqual(y_, rhs.y_) &&
             IsEqual(z_, rhs.z_) &&
             IsEqual(w_, rhs.w_);
    }

    // Operator +=
    Tuple& operator+=(const Tuple &rhs) {
      x_ += rhs.x_;
      y_ += rhs.y_;
      z_ += rhs.z_;
      w_ += rhs.w_;
    }

    // Operator +
    Tuple operator+(const Tuple &rhs) const {
      return Tuple(*this) += rhs;
    }

    // Operator -=
    Tuple &operator-=(const Tuple &rhs) {
      x_ -= rhs.x_;
      y_ -= rhs.y_;
      z_ -= rhs.z_;
      w_ -= rhs.w_;
    }

    // Operator -
    Tuple operator-(const Tuple &rhs) const {
      return Tuple(*this) -= rhs;
    }

    // Operator - (Unary minus)
    Tuple operator-() const {
      return Tuple(-1.0 * x_, -1.0 * y_, -1.0 * z_, -1.0 * w_);
    }

    // Operator *= (Scalar multiplication)
    Tuple &operator*=(const float scalar) {
      x_ *= scalar;
      y_ *= scalar;
      z_ *= scalar;
      w_ *= scalar;

      return *this;
    }

    // Operator * (Scalar multiplication)
    Tuple operator*(const float scalar) const {
      return Tuple(*this) *= scalar;
    }

    // Operator /= (Scalar division)
    Tuple &operator/=(const float scalar) {
      x_ /= scalar;
      y_ /= scalar;
      z_ /= scalar;
      w_ /= scalar;

      return *this;
    }

    // Operator / (Scalar division)
    Tuple operator/(const float scalar) const {
      return Tuple(*this) /= scalar;
    }

    // Accessors/Modifiers:
    inline float X() const { return x_; }
    inline float Y() const { return y_; }
    inline float Z() const { return z_; }
    inline float W() const { return w_; }

    inline bool IsPoint() const { return IsEqual(w_, 1.0); }
    inline bool IsVector() const { return IsEqual(w_, 0.0); } 

private:        
    // Comparing floating point numbers with each other safely:
    bool IsEqual(const float num1, const float num2) const {
      return std::fabs(num1 - num2) < 
             std::numeric_limits<float>::epsilon();
    }

    // (x, y, z) coordinates:
    float x_, y_, z_;

    /*
     * Set to 1.0 if this Tuple represents a point; 0.0 if this
     * Tuple represents a vector.
     */
    float w_;
};

/**
 * @brief  Constructs a Tuple object that is a point with
 *         the specified arguments.
 * @param x, y, z: (x, y, z) coordinates.
 * @return a Tuple representation of a point.
 */
Tuple Point(const float x, const float y, const float z) {
  return Tuple(x, y, z, 1.0);
}

/**
 * @brief  Constructs a Tuple object that is a vector with
 *         the specified arguments.
 *
 * @param x, y, z: (x, y, z) coordinates.
 * @return a Tuple representation of a vector.
 */
Tuple Vector(const float x, const float y, const float z) {
  return Tuple(x, y, z, 0.0);
}

/**
 * @brief  Computes the magnitude of a vector.
 *
 * @param vec: The vector to compute the magnitude of
 * @return float The magnitude of the input vector.
 */
float Magnitude(const Tuple& vec) {
  return sqrtf(vec.X() * vec.X() +
               vec.Y() * vec.Y() +
               vec.Z() * vec.Z() +
               vec.W() * vec.W());
}

/**
 * @brief  Normalizes the given vector.
 *
 * @param vec: The vector to normalize
 * @return Tuple: The normalized vector.
 */
Tuple Normalize(const Tuple& vec) {
  // Compute vector's magnitude:
  const float MAG = Magnitude(vec);

  return Tuple(vec.X() / MAG,
               vec.Y() / MAG,
               vec.Z() / MAG,
               vec.W() / MAG); 
}

/**
 * @brief  Computes the dot product of two vectors.
 *
 * @param vec1, vec2: The two vectors to compute the dot product of.
 * @return float: Computed dot product.
 */
float Dot(const Tuple &vec1, const Tuple &vec2) {
  return vec1.X() * vec2.X() +
         vec1.Y() * vec2.Y() +
         vec1.Z() * vec2.Z() +
         vec1.W() * vec2.W();
}

/**
 * @brief  Computes the cross product of two vectors.
 *
 * @param vec1, vec2: The two vectors to compute the cross product of.
 * @return Tuple: Cross product.
 */
Tuple Cross(const Tuple &vec1, const Tuple &vec2) {
  return Vector(vec1.Y() * vec2.Z() - vec1.Z() * vec2.Y(),
                vec1.Z() * vec2.X() - vec1.X() * vec2.Z(),
                vec1.X() * vec2.Y() - vec1.Y() * vec2.X());
}
#endif
