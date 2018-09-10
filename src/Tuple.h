/*
 * Tuple.h
 *
 * Class definition of a 3D Tuple object. Can represent both a point and a
 * vector.
 *
 * Bryant Pong
 * 9/7/18
 */ 

#ifndef _TUPLE_H_
#define _TUPLE_H_

#include <cmath>

class Tuple
{
public:
    // Default Constructor.  Tuple is initialized to (0.0, 0.0, 0.0, 0.0)
    Tuple() : m_x( 0.0 ),
              m_y( 0.0 ),
              m_z( 0.0 ),
              m_w( 0.0 ) {}

    // Constructor with arguments
    Tuple( double x, double y, double z, double w ) :
        m_x( x ),
        m_y( y ),
        m_z( z ),
        m_w( w ) {}

    // Copy Constructor
    Tuple( const Tuple& rhs ) :
        m_x( rhs.m_x ),
        m_y( rhs.m_y ),
        m_z( rhs.m_z ),
        m_w( rhs.m_w ) {}

    // Destructor
    ~Tuple() {}

    // Assignment operator=
    Tuple& operator=( const Tuple& rhs )
    {
        // Check for self-referencing:
        if( this != &rhs )
        {
            m_x = rhs.m_x;
            m_y = rhs.m_y;
            m_z = rhs.m_z;
            m_w = rhs.m_w;
        }
        return *this;
    }

    // Assignment operator==
    bool operator==( const Tuple& rhs ) const
    {
       return IsEqual( m_x, rhs.m_x ) &&
              IsEqual( m_y, rhs.m_y ) &&
              IsEqual( m_z, rhs.m_z ) &&
              IsEqual( m_w, rhs.m_w );
    }

    // operator+= 
    Tuple& operator+=( const Tuple& rhs )
    {
        m_x += rhs.m_x;
        m_y += rhs.m_y;
        m_z += rhs.m_z;
        m_w += rhs.m_w;
        return *this;
    }

    // operator-=
    Tuple& operator-=( const Tuple& rhs )
    {
        m_x -= rhs.m_x;
        m_y -= rhs.m_y;
        m_z -= rhs.m_z;
        m_w -= rhs.m_w;
        return *this;
    }

    // operator *=
    Tuple& operator*=( const double scalar )
    {
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
        m_w *= scalar;
        return *this;
    }

    // operator /=
    Tuple& operator/=( const double scalar )
    {
        m_x /= scalar;
        m_y /= scalar;
        m_z /= scalar;
        m_w /= scalar;
        return *this;
    }

    // operator+
    const Tuple operator+( const Tuple& rhs )
    {
        return Tuple( *this ) += rhs;
    }

    // operator-
    const Tuple operator-( const Tuple& rhs )
    {
        return Tuple( *this ) -= rhs;
    }

    // operator*
    const Tuple operator*( const double scalar )
    {
        return Tuple( *this ) *= scalar;
    }

    // operator/
    const Tuple operator/( const double scalar )
    {
        return Tuple( *this ) /= scalar;
    }

    // Negation operator:
    const Tuple operator-()
    {
        return Tuple( -1 * m_x, -1 * m_y, -1 * m_z, -1 * m_w ); 
    }

    // Accessors/Modifiers:
    inline double GetX() const { return m_x; }
    inline double GetY() const { return m_y; }
    inline double GetZ() const { return m_z; }
    inline double GetW() const { return m_w; }

    inline void SetX( const double x ) { m_x = x; }
    inline void SetY( const double y ) { m_y = y; }
    inline void SetZ( const double z ) { m_z = z; }
    inline void SetW( const double w ) { m_w = w; }
        
protected:

    // Comparing floating point numbers with each other safely:
    bool IsEqual( const double lhs, const double rhs ) const
    {
        const double EPSILON = 0.0001;
        return fabs( lhs - rhs ) < EPSILON;
    }

    // (x, y, z, w) coordinates:
    double m_x, m_y, m_z, m_w;
};

// Derived classes to aid in the creation of Points/Vectors
class Point : public Tuple
{
public:
    Point() : Tuple( 0.0, 0.0, 0.0, 1.0 ) {}
    Point( double x, double y, double z ) : Tuple( x, y, z, 1.0 ) {}
};

class Vector : public Tuple
{
public:
    Vector() : Tuple( 0.0, 0.0, 0.0, 0.0 ) {}
    Vector( double x, double y, double z ) : Tuple( x, y, z, 0.0 ) {}

    // Compute the magnitude of the vector
    inline double GetMagnitude() const
    {
        return sqrt( (m_x*m_x) + (m_y*m_y) + (m_z*m_z) + (m_w*m_w) );
    }

    // Normalize the vector
    Vector Normalize() const
    {
        const double MAGNITUDE = GetMagnitude();
        return Vector( m_x / MAGNITUDE, m_y / MAGNITUDE, m_z / MAGNITUDE );
    }

    // Dot product
    double Dot( const Vector& rhs ) const
    {
        return ( m_x * rhs.m_x ) + ( m_y * rhs.m_y ) + ( m_z * rhs.m_z );
    }

    // Cross product
    Vector Cross( const Vector& rhs ) const
    {
        const double I_TERM = ( m_y * rhs.m_z ) - ( rhs.m_y * m_z );
        const double J_TERM = -1.0 * ( ( m_x * rhs.m_z ) - ( rhs.m_x * m_z ) );
        const double K_TERM = ( m_x * rhs.m_y ) - ( rhs.m_x * m_y );
        return Vector( I_TERM, J_TERM, K_TERM );
    }
};
#endif
