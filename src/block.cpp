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
  x_block--;
}

void Block::MoveRight() {
  x_block++;
}

}