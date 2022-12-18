#ifndef __WORLD_TESTS_H__
#define __WORLD_TESTS_H__

/*
 * world_tests.h
 *
 * Catch unit tests for the World class.
 */

#include "World.h"

// World Creation tests
SCENARIO("a world can be created", "[World]") {
  GIVEN("an empty world is created") {
    THEN("it is constructed without any errors") {
      REQUIRE_NOTHROW(World());
    }
  }

  GIVEN("an empty world is created") {
    World w;
    THEN("its member variables are instantiated correctly") {
      REQUIRE(w.GetNumObjects() == 0);
      REQUIRE(w.GetLightSource() == nullptr);
    }
  }
}

#endif
