/*
 * cannon.cpp
 *
 * A fun program to exercise the Vector and Point classes.
 * Simulates a 3-Dimensional object with an initial velocity
 * in a world with gravity and wind.
 *
 * Bryant Pong
 * 9/10/18
 */  

#include "Tuple.h"
#include "Canvas.h"

#include <iostream>

/*
 * A projectile has a position and a current
 * velocity.
 */
typedef struct SProjectile
{
    Point position;
    Vector velocity;
} Projectile;

/*
 * The world in which a projectile is in has
 * a gravity vector and a wind vector.
 */
typedef struct SWorld
{
    Vector gravity;
    Vector wind;
} World;

/*
 * Tick function.  When called this function will
 * update a projectile's position and velocity given
 * its current velocity, the world's gravity and
 * wind resistance.
 */
void Tick( World& world, Projectile& projectile )
{
    // Update projectile's position
    projectile.position += projectile.velocity;

    // Update projectile's velocity
    projectile.velocity += ( world.gravity + world.wind );
}

/*
 * Function to convert (X,Y) coordinates (0,0) being the bottom left to
 * image coordinates (0,0) being the top left.
 */
Point World2Image( const Point& worldCoordinate, const int imgHeight )
{
    // Invert the Y-Coordinate as the only needed transformation
    Point tmp( worldCoordinate );
    tmp.SetY( imgHeight - tmp.GetY() );
    return tmp;
} 

int main( int argc, char *argv[] )
{
    // The canvas to draw on
    Canvas canvas( 900, 550 );

    // Initialize the projectile's initial position and velocity
    Projectile projectile;
    projectile.position = Point( 0, 1, 0 );
    projectile.velocity = ( Vector( 1, 1.8, 0 ).Normalize() ) * 11.25;

    std::cout << "Initial velocity: ( " << projectile.velocity.GetX() << ", " << projectile.velocity.GetY() << ", " << projectile.velocity.GetZ() << " )" << std::endl;

    // Create the world's gravity and wind
    World world;
    world.gravity = Vector( 0, -0.1, 0 );
    world.wind    = Vector( -0.01, 0, 0 );

    std::cout << "Projectile initial position is at (" << projectile.position.GetX() << ", " << projectile.position.GetY() << ", " << projectile.position.GetZ() << ")" << std::endl; 

    // Run the Tick() function until the projectile has hit the ground
    while( projectile.position.GetY() > 0.0 )
    {
        Tick( world, projectile );
        std::cout << "Projectile is now at (" << projectile.position.GetX() << ", " << projectile.position.GetY() << ", " << projectile.position.GetZ() << ")" << std::endl;

        // Convert the world coordinate to image coordinate and plot it
        Point imgCoordinate = World2Image( projectile.position, canvas.GetHeight() );
        canvas.WritePixel( imgCoordinate.GetX(), imgCoordinate.GetY(), Color( 1, 0, 0 ) );  
    }

    // Save the trajectory to file
    canvas.WriteToPPM( "trajectory.ppm" );

    return 0;
}
