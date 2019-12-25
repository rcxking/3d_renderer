#ifndef __TUPLE_TESTS_H_
#define __TUPLE_TESTS_H_

/*
 * tuple_tests.h
 *
 * Unit tests for the Tuple class.
 *
 * Bryant Pong
 * 12/24/19
 */

#include "Tuple.h"

#include <cmath>
#include <limits>

/**
 * @brief  Helper function for floating point comparisons
 * @param num1, num2  Numbers to compare
 * @return  true if numbers are equal; false otherwise
 */
bool FloatCompare(const float num1, const float num2) {
  return std::fabs(num1 - num2) < 
         std::numeric_limits<float>::epsilon();
}

// Tuple Creation tests 
SCENARIO("a tuple can be created", "[Tuple]") {
  GIVEN("a tuple is needed") {
    WHEN("it is created without arguments") {
      Tuple tuple;
      THEN("it is initialized to default values") {
        /*
         * Default tuple is (0.0, 0.0, 0.0, 0.0),
         * representing a vector at (0.0, 0.0, 0.0)
         */
         REQUIRE(FloatCompare(tuple.X(), 0.0) == true);
         REQUIRE(FloatCompare(tuple.Y(), 0.0) == true);
         REQUIRE(FloatCompare(tuple.Z(), 0.0) == true);
         REQUIRE(FloatCompare(tuple.W(), 0.0) == true);
         REQUIRE(tuple.IsPoint()              == false);
         REQUIRE(tuple.IsVector()             == true);
      }
    }

    WHEN("it is created as a point with arguments") {
      Tuple point(4.3, -4.2, 3.1, 1.0);
        THEN("it is initialized with the correct values") {
          REQUIRE(FloatCompare(point.X(), 4.3)  == true);
          REQUIRE(FloatCompare(point.Y(), -4.2) == true);
          REQUIRE(FloatCompare(point.Z(), 3.1)  == true);
          REQUIRE(FloatCompare(point.W(), 1.0)  == true);
          REQUIRE(point.IsPoint()               == true);
          REQUIRE(point.IsVector()              == false);
        }
      }

    WHEN("it is created as a vector with arguments") {
      Tuple vector(4.3, -4.2, 3.1, 0.0);
      THEN("it is initialized with the correct values") {
        REQUIRE(FloatCompare(vector.X(), 4.3)  == true);
        REQUIRE(FloatCompare(vector.Y(), -4.2) == true);
        REQUIRE(FloatCompare(vector.Z(), 3.1)  == true);
        REQUIRE(FloatCompare(vector.W(), 0.0)  == true);
        REQUIRE(vector.IsPoint()               == false);
        REQUIRE(vector.IsVector()              == true);
      }
    }

    WHEN("it is created via the Point() function") {
      const Tuple POINT = Point(4, -4, 3);
      THEN("the point is initialized correctly") {
        const Tuple EXPECTED_TUPLE(4, -4, 3, 1);
        REQUIRE(POINT == EXPECTED_TUPLE);
      }
    }

    WHEN("it is created via the Vector() function") {
      const Tuple VECTOR = Vector(4, -4, 3);
      THEN("the vector is initialized correctly") {
        const Tuple EXPECTED_TUPLE(4, -4, 3, 0);
        REQUIRE(VECTOR == EXPECTED_TUPLE);
      }
    }
  }
 
  // Tuple operation tests
  GIVEN("operations need to be performed on a tuple") {
    WHEN("two tuples are added together") {
      const Tuple TUPLE1(3, -2, 5, 1);
      const Tuple TUPLE2(-2, 3, 1, 0);
      const Tuple RESULT = TUPLE1 + TUPLE2;

      THEN("the sum is computed correctly") {
        const Tuple EXPECTED(1, 1, 6, 1);
        REQUIRE(RESULT == EXPECTED);        
      }
    }

    WHEN("a point is subtracting from another point") {
      const Tuple POINT1 = Point(3, 2, 1);
      const Tuple POINT2 = Point(5, 6, 7); 
      const Tuple RESULT = POINT1 - POINT2;

      THEN("the difference is computed correctly") {
        const Tuple EXPECTED = Vector(-2, -4, -6);
        REQUIRE(RESULT == EXPECTED);
      }
    }

    WHEN("a vector is subtracted from a point") {
      const Tuple POINT = Point(3, 2, 1);
      const Tuple VECTOR = Vector(5, 6, 7);
      const Tuple RESULT = POINT - VECTOR;

      THEN("the difference is computed correctly") {
        const Tuple EXPECTED = Point(-2, -4, -6);
        REQUIRE(RESULT == EXPECTED);
      }
    }

    WHEN("a vector is subtracted from another vector") {
      const Tuple VECTOR1 = Vector(3, 2, 1);
      const Tuple VECTOR2 = Vector(5, 6, 7);
      const Tuple RESULT = VECTOR1 - VECTOR2;

      THEN("the difference is computed correctly") {
        const Tuple EXPECTED = Vector(-2, -4, -6);
        REQUIRE(RESULT == EXPECTED);
      }
    }

    WHEN("a vector is subtracted from the zero vector") {
      const Tuple ZERO_VECTOR = Vector(0, 0, 0);
      const Tuple VECTOR = Vector(1, -2, 3);
      const Tuple RESULT = ZERO_VECTOR - VECTOR;
      
      THEN("the difference is computed correctly") {
        const Tuple EXPECTED = Vector(-1, 2, -3);
        REQUIRE(RESULT == EXPECTED);
      }
    }

    WHEN("a tuple is negated") {
      const Tuple TUPLE(1, -2, 3, -4);
      const Tuple RESULT = -TUPLE;

      THEN("the negation is computed correctly") {
        const Tuple EXPECTED(-1, 2, -3, 4);
        REQUIRE(RESULT == EXPECTED);
      }
    }

    WHEN("a tuple is multiplied by a scalar") {
      const Tuple TUPLE(1, -2, 3, -4);
      const float SCALAR = 3.5;
      const Tuple RESULT = TUPLE * SCALAR;
  
      THEN("the multiplication is computed correctly") {
        const Tuple EXPECTED(3.5, -7, 10.5, -14);
        REQUIRE(RESULT == EXPECTED);
      }    
    }

    WHEN("a tuple is multiplied by a fraction") {
      const Tuple TUPLE(1, -2, 3, -4);
      const float FRACTION = 0.5;
      const Tuple RESULT = TUPLE * FRACTION;

      THEN("the multiplication is computed correctly") {
        const Tuple EXPECTED(0.5, -1, 1.5, -2);
        REQUIRE(RESULT == EXPECTED);
      }
    }

    WHEN("a tuple is divided by a scalar") {
      const Tuple TUPLE(1, -2, 3, -4);
      const float SCALAR = 2.0;
      const Tuple RESULT = TUPLE / SCALAR;

      THEN("the division is computed correctly") {
        const Tuple EXPECTED(0.5, -1.0, 1.5, -2.0);
        REQUIRE(RESULT == EXPECTED);
      }
    }

    // Magnitude tests
    WHEN("the magnitudes of different vectors are calculated") {
      const Tuple VECTOR1 = Vector(1, 0, 0);
      const Tuple VECTOR2 = Vector(0, 1, 0);
      const Tuple VECTOR3 = Vector(0, 0, 1);
      const Tuple VECTOR4 = Vector(1, 2, 3);
      const Tuple VECTOR5 = Vector(-1, -2, -3);

      const float MAG1 = Magnitude(VECTOR1);
      const float MAG2 = Magnitude(VECTOR2);
      const float MAG3 = Magnitude(VECTOR3);
      const float MAG4 = Magnitude(VECTOR4);
      const float MAG5 = Magnitude(VECTOR5);

      THEN("the magnitudes are computed correctly") {
        const float EXP1 = 1;
        const float EXP2 = 1;
        const float EXP3 = 1;
        const float EXP4 = sqrtf(14);
        const float EXP5 = sqrtf(14);

        REQUIRE(FloatCompare(MAG1, EXP1) == true);
        REQUIRE(FloatCompare(MAG2, EXP2) == true);      
        REQUIRE(FloatCompare(MAG3, EXP3) == true);
        REQUIRE(FloatCompare(MAG4, EXP4) == true);
        REQUIRE(FloatCompare(MAG5, EXP5) == true);
      }
    }

    // Normalization tests
    WHEN("vectors are normalized") {
      const Tuple VECTOR1 = Vector(4, 0, 0);
      const Tuple VECTOR2 = Vector(1, 2, 3);

      const Tuple NORM1 = Normalize(VECTOR1);
      const Tuple NORM2 = Normalize(VECTOR2);
      
      THEN("the vectors are normalized correctly") {
        const Tuple EXP1 = Vector(1, 0, 0);
        const Tuple EXP2 = Vector(1 / sqrtf(14), 2 / sqrtf(14), 3 / sqrtf(14));

        REQUIRE(NORM1                               == EXP1);
        REQUIRE(NORM2                               == EXP2);
        REQUIRE(FloatCompare(Magnitude(NORM2), 1.0) == true);
      }
    }

    // Dot Product tests
    WHEN("the dot product of two vectors is computed") {
      const Tuple VECTOR1 = Vector(1, 2, 3);
      const Tuple VECTOR2 = Vector(2, 3, 4);
      
      const float DOT = Dot(VECTOR1, VECTOR2);

      THEN("the dot product is computed correctly") {
        REQUIRE(FloatCompare(DOT, 20.0) == true);
      }
    }

    // Cross Product tests
    WHEN("the cross product of two vectors is computed") {
      const Tuple VECTOR1 = Vector(1, 2, 3);
      const Tuple VECTOR2 = Vector(2, 3, 4);
  
      const Tuple CROSS1 = Cross(VECTOR1, VECTOR2);
      const Tuple CROSS2 = Cross(VECTOR2, VECTOR1);

      THEN("the cross products are computed correctly") {
        const Tuple EXP1 = Vector(-1, 2, -1);
        const Tuple EXP2 = Vector(1, -2, 1); 

        REQUIRE(CROSS1 == EXP1);
        REQUIRE(CROSS2 == EXP2);
      }
    }
  }
}
#endif
