//
// Created by Praval Telagi on 4/19/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <mylibrary/block.h>

#include <string>
#include <vector>

#include "floor.h"
using std::vector;
using std::string;
const vector<string> game_modes{"easy", "medium", "hard"};
const int kNumOfStartingFloors = 10;
const int kHeightOfFloor = 40;

namespace myapp {

class Engine {

 private:
  vector<Floor> floors;
  int score;
  Block block;
  double speed;
  int floor_generator_offset;
  string game_mode;

 public:
  vector<Floor>& GetFloors();
  int GetScore();
  Block& GetBlock();
  void BlockCanMoveDown();
  void PlaceBlockOnLowestSurface();
  void AddRandomFloor();
  void AddInitialFloors();
  bool IsGameOver();
  void SetGameMode(double game_speed);
  double GetSpeed();
  int GetFloorGeneratorOffset();
  void MoveBlockUp();
  void IncreaseSpeed(double percent);
  string GetGameMode();
};

}







#endif  // FINALPROJECT_ENGINE_H
