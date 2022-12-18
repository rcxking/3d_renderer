/*
 * Canvas.cpp
 *
 * Class implementation of a Canvas to render on.
 */

#include "Canvas.h"
#include "Color.h"

#include <algorithm>
#include <cstdio>
#include <cstring>

Canvas::Canvas(const int width, const int height) {
	width_ = width;
	height_ = height;

	// Allocate memory for the canvas
	canvas_ = new Color*[height_];
	for(int i = 0; i < height_; ++i) {
		canvas_[i] = new Color[width_];
	}
}

Canvas::~Canvas() {
  for (int i = 0; i < height_; ++i) {
    delete [] canvas_[i];
  }
  delete [] canvas_;
}

void Canvas::WriteToPPM(const char *filename) const {
  FILE *output = fopen(filename, "wb");
  if (output) {
    /*
     * A PPM header consists of:
     * P3\n
     * <width> <height>\n
     * 255\n
     * <data>\n
     */
    char header[100];
    const char *HEADER_TEMPLATE = "P3\n%d %d\n255\n";
    sprintf(header, HEADER_TEMPLATE, width_, height_);

    // Write the header
    fwrite(header, 1, strlen(header), output);

    /*
     * The data is as follows:
     * R G B
     *
     * where R, G, B are scaled from 0 to 255.
     */
    for (int y = 0; y < height_; ++y) {
      for (int x = 0; x < width_; ++x) {
        const Color nextColor = canvas_[y][x];
        const int scaledRed = ScaleColorValue(nextColor.Red());
        const int scaledGreen = ScaleColorValue(nextColor.Green());
        const int scaledBlue = ScaleColorValue(nextColor.Blue());

        char nextColorBody[100] = {0};
        const char *COLOR_TEMPLATE = "%d %d %d ";
        sprintf(nextColorBody, COLOR_TEMPLATE, scaledRed, scaledGreen,
            scaledBlue);
        fwrite(nextColorBody, 1, strlen(nextColorBody), output);
      }
    }
    fwrite("\n", 1, 1, output);
    fclose(output);
  }
}

void Canvas::WritePixel(const int x, const int y, const Color& color) {
  if ((x > 0) && (x < width_) && (y > 0) && (y < height_))
    canvas_[y][x] = color;
}

int Canvas::ScaleColorValue(const double colorValue) const {
  double clr = colorValue;
  clr = std::min(clr, 1.0);
  clr = std::max(clr, 0.0);
  return static_cast<int>(255 * clr);
}
