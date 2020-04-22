//
// Created by Praval Telagi on 4/19/20.
//

#include <mylibrary/engine.h>

namespace myapp {


Block& Engine::GetBlock() {
  return (Block&)block;
}
int Engine::GetScore() {
  return score;
}

}