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

#include <cstring>
#include <cmath>
#include <cassert>

class Matrix {
public:
  // Create an empty matrix
  Matrix(const int rows, const int cols) : rows_(rows),
                                           cols_(cols),
                                           totalSize_(rows * cols) {
    matrix_ = new float[totalSize_];
    memset(matrix_, 0, sizeof(float) * totalSize_);
  }

  // Create a matrix from an array of floats
  Matrix(const int rows, const int cols, float *values) :
       rows_(rows), cols_(cols), totalSize_(rows * cols) {
    matrix_ = new float[totalSize_];
    // Copy values over
    memcpy(matrix_, values, sizeof(float) * totalSize_);
  }

  // Assignment operator=
  Matrix& operator=(const Matrix& rhs) {
    // Check for self-referencing
    if(this != &rhs) {
      // Delete old allocation
      delete [] matrix_;
      rows_ = rhs.rows_;
      cols_ = rhs.cols_;
      totalSize_ = rhs.totalSize_;

      matrix_ = new float[totalSize_];
      memcpy(matrix_, rhs.matrix_, sizeof(float) * totalSize_);
    }

    return *this;
  }

  // Copy constructor
  Matrix(const Matrix& rhs) :
                              rows_(rhs.rows_),
                              cols_(rhs.cols_),
                              totalSize_(rhs.totalSize_) {
    matrix_ = new float[totalSize_];
    memcpy(matrix_, rhs.matrix_, sizeof(float) * totalSize_);
  }

  // Destructor
  ~Matrix() {
    if (matrix_) {
      delete [] matrix_;
      matrix_ = NULL;
    }
  }

  // operator==
  bool operator==(const Matrix& rhs) const {
    const bool ROWS_EQUAL = (rows_ == rhs.rows_);
    const bool COLS_EQUAL = (cols_ == rhs.cols_);

    if (ROWS_EQUAL && COLS_EQUAL) {
      // Compare the values:
      for (int i = 0; i < totalSize_; ++i) {
        if (std::fabs(matrix_[i] - rhs.matrix_[i]) > 0.0001) {
          return false;
        }
      }
    }
    return true;
  }

  // Comparison operator !=
  bool operator!=(const Matrix& rhs) const {
    return !operator==(rhs);
  }

  // operator*= (matrix multiplication)
  Matrix& operator*= (const Matrix& rhs) {
    Matrix temp(rows_, rhs.cols_);
    for (int y = 0; y < rows_; ++y) {
      for (int x = 0; x < rhs.cols_; ++x) {
        float dotProduct = 0.0;

        for (int index = 0; index < cols_; ++index) {
          const int thisIndex = y * cols_ + index;
          const int thatIndex = index * rhs.cols_ + x;
          dotProduct += (matrix_[thisIndex] * rhs.matrix_[thatIndex]);
        }

        temp.SetValue(y, x, dotProduct);
      }
    }

    // Copy over the new values
    delete [] matrix_;

    rows_ = temp.rows_;
    cols_ = temp.cols_;
    totalSize_ = rows_ * cols_;
    matrix_ = new float[totalSize_];
    memcpy(matrix_, temp.matrix_, sizeof(float) * totalSize_);

    return *this;
  }

  // operator* (matrix multiplication)
  Matrix operator*(const Matrix& rhs) const {
    return Matrix(*this) *= rhs;
  }

  // operator* (matrix x tuple)
  Tuple operator*(const Tuple& rhs) const {

    // Convert the tuple to a 4x1 matrix
    float values[] = {rhs.X(),
                      rhs.Y(),
                      rhs.Z(),
                      rhs.W()};
    Matrix rhsMatrix(4, 1, values);
    Matrix result = Matrix(*this) * rhsMatrix;

    Tuple product(result.GetValue(0, 0),
                  result.GetValue(1, 0),
                  result.GetValue(2, 0),
                  result.GetValue(3, 0));
    return product;
  }

  // Accessor/modifier functions
  int GetRows() const { return rows_; }
  int GetCols() const { return cols_; }
  float GetValue(const int y, const int x) const {
    return matrix_[y * cols_ + x];
  }

  void SetValue(const int y, const int x, const float val) {
    matrix_[y * cols_ + x] = val;
  }
private:
    // Matrix dimensions
    int rows_, cols_, totalSize_;

    // Pointer to storage backing
    float *matrix_;
};

// Function prototypes
Matrix Identity(const int);
Matrix Transpose(const Matrix &);
float Determinant(const Matrix &);
Matrix Submatrix(const Matrix &, const int, const int);
float Minor(const Matrix &, const int, const int);
float Cofactor(const Matrix &, const int, const int);
bool IsInvertible(const Matrix &);
Matrix Inverse(const Matrix &);

/**
 * @brief  Constructs an n x n Identity Matrix
 * @param n: dimension of Identity Matrix
 * @return Matrix: Identity matrix of size n x n
 */
Matrix Identity(const int n) {
  Matrix mat(n, n);

  for (int i = 0; i < n; ++i) {
    mat.SetValue(i, i, 1);
  }
  return mat;
}

/**
 * @brief  Computes the tranpose of a matrix
 * @param mat: Matrix to compute the transpose of
 * @return Matrix: Matrix transpose
 */
Matrix Transpose(const Matrix &mat) {
  Matrix result(mat.GetRows(), mat.GetCols());

  for (int y = 0; y < result.GetRows(); ++y) {
    for (int x = 0; x < result.GetCols(); ++x) {
      result.SetValue(y, x, mat.GetValue(x, y));
    }
  }

  return result;
}

/**
 * @brief  Computes the determinant of a 2x2 matrix
 * @param mat: Matrix to compute the determinant of
 * @return float: Determinant
 */
float Determinant(const Matrix &mat) {
  if (mat.GetRows() == 2) {
    // Special case for 2x2 matrices
    return (mat.GetValue(0, 0) * mat.GetValue(1, 1)) -
           (mat.GetValue(0, 1) * mat.GetValue(1, 0));
  } else {
    /*
     * For larger matrices, the determinant is the sum
     * of any row's elements each multiplied its cofactor.
     */
    float det = 0.0;
    for (int x = 0; x < mat.GetCols(); ++x) {
      det += (Cofactor(mat, 0, x) * mat.GetValue(0, x));
    }
    return det;
  }
}

/**
 * @brief  Computes the submatrix of the given matrix.
 * @param mat: Input matrix
 * @param row, col: Eliminate values that are in either this row or column
 * @return Matrix: Submatrix
 */
Matrix Submatrix(const Matrix &mat, const int row, const int col) {
  // Submatrix removes the specified row and column from mat
  const int NEW_ROWS = mat.GetRows() - 1;
  const int NEW_COLS = mat.GetCols() - 1;
  const int NEW_SIZE = NEW_ROWS * NEW_COLS;
  float newVals[NEW_SIZE];
  memset(newVals, 0, sizeof(newVals));

  int idx = 0;
  for (int y = 0; y < mat.GetRows(); ++y) {
    for (int x = 0; x < mat.GetCols(); ++x) {
      // Skip elements if it's the specified row or column:
      if (y == row || x == col) {
        continue;
      }

      newVals[idx] = mat.GetValue(y, x);
      ++idx;
    }
  }

  return Matrix(NEW_ROWS, NEW_COLS, newVals);
}

/**
 * @brief  Computes the Minor of the given matrix.
 * @param mat: Input matrix
 * @param row, col: Compute the determinant of the submatrix of the given row/col
 * @return float: Minor
 */
float Minor(const Matrix &mat, const int row, const int col) {
  // The minor is the determinant of the submatrix at row and col
  return Determinant(Submatrix(mat, row, col));
}

/**
 * @brief  Computes the Cofactor of the given matrix.
 * @param mat: Input matrix
 * @param row, col: Compute the cofactor of the submatrix with the given row/col
 * @return float: Cofactor
 */
float Cofactor(const Matrix &mat, const int row, const int col) {
  // The Cofactor is the minor if (row + col) is even and -minor if (row + col) is odd
  const float MINOR = Minor(mat, row, col);
  return ((row + col) % 2 == 0) ? MINOR : -MINOR;
}

/**
 * @brief  Checks if a matrix is invertible
 * @param mat: Input matrix
 * @return bool: True if invertible; false if not
 */
bool IsInvertible(const Matrix &mat) {
  // If the determinant is 0, the matrix is not invertible
  return Determinant(mat) != 0.0;
}

/**
 * @brief  Computes the inverse of the matrix.
 * @param mat: Input matrix
 * @return Matrix: Inverse
 */
Matrix Inverse(const Matrix &mat) {
  // Ensure the matrix is invertible
  assert(IsInvertible(mat) == true);

  Matrix inv(mat.GetRows(), mat.GetCols());

  const float MAT_DET = Determinant(mat);

  for (int row = 0; row < mat.GetRows(); ++row) {
    for (int col = 0; col < mat.GetCols(); ++col) {
      const float C = Cofactor(mat, row, col);
      inv.SetValue(col, row, C / MAT_DET);
    }
  }

  return inv;
}
#endif
