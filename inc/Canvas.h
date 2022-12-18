/*
 * Canvas.h
 *
 * Class declaration of a Canvas to render on.
 *
 * Bryant Pong
 * 9/12/18
 */

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "Color.h" // Each pixel is a color

class Canvas {
public:
  // Constructor:
  Canvas(const int width, const int height);

  // Destructor:
  ~Canvas();

  // Write the canvas to a PPM file
  void WriteToPPM(const char *filename) const;

  // Accessor/Modifier functions
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
  Color PixelAt(const int x, const int y) const {
    return canvas_[y][x];
  }

  void WritePixel(const int x, const int y, const Color& color);

private:
  // Scale the RGB color values from (0.0-1.0) to (0-255)
  int ScaleColorValue(const double colorValue) const;

  // Canvas dimensions
  int width_, height_;

  // Pointer to the actual canvas
  Color **canvas_;
};
#endif
