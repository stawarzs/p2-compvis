// Project UID af1f95f547e44c8ea88730dfb185559d

// EECS 280 Fall 2021
// Razmik Vardanyan
// Sara Stawarz
// Project 2

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include "Matrix.h"

using namespace std;

// ADDITIONAL HELPER FUNCTIONS
// Created by Razmik Vardanyan

// EFFECTS: asserts that ptr points to an element in the Matrix
//          returns "i" of the element that ptr points to
const int validPointer(const Matrix* mat, const int* ptr) {
  int width = Matrix_width(mat);
  int height = Matrix_height(mat);
  int isValid = 0;
  int i = 0;

  for (i = 0; i < width * height; ++i) {
    if (ptr == &mat->data[i]) {
      isValid = 1;
      break;
    }
  }
  assert (isValid == 1);
  return i;
}

// End of ADDITIONAL HELPER FUNCTIONS


// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  //assert (typeid(*mat) == typeid(Matrix));
  assert (0 < width && width <= MAX_MATRIX_WIDTH);
  assert (0 < height && height <= MAX_MATRIX_HEIGHT);

  mat->width = width;
  mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
 //assert (typeid(*mat) == typeid(Matrix));

  int width = Matrix_width(mat);
  int height = Matrix_height(mat);

  os << width << ' ' << height << '\n';

  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      os << mat->data[width*r+c] << ' ';
    }
    os << '\n';
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  //assert (typeid(*mat) == typeid(Matrix));

  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  //assert (typeid(*mat) == typeid(Matrix));

  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  //assert (typeid(*mat) == typeid(Matrix));
  int i = validPointer(mat, ptr);

  return (i / Matrix_width(mat));
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  //assert (typeid(*mat) == typeid(Matrix));
  int i = validPointer(mat, ptr);

  return (i % Matrix_width(mat));
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  //assert (typeid(*mat) == typeid(Matrix));
  //assert (0 <= row && row < Matrix_height(mat));
  //assert (0 <= column && column < Matrix_width(mat));

  int width = Matrix_width(mat);
  int i = width * row + column;
  return (&mat->data[i]);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  //assert (typeid(*mat) == typeid(Matrix));
  //assert (0 <= row && row < Matrix_height(mat));
  //assert (0 <= column && column < Matrix_width(mat));
  
  int width = Matrix_width(mat);
  int i = width * row + column;
  const int* j = &mat->data[i];
  return (j);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  //assert (typeid(*mat) == typeid(Matrix));

  int width = Matrix_width(mat);
  int height = Matrix_height(mat);

  for (int i = 0; i < width * height; ++i) {
    mat->data[i] = value;
  }
} 

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  //assert (typeid(*mat) == typeid(Matrix));

  for (int r = 0; r < Matrix_height(mat); ++r) {
    for (int c = 0; c < Matrix_width(mat); ++c) {

      if (r == 0 || r == Matrix_height(mat)-1) {
        mat->data[Matrix_width(mat)*r+c] = value;
      }
      if (c == 0 || c == Matrix_width(mat)-1) {
        mat->data[Matrix_width(mat)*r+c] = value;
      }

    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  //assert (typeid(*mat) == typeid(Matrix));
  int max_value = -2147483647;

  for (int r = 0; r < Matrix_height(mat); ++r) {
    for (int c = 0; c < Matrix_width(mat); ++c) {
      
      if(mat->data[Matrix_width(mat)*r+c] > max_value) {
        max_value = mat->data[Matrix_width(mat)*r+c];
      }

    }
  }
  return max_value;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row, 
  int column_start, int column_end) {
  //assert (typeid(*mat) == typeid(Matrix));
  assert (0 <= row && row < Matrix_height(mat));
  assert (0 <= column_start && column_end <= Matrix_width(mat));
  assert (column_start < column_end);
  
  int min_value = 2147483647;
  int min_col = column_end;
  
  for (int c = column_start; c < column_end; ++c) {  
    if (mat->data[Matrix_width(mat)*row+c] < min_value) {
      min_value = mat->data[Matrix_width(mat)*row+c];
      min_col = c;
    }
  }
  
  return min_col;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row, 
  int column_start, int column_end) {
  //assert (typeid(*mat) == typeid(Matrix));
  assert (0 <= row && row < Matrix_height(mat));
  assert (0 <= column_start && column_end <= Matrix_width(mat));
  assert (column_start < column_end);

  int min_value = 2147483647;
  
  for (int c = column_start; c < column_end; ++c) {  
    if (mat->data[Matrix_width(mat)*row+c] < min_value) {
      min_value = mat->data[Matrix_width(mat)*row+c];
    }
  }
  
  return min_value;
}