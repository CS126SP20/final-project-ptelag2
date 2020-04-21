//
// Created by Praval Telagi on 4/19/20.
//

#include <mylibrary/engine.h>

namespace myapp {

int Engine::GetXBlock() {
  return x_block;
}

int Engine::GetYBlock() {
  return y_block;
}

void Engine::SetXBlock(int x) {
  x_block = x;
}

void Engine::SetYBlock(int y) {
  y_block = y;
}

}