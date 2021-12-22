// resize.cpp
// Project UID af1f95f547e44c8ea88730dfb185559d

// EECS 280 Fall 2021
// Razmik Vardanyan
// Sara Stawarz
// Project 2

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include "Matrix.h"
#include "Image.h"
#include "processing.h"

using namespace std;

int main(int argc, char *argv[]) {
  
  string imgName = argv[1];
  string outputName = argv[2];
  int width = atoi(argv[3]);
  int height = atoi(argv[4]);
  int origW = 0;
  int origH = 0;
  Image *img = new Image;

    //Open input file
  ifstream input(imgName);
  if (input.fail()){
    cout << "Error opening file: " << imgName << endl;
    return 1;
  }

  // Create and open a file
  ofstream output(outputName);

  // put input file into a readable format???
  Image_init(img, input);
  origW = Image_width(img);
  origH = Image_height(img);

  // check that you have proper # of args
  if (argc > 5 || width < 1 || width > origW
    || height < 1 || height > origH){
    
    // return error message
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;

    // return non zero value
    return 1;
  }
  
  // Perform seam carve
  if(argc < 5){
    seam_carve(img, width, origH);
  } else {
    seam_carve(img, width, height);
  }
  // Print out results to output file
  Image_print(img, output);
  // profit 

}