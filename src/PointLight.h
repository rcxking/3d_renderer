#ifndef __POINT_LIGHT_H_
#define __POINT_LIGHT_H_
/*
 * PointLight.h
 *
 * Class implementation for a point light source.
 *
 * Bryant Pong
 * 12/25/19
 */
#include "Color.h"
#include "Tuple.h"

class PointLight {
public:
  /**
   * @brief Constructor
   */
  PointLight(const Tuple &pos, const Color &inten) :
    position_(pos), intensity_(inten) {
  }

  /**
   * @brief Destructor
   */
  ~PointLight() {
  }

  /**
   * @brief Copy Constructor
   */
  PointLight(const PointLight &rhs) :
    position_(rhs.position_), intensity_(rhs.intensity_) {
  }

  /**
   * @brief Assignment operator=
   */
  PointLight &operator=(const PointLight &rhs) {
    // Check for self-assignment:
    if (this != &rhs) {
      position_  = rhs.position_;
      intensity_ = rhs.intensity_;
    }
    return *this;
  }

  // Accessor functions
  Tuple Position() const { return position_; }
  Color Intensity() const { return intensity_; }
private:
  // A point light source has a position and an intensity/color:
  Tuple position_;
  Color intensity_;
};
#endif
