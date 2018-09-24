/*
 * Matrix.h
 *
 * Class implementation of a Matrix data structure.
 *
 * Bryant Pong
 * 9/14/18
 */
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Tuple.h"

#include <cassert>
#include <cstring>
#include <cmath>

class Matrix
{
public:
    // Create an empty matrix
    Matrix( int rows, int cols ) : m_rows( rows ), 
                                   m_cols( cols ),
                                   m_totalSize( rows * cols )
    {
        m_matrix = new double[ m_totalSize ];
        memset( m_matrix, 0, sizeof( double ) * m_totalSize );
    }

    // Create a matrix from an array of doubles
    Matrix( int rows, int cols, double *values, int numElements ) :
       m_rows( rows ), m_cols( cols ), m_totalSize( rows * cols )
    {
        // Ensure numElements equals the dimensions of the matrix
        assert( numElements == ( rows * cols ) );
    
        m_matrix = new double[ m_totalSize ];

        // Copy values over
        memcpy( m_matrix, values, sizeof( double ) * numElements ); 
    }

    // Assignment operator=
    Matrix& operator=( const Matrix& rhs )
    {
        // Check for self-referencing
        if( this != &rhs )
        {
            // Delete old allocation
            delete [] m_matrix;

            m_rows = rhs.m_rows;
            m_cols = rhs.m_cols;
            m_totalSize = rhs.m_totalSize;

            m_matrix = new double[ m_totalSize ];
            memcpy( m_matrix, rhs.m_matrix, sizeof( double ) * m_totalSize );   
        }

        return *this;
    }

    // Copy constructor
    Matrix( const Matrix& rhs ) :
        m_rows( rhs.m_rows ),
        m_cols( rhs.m_cols ),
        m_totalSize( rhs.m_totalSize )
    {
        m_matrix = new double[ m_totalSize ];
        memcpy( m_matrix, rhs.m_matrix, sizeof( double ) * m_totalSize ); 
    }

    // Destructor
    ~Matrix()
    {
        delete [] m_matrix;
    }

    // operator==
    bool operator==( const Matrix& rhs ) const
    {
        const bool ROWS_EQUAL = ( m_rows == rhs.m_rows );
        const bool COLS_EQUAL = ( m_cols == rhs.m_cols );

        if( ROWS_EQUAL && COLS_EQUAL )
        {
            // Compare the values:
            for( int i = 0; i < m_totalSize; ++i )
            {
                if( !IsEqual( m_matrix[ i ], rhs.m_matrix[ i ] ) )
                {
                   return false;
                } 
            }
            return true;
        }
        return false;
    }  

    // operator*= (matrix multiplication) 
    Matrix& operator*= ( const Matrix& rhs )
    {
        /*
         * Ensure that this matrix's columns match the
         * other's rows.
         *
         * Example: Matrix A: 4 rows x 2 cols
         *          Matrix B: 2 rows x 4 cols
         *          Product: 4x4 matrix
         */
        assert( m_cols == rhs.m_rows );

        Matrix temp( m_rows, rhs.m_cols );   
        for( int y = 0; y < m_rows; ++y )
        {
            for( int x = 0; x < rhs.m_cols; ++x )
            {
                double dotProduct = 0.0;

                for( int index = 0; index < m_cols; ++index )
                {
                    const int thisIndex = y * m_cols + index;
                    const int thatIndex = index * rhs.m_cols + x;  
                    dotProduct += ( m_matrix[ thisIndex ] * rhs.m_matrix[ thatIndex ] ); 
                }  

               temp.SetValue( y, x, dotProduct );    
            }
        }

        // Copy over the new values
        delete [] m_matrix;

        m_rows = temp.m_rows;
        m_cols = temp.m_cols;
        m_totalSize = m_rows * m_cols;
        m_matrix = new double[ m_totalSize ];
        memcpy( m_matrix, temp.m_matrix, sizeof( double ) * m_totalSize );  

        return *this;
    }

    // operator* (matrix multiplication)
    const Matrix operator*( const Matrix& rhs ) const
    {
        return Matrix( *this ) *= rhs;
    }

    // operator* (matrix x tuple)
    const Tuple operator*( const Tuple& rhs ) const
    {
        // Ensure this matrix's columns == 4  
        assert( m_cols == 4 );

        // Convert the tuple to a 4x1 matrix
        double values[] = { rhs.GetX(),
                            rhs.GetY(),
                            rhs.GetZ(),
                            rhs.GetW() };
        Matrix rhsMatrix( 4, 1, values, 4 ); 

        Matrix result = Matrix( *this ) * rhsMatrix;  

        Tuple product( result.GetValue( 0, 0 ),
                       result.GetValue( 1, 0 ),
                       result.GetValue( 2, 0 ),
                       result.GetValue( 3, 0 ) );

        return product;   
    }

    // Transpose
    const Matrix Transpose() const
    {
        Matrix trans( m_rows, m_cols );

        for( int row = 0; row < m_rows; ++row )
        {
           for( int col = 0; col < m_cols; ++col )
           {
                trans.SetValue( col, row, GetValue( row, col ) ); 
           }
        } 

        return trans;
    }

    // Determinant
    const double Determinant() const
    {
        // Ensure this matrix is square
        assert( m_rows == m_cols );

        double determinant = 0.0;

        // Special case for a 2x2 matrix
        if( m_rows == 2 )
        {
            // ad - bc
            determinant = ( GetValue( 0, 0 ) * GetValue( 1, 1 ) ) -
                          ( GetValue( 1, 0 ) * GetValue( 0, 1 ) ); 
        }
        else
        {
            /*
             * For any square matrices larger than 2x2, the determinant is found
             * by picking Row 0.  Multiply each element by its cofactor; the sum
             * will be the determinant.
             */
           for( int col = 0; col < m_cols; ++col )
           {
                determinant += ( GetValue( 0, col ) * Cofactor( 0, col ) ); 
           } 
        } 

        return determinant;
    }

    /*
     * Submatrix.  Remove all values in the given row
     * and column.
     */
    const Matrix Submatrix( const int row, const int col ) const
    {
        Matrix sub( m_rows - 1, m_cols - 1 );

        int index = 0;

        for( int rowIdx = 0; rowIdx < m_rows; ++rowIdx )
        {
            for( int colIdx = 0; colIdx < m_cols; ++colIdx )
            {
                // Skip any value in this row or column
                if( ( rowIdx == row ) || ( colIdx == col ) )
                {
                    continue;
                }
                
                sub.SetValue( index / sub.GetCols(), index % sub.GetCols(), GetValue( rowIdx, colIdx ) );

                ++index;
            }
        }

        return sub;
    }

    /*
     * Minor
     *
     * The minor is the determinant of the submatrix at the given row and column.
     */
    const double Minor( const int row, const int col ) const
    {
        return Submatrix( row, col ).Determinant();
    }

    /*
     * Cofactor
     *
     * The cofactor is computed by finding the minor at the given row
     * and column.  If the sum of the given row and column is odd,
     * negate the minor; otherwise return the minor.
     */
    const double Cofactor( const int row, const int col ) const
    {
        double cofactor = Minor( row, col );
        if( ( row + col ) % 2 == 1 )
        {
            // Negate the minor
            cofactor *= -1;
        }

        return cofactor;
    }   
    
    /*
     * IsInvertible
     *
     * A matrix is invertible if its determinant is NOT 0.
     */
    const bool IsInvertible() const
    {
        return ( Determinant() != 0 );
    }

    /*
     * Inverse
     *
     * Calculate the matrix inverse with the following steps:
     * 1) Create a cofactor matrix
     * 2) Transpose the cofactor matrix
     * 3) Divide each element by the determinant of the original matrix
     */
    const Matrix Inverse() const
    {
        Matrix cofactor( m_rows, m_cols );

        // Generate the cofactor matrix
        for( int row = 0; row < m_rows; ++row )
        {
            for( int col = 0; col < m_cols; ++col )
            {
                cofactor.SetValue( row, col, Cofactor( row, col ) );
            }
        }

        // Get the transpose of the cofactor matrix
        Matrix cofactorTranspose = cofactor.Transpose();

        // Finally compute the inverse
        const double DETERMINANT = Determinant();
        Matrix inverse( m_rows, m_cols );
        for( int row = 0; row < m_rows; ++row )
        {
            for( int col = 0; col < m_cols; ++col )
            {
                inverse.SetValue( row, col, cofactorTranspose.GetValue( row, col ) / DETERMINANT );
            }
        }

        return inverse;
    } 

    // Accessor/modifier functions
    inline int GetRows() const { return m_rows; }
    inline int GetCols() const { return m_cols; }
    inline double GetValue( const int y, const int x ) const { return m_matrix[ y * m_cols + x ]; }

    inline void SetValue( const int y, const int x, const double val ) { m_matrix[ y * m_cols + x ] = val; }

protected:

    // Floating point comparison test
    const bool IsEqual( const double lhs, const double rhs ) const
    {
        const double EPSILON = 0.0001;
        return fabs( lhs - rhs ) < EPSILON;
    } 

    // Matrix dimensions
    int m_rows, m_cols, m_totalSize;

    // Pointer to storage backing
    double *m_matrix; 
};

// Identity Matrix
class IdentityMatrix : public Matrix
{

public:
    IdentityMatrix( int dimensions ) : Matrix( dimensions, dimensions )
    {
        // The diagonal should be 1.0:
        for( int i = 0; i < dimensions; ++i )
        {
            SetValue( i, i, 1.0 );
        }
    }  
};

#endif
