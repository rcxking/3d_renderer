#ifndef __MATERIAL_TESTS_H_
#define __MATERIAL_TESTS_H_
/*
 * material_tests.h
 *
 * Unit tests for the Material class.
 *
 * Bryant Pong
 * 12/27/19
 */
#include "Material.h"

SCENARIO("a material object is created", "[Material]") {
  GIVEN("a material is created") {
    Material m;
    THEN("it is initialized to the correct defaults") {
      REQUIRE(m.GetColor()                       == Color(1, 1, 1));
      REQUIRE(FloatCompare(m.Ambient(), 0.1)     == true);
      REQUIRE(FloatCompare(m.Diffuse(), 0.9)     == true);
      REQUIRE(FloatCompare(m.Specular(), 0.9)    == true);
      REQUIRE(FloatCompare(m.Shininess(), 200.0) == true);
    } 
  }
}
#endif
