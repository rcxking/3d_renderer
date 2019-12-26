#ifndef __LIGHT_TESTS_H_
#define __LIGHT_TESTS_H_
/*
 * light_tests.h
 *
 * Unit tests for a point light source.
 * 
 * Bryant Pong
 * 12/25/19 
 */
#include "PointLight.h"

SCENARIO("a point light is created", "[PointLight]") {
  GIVEN("a color and position") {
    const Color INTENSITY(1, 1, 1);
    const Tuple POSITION = Point(0, 0, 0);
  
    WHEN("a point light is created") {
      const PointLight POINT_LIGHT(POSITION, INTENSITY);

      THEN("it is initialized correctly") {
        REQUIRE(POINT_LIGHT.Position()  == POSITION);
        REQUIRE(POINT_LIGHT.Intensity() == INTENSITY);
      }
    }
  }
}
#endif
