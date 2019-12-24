#ifndef __COLOR_TESTS_H_
#define __COLOR_TESTS_H_

#include "Color.h"

// Color tests
SCENARIO( "a color is created", "[Color]" )
{
    GIVEN( "a color is constructed" )
    {
        Color color( -0.5, 0.4, 1.7 );
        THEN( "it is initialized to the correct values" )
        {
            REQUIRE( color.GetRed()   == -0.5 );
            REQUIRE( color.GetGreen() ==  0.4 );
            REQUIRE( color.GetBlue()  ==  1.7 );
        }
    }

    GIVEN( "two colors are added together" )
    {
        Color color1( 0.9, 0.6, 0.75 );
        Color color2( 0.7, 0.1, 0.25 );
        const Color EXPECTED( 1.6, 0.7, 1.0 );
        THEN( "the sum of the colors is correct" )
        {
            REQUIRE( ( color1 + color2 ) == EXPECTED );
        }
    }

    GIVEN( "a color is subtracted from another" )
    {
        Color color1( 0.9, 0.6, 0.75 );
        Color color2( 0.7, 0.1, 0.25 );
        const Color EXPECTED( 0.2, 0.5, 0.5 );
        THEN( "the difference of the colors is correct" )
        {
            REQUIRE( ( color1 - color2 ) == EXPECTED );
        }
    }

    GIVEN( "a color is multiplied by a scalar" )
    {
        Color color( 0.2, 0.3, 0.4 );
        const Color EXPECTED( 0.4, 0.6, 0.8 );
        THEN( "the color has the expected values" )
        {
            REQUIRE( ( color * 2 ) == EXPECTED );
        }
    }

    GIVEN( "a color is multiplied by another color" )
    {
        Color color1( 1, 0.2, 0.4 );
        Color color2( 0.9, 1, 0.1 );
        const Color EXPECTED( 0.9, 0.2, 0.04 );
        THEN( "the color product has the expected values" )
        {
            REQUIRE( color1.HadamardProduct( color2 ) == EXPECTED );
        }
    }
}


#endif
