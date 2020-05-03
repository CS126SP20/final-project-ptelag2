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
const double kEasy = 1.0;
const double kMedium = 1.5;
const double kHard = 2.0;

double RGB_colors[]{1, 1, 0};

MyApp::MyApp() : engine{},
                   leaderboard{cinder::app::getAssetPath(kDbPath).string()} {}

void MyApp::setup() {
  engine.AddInitialFloors();
  engine.PlaceBlockOnLowestSurface();
  engine.SetGameMode(kMedium);
}

auto game_starting_time = std::chrono::system_clock::now();
auto starting_time = std::chrono::system_clock::now();
double height_offset = 0;
bool speed_can_increase = false;
bool added_score_to_table = false;
void MyApp::update() {

  auto current_time = std::chrono::system_clock::now();
  double animation_start_delay =
      duration_cast<milliseconds>(current_time - game_starting_time).count() / 1000.0;

  double speed_increase_delay =
      duration_cast<milliseconds>(current_time - starting_time).count() / 1000.0;

  if (speed_increase_delay > 5 && speed_can_increase) {
    engine.IncreaseSpeed(0.05);
    starting_time = std::chrono::system_clock::now();
    RGB_colors[0] = (float)rand() / (RAND_MAX);
    RGB_colors[1] = (float)rand() / (RAND_MAX);
    RGB_colors[2] = (float)rand() / (RAND_MAX);
  }

  if (animation_start_delay > 10) {
    height_offset+= engine.GetSpeed();
    engine.MoveBlockUp();
    if (!speed_can_increase) {
      starting_time = std::chrono::system_clock::now();
    }
    speed_can_increase = true;
  }



  if (engine.GetFloors().size() <= engine.GetFloorGeneratorOffset()) {
    engine.AddRandomFloor();
  }

  if (engine.IsGameOver() && !added_score_to_table) {
    leaderboard.InsertScoreToLeaderboard(engine.GetScore(), engine.GetGameMode());
    added_score_to_table = true;
  }
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

void MyApp::DrawFloors() {
  cinder::gl::color(RGB_colors[0], RGB_colors[1], RGB_colors[2]);
  for (int i = 0; i < engine.GetFloors().size(); i++) {
    cinder::gl::drawSolidRect(Rectf(0,
                                    engine.GetFloors()[i].GetHeight() * 40 - height_offset,
                                    (engine.GetFloors()[i].GetOpenSpot()) * kHeightOfFloor,
                                    engine.GetFloors()[i].GetHeight() * 40 + kHeightOfFloor - height_offset));

    cinder::gl::drawSolidRect(Rectf((engine.GetFloors()[i].GetOpenSpot() + 1) * kHeightOfFloor,
                                    engine.GetFloors()[i].GetHeight() * 40 - height_offset,
                                    800,
                                    engine.GetFloors()[i].GetHeight() * 40 + kHeightOfFloor - height_offset));
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
  string player_score = "Your Score: ";
  player_score.append(std::to_string(engine.GetScore()));
  string game_mode = "Your Game Mode: ";
  game_mode.append(engine.GetGameMode());
  PrintText(game_mode, Color::black(), size, {center.x, center.y + 50});
  PrintText(player_score, Color::black(), size, {center.x, center.y + 100});
  vector<int> top_scores = leaderboard.GetHighestScores(3, engine.GetGameMode());
  int row = 2;
  for (const int score : top_scores) {
    std::stringstream ss;
    ss << score;
    PrintText(ss.str(), Color::black(), size, {center.x, center.y + (++row * 50)});
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_a:
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
