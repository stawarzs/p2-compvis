// Project UID af1f95f547e44c8ea88730dfb185559d

// EECS 280 Fall 2021
// Razmik Vardanyan
// Sara Stawarz
// Project 2

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// Creates a 3x5 Matrix and fills it then 
// checks that Matrix_width returns the proper width
TEST(test_width_value) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  ASSERT_EQUAL(Matrix_width(mat), 3);

  delete mat; // delete the Matrix
}

// Creates a 3x5 matrix, fills it, then checks 
// to see if the function Matrix_height returns 
// the proper height value
TEST(test_height_value) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  ASSERT_EQUAL(Matrix_height(mat), 5);

  delete mat; // delete the Matrix
}

// Creates a 3x5 Matrix, fills all spaces with
// the value 365, then checks to make sure 
// Matrix_fill fills all spaces with the 
// appropriate value
TEST(test_matrix_fill) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 365;
  Matrix_init(mat, 2, 2);
  Matrix_fill(mat, value);


  for (int i = 0; i < width * height; ++i) {
    for (int x = 0; x < width * height; x++){
       ASSERT_EQUAL(*Matrix_at (mat, x, i), value);
      }
    }
  
  delete mat; // delete the Matrix
}

// Creates a 3x5 matrix and fills all spaces with 
// increasing values, checking to see if Matrix_max
// returns the proper maximum value
TEST(test_matrix_max) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, 30);
  Matrix_fill_border(mat, 255);

  ASSERT_EQUAL(Matrix_max(mat), 255);
  
  delete mat; // delete the Matrix
}

// Creates a 3x5 matrix and checks to see that all
// parameters (width & height) are correct
TEST(test_matrix_init) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  Matrix_init(mat, 3, 5);

  ASSERT_EQUAL(Matrix_width(mat), 3);
  ASSERT_EQUAL(Matrix_height(mat), 5);
  delete mat; // delete the Matrix
}



// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
