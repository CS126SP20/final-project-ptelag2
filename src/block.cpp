//
// Created by Praval Telagi on 4/21/20.
//

#include <mylibrary/block.h>
#include "../include/mylibrary/block.h"


namespace myapp {

double myapp::Block::GetXPosition() {
  return x_position;
}

double Block::GetYPosition() {
  return y_position;
}

void Block::SetXPosition(double x) {
  x_position = x;
}

void Block::SetYPosition(double y) {
  y_position = y;
}

void Block::MoveLeft() {
  if (x_position > 0) {
    x_position--;
  }
}

void Block::MoveRight() {
  if (x_position < 19) {
    x_position++;
  }
}

}