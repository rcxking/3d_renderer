#ifndef __TRANSFORMATION_TESTS_H_
#define __TRANSFORMATION_TESTS_H_

#include "Transformations.h"

// Transformation tests
SCENARIO( "matrix transformations are performed" )
{
    GIVEN( "a point is translated" )
    {
        Point p( -3, 4, 5 );
        Matrix transform = Translation( 5, -3, 2 );

        THEN( "the point is translated correctly" )
        {
            REQUIRE( ( transform * p ) == Point( 2, 1, 7 ) );
        }
    }

    GIVEN( "a point is translated with the inverse of a translation" )
    {
        Point p( -3, 4, 5 );
        Matrix transform = Translation( 5, -3, 2 ).Inverse();
        
        THEN( "the point is translated correctly" )
        {
            REQUIRE( ( transform * p ) == Point( -8, 7, 3 ) );
        }
    }

    GIVEN( "a vector is multiplied by a translation matrix" )
    {
        Vector v( -3, 4, 5 );
        Matrix transform = Translation( 5, -3, 2 );

        THEN( "the vector is unchanged" )
        {
            REQUIRE( ( transform * v ) == v );
        }
    }

    GIVEN( "a point is scaled" )
    {
        Point p( -4, 6, 8 );
        Matrix transform = Scaling( 2, 3, 4 );

        THEN( "the point is scaled appropriately" )
        {
            REQUIRE( ( transform * p ) == Point( -8, 18, 32 ) );
        }
    } 

    GIVEN( "a vector is scaled" )
    {
        Vector v( -4, 6, 8 );
        Matrix transform = Scaling( 2, 3, 4 );

        THEN( "the vector is scaled appropriately" )
        {
            REQUIRE( ( transform * v ) == Vector( -8, 18, 32 ) );
        }
    }

    GIVEN( "a vector is shrunk" )
    {
        Vector v( -4, 6, 8 );
        Matrix transform = Scaling( 2, 3, 4 ).Inverse();

        THEN( "the vector is shrunk appropriately" )
        {
            REQUIRE( ( transform * v ) == Vector( -2, 2, 2 ) );
        }
    }

    GIVEN( "a point is reflected across the x-axis" )
    {
        Point p( 2, 3, 4 );
        Matrix reflect = Scaling( -1, 1, 1 );

        THEN( "the point is reflected appropriately" )
        {
            REQUIRE( ( reflect * p ) == Point( -2, 3, 4 ) );
        }
    }

    GIVEN( "a point is rotated around the x-axis" )
    {
        Point p( 0, 1, 0 );
        Matrix rot45x = RotX( M_PI / 4 );
        Matrix rot90x = RotX( M_PI / 2 );

        THEN( "the point is rotated correctly" )
        {
            REQUIRE( ( rot45x * p ) == Point( 0, sqrt( 2 ) / 2, sqrt( 2 ) / 2 ) );
            REQUIRE( ( rot90x * p ) == Point( 0, 0, 1 ) );  
        }
    }

    GIVEN( "a point is rotated in the opposite direction around the x-axis" )
    {
        Point p( 0, 1, 0 );
        Matrix rot45x = RotX( M_PI / 4 );
        Matrix negRot45x = rot45x.Inverse();

        THEN( "the point is rotated correctly" )
        {
            REQUIRE( ( negRot45x * p ) == Point( 0, sqrt( 2 ) / 2, -sqrt( 2 ) / 2 ) );
        }
    }

    GIVEN( "a point is rotated around the y-axis" )
    {
        Point p( 0, 0, 1 );
        Matrix rot45y = RotY( M_PI / 4 );
        Matrix rot90y = RotY( M_PI / 2 );

        THEN( "the point is rotated correctly" )
        {
            REQUIRE( ( rot45y * p ) == Point( sqrt( 2 ) / 2, 0, sqrt( 2 ) / 2 ) );
            REQUIRE( ( rot90y * p ) == Point( 1, 0, 0 ) );
        }
    }

    GIVEN( "a point is rotated around the z-axis" )
    {
        Point p( 0, 1, 0 );
        Matrix rot45z = RotZ( M_PI / 4 );
        Matrix rot90z = RotZ( M_PI / 2 );

        THEN( "the point is rotated correctly" )
        {
            REQUIRE( ( rot45z * p ) == Point( -sqrt( 2 ) / 2, sqrt( 2 ) / 2, 0 ) );
            REQUIRE( ( rot90z * p ) == Point( -1, 0, 0 ) );
        }
    }

    GIVEN( "a shearing matrix moves x in proportion to y" )
    {
        Point p( 2, 3, 4 );
        Matrix shear = Shearing( 1, 0, 0, 0, 0, 0 );

        THEN( "the point is sheared correctly" )
        {
            REQUIRE( ( shear * p ) == Point( 5, 3, 4 ) );
        }
    }

    GIVEN( "a shearing matrix moves x in proportion to z" )
    {
        Point p( 2, 3, 4 );
        Matrix shear = Shearing( 0, 1, 0, 0, 0, 0 );

        THEN( "the point is sheared correctly" )
        {
            REQUIRE( ( shear * p ) == Point( 6, 3, 4 ) );
        }
    }

    GIVEN( "a shearing matrix moves y in proportion to x" )
    {
        Point p( 2, 3, 4 );
        Matrix shear = Shearing( 0, 0, 1, 0, 0, 0 );

        THEN( "the point is sheared correctly" )
        {
            REQUIRE( ( shear * p ) == Point( 2, 5, 4 ) ); 
        }
    }

    GIVEN( "a shearing matrix moves y in proportion to z" )
    {
        Point p( 2, 3, 4 );
        Matrix shear = Shearing( 0, 0, 0, 1, 0, 0 );

        THEN( "the point is sheared correctly" )
        {
            REQUIRE( ( shear * p ) == Point( 2, 7, 4 ) );
        }
    }

    GIVEN( "a shearing matrix moves z in proportion to x" )
    {
        Point p( 2, 3, 4 );
        Matrix shear = Shearing( 0, 0, 0, 0, 1, 0 );

        THEN( "the point is sheared correctly" )
        {
            REQUIRE( ( shear * p ) == Point( 2, 3, 6 ) );
        } 
    }

    GIVEN( "a shearing matrix moves z in proportion to y" )
    {
        Point p( 2, 3, 4 );
        Matrix shear = Shearing( 0, 0, 0, 0, 0, 1 );

        THEN( "the point is sheared correctly" )
        {
            REQUIRE( ( shear * p ) == Point( 2, 3, 7 ) );
        }
    }
}

#endif
