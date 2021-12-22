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
#include "Image.h"

using namespace std;

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  //assert (typeid(*img) == typeid(Image));
  assert (0 < width && width <= MAX_MATRIX_WIDTH);
  assert (0 < height && height <= MAX_MATRIX_HEIGHT);

  img->width = width;
  img->height = height;

  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
  //assert (typeid(*img) == typeid(Image));
  //assert (false); // CREATE A HELPER FUNCTION FOR .ppm ASSERTIONS !!!

  string tmp;
  is >> tmp;
  is >> img->width;
  is >> img->height;
  is >> tmp;

  Matrix_init(&img->red_channel, Image_width(img), Image_height(img));
  Matrix_init(&img->green_channel, Image_width(img), Image_height(img));
  Matrix_init(&img->blue_channel, Image_width(img), Image_height(img));

  for (int r = 0; r < Image_height(img); ++r) {
    for (int c = 0; c < Image_width(img); ++c) {
      
      Pixel pxl;
      is >> pxl.r;
      is >> pxl.g;
      is >> pxl.b;
      
      *Matrix_at(&img->red_channel, r, c) = pxl.r;
      *Matrix_at(&img->green_channel, r, c) = pxl.g;
      *Matrix_at(&img->blue_channel, r, c) = pxl.b;

    }
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  //assert (typeid(*img) == typeid(Image));

  os << "P3\n"
     << Image_width(img) << " " << Image_height(img) << "\n"
     << "255\n";

  for (int r = 0; r < Image_height(img); ++r) {
    for (int c = 0; c < Image_width(img); ++c) {
      
      os << *Matrix_at(&img->red_channel, r, c) << ' '
         << *Matrix_at(&img->green_channel, r, c) << ' '
         << *Matrix_at(&img->blue_channel, r, c) << ' ';

    }
    os << '\n';
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  //assert (typeid(*img) == typeid(Image));

  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  //assert (typeid(*img) == typeid(Image));

  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  //assert (typeid(*img) == typeid(Image));
  //assert (0 <= row && row < Image_height(img));
  //assert (0 <= column && column < Image_width(img));

  Pixel pxl;

  pxl.r = *Matrix_at(&img->red_channel, row, column);
  pxl.g = *Matrix_at(&img->green_channel, row, column);
  pxl.b = *Matrix_at(&img->blue_channel, row, column);

  return pxl;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  //assert (typeid(*img) == typeid(Image));
  //assert (0 <= row && row < Image_height(img));
  //assert (0 <= column && column < Image_width(img));

  *Matrix_at(&img->red_channel, row, column) = color.r;
  *Matrix_at(&img->green_channel, row, column) = color.g;
  *Matrix_at(&img->blue_channel, row, column) = color.b;

}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  //assert (typeid(*img) == typeid(Image));

  for (int r = 0; r < Image_height(img); ++r) {
    for (int c = 0; c < Image_width(img); ++c) {
      *Matrix_at(&img->red_channel, r, c) = color.r;
      *Matrix_at(&img->green_channel, r, c) = color.g;
      *Matrix_at(&img->blue_channel, r, c) = color.b;
    }
  }
}
