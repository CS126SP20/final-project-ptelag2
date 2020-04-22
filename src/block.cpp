//
// Created by Praval Telagi on 4/21/20.
//

#include <mylibrary/block.h>
#include "../include/mylibrary/block.h"


namespace myapp {

int myapp::Block::GetXBlock() {
  return x_block;
}

int Block::GetYBlock() {
  return y_block;
}

void Block::SetXBlock(int x) {
  x_block = x;
}

void Block::SetYBlock(int y) {
  y_block = y;
}

void Block::MoveLeft() {
  if (x_block > 0) {
    x_block--;
  }
}

void Block::MoveRight() {
  if (x_block < 19) {
    x_block++;
  }
}

}