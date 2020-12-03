#ifndef __WORLD_TESTS_H_
#define __WORLD_TESTS_H_
/*
 * world_tests.h
 *
 * Unit tests for a World object that keeps track of objects and light sources
 * within a scene.
 *
 * Bryant Pong
 * 12/29/19
 */
#include "World.h"
#include "RaySphere.h"
#include "Material.h"
#include "Color.h"
#include "PointLight.h"
#include "Tuple.h"

SCENARIO("a world is created", "[World]") {
  GIVEN("a default world is created") {
    World world;

    THEN("it is created with no objects and no light source") {
      REQUIRE(world.GetObjects().size() == 0);
      REQUIRE(world.HasLightSource()    == false);
    }
  }

  GIVEN("a world is created via the DefaultWorld() function") {
    const World DEFAULT = DefaultWorld();

    THEN("the world is instantiated correctly") {
      // Expecting the world to have 2 spheres and a light source
      Sphere expSphere1, expSphere2;  
      const PointLight EXPECTED_LIGHT(Point(-10, 10, -10), Color(1, 1, 1));

      // Sphere 1 Properties
      Material mat;
      mat.SetColor(Color(0.8, 1.0, 0.6));
      mat.SetDiffuse(0.7);
      mat.SetSpecular(0.2);
      expSphere1.SetMaterial(mat);

      // Sphere 2 Properties
      expSphere2.SetTransform(Scaling(0.5, 0.5, 0.5));

      REQUIRE(*(DEFAULT.GetLightSource())  == EXPECTED_LIGHT);
      REQUIRE(DEFAULT.Contains(expSphere1) == true);
      REQUIRE(DEFAULT.Contains(expSphere2) == true);
    }
  }
} 
#endif
