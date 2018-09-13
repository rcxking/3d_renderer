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

class Canvas
{
public:
    
    // Constructor:
    Canvas( int width, int height ) : m_width( width ), m_height( height )
    {
        // Allocate memory for canvas
        m_canvas = new Color*[ m_height ];
        for( int i = 0; i < m_height; i++ )
        {
            m_canvas[ i ] = new Color[ m_width ];
        }
    } 

    // Destructor:
    ~Canvas()
    {
        // Free up the canvas
        for( int i = 0; i < m_height; i++ )
        {
            delete [] m_canvas[ i ];
        }
        delete [] m_canvas;
    }

    // Write the canvas to a PPM file
    void WriteToPPM( const char *filename )
    {
        FILE *output = fopen( filename, "wb" );
        if( output )
        {
            /*
             * A PPM header consists of:
             * P3\n
             * <width> <height>\n
             * 255\n
             * <data>\n
             */
            char header[ 100 ];
            const char *HEADER_TEMPLATE = "P3\n%d %d\n255\n";
            sprintf( header, HEADER_TEMPLATE, m_width, m_height );

            // Write the header
            fwrite( header, 1, strlen( header ), output ); 

            /*
             * The data is as follows:
             * R G B
             *
             * where R, G, B are scaled from 0 to 255. 
             */
            for( int y = 0; y < m_height; ++y )
            {
                for( int x = 0; x < m_width; ++x )
                {
                    // Next color
                    Color nextColor = m_canvas[ y ][ x ];
                    int scaledRed = ScaleColorValue( nextColor.GetRed() );
                    int scaledGreen = ScaleColorValue( nextColor.GetGreen() );
                    int scaledBlue = ScaleColorValue( nextColor.GetBlue() );
                
                    char nextColorBody[ 100 ] = { 0 };
                    const char *COLOR_TEMPLATE = "%d %d %d ";
                    sprintf( nextColorBody, COLOR_TEMPLATE, scaledRed, scaledGreen, scaledBlue );

                     
                    fwrite( nextColorBody, 1, strlen( nextColorBody ), output );
                }
            }  
            fwrite( "\n", 1, 1, output );


            fclose( output );
        }
    } 

    // Accessor/Modifier functions
    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }
    inline Color PixelAt( const int x, const int y ) const 
    { 
        return m_canvas[ y ][ x ]; 
    }

    inline void WritePixel( const int x, const int y, const Color& color )
    {
        m_canvas[ y ][ x ] = color;
    }

private:

    // Scale the RGB color values from (0.0-1.0) to (0-255)
    int ScaleColorValue( const double colorValue ) const
    {
        return 255 * colorValue;   
    }     

    // Canvas dimensions
    int m_width, m_height;

    // Pointer to the actual canvas
    Color **m_canvas;

};

#endif
