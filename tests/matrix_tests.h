#ifndef __MATRIX_TESTS_H_
#define __MATRIX_TESTS_H_
/*
 * matrix_tests.h
 *
 * Unit tests for the Matrix class.
 *
 * Bryant Pong
 * 12/24/19
 */

#include "Matrix.h"
#include "Tuple.h"

// Matrix tests
SCENARIO("a matrix is needed", "[Matrix]") {
  // Matrix construction tests 
  GIVEN("a 4x4 matrix is created") {
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;
    float values[] = {1, 2, 3, 4,
                      5.5, 6.5, 7.5, 8.5,
                      9, 10, 11, 12,
                      13.5, 14.5, 15.5, 16.5};
    Matrix matrix(NUM_ROWS, NUM_COLS, values);

    THEN("the matrix should be instantiated correctly") {
      REQUIRE(matrix.GetRows() == NUM_ROWS);
      REQUIRE(matrix.GetCols() == NUM_COLS);
      for(int x = 0; x < NUM_COLS; ++x) {
        for(int y = 0; y < NUM_ROWS; ++y) {
          REQUIRE( matrix.GetValue(y, x) == values[y * NUM_COLS + x]); 
        }
      }
    }
  }

  GIVEN("a 2x2 matrix is created") {
    float values[] = {-3, 5, 1, -2};
    const int NUM_ROWS = 2;     
    const int NUM_COLS = 2;
    Matrix matrix(NUM_ROWS, NUM_COLS, values);

    THEN("the matrix should be instantiated correctly") {
      REQUIRE(matrix.GetRows() == NUM_ROWS);
      REQUIRE(matrix.GetCols() == NUM_COLS);

      for(int y = 0; y < matrix.GetRows(); ++y) {
        for(int x = 0; x < matrix.GetCols(); ++x) {
          REQUIRE(matrix.GetValue(y, x) == values[y * NUM_COLS + x]);
        }
      }
    }
  }

  GIVEN("a 3x3 matrix is created") {
    float values[] = {-3, 5, 0,
                       1, -2, -7,
                       0, 1, 1};
    const int NUM_ROWS = 3;
    const int NUM_COLS = 3;
    Matrix matrix(NUM_ROWS, NUM_COLS, values);

    THEN("the 3x3 matrix should be instantiated correctly") {
      REQUIRE(matrix.GetRows() == NUM_ROWS);
      REQUIRE(matrix.GetCols() == NUM_COLS);

      for(int y = 0; y < matrix.GetRows(); ++y) {
        for(int x = 0; x < matrix.GetCols(); ++x) {
          REQUIRE(matrix.GetValue(y, x) == values[y * NUM_COLS + x]);
        }
      }
    }
  }

  // Matrix comparison tests
  GIVEN("two matrices") {
    float values1[] = {1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       5, 4, 3, 2};
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;

    // MAT1 == MAT2
    const Matrix MAT1(NUM_ROWS, NUM_COLS, values1);
    const Matrix MAT2(MAT1);

    THEN("MAT1 == MAT2") {
      REQUIRE(MAT1 == MAT2);
    }

    // MAT3 != (MAT1 || MAT2)
    float values2[] = {2, 3, 4, 5,
                       6, 7, 8, 9,
                       8, 7, 6, 5,
                       4, 3, 2, 1};
    const Matrix MAT3(NUM_ROWS, NUM_COLS, values2);
    
    THEN("MAT3 != MAT1") {
      REQUIRE(MAT3 != MAT1);
    }
  }

  GIVEN("two matrices are multipled together") {
    float values1[] = {1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       5, 4, 3, 2};
    float values2[] = {-2, 1, 2, 3,
                        3, 2, 1, -1,
                        4, 3, 6, 5,
                        1, 2, 7, 8};
    float expectedValues[] = {20, 22, 50, 48,
                              44, 54, 114, 108,
                              40, 58, 110, 102,
                              16, 26, 46, 42};
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;
    const Matrix A(NUM_ROWS, NUM_COLS, values1);
    const Matrix B(NUM_ROWS, NUM_COLS, values2);
    const Matrix RESULT = A * B;

    THEN("the product of the matrices is correct") {
      const Matrix EXPECTED(NUM_ROWS, NUM_COLS, expectedValues);
      REQUIRE(RESULT == EXPECTED);
    }
  }

  GIVEN("a matrix and a tuple") {
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;
    float values[] = {1, 2, 3, 4,
                      2, 4, 4, 2,
                      8, 6, 4, 1,
                      0, 0, 0, 1};
    const Matrix MAT(NUM_ROWS, NUM_COLS, values);
    const Tuple TUP(1, 2, 3, 1);

    WHEN("the matrix is multipled by the tuple") {
      const Tuple RESULT = MAT * TUP;
      
      THEN("the resulting tuple is computed correctly") {
        const Tuple EXPECTED(18, 24, 33, 1);
        REQUIRE(RESULT == EXPECTED);
      } 
    }
  }

  // Identity Matrix tests
  GIVEN("a matrix") {
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;
    float values[] = {0, 1, 2, 4,
                      1, 2, 4, 8,
                      2, 4, 8, 16,
                      4, 8, 16, 32};
    const Matrix A(NUM_ROWS, NUM_COLS, values);

    WHEN("A is multiplied by the identity matrix") {
      const Matrix IDENTITY = Identity(4);
      const Matrix RESULT = A * IDENTITY;

      THEN("the result is the matrix A") {
        REQUIRE(RESULT == A);
      }
    }
  }

  GIVEN("an identity matrix") {
    const Matrix IDENTITY = Identity(4);
    
    WHEN("it is multiplied by a tuple") {
      const Tuple TUP(1, 2, 3, 4);
      const Tuple RESULT = IDENTITY * TUP;

      THEN("the product is the tuple TUP") {
        REQUIRE(RESULT == TUP);
      } 
    }
  }

  // Transpose tests
  GIVEN("a matrix") {
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;
    float values[] = {0, 9, 3, 0,
                      9, 8, 0, 8,
                      1, 8, 5, 3,
                      0, 0, 5, 8};
    const Matrix A(NUM_ROWS, NUM_COLS, values);

    WHEN("the transpose is calculated") {
      const Matrix RESULT = Transpose(A);

      THEN("the transpose is calculated correctly") {
        float expVals[] = {0, 9, 1, 0,
                           9, 8, 8, 0,
                           3, 0, 5, 5,
                           0, 8, 3, 8};
        const Matrix EXPECTED(NUM_ROWS, NUM_COLS, expVals);
        REQUIRE(RESULT == EXPECTED);
      } 
    }
  }

  GIVEN("a 4x4 identity matrix") {
    const Matrix IDENTITY = Identity(4);

    WHEN("the transpose is calculated") {
      const Matrix RESULT = Transpose(IDENTITY);

      THEN("the traponse is the same as the identity matrix") {
        REQUIRE(RESULT == IDENTITY);
      }
    }
  }

  // Determinant tests
  GIVEN("a 2x2 matrix") {
    const int NUM_ROWS = 2;
    const int NUM_COLS = 2;
    float values[] = {1, 5,
                      -3, 2};
    const Matrix A(NUM_ROWS, NUM_COLS, values);
    
    WHEN("the determinant is calculated") {
      const float RESULT = Determinant(A);

      THEN("the determinant is calculated correctly") {
        REQUIRE(FloatCompare(RESULT, 17) == true);
      }
    }
  }

  GIVEN("a 3x3 matrix") {
    const int NUM_ROWS = 3;     
    const int NUM_COLS = 3;
    float vals[] = {1, 2, 6,
                    -5, 8, -4,
                     2, 6, 4};
    const Matrix A(NUM_ROWS, NUM_COLS, vals);
    
    WHEN("its determinant is found") {
      const float DET = Determinant(A);

      THEN("the determinant is computed correctly") {
        REQUIRE(FloatCompare(Cofactor(A, 0, 0), 56)  == true);
        REQUIRE(FloatCompare(Cofactor(A, 0, 1), 12)  == true);
        REQUIRE(FloatCompare(Cofactor(A, 0, 2), -46) == true);
        REQUIRE(FloatCompare(DET, -196)   == true);
      }
    }
  }

  GIVEN("a 4x4 matrix") {
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;
    float vals[] = {-2, -8, 3, 5,
                    -3, 1, 7, 3,
                    1, 2, -9, 6,
                    -6, 7, 7, -9};
    const Matrix A(NUM_ROWS, NUM_COLS, vals);

    WHEN("its determinant is found") {
      const float DET = Determinant(A);
      
      THEN("the determinant is computed correctly") {
        REQUIRE(FloatCompare(Cofactor(A, 0, 0), 690) == true);
        REQUIRE(FloatCompare(Cofactor(A, 0, 1), 447) == true);
        REQUIRE(FloatCompare(Cofactor(A, 0, 2), 210) == true);
        REQUIRE(FloatCompare(Cofactor(A, 0, 3), 51)  == true);
        REQUIRE(FloatCompare(DET, -4071)             == true);
      } 
    }
  }

  // Submatrix tests
  GIVEN("a 3x3 matrix") {
    const int NUM_ROWS = 3;
    const int NUM_COLS = 3;
    float vals[] = {1, 5, 0,
                    -3, 2, 7,
                    0, 6, 3};
    const Matrix A(NUM_ROWS, NUM_COLS, vals);

    WHEN("its submatrix of row 0 and column 2 is computed") {
      const Matrix RESULT = Submatrix(A, 0, 2);

      THEN("the submatrix is computed correctly") {
        const int EXP_ROWS = NUM_ROWS - 1;
        const int EXP_COLS = NUM_COLS - 1;
        float expVals[] = {-3, 2,
                            0, 6};
        const Matrix EXPECTED(EXP_ROWS, EXP_COLS, expVals);
        REQUIRE(RESULT == EXPECTED);
      }
    } 
  }

  GIVEN("a 4x4 matrix") {
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;
    float vals[] = {-6, 1, 1, 6,
                    -8, 5, 8, 6,
                    -1, 0, 8, 2,
                    -7, 1, -1, 1};
    const Matrix A(NUM_ROWS, NUM_COLS, vals);

    WHEN("its submatrix of row 2 and column 1 is computed") {
      const Matrix RESULT = Submatrix(A, 2, 1);
      
      THEN("the submatrix is computed correctly") {
        const int EXP_ROWS = NUM_ROWS - 1;
        const int EXP_COLS = NUM_COLS - 1;
        float expVals[] = {-6, 1, 6,
                           -8, 8, 6,
                           -7, -1, 1};
        const Matrix EXPECTED(EXP_ROWS, EXP_COLS, expVals);
        REQUIRE(RESULT == EXPECTED);
      } 
    }
  }

  // Minor tests
  GIVEN("a 3x3 matrix") {
    const int NUM_ROWS = 3;
    const int NUM_COLS = 3;
    float vals[] = {3, 5, 0,
                    2, -1, -7,
                    6, -1, 5};
    const Matrix A(NUM_ROWS, NUM_COLS, vals);

    WHEN("the minor at row 1 column 0 is computed") {
      const float RESULT = Minor(A, 1, 0);

      THEN("the minor is computed correctly") {
        const Matrix B = Submatrix(A, 1, 0);
        REQUIRE(FloatCompare(Determinant(B), 25.0) == true);
        REQUIRE(FloatCompare(RESULT, 25.0)         == true);
      }
    }
  }

  // Cofactor tests
  GIVEN("a 3x3 matrix") {
    const int NUM_ROWS = 3;
    const int NUM_COLS = 3;
    float vals[] = {3, 5, 0,
                    2, -1, -7,
                    6, -1, 5};
    const Matrix A(NUM_ROWS, NUM_COLS, vals);

    WHEN("its cofactors are calculated") {
      const float COFACTOR1 = Cofactor(A, 0, 0);
      const float COFACTOR2 = Cofactor(A, 1, 0);

      THEN("the cofactors are computed correctly") {
        REQUIRE(FloatCompare(Minor(A, 0, 0), -12.0) == true);
        REQUIRE(FloatCompare(COFACTOR1, -12.0)      == true);
        REQUIRE(FloatCompare(Minor(A, 1, 0), 25.0)  == true);
        REQUIRE(FloatCompare(COFACTOR2, -25.0)      == true);
      }
    }
  }

  // Invertibility tests
  GIVEN("invertible and noninventible matrices") {
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;

    float vals[] = {6, 4, 4, 4,
                    5, 5, 7, 6,
                    4, -9, 3, -7,
                    9, 1, 7, -6};
    float vals2[] = {-4, 2, -2, -3,
                     9, 6, 2, 6,
                     0, -5, 1, -5,
                     0, 0, 0, 0};

    const Matrix INVERTIBLE(NUM_ROWS, NUM_COLS, vals);
    const Matrix NONINVERTIBLE(NUM_ROWS, NUM_COLS, vals2);

    WHEN("invertibility checks are performed") {
      const bool INVERTIBLE1 = IsInvertible(INVERTIBLE);
      const bool INVERTIBLE2 = IsInvertible(NONINVERTIBLE);

      THEN("the results are correct") {
        REQUIRE(INVERTIBLE1 == true);
        REQUIRE(INVERTIBLE2 == false);
      }
    }
  }

  // Inverse tests
  GIVEN("4x4 matrices") {
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;
    
    float vals[] = {-5, 2, 6, -8,
                    1, -5, 1, 8,
                    7, 7, -6, -7,
                    1, -3, 7, 4};
    float vals2[] = {8, -5, 9, 2,
                     7, 5, 6, 1,
                     -6, 0, 9, 6,
                     -3, 0, -9, -4};
    float vals3[] = {9, 3, 0, 9,
                     -5, -2, -6, -3,
                     -4, 9, 6, 4,
                     -7, 6, 6, 2};

    const Matrix A(NUM_ROWS, NUM_COLS, vals);
    const Matrix B(NUM_ROWS, NUM_COLS, vals2);
    const Matrix C(NUM_ROWS, NUM_COLS, vals3);

    WHEN("their inverses are found") {
      const Matrix RESULT  = Inverse(A);
      const Matrix RESULT2 = Inverse(B);
      const Matrix RESULT3 = Inverse(C);
      THEN("the inverses are computed correctly") {
        REQUIRE(FloatCompare(Determinant(A), 532) == true);
        REQUIRE(FloatCompare(Cofactor(A, 2, 3), -160) == true);
        REQUIRE(FloatCompare(RESULT.GetValue(3, 2), -160.0/532.0) == true);
        REQUIRE(FloatCompare(Cofactor(A, 3, 2), 105) == true);
        REQUIRE(FloatCompare(RESULT.GetValue(2, 3), 105.0/532.0) == true);
        
        float expVals[] = {0.21805, 0.45113, 0.24060, -0.04511,
                           -0.80827, -1.45677, -0.44361, 0.52068,
                           -0.07895, -0.22368, -0.05263, 0.19737,
                           -0.52256, -0.81391, -0.30075, 0.30639};
        const Matrix EXPECTED(NUM_ROWS, NUM_COLS, expVals);
        REQUIRE(RESULT == EXPECTED);

        // B Test
        float expVals2[] = {-0.15385, -0.15385, -0.28205, -0.53846,
                            -0.07692, 0.12308, 0.02564, 0.03077,
                             0.35897, 0.35897, 0.43590, 0.92308,
                            -0.69231, -0.69231, -0.76923, -1.92308};
        const Matrix EXPECTEDB(NUM_ROWS, NUM_COLS, expVals2);
        REQUIRE(RESULT2 == EXPECTEDB);

        // C Test
        float expVals3[] = {-0.04074, -0.07778, 0.14444, -0.22222,
                            -0.07778,  0.03333, 0.36667, -0.33333,
                            -0.02901, -0.14630, -0.10926, 0.12963,
                             0.17778, 0.066667, -0.26667, 0.33333};
        const Matrix EXPECTEDC(NUM_ROWS, NUM_COLS, expVals3);
        REQUIRE(RESULT3 == EXPECTEDC);
      }
    }
  }

  GIVEN("two 4x4 matrices") {
    const int NUM_ROWS = 4;
    const int NUM_COLS = 4;
    float vals[] = {3, -9, 7, 3,
                    3, -8, 2, -9,
                    -4, 4, 4, 1,
                    -6, 5, -1, 1};
    float vals2[] = {8, 2, 2, 2,
                     3, -1, 7, 0,
                     7, 0, 5, 4,
                    6, -2, 0, 5};

    const Matrix A(NUM_ROWS, NUM_COLS, vals);
    const Matrix B(NUM_ROWS, NUM_COLS, vals2);

    WHEN("the matrices are multiplied together and then by B's inverse") {
      const Matrix PRODUCT = A * B;
      const Matrix SECOND_PRODUCT = PRODUCT * Inverse(B);
      
      THEN("the matrix A is retrieved") {
        REQUIRE(SECOND_PRODUCT == A);
      }
    }
  }
}
#endif
