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
    /*
     * Default Constructor.  Tuple is initialized to (0.0, 0.0, 0.0) and
     * is a point.
     */
    Tuple() : m_x( 0.0 ),
              m_y( 0.0 ),
              m_z( 0.0 ),
              m_isPoint( true ) {}

    // Constructor with arguments
    Tuple( double x, double y, double z, bool isPoint ) :
        m_x( x ),
        m_y( y ),
        m_z( z ),
        m_isPoint( isPoint ) {}

    // Copy Constructor
    Tuple( const Tuple& rhs ) :
        m_x( rhs.m_x ),
        m_y( rhs.m_y ),
        m_z( rhs.m_z ),
        m_isPoint( rhs.m_isPoint ) {}

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
            m_isPoint = rhs.m_isPoint;
        }
        return *this;
    }

    // Assignment operator==
    bool operator==( const Tuple& rhs ) const
    {
       return IsEqual( m_x, rhs.m_x ) &&
              IsEqual( m_y, rhs.m_y ) &&
              IsEqual( m_z, rhs.m_z ) &&
              ( m_isPoint == rhs.m_isPoint );
    }

    // operator+= 
    Tuple& operator+=( const Tuple& rhs )
    {
        m_x += rhs.m_x;
        m_y += rhs.m_y;
        m_z += rhs.m_z;
        m_isPoint = m_isPoint || rhs.m_isPoint; 
        return *this;
    }

    // operator-=
    Tuple& operator-=( const Tuple& rhs )
    {
        m_x -= rhs.m_x;
        m_y -= rhs.m_y;
        m_z -= rhs.m_z;
        m_isPoint -= rhs.m_isPoint;
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

    // Negation operator:
    const Tuple operator-()
    {
        return Tuple( -1 * m_x, -1 * m_y, -1 * m_z, m_isPoint ); 
    }

    // Accessors/Modifiers:
    inline double GetX() const { return m_x; }
    inline double GetY() const { return m_y; }
    inline double GetZ() const { return m_z; }

    inline bool IsPoint() const { return m_isPoint; }

    void SetX( const double x ) { m_x = x; }
    void SetY( const double y ) { m_y = y; }
    void SetZ( const double z ) { m_z = z; }
    void SetIsPoint( const bool isPoint ) { m_isPoint = isPoint; }

private:

    // Comparing floating point numbers with each other safely:
    bool IsEqual( const double lhs, const double rhs ) const
    {
        const double EPSILON = 0.0001;
        return fabs( lhs - rhs ) < EPSILON;
    }

    // (x, y, z) coordinates:
    double m_x, m_y, m_z;

    // Does this tuple represent a point?
    bool m_isPoint;
};

// Derived classes to aid in the creation of Points/Vectors
class Point : public Tuple
{
public:
    Point() : Tuple( 0.0, 0.0, 0.0, true ) {}
    Point( double x, double y, double z ) : Tuple( x, y, z, true ) {}
};

class Vector : public Tuple
{
public:
    Vector() : Tuple( 0.0, 0.0, 0.0, false ) {}
    Vector( double x, double y, double z ) : Tuple( x, y, z, false ) {}
};
#endif
