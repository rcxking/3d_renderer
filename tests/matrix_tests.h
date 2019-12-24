#ifndef __MATRIX_TESTS_H_
#define __MATRIX_TESTS_H_

#include "Matrix.h"

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

    GIVEN( "the identity matrix is muliplied by a tuple" )
    {
        IdentityMatrix identity( 4 );
        Tuple tuple( 1, 2, 3, 4 );

        THEN( "the product is the tuple" )
        {
            REQUIRE( ( identity * tuple ) == tuple );
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

#endif
