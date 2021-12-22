// Project UID af1f95f547e44c8ea88730dfb185559d

// EECS 280 Fall 2021
// Razmik Vardanyan
// Sara Stawarz
// Project 2

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include "Image.h"
using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// Sets image width and height
// to 13 and 8 respectively
// ensures that init creates img with 
// proper values
TEST(test_init_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  //width 13, height 8
  Image_init(img, 13, 8);


  ASSERT_EQUAL(Image_height(img), 8);
  ASSERT_EQUAL(Image_width(img), 13);
  
  delete img; // delete the Image
}

TEST(test_width_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  //width 30, height 8
  Image_init(img, 30, 8);

  ASSERT_EQUAL(Image_width(img), 30);
  
  delete img; // delete the Image
}

TEST(test_height_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  //width 3, height 50
  Image_init(img, 3, 50);

  ASSERT_EQUAL(Image_height(img), 50);
  
  delete img; // delete the Image
}

TEST(test_get_pixel) {
  Image *img = new Image; // create an Image in dynamic memory
  const Pixel white = {255, 255, 255};
  
  //width 2, height 2
  Image_init(img, 2, 2);
  Image_fill(img, white);
  
  // capture output
  ostringstream s;
  Image_print(img, s);
  
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 255 255 255 255 255 \n";
  correct << "255 255 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  delete img; // delete the Image
}

// TEST(test_set_pixel) {
//   // Image *img = new Image; // create an Image in dynamic memory

//   // //width 3, height 50
//   // Image_init(img, 3, 50);

//   // ASSERT_EQUAL(Image_height(img), 50);
  
//   // delete img; // delete the Image
// }

TEST(test_fill_basic) {
  Image *img = new Image; // create an Image in dynamic memory
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_fill(img, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 255 255 255 255 255 \n";
  correct << "255 255 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
