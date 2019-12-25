/*
 * test.cpp
 *
 * Unit tests for the 3D renderer classes.  Requires the "catch.hpp" test
 * library.
 *
 * Bryant Pong
 * 9/7/18
 */

// Tell catch to provide its own "main" function
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// The actual tests are located in these headers:
#include "tuple_tests.h"
#include "color_tests.h"
#include "canvas_tests.h"
#if 0
#include "matrix_tests.h"
#include "transform_tests.h"
#endif
