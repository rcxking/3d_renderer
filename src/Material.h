#ifndef __MATERIAL_H_
#define __MATERIAL_H_
/*
 * Material.h
 *
 * Class definition for a material object that represents the Phong Lighting Model
 * surface attributes.
 *
 * Bryant Pong
 * 12/28/19
 */
#include "Color.h"

#include <cmath>

class Material {
public:
  /**
   * @brief Default Constructor
   */
  Material() :
    color_(Color(1, 1, 1)),
    ambient_(0.1),
    diffuse_(0.9),
    specular_(0.9),
    shininess_(200.0) {
  }

  /**
   * @brief Destructor
   */
  ~Material() {
  }

  /**
   * @brief Copy Constructor
   */
  Material(const Material &rhs) :
    color_(rhs.color_),
    ambient_(rhs.ambient_),
    diffuse_(rhs.diffuse_),
    specular_(rhs.specular_),
    shininess_(rhs.shininess_) {
  }

  /**
   * @brief Assignment operator=
   */
  Material &operator=(const Material &rhs) {
    // Check for self-assignment
    if (this != &rhs) {
      color_ = rhs.color_;
      ambient_ = rhs.ambient_;
      diffuse_ = rhs.diffuse_;
      specular_ = rhs.specular_;
      shininess_ = rhs.shininess_;
    }
    return *this;
  }

  /**
   * @brief Comparison operator==
   */
  bool operator==(const Material &rhs) const {
    return (color_ == rhs.color_) &&
           IsEqual(ambient_, rhs.ambient_) &&
           IsEqual(diffuse_, rhs.diffuse_) &&
           IsEqual(specular_, rhs.specular_) &&
           IsEqual(shininess_, rhs.shininess_);
  }

  // Accessor functions
  Color GetColor() const { return color_; }
  float Ambient() const { return ambient_; }
  float Diffuse() const { return diffuse_; }
  float Specular() const { return specular_; }
  float Shininess() const { return shininess_; }

  // Modifier functions
  void SetColor(const Color &clr) { color_ = clr; }
  void SetAmbient(const float amb) { ambient_ = amb; }
  void SetDiffuse(const float dif) { diffuse_ = dif; }
  void SetSpecular(const float spec) { specular_ = spec; }
  void SetShininess(const float shi) { shininess_ = shi; }

private:
  /**
   * @brief Compares two floats
   */
  bool IsEqual(const float num1, const float num2) const {
    return std::fabs(num1 - num2) <= 0.0001;
  }

  // Color of material
  Color color_;

  // Ambient lighting
  float ambient_;

  // Diffuse lighting
  float diffuse_;

  // Specular lighting
  float specular_;

  // Shininess
  float shininess_;
};
#endif
