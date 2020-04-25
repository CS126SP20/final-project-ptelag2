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
  engine.AddInitialFloors();
  //engine.GetOpenFloor().pop_back();
  //engine.PlaceBlockOnLowestSurface();
  engine.PlaceBlockOnLowestSurface();
}

void MyApp::update() {
  if (engine.GetOpenFloor().empty()) {
    //leaderboard.InsertScoreToLeaderboard(engine.GetScore());
  }

  if (engine.GetFloors().size() <= 7) {
    //engine.GetOpenFloor().insert(engine.GetOpenFloor().begin(), 5);
    engine.AddRandomFloor();
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
  /*if (engine.GetOpenFloor().size() <= 7) {
    //engine.GetOpenFloor().insert(engine.GetOpenFloor().begin(), 5);
    //engine.AddRandomFloor();
  }*/
}

auto starting_time = std::chrono::system_clock::now();
double height = 0;
double speed = 5;
void MyApp::DrawFloors() {

  //vector<int> vector{0, 1, 2, 3, 4, 19, 15, 6, 7, 13, 1, 8};
  auto current_time = std::chrono::system_clock::now();
  double current_delay =
      duration_cast<milliseconds>(current_time - starting_time).count() / 1000.0;
  if (current_delay > 10) {
    height+= speed;
    //engine.GetBlock().SetYBlock(engine.GetBlock().GetYBlock() - 1);
    cinder::gl::color(0, 1, 0);

    engine.GetBlock().SetYPosition(engine.GetBlock().GetYPosition() - (speed/40.0));
    //starting_time = std::chrono::system_clock::now();
  }
  /*vector<int> vector = engine.GetOpenFloor();
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
  }*/
  cinder::gl::color(1, 1, 0);
  for (int i = 0; i < engine.GetFloors().size(); i++) {
    cinder::gl::drawSolidRect(Rectf(0,
                                    engine.GetFloors()[i].GetHeight() * 40 - height,
                                    (engine.GetFloors()[i].GetOpenSpot()) * kHeightOfFloor,
                                    engine.GetFloors()[i].GetHeight() * 40 + kHeightOfFloor - height));

    cinder::gl::drawSolidRect(Rectf((engine.GetFloors()[i].GetOpenSpot() + 1) * kHeightOfFloor,
                                    engine.GetFloors()[i].GetHeight() * 40 - height,
                                    800,
                                    engine.GetFloors()[i].GetHeight() * 40 + kHeightOfFloor - height));
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
