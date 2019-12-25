/*
 * canvas_tests.h
 *
 * Unit tests for the Canvas class.
 *
 * Bryant Pong
 * 12/24/19
 */

#ifndef __CANVAS_TESTS_H_
#define __CANVAS_TESTS_H_

#include "Canvas.h"

// Canvas tests
SCENARIO("a canvas is needed", "[Canvas]") {
  GIVEN("a canvas is constructed") {
    Canvas canvas(10, 20);
    THEN("the canvas should be instantiated correctly") {
      REQUIRE(canvas.GetWidth()  == 10);
      REQUIRE(canvas.GetHeight() == 20); 

      // All pixels on the canvas should be black:
      const Color EXPECTED_COLOR;
      for(int x = 0; x < canvas.GetWidth(); ++x){
        for(int y = 0; y < canvas.GetHeight(); ++y) {
          REQUIRE(canvas.PixelAt(x, y) == EXPECTED_COLOR);
        }
      }
    } 
  }

  GIVEN("a pixel is written onto the canvas") {
    Canvas canvas(10, 20);

    // Make the pixel at (2, 3) red
    canvas.WritePixel(2, 3, Color(1, 0, 0));

    THEN("the pixel at (2, 3) should be red") {
      REQUIRE(canvas.PixelAt( 2, 3) == Color(1, 0, 0 ));
    } 
  }

  GIVEN("an empty PPM image is written") {
    Canvas canvas(5, 3);
    canvas.WriteToPPM("output.ppm");

    THEN("the PPM header is correct") {
      // Open the output.ppm file for reading as a binary stream
      FILE *ppm = fopen("output.ppm", "rb");
      char readBuffer[ 100 ];
      memset(readBuffer, 0, sizeof(readBuffer));
      const char *EXPECTED_HEADER = "P3\n5 3\n255\n";

      if(ppm) {
        fread(readBuffer, 1, 11, ppm);
        fclose(ppm);
      }
      REQUIRE(strcmp(readBuffer, EXPECTED_HEADER) == 0);
    }
  }
}
#endif
