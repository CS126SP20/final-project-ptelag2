//
// Created by Praval Telagi on 4/19/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <vector>
using std::vector;

namespace myapp {

class Engine {

 private:
  vector<int> open_floor;
  int score;

  int x_block;
  int y_block;

 public:
  vector<int> GetOpenFloor();
  int GetXBlock();
  int GetYBlock();
  void SetXBlock(int x);
  void SetYBlock(int y);
};

}







#endif  // FINALPROJECT_ENGINE_H
