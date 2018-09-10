/*
 * Color.h
 *
 * Class implementation of a RGB-Color representation.
 *
 * Bryant Pong
 * 9/10/18
 */

#ifndef _COLOR_H_
#define _COLOR_H_

#include "Tuple.h"

// Color is built on top of a Tuple 
class Color : public Tuple
{
public:
    // Default Constructor (defaults to black)
    Color() : Tuple( 0.0, 0.0, 0.0, 0.0 ) {} 
    Color( double red, double green, double blue ) :
        Tuple( red, green, blue, 0.0 ) {}

    // Accessors/Modifiers.  We don't need the m_w parameter.
    inline double GetRed()   const { return m_x; }
    inline double GetGreen() const { return m_y; }
    inline double GetBlue()  const { return m_z; }

    inline void SetRed( const double red )     { m_x = red;   }
    inline void SetGreen( const double green ) { m_y = green; }
    inline void SetBlue( const double blue )   { m_z = blue;  }

    /*
     * Compute the Hadamard product.  When two colors are multiplied
     * together the result is a color where the red component is
     * the product of the two colors' red components.  The same applies
     * to the green and blue color components.
     */
    Color HadamardProduct( const Color& rhs ) const
    {
        return Color( m_x * rhs.m_x, m_y * rhs.m_y, m_z * rhs.m_z );
    }
};

#endif
