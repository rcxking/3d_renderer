/*
 * shadedsphere.cpp
 *
 * A program that casts rays from an origin point at a unit sphere.
 * Rays that hit the sphere will be marked red; rays that miss the
 * sphere will be marked black.
 *
 * The sphere will be lit using the Phong Lighting Model to create
 * 3D shading.
 *
 * Bryant Pong
 * 12/28/19
 */
#include "Tuple.h"
#include "RaySphere.h"
#include "Canvas.h"
#include "Lighting.h"

int main(void) {
  // Ray's origin:
  const Tuple RAY_ORIGIN = Point(0, 0, -5);

  // Wall location at Z = 10
  const float WALL_Z = 10.0;

  /*
   * The size of the wall.  The unit sphere has a radius of 1/origin at (0,0,0),
   * so the maximum Y-value of the sphere is Y = 1.  We also know that
   * the ray's origin is at Z = -5, and the wall is located at Z = 10.0.
   *
   * The line from ray origin (0, 0, -5) to the top of the sphere (0, 1, 0) is:
   * y = mz + b
   *
   * m = (1 - 0)/(0 - -5) = 1/5
   * b = 1
   * y = 0.2z + 1
   *
   * Using this equation, we know that if WALL_Z = 10, then it needs to be at least
   * y = (0.2 * 10) + 1 = 3*2 units across to capture the whole sphere.  To be safe,
   * we will give it 7 units.
   */
  const float WALL_SIZE = 7.0;
  const float HALF = WALL_SIZE/2.0;

  // Canvas dimensions (in pixels)
  const int CANVAS_PIXELS  = 512;

  Canvas canvas(CANVAS_PIXELS, CANVAS_PIXELS);

  // Determine how much a pixel in the canvas represents in world space
  const float WORLD_TO_CANVAS = WALL_SIZE/CANVAS_PIXELS;

  // Sphere to cast our rays at.
  Sphere SPHERE;

  // Set the sphere material properties
  Material mat;
  mat.SetColor(Color(1, 0.2, 1));
  SPHERE.SetMaterial(mat);

  // Point Light for illumination
  const Tuple LIGHT_POS = Point(-10, 10, -10);
  const Color LIGHT_COLOR(1, 1, 1);
  const PointLight POINT_LIGHT(LIGHT_POS, LIGHT_COLOR);

  // Red Color to mark rays that hit the sphere
  const Color RED(1, 0, 0);

  // Iterate through the canvas and cast rays + check for hits
  for (int y = 0; y < CANVAS_PIXELS; ++y) {
    // Compute World Y-coordinate (y > 0 = +half; y < 0 = -half)
    const float WORLD_Y = HALF - WORLD_TO_CANVAS * y;

    for (int x = 0; x < CANVAS_PIXELS; ++x) {
      // Compute World X-coordinate (x > 0 = +half; x < 0 = -half)
      const float WORLD_X = -HALF + WORLD_TO_CANVAS * x;

      // Compute the point on the wall the ray will target
      const Tuple WALL_PT = Point(WORLD_X, WORLD_Y, WALL_Z);

      // Construct the ray from the origin to the wall
      const Tuple DIRECTION = Normalize(WALL_PT - RAY_ORIGIN);
      const Ray ray(RAY_ORIGIN, DIRECTION);

      // Check for intersections
      const std::vector<Intersection> XS = Intersect(SPHERE, ray);
      const Intersection HIT = Hit(XS);

      // If it's a hit, mark as red
      if (HIT.T() != FLT_MAX) {
        const Tuple POINT = Position(ray, HIT.T());
        const Tuple NORMAL = SPHERE.NormalAt(POINT);
        const Tuple EYE = -ray.Direction();

        const Color FINAL_COLOR = Lighting(SPHERE.GetMaterial(), POINT_LIGHT, POINT, EYE, NORMAL);

        canvas.WritePixel(x, y, FINAL_COLOR);
      }
    }
  }

  // Write canvas to file
  canvas.WriteToPPM("shadedsphere.ppm");
  return 0;
}
