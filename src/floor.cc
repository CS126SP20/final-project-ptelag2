//
// Created by Praval Telagi on 4/18/20.
//

#include <mylibrary/floor.h>
#include <cstdlib>

namespace myapp {

Floor::Floor() {
  int open_index =  (rand() % 15);
  open_spot = open_index;
}
double Floor::GetHeight() {
  return height;
}

int Floor::GetOpenSpot() {
  return open_spot;
}

void Floor::SetHeight(double new_height) {
  height = new_height;
}

} //namespace myapp