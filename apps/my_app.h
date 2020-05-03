// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/engine.h>
#include <mylibrary/scores.h>

const int kBlockSize = 40;
const int kHeightOfFloor = 40;
const char kDbPath[] = "leaderboard.db";
const char kNormalFont[] = "Arial";
const double kEasy = 1.0;
const double kMedium = 1.5;
const double kHard = 2.0;
const int kRed = 0;
const int kGreen = 1;
const int kBlue = 2;

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void DrawBackground();
  void DrawBlock();
  void DrawFloors();
  void DrawGameOver();
  void PrintGameMode();
  void PrintPlayerScore();
  void PrintTopScores();

 private:
  SQL_Leaderboard leaderboard;
  Engine engine;
  double height_offset;
  bool speed_can_increase;
  bool added_score_to_table;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
