#ifndef __TRANSFORMATION_TESTS_H_
#define __TRANSFORMATION_TESTS_H_
/*
 * transform_tests.h
 *
 * Unit tests for the transformations library.
 *
 * Bryant Pong
 * 12/24/19
 */

#include "Tuple.h"
#include "Transformations.h"

// Transformation tests
SCENARIO("matrix transformations are performed") {
  // Translation tests
  GIVEN("a point and a translation matrix") {
    const Tuple POINT = Point(-3, 4, 5);
    const Matrix TRANSFORM = Translation(5, -3, 2);

    WHEN("the point is translated") {
      const Tuple RESULT = TRANSFORM * POINT;

      THEN("the translation is applied correctly") {
        REQUIRE(RESULT == Point(2, 1, 7));
      }
    }

    WHEN("the point is multiplied by the inverse of the translation matrix") {
      const Matrix TRANSFORM_INV = Inverse(TRANSFORM);
      const Tuple RESULT = TRANSFORM_INV * POINT;
      
      THEN("the translation is applied correctly") {
        REQUIRE(RESULT == Point(-8, 7, 3));
      }
    }
  }

  GIVEN("a vector and a translation matrix") {
    const Tuple VECTOR = Vector(-3, 4, 5);
    const Matrix TRANSFORM = Translation(5, -3, 2);
  
    WHEN("the vector is multiplied by the translation matrix") {
      const Tuple RESULT = TRANSFORM * VECTOR;

      THEN("the vector is unaffected by the multiplication") {
        REQUIRE(RESULT == VECTOR);
      }
    }
  }

  // Scaling tests
  GIVEN("a point and a scaling matrix") {
    const Tuple POINT = Point(-4, 6, 8);
    const Matrix SCALE = Scaling(2, 3, 4);

    WHEN("the point is scaled") {
      const Tuple RESULT = SCALE * POINT;

      THEN("the scaling is applied correctly") {
        REQUIRE(RESULT == Point(-8, 18, 32));
      }
    }
  }
  
  GIVEN("a vector and a scaling matrix") {
    const Tuple VECTOR = Vector(-4, 6, 8);
    const Matrix SCALE = Scaling(2, 3, 4);

    WHEN("the vector is scaled") {
      const Tuple RESULT = SCALE * VECTOR;

      THEN("the scaling is applied correctly") {
        REQUIRE(RESULT == Vector(-8, 18, 32));
      }
    }

    WHEN("the vector is multiplied by the inverse of the scaling matrix") {
      const Tuple RESULT = Inverse(SCALE) * VECTOR;
    
      THEN("the vector is scaled correctly") {
        REQUIRE(RESULT == Vector(-2, 2, 2));
      }
    }
  }

  GIVEN("a point and a reflection matrix") {
    const Tuple POINT = Point(2, 3, 4);
    const Matrix REFLECT = Scaling(-1, 1, 1);

    WHEN("the reflection is applied to the point") {
      const Tuple RESULT = REFLECT * POINT;

      THEN("the point is reflected across the X-Axis") {
        REQUIRE(RESULT == Point(-2, 3, 4));
      }
    }
  }

  // Rotation tests
  GIVEN("a point and rotation matrices around the X-Axis") {
    const Tuple POINT = Point(0, 1, 0);
    const Matrix HALF_QUARTER = RotX(M_PI/4);
    const Matrix FULL_QUARTER = RotX(M_PI/2);
  
    WHEN("the point is rotated") {
      const Tuple RESULT1 = HALF_QUARTER * POINT;
      const Tuple RESULT2 = FULL_QUARTER * POINT;

      THEN("the point is correctly rotated") {
        REQUIRE(RESULT1 == Point(0, sqrt(2)/2, sqrt(2)/2));
        REQUIRE(RESULT2 == Point(0, 0, 1));
      }
    }
    WHEN("the point is rotated in the opposite direction") {
      const Matrix HALF_QUARTER_INV = Inverse(HALF_QUARTER);
      const Tuple RESULT3 = HALF_QUARTER_INV * POINT;

      THEN("the point is correctly rotated") {
        REQUIRE(RESULT3 == Point(0, sqrt(2)/2, -sqrt(2)/2));
      }
    }
  }

  GIVEN("a point and rotation matrices around the Y-Axis") {
    const Tuple POINT = Point(0, 0, 1);
    const Matrix HALF_QUARTER = RotY(M_PI/4);
    const Matrix FULL_QUARTER = RotY(M_PI/2);

    WHEN("the point is rotated") {
      const Tuple RESULT1 = HALF_QUARTER * POINT;
      const Tuple RESULT2 = FULL_QUARTER * POINT;

      THEN("the point is rotated correctly") {
        REQUIRE(RESULT1 == Point(sqrt(2)/2, 0, sqrt(2)/2));
        REQUIRE(RESULT2 == Point(1, 0, 0));
      }
    }
  }

  GIVEN("a point and rotation matrices around the Z-Axis") {
    const Tuple POINT = Point(0, 1, 0);
    const Matrix HALF_QUARTER = RotZ(M_PI/4);
    const Matrix FULL_QUARTER = RotZ(M_PI/2);

    WHEN("the point is rotated") {
      const Tuple RESULT1 = HALF_QUARTER * POINT;
      const Tuple RESULT2 = FULL_QUARTER * POINT;

      THEN("the point is rotated correctly") {
        REQUIRE(RESULT1 == Point(-sqrt(2)/2, sqrt(2)/2, 0));
        REQUIRE(RESULT2 == Point(-1, 0, 0));
      }
    }
  }

  // Shearing tests
  GIVEN("a point and shearing transformations") {
    const Tuple POINT = Point(2, 3, 4);
    const Matrix SHEAR1 = Shearing(1, 0, 0, 0, 0, 0);
    const Matrix SHEAR2 = Shearing(0, 1, 0, 0, 0, 0);
    const Matrix SHEAR3 = Shearing(0, 0, 1, 0, 0, 0);
    const Matrix SHEAR4 = Shearing(0, 0, 0, 1, 0, 0);
    const Matrix SHEAR5 = Shearing(0, 0, 0, 0, 1, 0);
    const Matrix SHEAR6 = Shearing(0, 0, 0, 0, 0, 1);
    
    WHEN("the point is sheared") {
      const Tuple RES1 = SHEAR1 * POINT;
      const Tuple RES2 = SHEAR2 * POINT;
      const Tuple RES3 = SHEAR3 * POINT;
      const Tuple RES4 = SHEAR4 * POINT;
      const Tuple RES5 = SHEAR5 * POINT;
      const Tuple RES6 = SHEAR6 * POINT;

      THEN("the point is sheared correctly") {
        REQUIRE(RES1 == Point(5, 3, 4));
        REQUIRE(RES2 == Point(6, 3, 4));
        REQUIRE(RES3 == Point(2, 5, 4));
        REQUIRE(RES4 == Point(2, 7, 4));
        REQUIRE(RES5 == Point(2, 3, 6));
        REQUIRE(RES6 == Point(2, 3, 7));
      }
    } 
  }

  // Chained Transformations tests
  GIVEN("a point and different transformation matrices") {
    const Tuple POINT = Point(1, 0, 1);
    const Matrix A = RotX(M_PI/2);
    const Matrix B = Scaling(5, 5, 5);
    const Matrix C = Translation(10, 5, 7);

    WHEN("each transformation is applied sequentially") {
      const Tuple RES1 = A * POINT;
      const Tuple RES2 = B * RES1;
      const Tuple RES3 = C * RES2;

      THEN("each transformation is applied correctly") {
        REQUIRE(RES1 == Point(1, -1, 0));
        REQUIRE(RES2 == Point(5, -5, 0));
        REQUIRE(RES3 == Point(15, 0, 7));
      }
    }

    WHEN("all transformations are applied as one transformation matrix") {
      const Matrix TRANSFORM = C * B * A;
      const Tuple RES4 = TRANSFORM * POINT;

      THEN("the transformations are applied correctly") {
        REQUIRE(RES4 == Point(15, 0, 7));
      }
    }
  }
}
#endif
