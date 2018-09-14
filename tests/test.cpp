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
#include "Color.h"
#include "Canvas.h"
#include "Matrix.h"

// Tell catch to provide its own "main" function
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Support STL Libraries
#include <cmath>
#include <cstdio>
#include <cstring>

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

// Canvas tests
SCENARIO( "a canvas is needed", "[Canvas]" )
{
    GIVEN( "a canvas is constructed" )
    {
        Canvas canvas( 10, 20 );
        THEN( "the canvas should be instantiated correctly" )
        {
            REQUIRE( canvas.GetWidth()  == 10 );
            REQUIRE( canvas.GetHeight() == 20 ); 

            // All pixels on the canvas should be black:
            const Color EXPECTED_COLOR;
            for( int x = 0; x < canvas.GetWidth(); ++x )
            {
                for( int y = 0; y < canvas.GetHeight(); ++y )
                {
                    REQUIRE( canvas.PixelAt( x, y ) == EXPECTED_COLOR );
                }
            }
        } 
    }

    GIVEN( "a pixel is written onto the canvas" )
    {
        Canvas canvas( 10, 20 );
        // Make the pixel at ( 2, 3 ) red
        canvas.WritePixel( 2, 3, Color( 1, 0, 0 ) );

        THEN( "the pixel at (2, 3) should be red" )
        {
            REQUIRE( canvas.PixelAt( 2, 3 ) == Color( 1, 0, 0 ) );
        } 
    }

    GIVEN( "an empty PPM image is written" )
    {
        Canvas canvas( 5, 3 );
        canvas.WriteToPPM( "output.ppm" );

        THEN( "the PPM header is correct" )
        {
            // Open the output.ppm file for reading as a binary stream
            FILE *ppm = fopen( "output.ppm", "rb" );
            char readBuffer[ 100 ];
            memset( readBuffer, 0, sizeof( readBuffer ) );
            const char *EXPECTED_HEADER = "P3\n5 3\n255\n";

            if( ppm )
            {
                fread( readBuffer, 1, 11, ppm );
                fclose( ppm );
            }

            REQUIRE( strcmp( readBuffer, EXPECTED_HEADER ) == 0 );
        }
    }
}

// Matrix tests
SCENARIO( "a matrix is needed", "[Matrix]" )
{
    GIVEN( "a 4x4 matrix is created" )
    {
        const double NUM_ELEMENTS = 16;  
        double values[] = {  1, 2, 3, 4,
                             5.5, 6.5, 7.5, 8.5,
                             9, 10, 11, 12,
                             13.5, 14.5, 15.5, 16.5 };
        Matrix matrix( 4, 4, values, NUM_ELEMENTS );

        THEN( "the matrix should be instantiated correctly" )
        {
            REQUIRE( matrix.GetRows() == 4 );
            REQUIRE( matrix.GetCols() == 4 );
            for( int x = 0; x < 4; ++x )
            {
                for( int y = 0; y < 4; ++y )
                {
                    REQUIRE( matrix.GetValue( y, x ) == values[ y * 4 + x ] ); 
                }
            } 
        }
    }

    GIVEN( "a 2x2 matrix is created" )
    {
        const double NUM_ELEMENTS = 4;
        double values[] = { -3, 5, 1, -2 };
        Matrix matrix( 2, 2, values, NUM_ELEMENTS );

        THEN( "the matrix should be instantiated correctly" )
        {
            REQUIRE( matrix.GetRows() == 2 );
            REQUIRE( matrix.GetCols() == 2 );

            for( int y = 0; y < matrix.GetRows(); ++y )
            {
                for( int x = 0; x < matrix.GetCols(); ++x )
                {
                    REQUIRE( matrix.GetValue( y, x ) == values[ y * 2 + x ] );
                }
            } 
        }
    }

    GIVEN( "two matrices are multipled together" )
    {
        const double NUM_ELEMENTS = 16;
        double values1[] = { 1, 2, 3, 4,
                             2, 3, 4, 5,
                             3, 4, 5, 6,
                             4, 5, 6, 7 };
        double values2[] = { 0, 1, 2, 4,
                             1, 2, 4, 8,
                             2, 4, 8, 16,
                             4, 8, 16, 32 };

        double expectedValues[] = { 24, 49, 98, 196,
                                    31, 64, 128, 256,
                                    38, 79, 158, 316,
                                    45, 94, 188, 376 };
        Matrix a( 4, 4, values1, 16 );
        Matrix b( 4, 4, values2, 16 );
        Matrix expected( 4, 4, expectedValues, 16 );

        THEN( "the product of the matrices is correct" )
        {
            REQUIRE( ( a * b ) == expected );

            Matrix product = a * b;

            REQUIRE( product == expected );
        }
    }

    GIVEN( "a matrix is multiplied by the identity matrix" )
    {
        const double NUM_ELEMENTS = 16;
        double values[] = { 0, 1, 2, 4,
                            1, 2, 4, 8,
                            2, 4, 8, 16,
                            4, 8, 16, 32 };

        Matrix A( 4, 4, values, NUM_ELEMENTS );
        IdentityMatrix Identity( 4 );

        THEN( "the product should be the original matrix" )
        {
            REQUIRE( ( A * Identity ) == A );
        }
    }

    GIVEN( "the matrix transpose is calculated" )
    {
        const double NUM_ELEMENTS = 16;
        double values[] = { 0, 9, 3, 0,
                            9, 8, 0, 8,
                            1, 8, 5, 3,
                            0, 0, 5, 8 };
        double expectedValues[] = { 0, 9, 1, 0,
                                    9, 8, 8, 0,
                                    3, 0, 5, 5,
                                    0, 8, 3, 8 };

        Matrix A( 4, 4, values, NUM_ELEMENTS );
        Matrix expected( 4, 4, expectedValues, NUM_ELEMENTS );

        THEN( "the transpose has the correct values" )
        {
            REQUIRE( A.Transpose() == expected ); 
        } 
    }

    GIVEN( "the transpose of the identity matrix is calculated" )
    {
        IdentityMatrix identity( 4 );

        THEN( "the transpose equals the identity matrix" )
        {
            REQUIRE( identity.Transpose() == identity );
        }
    }

    GIVEN( "the determinant of a 2x2 matrix is calculated" )
    {
        const double NUM_ELEMENTS = 4;
        double values[] = { 1, 5, 
                           -3, 2 };
        Matrix A( 2, 2, values, NUM_ELEMENTS );

        THEN( "the determinant is correct" )
        {
            REQUIRE( A.Determinant() == 17 ); 
        }
    }

    GIVEN( "the determinant of a 3x3 matrix is calculated" )
    {
        const double NUM_ELEMENTS = 9;
        double values[] = { 1, 2, 6,
                            -5, 8, -4,
                            2, 6, 4 };
        Matrix A( 3, 3, values, NUM_ELEMENTS );

        THEN( "the determinant is correct" )
        {
            REQUIRE( A.Cofactor( 0, 0 ) == 56 );
            REQUIRE( A.Cofactor( 0, 1 ) == 12 );
            REQUIRE( A.Cofactor( 0, 2 ) == -46 );
            REQUIRE( A.Determinant() == -196 );
        }
    }

    GIVEN( "the determinant of a 4x4 matrix is calculated" )
    {
        const double NUM_ELEMENTS = 16;
        double values[] = { -2, -8, 3, 5,
                            -3, 1, 7, 3,
                            1, 2, -9, 6,
                            -6, 7, 7, -9 };
        Matrix A( 4, 4, values, NUM_ELEMENTS );

        THEN( "the determinant is correct" )
        {
            REQUIRE( A.Cofactor( 0, 0 ) == 690   );
            REQUIRE( A.Cofactor( 0, 1 ) == 447   );
            REQUIRE( A.Cofactor( 0, 2 ) == 210   );
            REQUIRE( A.Cofactor( 0, 3 ) == 51    );
            REQUIRE( A.Determinant()    == -4071 );
        }
    }

    GIVEN( "the following matrix is invertible" )
    {
        const double NUM_ELEMENTS = 16;
        double values[] = { 6, 4, 4, 4,
                            5, 5, 7, 6,
                            4, -9, 3, -7,
                            9, 1, 7, -6 };
        Matrix A( 4, 4, values, NUM_ELEMENTS );

        THEN( "it is invertible" )
        {
            REQUIRE( A.Determinant() == -2120 );
            REQUIRE( A.IsInvertible() == true ); 
        }
    }

    GIVEN( "the following matrix is not invertible" )
    {
        const double NUM_ELEMENTS = 16;
        double values[] = { -4, 2, -2, -3,
                             9, 6, 2, 6,
                             0, -5, 1, -5,
                             0, 0, 0, 0 };
        Matrix A( 4, 4, values, NUM_ELEMENTS );

        THEN( "it is not invertible" )
        {
            REQUIRE( A.Determinant() == 0 );
            REQUIRE( A.IsInvertible() == false );
        }
    }

    GIVEN( "the submatrix of a 3x3 matrix is calculated" )
    {
        const double NUM_ELEMENTS = 9;
        double values[] = { 1, 5, 0,
                            -3, 2, 7,
                           0, 6, -3 };
        const double EXPECTED_ELEMENTS = 4;
        double expectedValues[] = { -3, 2,
                                     0, 6 };

        Matrix A( 3, 3, values, NUM_ELEMENTS );
        Matrix Expected( 2, 2, expectedValues, EXPECTED_ELEMENTS );
        
        THEN( "the submatrix is correct" )
        {
            REQUIRE( A.Submatrix( 0, 2 ) == Expected ); 
        }
    }

    GIVEN( "the submatrix of a 4x4 matrix is calculated" )
    {
        const double NUM_ELEMENTS = 16;
        double values[] = { -6, 1, 1, 6,
                            -8, 5, 8, 6,
                            -1, 0, 8, 2,
                            -7, 1, -1, 1 };
        const double NUM_EXPECTED = 9;
        double expectedValues[] = { -6, 1, 6,
                                    -8, 8, 6,
                                    -7, -1, 1 };
        Matrix A( 4, 4, values, NUM_ELEMENTS );
        Matrix Expected( 3, 3, expectedValues, NUM_EXPECTED );

        THEN( "the submatrix is correct" )
        {
            REQUIRE( A.Submatrix( 2, 1 ) == Expected );
        }
    }

    GIVEN( "the minor of a 3x3 matrix is calculated" )
    {
        const double NUM_ELEMENTS = 9;
        double values[] = { 3, 5, 0,
                            2, -1, -7,
                            6, -1, 5 };
        Matrix A( 3, 3, values, NUM_ELEMENTS );

        THEN( "the minor is correct" )
        {
            REQUIRE( A.Minor( 1, 0 ) == 25 );
            REQUIRE( A.Submatrix( 1, 0 ).Determinant() == 25 );   
        }
    }

    GIVEN( "the cofactor of a 3x3 matrix is calculated" )
    {
        const double NUM_ELEMENTS = 9;
        double values[] = { 3, 5, 0,
                            2, -1, -7,
                            6, -1, 5 };
        Matrix A( 3, 3, values, NUM_ELEMENTS );

        THEN( "the cofactors are correct" )
        {
            REQUIRE( A.Minor( 0, 0 ) == -12 );
            REQUIRE( A.Cofactor( 0, 0 ) == -12 );
            REQUIRE( A.Minor( 1, 0 ) == 25 );
            REQUIRE( A.Cofactor( 1, 0 ) == -25 );
        }
    }

    GIVEN( "the inverse of a 4x4 matrix is found" )
    {
        const int NUM_ELEMENTS = 16;
        double values[] = { -5, 2, 6, -8,
                             1, -5, 1, 8,
                             7, 7, -6, -7,
                             1, -3, 7, 4 };
        Matrix A( 4, 4, values, NUM_ELEMENTS );
        Matrix B = A.Inverse();

        double expected[] = { 0.21805, 0.45113, 0.24060, -0.04511,
                             -0.80827, -1.45677, -0.44361, 0.52068,
                             -0.07895, -0.22368, -0.05263, 0.19737,
                             -0.52256, -0.81391, -0.30075, 0.30639 };
        Matrix EXPECTED( 4, 4, expected, NUM_ELEMENTS );

        THEN( "the inverse is correct" )
        {
            REQUIRE( A.Determinant() == 532 );
            REQUIRE( A.Cofactor( 2, 3 ) == -160 );
            REQUIRE( B.GetValue( 3, 2 ) == ( -160.0 / 532 ) );
            REQUIRE( A.Cofactor( 3, 2 ) == 105 );
            REQUIRE( B.GetValue( 2, 3 ) == ( 105.0 / 532 ) );
            REQUIRE( B == EXPECTED );
        }
    }
}
