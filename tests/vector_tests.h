#ifndef __VECTOR_TESTS_H_
#define __VECTOR_TESTS_H_

#include "Tuple.h"

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

    GIVEN( "operations are performed on a vector" )
    {
        WHEN( "the magnitude is found" )
        {
            Vector v1( 1, 0, 0 );
            Vector v2( 0, 1, 0 );
            Vector v3( 0, 0, 1 );
            Vector v4( 1, 2, 3 );
            Vector v5( -1, -2, -3 );

            THEN( "the magnitudes are correct" )
            {
                REQUIRE( v1.GetMagnitude() == 1 );
                REQUIRE( v2.GetMagnitude() == 1 );
                REQUIRE( v3.GetMagnitude() == 1 );
                REQUIRE( v4.GetMagnitude() == sqrt( 14 ) );
                REQUIRE( v5.GetMagnitude() == sqrt( 14 ) );
            }
        }
        WHEN( "the vector is normalized" )
        {
            Vector v1( 4, 0, 0 );
            Vector v2( 1, 2, 3 );
            
            THEN( "the normalized vector values are correct" )
            {
                REQUIRE( v1.Normalize() == Vector( 1, 0, 0 ) );
                REQUIRE( v2.Normalize() == Vector( 1 / sqrt( 14 ),
                                                   2 / sqrt( 14 ),
                                                   3 / sqrt( 14 ) ) );
                REQUIRE( v1.Normalize().GetMagnitude() == 1 );
            }
        }
        WHEN( "the dot product is calculated" )
        {
            Vector v1( 1, 2, 3 );
            Vector v2( 2, 3, 4 );

            THEN( "the dot product is correct" )
            {
                REQUIRE( v1.Dot( v2 ) == 20 );
            }
        }
        WHEN( "the cross product is calculated" )
        {
            Vector v1( 1, 2, 3 );
            Vector v2( 2, 3, 4 );

            THEN( "the cross product is correct" )
            {
                REQUIRE( v1.Cross( v2 ) == Vector( -1, 2, -1 ) );
                REQUIRE( v2.Cross( v1 ) == Vector( 1, -2, 1 ) );
            }
        }
    }
}

#endif 
