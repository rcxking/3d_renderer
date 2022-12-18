/*
 * Tuple.h
 *
 * Class definition of a 3D Tuple object. Can represent both a point and a
 * vector.
 *
 * Bryant Pong
 * 9/7/18
 */

#ifndef __TUPLE_H__
#define __TUPLE_H__

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
    Tuple(const double x, const double y, const double z, const double w) :
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
      return *this;
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
      return *this;
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
    Tuple &operator*=(const double scalar) {
      x_ *= scalar;
      y_ *= scalar;
      z_ *= scalar;
      w_ *= scalar;

      return *this;
    }

    // Operator * (Scalar multiplication)
    Tuple operator*(const double scalar) const {
      return Tuple(*this) *= scalar;
    }

    // Operator /= (Scalar division)
    Tuple &operator/=(const double scalar) {
      x_ /= scalar;
      y_ /= scalar;
      z_ /= scalar;
      w_ /= scalar;

      return *this;
    }

    // Operator / (Scalar division)
    Tuple operator/(const double scalar) const {
      return Tuple(*this) /= scalar;
    }

    // Accessors/Modifiers:
    double X() const { return x_; }
    double Y() const { return y_; }
    double Z() const { return z_; }
    double W() const { return w_; }

    void SetX(const double x) { x_ = x; }
    void SetY(const double y) { y_ = y; }
    void SetZ(const double z) { z_ = z; }
    void SetW(const double w) { w_ = w; }

    bool IsPoint() const { return IsEqual(w_, 1.0); }
    bool IsVector() const { return IsEqual(w_, 0.0); }

protected:
    // Comparing floating point numbers with each other safely:
    bool IsEqual(const double num1, const double num2) const {
      return std::fabs(num1 - num2) <= std::numeric_limits<double>::epsilon();
    }

    // (x, y, z) coordinates:
    double x_, y_, z_;

    /*
     * Set to 1.0 if this Tuple represents a point; 0.0 if this
     * Tuple represents a vector.
     */
    double w_;
};

/**
 * @brief  Constructs a Tuple object that is a point with
 *         the specified arguments.
 * @param x, y, z: (x, y, z) coordinates.
 * @return a Tuple representation of a point.
 */
Tuple Point(const double x, const double y, const double z);

/**
 * @brief  Constructs a Tuple object that is a vector with
 *         the specified arguments.
 *
 * @param x, y, z: (x, y, z) coordinates.
 * @return a Tuple representation of a vector.
 */
Tuple Vector(const double x, const double y, const double z);

/**
 * @brief  Computes the magnitude of a vector.
 *
 * @param vec: The vector to compute the magnitude of
 * @return double The magnitude of the input vector.
 */
double Magnitude(const Tuple& vec);

/**
 * @brief  Normalizes the given vector.
 *
 * @param vec: The vector to normalize
 * @return Tuple: The normalized vector.
 */
Tuple Normalize(const Tuple& vec);

/**
 * @brief  Computes the dot product of two vectors.
 *
 * @param vec1, vec2: The two vectors to compute the dot product of.
 * @return double: Computed dot product.
 */
double Dot(const Tuple &vec1, const Tuple &vec2);

/**
 * @brief  Computes the cross product of two vectors.
 *
 * @param vec1, vec2: The two vectors to compute the cross product of.
 * @return Tuple: Cross product.
 */
Tuple Cross(const Tuple &vec1, const Tuple &vec2);
#endif
