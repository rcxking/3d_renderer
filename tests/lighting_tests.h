#ifndef __LIGHTING_TESTS_H_
#define __LIGHTING_TESTS_H_
/*
 * lighting_tests.h
 *
 * Unit tests for the Lighting() function that honors the Phong Lighting Model.
 *
 * Bryant Pong
 * 12/28/19
 */
#include "Lighting.h"
#include "Material.h"
#include "Tuple.h"

#include <cmath>

SCENARIO("objects are shaded according to the Phong Lighting Model") {
  // We will use the same Material and Position for all tests
  const Material M;
  const Tuple POSITION = Point(0, 0, 0);

  GIVEN("the eye is between the light and the surface") {
    const Tuple EYE    = Vector(0, 0, -1);
    const Tuple NORMAL = Vector(0, 0, -1);
    const PointLight LIGHT(Point(0, 0, -10), Color(1, 1, 1));

    WHEN("the shading is computed") {
      const Color RESULT = Lighting(M, LIGHT, POSITION, EYE, NORMAL);

      THEN("the ambient/diffuse/specular light is at full strength") {
        REQUIRE(RESULT == Color(1.9, 1.9, 1.9));
      }
    }
  }

  GIVEN("the eye is 45 degrees off of the normal") {
    const Tuple EYE    = Vector(0, sqrt(2)/2, -sqrt(2)/2);
    const Tuple NORMAL = Vector(0, 0, -1);
    const PointLight LIGHT(Point(0, 0, -10), Color(1, 1, 1));

    WHEN("the shading is computed") {
      const Color RESULT = Lighting(M, LIGHT, POSITION, EYE, NORMAL);

      THEN("the ambient/diffuse values are at full strength and the specular value is 0") {
        REQUIRE(RESULT == Color(1.0, 1.0, 1.0));
      }
    }
  }

  GIVEN("the light is moved 45 degrees off of the normal") {
    const Tuple EYE = Vector(0, 0, -1);
    const Tuple NORMAL = Vector(0, 0, -1);
    const PointLight LIGHT(Point(0, 10, -10), Color(1, 1, 1));

    WHEN("the shading is computed") {
      const Color RESULT = Lighting(M, LIGHT, POSITION, EYE, NORMAL);

      THEN("the diffuse component is lessened and the specular component is 0") {
        REQUIRE(RESULT == Color(0.7364, 0.7364, 0.7364));
      }
    }
  }

  GIVEN("the light is moved 45 degrees off of the normal and the eye is in the reflection vector path") {
    const Tuple EYE    = Vector(0, -sqrt(2)/2, -sqrt(2)/2);
    const Tuple NORMAL = Vector(0, 0, -1);
    const PointLight LIGHT(Point(0, 10, -10), Color(1, 1, 1));
  
    WHEN("the shading is computed") {
      const Color RESULT = Lighting(M, LIGHT, POSITION, EYE, NORMAL);

      THEN("the specular component is at full strength and the ambient/diffuse is correct") {
        REQUIRE(RESULT == Color(1.6364, 1.6364, 1.6364));
      }
    }
  }

  GIVEN("the light is behind the surface") {
    const Tuple EYE = Vector(0, 0, -1);
    const Tuple NORMAL = Vector(0, 0, -1);
    const PointLight LIGHT(Point(0, 0, 10), Color(1, 1, 1));
  
    WHEN("the shading is computed") {
      const Color RESULT = Lighting(M, LIGHT, POSITION, EYE, NORMAL);

      THEN("the intensity is the same as the ambient component") {
        REQUIRE(RESULT == Color(0.1, 0.1, 0.1));
      }
    }
  }
}
#endif
