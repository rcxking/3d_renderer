/*
 * color_tests.h
 *
 * Unit tests for the Color class.
 *
 * Bryant Pong
 * 12/24/19
 */

#ifndef __COLOR_TESTS_H_
#define __COLOR_TESTS_H_

#include "Color.h"

// Color tests
SCENARIO("a color is created", "[Color]") {
  WHEN("a color is created from RGB values") {
    const Color C(-0.5, 0.4, 1.7);

    THEN("it is initialized correctly") {
      REQUIRE(FloatCompare(C.Red(), -0.5)  == true);
      REQUIRE(FloatCompare(C.Green(), 0.4) == true);
      REQUIRE(FloatCompare(C.Blue(), 1.7)  == true);
    }
  }

  // Color operation tests
  WHEN("two colors are added together") {
    const Color COLOR1(0.9, 0.6, 0.75);
    const Color COLOR2(0.7, 0.1, 0.25);
    
    const Color RESULT = COLOR1 + COLOR2;

    THEN("the colors are added correctly") {
      const Color EXPECTED(1.6, 0.7, 1.0);
      REQUIRE(RESULT == EXPECTED);
    }
  }

  WHEN("a color is subtracted from another") {
    const Color COLOR1(0.9, 0.6, 0.75);
    const Color COLOR2(0.7, 0.1, 0.25);

    const Color RESULT = COLOR1 - COLOR2;

    THEN("the colors are subtracted correctly") {
      const Color EXPECTED(0.2, 0.5, 0.5);
      REQUIRE(RESULT == EXPECTED);
    }
  }

  WHEN("a color is multiplied by a scalar") {
    const Color COLOR(0.2, 0.3, 0.4);
    const float SCALAR = 2;
    
    const Color RESULT = COLOR * SCALAR;

    THEN("the scaled color is correct") {
      const Color EXPECTED(0.4, 0.6, 0.8);
      REQUIRE(RESULT == EXPECTED);
    }
  }

  WHEN("a color is multiplied by another color") {
    const Color COLOR1(1, 0.2, 0.4);
    const Color COLOR2(0.9, 1, 0.1);

    const Color RESULT = COLOR1 * COLOR2;

    THEN("the multiplied color is correct") {
      const Color EXPECTED(0.9, 0.2, 0.04);
      REQUIRE(RESULT == EXPECTED);
    }
  }
}
#endif
