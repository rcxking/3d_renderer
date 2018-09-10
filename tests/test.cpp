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
                 * Default tuple is ( 0.0, 0.0, 0.0, 0.0 ),
                 * representing a point at (0.0, 0.0, 0.0)
                 */
                REQUIRE( tuple.GetX()    == 0.0 );
                REQUIRE( tuple.GetY()    == 0.0 );
                REQUIRE( tuple.GetZ()    == 0.0 );
                REQUIRE( tuple.GetW()    == 0.0 );
            }
        }

        WHEN( "it is created as a point with arguments" )
        {
            Tuple point( 4.3, -4.2, 3.1, 1.0 );
            THEN( "it is initialized with the correct values" )
            {
                REQUIRE( point.GetX()    ==  4.3 );
                REQUIRE( point.GetY()    == -4.2 );
                REQUIRE( point.GetZ()    ==  3.1 );
                REQUIRE( point.GetW()    ==  1.0 );
            }
        }

        WHEN( "it is created as a vector with arguments" )
        {
            Tuple vector( 4.3, -4.2, 3.1, 0.0 );
            THEN( "it is initialized with the correct values" )
            {
                REQUIRE( vector.GetX()    ==  4.3 );
                REQUIRE( vector.GetY()    == -4.2 );
                REQUIRE( vector.GetZ()    ==  3.1 );
                REQUIRE( vector.GetW()    ==  0.0 );
            }
        }
    }

    GIVEN( "operations need to be performed on a tuple" )
    {
        WHEN( "two identical tuples are compared" )
        {
            Tuple tuple1( 4.3, -4.2, 3.1, 1.0 );
            Tuple tuple2( 4.3, -4.2, 3.1, 1.0 );
            THEN( "the tuples equal each other" )
            {
                bool isEqual = ( tuple1 == tuple2 );
                REQUIRE( isEqual == true );
            }
        }
        WHEN( "two different tuples are compared" )
        {
            Tuple tuple1;
            Tuple tuple2( 4.3, -4.2, 3.1, 1.0 );
            THEN( "the tuples do not equal each other" )
            {
                bool isEqual = ( tuple1 == tuple2 );
                REQUIRE( isEqual == false );
            }
        }
        WHEN( "a tuple is added to another" )
        {
            Tuple tuple1( 3, -2, 5, 1 );
            Tuple tuple2( -2, 3, 1, 0 );
            tuple1 += tuple2;
            THEN( "the sum of the tuples has the correct values" )
            {
                REQUIRE( tuple1.GetX() == 1   );
                REQUIRE( tuple1.GetY() == 1   );
                REQUIRE( tuple1.GetZ() == 6   );
                REQUIRE( tuple1.GetW() == 1.0 );
            }
        }
        WHEN( "two tuples are added together" )
        {
            Tuple tuple1( 3, -2, 5, 1 );
            Tuple tuple2( -2, 3, 1, 0 );
            Tuple tuple3 = tuple1 + tuple2;
            THEN( "the sum of the tuples has the correct values" )
            {
                REQUIRE( tuple3.GetX() == 1.0 );
                REQUIRE( tuple3.GetY() == 1.0 );
                REQUIRE( tuple3.GetZ() == 6.0 );
                REQUIRE( tuple3.GetW() == 1.0 );
            } 
        }
        WHEN( "a tuple is subtracted from another" )
        {
            Point pt1( 3, 2, 1 );
            Point pt2( 5, 6, 7 );
            pt1 -= pt2;
            const Vector EXPECTED( -2, -4, -6 );
            THEN( "the difference of the tuples has the correct values" )
            {
                REQUIRE( pt1 == EXPECTED );
            }
        }
        WHEN( "the difference between two tuples is found" )
        {
            Point pt1( 3, 2, 1 );
            Point pt2( 5, 6, 7 );
            Tuple difference = pt1 - pt2;
            const Vector EXPECTED( -2, -4, -6 );
            THEN( "the difference of the tuples has the correct values" )
            {
                REQUIRE( difference == EXPECTED );
            }
        }
        WHEN( "a vector is subtracted from a point" )
        {
            Point pt( 3, 2, 1 );
            Vector vec( 5, 6, 7 );
            Tuple difference = pt - vec;
            const Point EXPECTED( -2, -4, -6 );
            THEN( "the difference has the correct values" )
            {
                REQUIRE( difference == EXPECTED );
            }
        }
        WHEN( "two vectors are subtracted" )
        {
            Vector vec1( 3, 2, 1 );
            Vector vec2( 5, 6, 7 );
            Tuple difference = vec1 - vec2;
            const Vector EXPECTED( -2, -4, -6 );
            THEN( "the difference has the correct values" )
            {
                REQUIRE( difference == EXPECTED );
            }
        }
        WHEN( "subtracting a vector from the zero vector" )
        {
            Vector zero;
            Vector vec1( 1, -2, 3 );
            Tuple difference = zero - vec1;
            const Vector EXPECTED( -1, 2, -3 );
            THEN( "the difference has the correct values" )
            {
                REQUIRE( difference == EXPECTED );
            }
        }
        WHEN( "negating a tuple" )
        {
            Tuple tuple( 1, -2, 3, 1 );
            Tuple negated = -tuple;
            const Tuple EXPECTED( -1, 2, -3, -1 );
            THEN( "the negation has the correct values" )
            {
                REQUIRE( negated == EXPECTED );
            }
        }
        WHEN( "multiplying by a scalar" )
        {
            Tuple tuple1( 1, -2, 3, 0 );
            tuple1 *= 3.5;
            const Tuple EXPECTED1( 3.5, -7, 10.5, 0 );

            Tuple tuple2( 1, -2, 3, 1 );
            Tuple product = tuple2 * 0.5;
            const Tuple EXPECTED2( 0.5, -1, 1.5, 0.5 );

            THEN( "the tuples have the appropriate scaling" )
            {
                REQUIRE( tuple1 == EXPECTED1 );
                REQUIRE( product == EXPECTED2 );
            }
        }
        WHEN( "dividing by a scalar" )
        {
            Tuple tuple1( 1, -2, 3, -4 );
            tuple1 /= 2;

            Tuple tuple2( 1, -2, 3, -4 );
            
            THEN( "the tuples have the appropriate values" )
            {
                REQUIRE(         tuple1 == Tuple( 0.5, -1, 1.5, -2 ) );
                REQUIRE( ( tuple2 / 2 ) == Tuple( 0.5, -1, 1.5, -2 ) );
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
                REQUIRE( point.GetW() == 1.0 );
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
                REQUIRE( point.GetW() == 1.0 );
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
                REQUIRE( vector.GetW() == 0.0 );
            }
        }

        WHEN( "it is created with arguments" )
        {
            Vector vector( 4, -4, 3 );
            THEN( "it is initialized with the correct values" )
            {
                REQUIRE( vector.GetX() ==  4.0 );
                REQUIRE( vector.GetY() == -4.0 );
                REQUIRE( vector.GetZ() ==  3.0 );
                REQUIRE( vector.GetW() ==  0.0 );
            }
        }
    }
}
