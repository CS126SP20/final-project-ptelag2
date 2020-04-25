// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <chrono>


namespace myapp {

using cinder::app::KeyEvent;
using cinder::Rectf;
using cinder::Color;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::chrono::milliseconds;
const char kDbPath[] = "leaderboard.db";

MyApp::MyApp() : engine{},
                   leaderboard{cinder::app::getAssetPath(kDbPath).string()} {}

void MyApp::setup() {
  cinder::gl::color(0, 0, 1);
  engine.PlaceBlockOnLowestSurface();
}

void MyApp::update() {
  if (engine.GetOpenFloor().empty()) {
    //leaderboard.InsertScoreToLeaderboard(engine.GetScore());
  }
}

void MyApp::draw() {
  DrawBackground();
  DrawFloors();
  DrawBlock();
}

void MyApp::DrawBackground() {
  cinder::gl::clear(Color(0, 0, 0));
}

void MyApp::DrawBlock() {
  engine.BlockCanMoveDown();
  cinder::gl::color(0, 1, 0);
  cinder::gl::drawSolidRect(Rectf(kBlockSize * engine.GetBlock().GetXPosition(),
                                  kBlockSize * engine.GetBlock().GetYPosition(),
                                  kBlockSize * engine.GetBlock().GetXPosition()
                                  + kBlockSize,
                                  kBlockSize * engine.GetBlock().GetYPosition()
                                  + kBlockSize));
}

auto starting_time = std::chrono::system_clock::now();
double height = 800;
void MyApp::DrawFloors() {

  //vector<int> vector{0, 1, 2, 3, 4, 19, 15, 6, 7, 13, 1, 8};
  auto current_time = std::chrono::system_clock::now();
  double current_delay =
      duration_cast<milliseconds>(current_time - starting_time).count() / 1000.0;
  if (current_delay > 5) {
    height-= 0.5;
    //engine.GetBlock().SetYBlock(engine.GetBlock().GetYBlock() - 1);
    cinder::gl::color(0, 1, 0);
    /*cinder::gl::drawSolidRect(Rectf(kBlockSize * engine.GetBlock().GetXPosition(),
                                    kBlockSize * engine.GetBlock().GetYPosition() - 1,
                                    kBlockSize * engine.GetBlock().GetXPosition()
                                    + kBlockSize,
                                    kBlockSize * engine.GetBlock().GetYPosition()
                                    + kBlockSize - 1));*/
    engine.GetBlock().SetYPosition(engine.GetBlock().GetYPosition() - (0.50/40.0));
    //starting_time = std::chrono::system_clock::now();
  }
  vector<int> vector = engine.GetOpenFloor();
  cinder::gl::color(1, 1, 0);
  for (int i = vector.size() - 1; i >= 0; i--) {
    cinder::gl::drawSolidRect(Rectf(0,
                                    height - (2 * i * kHeightOfFloor),
                                    (vector[i]) * kHeightOfFloor,
                                    height - (2 * i * kHeightOfFloor) - kHeightOfFloor));

    cinder::gl::drawSolidRect(Rectf((vector[i]+1) * kHeightOfFloor,
                                    height - (2 * i * kHeightOfFloor),
                                    800,
                                    height - (2 * i * kHeightOfFloor) - kHeightOfFloor));
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_LEFT: {
      engine.GetBlock().MoveLeft();
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      engine.GetBlock().MoveRight();
      break;
    }
  }
}

}  // namespace myapp
