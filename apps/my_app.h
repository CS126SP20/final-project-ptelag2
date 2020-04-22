// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/engine.h>
#include <mylibrary/scores.h>

const int kBlockSize = 40;
const int kHeightOfFloor = 40;

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

 private:
  SQL_Leaderboard leaderboard;
  Engine engine;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
