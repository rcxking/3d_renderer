/*
 * Transformations.h
 *
 * Collection of transformations that generate transformation
 * matrices.
 *
 * Bryant Pong
 * 9/17/18
 */

#ifndef _TRANSFORMATIONS_H_
#define _TRANSFORMATIONS_H_

#include "Matrix.h"

#include <cmath>

/*
 * Translation Matrix
 */
const Matrix Translation( const double x, const double y, const double z )
{
    Matrix temp = IdentityMatrix( 4 );

    // The rightmost column is (from top to bottom): x y z 1
    temp.SetValue( 0, 3, x );
    temp.SetValue( 1, 3, y );
    temp.SetValue( 2, 3, z );

    return temp;
}

/*
 * Scaling
 *
 * Pass in values < 1 to shrink; values > 1 to expand
 */
const Matrix Scaling( const double x, const double y, const double z )
{
    Matrix temp( 4, 4 );

    // The main diagonal holds the scaling values
    temp.SetValue( 0, 0, x );
    temp.SetValue( 1, 1, y );
    temp.SetValue( 2, 2, z );
    temp.SetValue( 3, 3, 1 );

    return temp;
}

/*
 * RotX
 *
 * Constructs a 3-Dimensional rotation matrix
 * around the X-Axis.
 *
 * @param theta double: angle to rotate in radians
 */
const Matrix RotX( const double theta )
{
    double values[] = { 1, 0,             0,            0,
                        0, cos( theta ), -sin( theta ), 0,
                        0, sin( theta ),  cos( theta ), 0,
                        0, 0,             0,            1 };
    
    return Matrix( 4, 4, values, 16 ); 
}

/*
 * RotY
 *
 * Constructs a 3-Dimensional rotation matrix
 * around the Y-Axis.
 *
 * @param theta double: angle to rotate in radians
 */
const Matrix RotY( const double theta )
{
    double values[] = {  cos( theta ), 0, sin( theta ), 0,
                         0,            1, 0,            0,
                        -sin( theta ), 0, cos( theta ), 0,
                         0,            0, 0,            1 };

    return Matrix( 4, 4, values, 16 );
}

/*
 * RotZ
 *
 * Constructs a 3-Dimensional rotation matrix
 * around the Z-Axis.
 *
 * @param theta double: angle to rotate in radians
 */
const Matrix RotZ( const double theta )
{
    double values[] = { cos( theta ), -sin( theta ), 0, 0,
                        sin( theta ),  cos( theta ), 0, 0,
                        0,             0,            1, 0,
                        0,             0,            0, 1 };

    return Matrix( 4, 4, values, 16 );
}

/*
 * Shearing
 *
 * Constructs a Shearing Matrix.
 */
const Matrix Shearing( const double xy,
                       const double xz,
                       const double yx,
                       const double yz,
                       const double zx,
                       const double zy )
{
    double values[] = { 1,  xy, xz, 0,
                        yx, 1,  yz, 0,
                        zx, zy, 1,  0,
                        0,  0,  0,  1 };

    return Matrix( 4, 4, values, 16 );
}

#endif
