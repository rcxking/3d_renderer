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
typedef struct SProjectile {
  Tuple position;
  Tuple velocity;
} Projectile;

/*
 * The world in which a projectile is in has
 * a gravity vector and a wind vector.
 */
typedef struct SWorld {
  Tuple gravity;
  Tuple wind;
} World;

/*
 * Tick function.  When called this function will
 * update a projectile's position and velocity given
 * its current velocity, the world's gravity and
 * wind resistance.
 */
void Tick(World& world, Projectile& projectile) {
  // Update projectile's position
  projectile.position += projectile.velocity;

  // Update projectile's velocity
  projectile.velocity += (world.gravity + world.wind);
}

/*
 * Function to convert (X,Y) coordinates (0,0) being the bottom left to
 * image coordinates (0,0) being the top left.
 */
Tuple World2Image(const Tuple &worldCoordinate, const int imgHeight) {
  // Invert the Y-Coordinate as the only needed transformation
  return Point(worldCoordinate.X(), imgHeight - worldCoordinate.Y(), worldCoordinate.Z());
}

int main(void) {
  // Initialize the projectile's initial position and velocity
  const Tuple START     = Point(0, 1, 0);
  const Tuple VELOCITY  = Normalize(Vector(1, 1.8, 0)) * 11.25;
  Projectile projectile = {START, VELOCITY};

  std::cout << "Initial velocity: (" << projectile.velocity.X() << ", " << projectile.velocity.Y() << ", " << projectile.velocity.Z() << ")" << std::endl;

  std::cout << "Projectile initial position is at (" << projectile.position.X() << ", " << projectile.position.Y() << ", " << projectile.position.Z() << ")" << std::endl;

  // Create the world's gravity (-0.1 units/tick) and wind (-0.01 unit/tick)
  const Tuple GRAVITY = Vector(0, -0.1, 0);
  const Tuple WIND    = Vector(-0.01, 0, 0);
  World world         = {GRAVITY, WIND};

  // Canvas to draw on
  Canvas canvas(900, 550);

  // Run the Tick() function until the projectile has hit the ground
  while(projectile.position.Y() >= 0.0) {
    Tick(world, projectile);
    std::cout << "Projectile is now at (" << projectile.position.X() << ", " << projectile.position.Y() << ", " << projectile.position.Z() << ")" << std::endl;

    // Convert the world coordinate to image coordinate and plot it
    Tuple imgCoordinate = World2Image(projectile.position, canvas.GetHeight());
    canvas.WritePixel(imgCoordinate.X(), imgCoordinate.Y(), Color(1, 0, 0));
  }

  // Save the trajectory to file
  canvas.WriteToPPM("trajectory.ppm");

  return 0;
}
