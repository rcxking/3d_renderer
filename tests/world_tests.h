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

SCENARIO("a world is created", "[World]") {
  GIVEN("a default world is created") {
    World world;

    THEN("it is created with no objects and no light source") {
      REQUIRE(world.GetObjects().size() == 0);
      REQUIRE(world.HasLightSource()    == false);
    }
  }
} 
#endif
