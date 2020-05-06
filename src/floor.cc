//
// Created by Praval Telagi on 4/18/20.
//

#include <mylibrary/floor.h>
#include <cstdlib>

namespace myapp {

Floor::Floor() {
  //Randomly generates an integer between 0-19
  int open_index =  (rand() % kLengthOfFloor);
  open_spot = open_index;
}

double Floor::GetHeight() const {
  return height;
}

int Floor::GetOpenSpot() const {
  return open_spot;
}

void Floor::SetHeight(double new_height) {
  height = new_height;
}

} //namespace myapp