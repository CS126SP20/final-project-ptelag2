//
// Created by Praval Telagi on 4/18/20.
//

#include <mylibrary/floor.h>
#include <cstdlib>

namespace myapp {

Floor::Floor() {
  int open_index =  (rand() % 15);
  floor_layout[open_index];
}
bool Floor::GetFloor() {
  return &floor_layout;
}

} //namespace myapp