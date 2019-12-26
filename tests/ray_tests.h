#ifndef __RAY_TESTS_H_
#define __RAY_TESTS_H_
/*
 * ray_tests.h
 *
 * Unit tests for Ray/Sphere interactions.
 *
 * Bryant Pong
 * 12/25/19
 */
#include "RaySphere.h"
#include "Tuple.h"

#include <vector>

SCENARIO("a ray is to be used", "[Ray]") {
  // Ray Construction tests
  GIVEN("a point and a vector") {
    const Tuple ORIGIN    = Point(1, 2, 3);
    const Tuple DIRECTION = Vector(4, 5, 6);

    WHEN("a ray is constructed with the specified origin/direction") {
      const Ray RAY(ORIGIN, DIRECTION);

      THEN("the ray is instantiated correctly") {
        REQUIRE(RAY.Origin()    == ORIGIN);
        REQUIRE(RAY.Direction() == DIRECTION);
      }
    }
  }

  // Position() tests
  GIVEN("a ray") {
    const Ray RAY(Point(2, 3, 4), Vector(1, 0, 0));

    WHEN("its position at distance t is computed") {
      const Tuple RES1 = Position(RAY, 0);
      const Tuple RES2 = Position(RAY, 1);
      const Tuple RES3 = Position(RAY, -1);
      const Tuple RES4 = Position(RAY, 2.5);  

      THEN("the positions are computed correctly") {
        REQUIRE(RES1 == Point(2, 3, 4));
        REQUIRE(RES2 == Point(3, 3, 4));
        REQUIRE(RES3 == Point(1, 3, 4));
        REQUIRE(RES4 == Point(4.5, 3, 4));
      }
    }
  }

  // Transform() tests
  GIVEN("a ray and a translation matrix") {
    const Ray RAY(Point(1, 2, 3), Vector(0, 1, 0));
    const Matrix M = Translation(3, 4, 5);

    WHEN("the ray is translated") {
      const Ray RESULT = Transform(RAY, M);

      THEN("the ray is properly transformed") {
        REQUIRE(RESULT.Origin()    == Point(4, 6, 8));
        REQUIRE(RESULT.Direction() == Vector(0, 1, 0));
      } 
    }
  }

  GIVEN("a ray and a scaling matrix") {
    const Ray RAY(Point(1, 2, 3), Vector(0, 1, 0));
    const Matrix M = Scaling(2, 3, 4);

    WHEN("the ray is scaled") {
      const Ray RESULT = Transform(RAY, M);

      THEN("the ray is properly transformed") {
        REQUIRE(RESULT.Origin()    == Point(2, 6, 12));
        REQUIRE(RESULT.Direction() == Vector(0, 3, 0));
      } 
    }
  }
}

SCENARIO("a sphere is to be used", "[Sphere]") {
  // Sphere Construction tests
  GIVEN("a sphere is constructed") {
    const Sphere SPHERE;
    THEN("it should be centered around the origin and have a radius of 1") {
      REQUIRE(SPHERE.Origin()                    == Point(0, 0, 0));
      REQUIRE(FloatCompare(SPHERE.Radius(), 1.0) == true);
      REQUIRE(SPHERE.ID()                        == 0);
      REQUIRE(SPHERE.Transform()                 == Identity(4));
    }
  }

  GIVEN("a sphere and a transform matrix") {
    Sphere sphere;
    const Matrix T = Translation(2, 3, 4);
    WHEN("the sphere sets its transformation matrix") {
      sphere.SetTransform(T);
      
      THEN("the transform is set correctly") {
        REQUIRE(sphere.Transform() == T);
      }
    }
  }

  GIVEN("multiple spheres are constructed") {
    const Sphere SPHERE1, SPHERE2;
    THEN("the spheres' IDs should be unique") {
      REQUIRE(SPHERE1.ID() != SPHERE2.ID());
    }
  } 
}

SCENARIO("intersections between a ray and a sphere are computed", "[Sphere]/[Ray]") {
  // Ray-Sphere intersection tests
  GIVEN("a ray that intersects a sphere in two places") {
    const Ray RAY(Point(0, 0, -5), Vector(0, 0, 1));
    const Sphere SPHERE;

    WHEN("the intersections are computed") {
      const std::vector<Intersection> INTERSECTIONS = Intersect(SPHERE, RAY);
      
      THEN("the intersections are correct") {
        REQUIRE(INTERSECTIONS.size()                    == 2);
        REQUIRE(FloatCompare(INTERSECTIONS[0].T(), 4.0) == true);
        REQUIRE(FloatCompare(INTERSECTIONS[1].T(), 6.0) == true);
      }
    }
  }

  GIVEN("a ray that intersects a sphere at a tangent") {
    const Ray RAY(Point(0, 1, -5), Vector(0, 0, 1));
    const Sphere SPHERE;

    WHEN("the intersections are computed") {
      const std::vector<Intersection> INTERSECTIONS = Intersect(SPHERE, RAY);

      THEN("there are two copies of the same intersection") {
        REQUIRE(INTERSECTIONS.size()                    == 2);
        REQUIRE(FloatCompare(INTERSECTIONS[0].T(), 5.0) == true);
        REQUIRE(FloatCompare(INTERSECTIONS[1].T(), 5.0) == true);
      }
    }
  }

  GIVEN("a ray that does not intersect a sphere") {
    const Ray RAY(Point(0, 2, -5), Vector(0, 0, 1));
    const Sphere SPHERE;

    WHEN("the intersections are computed") {
      const std::vector<Intersection> INTERSECTIONS = Intersect(SPHERE, RAY);

      THEN("no intersections are found") {
        REQUIRE(INTERSECTIONS.size() == 0);
      }
    }
  }

  GIVEN("a ray that originates inside a sphere") {
    const Ray RAY(Point(0, 0, 0), Vector(0, 0, 1));
    const Sphere SPHERE;

    WHEN("the intersections are computed") {
      const std::vector<Intersection> INTERSECTIONS = Intersect(SPHERE, RAY);
      
      THEN("two intersections are found") {
        REQUIRE(INTERSECTIONS.size()                     == 2);
        REQUIRE(FloatCompare(INTERSECTIONS[0].T(), -1.0) == true);
        REQUIRE(FloatCompare(INTERSECTIONS[1].T(),  1.0) == true);
      }
    }
  }

  GIVEN("a ray that is in front of a sphere") {
    const Ray RAY(Point(0, 0, 5), Vector(0, 0, 1));
    const Sphere SPHERE;

    WHEN("the intersections are computed") {
      const std::vector<Intersection> INTERSECTIONS = Intersect(SPHERE, RAY);

      THEN("two intersections are found") {
        REQUIRE(INTERSECTIONS.size()                     == 2);
        REQUIRE(FloatCompare(INTERSECTIONS[0].T(), -6.0) == true);
        REQUIRE(FloatCompare(INTERSECTIONS[1].T(), -4.0) == true);
      }
    }
  }

  GIVEN("a ray and a sphere") {
    const Ray RAY(Point(0, 0, -5), Vector(0, 0, 1));
    const Sphere SPHERE;

    WHEN("the intersections are computed") {
      const std::vector<Intersection> INTERSECTIONS = Intersect(SPHERE, RAY);
      
      THEN("two intersections are found") {
        REQUIRE(INTERSECTIONS.size()      == 2);
        REQUIRE(INTERSECTIONS[0].Object() == SPHERE);
        REQUIRE(INTERSECTIONS[1].Object() == SPHERE);
      }
    }
  }

  GIVEN("a ray and a sphere with a transformation matrix") {
    const Ray RAY(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere sphere;
    sphere.SetTransform(Scaling(2, 2, 2));

    WHEN("the intersections are computed") {
      const std::vector<Intersection> INTERSECTIONS = Intersect(sphere, RAY);
  
      THEN("two intersections are found") {
        REQUIRE(INTERSECTIONS.size()                  == 2);
        REQUIRE(FloatCompare(INTERSECTIONS[0].T(), 3) == true);
        REQUIRE(FloatCompare(INTERSECTIONS[1].T(), 7) == true);
      }
    }

    WHEN("the sphere is translated and intersections are computed") {
      sphere.SetTransform(Translation(5, 0, 0));
      const std::vector<Intersection> INTERSECTIONS = Intersect(sphere, RAY);

      THEN("no intersections are found") {
        REQUIRE(INTERSECTIONS.size() == 0);
      }
    }
  }
}

// Intersection class tests
SCENARIO("an intersection object is to be used", "[Intersection]") {
  // Intersection construction tests
  GIVEN("a distance and a sphere") {
    const float T = 3.5;
    const Sphere SPHERE;

    WHEN("an intersection object is constructed") {
      const Intersection I(T, SPHERE);

      THEN("the intersection is constructed correctly") {
        REQUIRE(FloatCompare(I.T(), T) == true);
        REQUIRE(I.Object()             == SPHERE);
      }
    }
  } 

  // Intersection aggregation tests
  GIVEN("a sphere and two intersections") {
    const Sphere SPHERE;
   
    const Intersection I1(1, SPHERE);
    const Intersection I2(2, SPHERE);

    WHEN("they are aggregated together") {
      const std::vector<Intersection> AGGREGATE = Intersections(2, I1, I2);

      THEN("they are stored correctly") {
        REQUIRE(AGGREGATE.size() == 2);
        REQUIRE(AGGREGATE[0].T() == 1);
        REQUIRE(AGGREGATE[1].T() == 2);
      }
    }   
  }
}

// Hit function tests
SCENARIO("we want to determine which intersection hits a sphere") {
  GIVEN("a sphere and positive t intersections") {
    const Sphere SPHERE;
    const Intersection I1(1, SPHERE);
    const Intersection I2(2, SPHERE);
    const std::vector<Intersection> XS = Intersections(2, I2, I1);
  
    WHEN("the hit is calculated") {
      const Intersection I = Hit(XS);

      THEN("the hit is correct") {
        REQUIRE(I == I1);
      } 
    }
  }

  GIVEN("a sphere and mixed positive/negative intersections") {
    const Sphere SPHERE;
    const Intersection I1(-1, SPHERE);
    const Intersection I2(1, SPHERE);
    const std::vector<Intersection> XS = Intersections(2, I2, I1);
    
    WHEN("the hit is calculated") {
      const Intersection I = Hit(XS);

      THEN("the hit is correct") {
        REQUIRE(I == I2);   
      }
    }
  }

  GIVEN("a sphere and all negative intersections") {
    const Sphere SPHERE;
    const Intersection I1(-2, SPHERE);
    const Intersection I2(-1, SPHERE);
    const std::vector<Intersection> XS = Intersections(2, I2, I1);

    WHEN("the hit is calculated") {
      const Intersection I = Hit(XS);

      THEN("there is no hit found") {
        REQUIRE(FloatCompare(I.T(), FLT_MAX) == true);
      }
    }
  }

  GIVEN("a sphere and several intersections") {
    const Sphere SPHERE;
    const Intersection I1(5, SPHERE);
    const Intersection I2(7, SPHERE);
    const Intersection I3(-3, SPHERE);
    const Intersection I4(2, SPHERE);
    const std::vector<Intersection> XS = Intersections(4, I1, I2, I3, I4);

    WHEN("the hit is calculated") {
      const Intersection I = Hit(XS);

      THEN("the hit is correct") {
        REQUIRE(I == I4);
      }
    }
  }
}
#endif
