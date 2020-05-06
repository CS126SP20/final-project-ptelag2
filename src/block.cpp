//
// Created by Praval Telagi on 4/21/20.
//

#include <mylibrary/block.h>

namespace myapp {

double myapp::Block::GetXPosition() const {
  return x_position;
}

double Block::GetYPosition() const {
  return y_position;
}

void Block::SetXPosition(double x) {
  x_position = x;
}

void Block::SetYPosition(double y) {
  y_position = y;
}

void Block::MoveLeft() {
  //Only move left if not touching the left wall
  if (x_position > kLeftWallPosition) {
    x_position--;
  }
}

void Block::MoveRight() {
  //Only move right if not touching the right wall
  if (x_position < kRightWallPosition) {
    x_position++;
  }
}

}