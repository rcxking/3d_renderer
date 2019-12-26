/*
 * Canvas.h
 *
 * Class implementation of a Canvas to render on.
 *
 * Bryant Pong
 * 9/12/18
 */

#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "Color.h" // Each pixel is a color 
#include <cstdio>
#include <cstring>

class Canvas {
public:
  // Constructor:
  Canvas(const int width, const int height) : width_(width), height_(height) {
    // Allocate memory for canvas
    canvas_ = new Color*[height_];
    for(int i = 0; i < height_; i++) {
      canvas_[i] = new Color[width_];
    }
  } 

  // Destructor:
  ~Canvas() {
    // Free up the canvas
    for(int i = 0; i < height_; i++) {
      delete [] canvas_[ i ];
    }
    delete [] canvas_;
  }

  // Write the canvas to a PPM file
  void WriteToPPM(const char *filename) {
    FILE *output = fopen(filename, "wb");
    if(output) {
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
      for(int y = 0; y < height_; ++y) {
        for(int x = 0; x < width_; ++x) {
          // Next color
          Color nextColor = canvas_[y][x];
          int scaledRed = ScaleColorValue(nextColor.Red());
          int scaledGreen = ScaleColorValue(nextColor.Green());
          int scaledBlue = ScaleColorValue(nextColor.Blue());
                
          char nextColorBody[100] = {0};
          const char *COLOR_TEMPLATE = "%d %d %d ";
          sprintf(nextColorBody, COLOR_TEMPLATE, scaledRed, scaledGreen, scaledBlue);
                     
          fwrite(nextColorBody, 1, strlen(nextColorBody), output);
        }
      }  
      fwrite("\n", 1, 1, output);
      fclose(output);
    }
  } 

  // Accessor/Modifier functions
  inline int GetWidth() const { return width_; }
  inline int GetHeight() const { return height_; }
  inline Color PixelAt( const int x, const int y ) const { 
    return canvas_[y][x]; 
  }

  inline void WritePixel(const int x, const int y, const Color& color) {
    // Ensure the pixel value is accessible
    if((x > 0) && (x < width_) &&
       (y > 0) && (y < height_)) {
      canvas_[ y ][ x ] = color;
    }
  }

private:
  // Scale the RGB color values from (0.0-1.0) to (0-255)
  int ScaleColorValue( const float colorValue ) const {
    float clr = colorValue;
    // Threshold the input color value to be between 0.0-1.0
    if (clr > 1.0) {
      clr = 1.0;
    } else if (clr < 0.0) {
      clr = 0.0;
    }
    return static_cast<int>(255 * clr);   
  }     

  // Canvas dimensions
  int width_, height_;

  // Pointer to the actual canvas
  Color **canvas_;
};
#endif
