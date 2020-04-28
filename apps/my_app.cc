// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <chrono>


namespace myapp {

using cinder::app::KeyEvent;
using cinder::Rectf;
using cinder::Color;
using cinder::ColorA;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;
using cinder::TextBox;
using std::chrono::milliseconds;
const char kDbPath[] = "leaderboard.db";
const char kNormalFont[] = "Arial";
double speed = 1.0;
MyApp::MyApp() : engine{},
                   leaderboard{cinder::app::getAssetPath(kDbPath).string()} {}

void MyApp::setup() {
  cinder::gl::color(0, 0, 1);
  //engine.PlaceBlockOnLowestSurface();
  engine.AddInitialFloors();
  //engine.GetOpenFloor().pop_back();
  //engine.PlaceBlockOnLowestSurface();
  engine.PlaceBlockOnLowestSurface();
  engine.SetGameModeEasy();
}

void MyApp::update() {
  //if (engine.GetOpenFloor().empty()) {
    //leaderboard.InsertScoreToLeaderboard(engine.GetScore());
  //}

  if (engine.GetFloors().size() <= engine.GetFloorGeneratorOffset()) {
    //engine.GetOpenFloor().insert(engine.GetOpenFloor().begin(), 5);
    engine.AddRandomFloor();
  }
  //speed += 0.001;
}

void MyApp::draw() {
  if (engine.IsGameOver()) {
    DrawGameOver();
    return;
  }
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
double height = 0;

void MyApp::DrawFloors() {

  auto current_time = std::chrono::system_clock::now();
  double current_delay =
      duration_cast<milliseconds>(current_time - starting_time).count() / 1000.0;
  if (current_delay > 10) {
    height+= speed;
    //engine.GetBlock().SetYBlock(engine.GetBlock().GetYBlock() - 1);
    cinder::gl::color(0, 1, 0);

    engine.GetBlock().SetYPosition(engine.GetBlock().GetYPosition() - (speed/40.0));
  }

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

template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawGameOver() {
  cinder::gl::clear(Color(0.8, 0, 0));
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  PrintText("Game Over", Color::black(), size, center);
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
