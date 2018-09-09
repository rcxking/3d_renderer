/*
 * test.cpp
 *
 * Unit tests for the 3D renderer classes.  Requires the "catch.hpp" test
 * library.
 *
 * Bryant Pong
 * 9/7/18
 */

// Classes to test
#include "Tuple.h"

// Tell catch to provide its own "main" function
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Tuple Creation tests 
SCENARIO( "a tuple can be created", "[Tuple]" )
{
    GIVEN( "a tuple is needed" )
    {
        WHEN( "it is created without arguments" )
        {
            Tuple tuple;
            THEN( "it is initialized to default values" )
            {
                /*
                 * Default tuple is ( 0.0, 0.0, 0.0, true ),
                 * representing a point at (0.0, 0.0, 0.0)
                 */
                REQUIRE( tuple.GetX()    == 0.0 );
                REQUIRE( tuple.GetY()    == 0.0 );
                REQUIRE( tuple.GetZ()    == 0.0 );
                REQUIRE( tuple.IsPoint() == true );
            }
        }

        WHEN( "it is created as a point with arguments" )
        {
            Tuple point( 4.3, -4.2, 3.1, 1.0 );
            THEN( "it is initialized with the correct values" )
            {
                REQUIRE( point.GetX()    == 4.3 );
                REQUIRE( point.GetY()    == -4.2 );
                REQUIRE( point.GetZ()    == 3.1 );
                REQUIRE( point.IsPoint() == true );
            }
        }

        WHEN( "it is created as a vector with arguments" )
        {
            Tuple vector( 4.3, -4.2, 3.1, 0.0 );
            THEN( "it is initialized with the correct values" )
            {
                REQUIRE( vector.GetX()    == 4.3 );
                REQUIRE( vector.GetY()    == -4.2 );
                REQUIRE( vector.GetZ()    == 3.1 );
                REQUIRE( vector.IsPoint() == false );
            }
        }        
    }
}

// Point creation tests
SCENARIO( "a point is created", "[Point]" )
{
    GIVEN( "a point is needed" )
    {
        WHEN( "it is created without arguments" )
        {
            Point point;
            THEN( "it is initialized to default arguments" )
            {
                REQUIRE( point.GetX() == 0.0 );
                REQUIRE( point.GetY() == 0.0 );
                REQUIRE( point.GetZ() == 0.0 );
                REQUIRE( point.IsPoint() == true );
            }
        }
        
        WHEN( "it is created with arguments" )
        {
            Point point( 4, -4, 3 );
            THEN( "it is initialized with the correct values" )
            {
                REQUIRE( point.GetX() == 4 );
                REQUIRE( point.GetY() == -4 );
                REQUIRE( point.GetZ() == 3 );
                REQUIRE( point.IsPoint() == true );
            }
        }
    } 
}

// Vector creation tests
SCENARIO( "a vector is created", "[Vector]" )
{
    GIVEN( "a vector is needed" )
    {
        WHEN( "it is created without arguments" )
        {
            Vector vector;
            THEN( "it is initialized to default arguments" )
            {
                REQUIRE( vector.GetX() == 0.0 );
                REQUIRE( vector.GetY() == 0.0 );
                REQUIRE( vector.GetZ() == 0.0 );
                REQUIRE( vector.IsPoint() == false );
            }
        }

        WHEN( "it is created with arguments" )
        {
            Vector vector( 4, -4, 3 );
            THEN( "it is initialized with the correct values" )
            {
                REQUIRE( vector.GetX() == 4 );
                REQUIRE( vector.GetY() == -4 );
                REQUIRE( vector.GetZ() == 3 );
                REQUIRE( vector.IsPoint() == false );
            }
        }
    }
}
