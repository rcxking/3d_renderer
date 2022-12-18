#ifndef __TRANSFORMATIONS_H_
#define __TRANSFORMATIONS_H_
/*
 * Transformations.h
 *
 * Collection of transformations that generate transformation
 * matrices.
 *
 * Bryant Pong
 * 9/17/18
 */
#include "Matrix.h"

#include <cmath>

/**
 * @brief  Constructs a Translation matrix
 * @param x, y, z: amount to translate by
 * @return Matrix: Translation matrix
 */
Matrix Translation(const float x, const float y, const float z) {
    Matrix temp = Identity(4);

    // The rightmost column is (from top to bottom): x y z 1
    temp.SetValue(0, 3, x);
    temp.SetValue(1, 3, y);
    temp.SetValue(2, 3, z);

    return temp;
}

/**
 * @brief  Constructs a scaling matrix.
 *         Pass in values < 1 to shrink; > 1 to grow.
 * @param x, y, z: scaling factors
 * @return Matrix: Scaling matrix
 */
Matrix Scaling(const float x, const float y, const float z) {
    Matrix temp = Identity(4);

    // The main diagonal holds the scaling values
    temp.SetValue( 0, 0, x );
    temp.SetValue( 1, 1, y );
    temp.SetValue( 2, 2, z );

    return temp;
}

/**
 * @brief  Computes rotation matrix around the X-Axis
 *         using the left-hand rule.
 * @param theta: Angle in radians to rotate
 * @return Matrix: X-Axis Rotation Matrix
 */
Matrix RotX(const float theta) {
  float values[] = {1, 0,             0,            0,
                    0, cosf(theta),  -sinf(theta),  0,
                    0, sinf(theta),   cosf(theta),  0,
                    0, 0,             0,            1};
  return Matrix(4, 4, values); 
}

/**
 * @brief  Computes rotation matrix around the Y-Axis
 *         using the left-hand rule.
 * @param theta: Angle in radians to rotate
 * @return Matrix: Y-Axis Rotation Matrix
 */
Matrix RotY(const float theta) {
  float values[] = {cosf(theta), 0, sinf(theta), 0,
                    0,           1, 0,           0,
                   -sinf(theta), 0, cosf(theta), 0,
                    0,           0, 0,           1};
  return Matrix(4, 4, values);
}

/**
 * @brief  Computes rotation matrix around the Z-Axis
 *         using the left-hand rule.
 *
 * @param theta: Angle in radians to rotate
 * @return Matrix: Z-Axis Rotation Matrix
 */
Matrix RotZ(const float theta) {
  float values[] = {cosf(theta), -sinf(theta), 0, 0,
                    sinf(theta),  cosf(theta), 0, 0,
                    0,            0,           1, 0,
                    0,            0,           0, 1};
  return Matrix(4, 4, values);
}

/**
 * @brief  Constructs a shearing matrix.
 * @param xy, xz, yx, yz, zx, zy: Shearing parameters.  Moves first axis in
 *                                proportion to the second axis.
 * @return Matrix: Shearing matrix
 */
Matrix Shearing(const float xy, const float xz,
                const float yx, const float yz,
                const float zx, const float zy) {
  float vals[] = {1,  xy, xz, 0,
                  yx, 1,  yz, 0,
                  zx, zy, 1,  0,
                  0,  0,  0,  1};
  return Matrix(4, 4, vals);
}
#endif
