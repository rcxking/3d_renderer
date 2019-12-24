#ifndef __POINT_TESTS_H_
#define __POINT_TESTS_H_

#include "Tuple.h"

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

#endif
