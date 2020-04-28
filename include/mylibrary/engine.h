//
// Created by Praval Telagi on 4/19/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <mylibrary/block.h>

#include <vector>

#include "floor.h"
using std::vector;

namespace myapp {

class Engine {

 private:
  vector<int> open_floor{0, 1, 2, 3, 4, 19, 15, 6, 7, 13};
  //vector<int> open_floor{0, 1, 2, 3, 4, 0};
  //vector<int> open_floor{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<Floor> floors;
  int score;
  Block block;

 public:
  vector<int> GetOpenFloor();
  vector<Floor>& GetFloors();
  int GetScore();
  Block& GetBlock();
  void BlockCanMoveDown();
  void PlaceBlockOnLowestSurface();
  void AddRandomFloor();
  void AddInitialFloors();
  bool IsGameOver();
};

}







#endif  // FINALPROJECT_ENGINE_H
