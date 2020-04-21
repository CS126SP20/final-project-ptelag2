//
// Created by Praval Telagi on 4/19/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <vector>
#include <mylibrary/block.h>
using std::vector;

namespace myapp {

class Engine {

 private:
  vector<int> open_floor;
  int score;
  Block block;

 public:
  vector<int> GetOpenFloor();
  int GetScore();
  Block& GetBlock();
};

}







#endif  // FINALPROJECT_ENGINE_H
