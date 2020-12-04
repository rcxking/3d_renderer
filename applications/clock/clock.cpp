/*
 * clock.cpp
 *
 * Uses the Transformations.h library to draw 12 points
 * representing an analog clock face.
 *
 * Bryant Pong
 * 9/23/18
 */
#include "Transformations.h"
#include "Color.h"
#include "Canvas.h"

#include <cmath> // M_PI

int main(void) {
  // Canvas dimensions
  const int CANVAS_WIDTH  = 240;
  const int CANVAS_HEIGHT = 240;

  // Center of the canvas
  const int CENTER_X = CANVAS_WIDTH  / 2;
  const int CENTER_Y = CANVAS_HEIGHT / 2;

  Canvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);

  // Initial right-most point; we'll be rotating this around the canvas center
  const Tuple p = Point(CENTER_X + 100, CENTER_Y, 0);

  // Color of the hour points
  Color color(1.0, 1.0, 1.0);

  /*
   * There are 12 hours on a clock's face.  We will rotate the Point p
   * by (2pi/12) = pi/6 radians and draw them on the canvas.
   */
  const float ROTATE_BY = M_PI/6.0;

  /*
   * To rotate around a point other than the origin, perform the following
   * steps:
   *
   * 1) Translate the point w.r.t. the origin
   * 2) Rotate the point around the origin
   * 3) Translate the point back to the original rotation point
   */

  for(float rot = 0; rot < (2*M_PI); rot += ROTATE_BY) {
    const Matrix TRANSLATE_WRT_ORIGIN = Translation(-CENTER_X, -CENTER_Y, 0);
    const Matrix TRANSLATE_BACK = Translation(CENTER_X, CENTER_Y, 0);
    const Tuple rotated = TRANSLATE_BACK * RotZ(rot) * TRANSLATE_WRT_ORIGIN * p;
    canvas.WritePixel(rotated.X(), rotated.Y(), color);
  }

  // Write the clock face image
  canvas.WriteToPPM("clock.ppm");

  return 0;
}
