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
  vector<Floor> floors;
  int score;
  Block block;
  double speed;
  int floor_generator_offset;

 public:
  vector<Floor>& GetFloors();
  int GetScore();
  Block& GetBlock();
  void BlockCanMoveDown();
  void PlaceBlockOnLowestSurface();
  void AddRandomFloor();
  void AddInitialFloors();
  bool IsGameOver();
  void SetGameModeEasy();
  double GetSpeed();
  int GetFloorGeneratorOffset();
  void MoveBlockUp();
  void IncreaseSpeed(double percent);
};

}







#endif  // FINALPROJECT_ENGINE_H
