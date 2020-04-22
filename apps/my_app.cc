// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>


namespace myapp {

using cinder::app::KeyEvent;
using cinder::Rectf;
using cinder::Color;
const char kDbPath[] = "leaderboard.db";

MyApp::MyApp() : engine{},
                   leaderboard{cinder::app::getAssetPath(kDbPath).string()} {}

void MyApp::setup() {
  cinder::gl::color(0, 0, 0);
  leaderboard.InsertScoreToLeaderboard(2);

}

void MyApp::update() { }

void MyApp::draw() {
  DrawBackground();
  DrawBlock();
  DrawFloors();
}

void MyApp::DrawBackground() {
  cinder::gl::clear(Color(0, 0, 0));
}

void MyApp::DrawBlock() {
  cinder::gl::color(0, 1, 0);
  cinder::gl::drawSolidRect(Rectf(kBlockSize * engine.GetBlock().GetXBlock(),
                                  kBlockSize * engine.GetBlock().GetYBlock(),
                                  kBlockSize * engine.GetBlock().GetXBlock()
                                  + kBlockSize,
                                  kBlockSize * engine.GetBlock().GetYBlock()
                                  + kBlockSize));
}

void MyApp::DrawFloors() {
vector<int> vector{0, 1, 2, 3, 4, 19, 15, 6, 7, 13, 1, 8};

  cinder::gl::color(1, 1, 0);
  for (int i = 0; i < vector.size(); i++) {
    cinder::gl::drawSolidRect(Rectf(0,
                                    800 - (2 * i * kHeightOfFloor),
                                    (vector[i]) * kHeightOfFloor,
                                    800 - (2 * i * kHeightOfFloor) - kHeightOfFloor));

    cinder::gl::drawSolidRect(Rectf((vector[i]+1) * kHeightOfFloor,
                                    800 - (2 * i * kHeightOfFloor),
                                    800,
                                    800 - (2 * i * kHeightOfFloor) - kHeightOfFloor));
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
