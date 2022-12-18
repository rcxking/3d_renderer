#ifndef __LIGHTING_H_
#define __LIGHTING_H_
/*
 * Lighting.h
 * 
 * Provides a function that computes the ambient, diffuse, and specular values in accordance
 * to the Phong Lighting Model.
 *
 * Bryant Pong
 * 12/28/19
 */
#include "Tuple.h"
#include "PointLight.h"
#include "Color.h"
#include "Material.h"

#include <cmath>

/**
 * @brief  Computes the Phong Lighting Model constants.
 */
Color Lighting(const Material &mat, const PointLight &pl, const Tuple &pt,
              const Tuple &eye, const Tuple &normal) {
  // Combine surface color with the light's color/intensity
  const Color EFFECTIVE_COLOR = mat.GetColor() * pl.Intensity();

  // Direction from the position to the light source
  const Tuple LIGHT_VECTOR = Normalize(pl.Position() - pt);

  // Compute ambient contribution
  const Color AMBIENT = EFFECTIVE_COLOR * mat.Ambient();

  /*
   * This dot product is the cosine of the angle between the light vector
   * and the normal vector.  If negative, the light is on the other side
   * of the surface.
   */
  const float LIGHT_DOT_NORMAL = Dot(LIGHT_VECTOR, normal);
  
  // Ambient, Diffuse, and Specular values
  Color ambient = AMBIENT;
  Color diffuse, specular;

  // Black value (all zeroes)
  const Color BLACK(0, 0, 0);

  if (LIGHT_DOT_NORMAL < 0) {
    // Light is on the other side of the surface.  No diffuse/specular light.
    diffuse  = BLACK;
    specular = BLACK;
  } else {
    // Compute diffuse contribution
    diffuse = EFFECTIVE_COLOR * mat.Diffuse() * LIGHT_DOT_NORMAL;

    /*
     * This represents the cosine of the angle between the reflection and eye vectors.
     * If negative, the light reflects away from the eye.
     */ 
    const Tuple REFLECT_VECTOR = Reflect(-LIGHT_VECTOR, normal);
    const float REFLECT_DOT_EYE = Dot(REFLECT_VECTOR, eye);
    if (REFLECT_DOT_EYE <= 0.0) {
      // No specular component
      specular = BLACK;
    } else {
      // Compute the specular contribution
      const float FACTOR = pow(REFLECT_DOT_EYE, mat.Shininess());
      specular = pl.Intensity() * mat.Specular() * FACTOR;
    }   
  }

  return ambient + diffuse + specular;
}
#endif
