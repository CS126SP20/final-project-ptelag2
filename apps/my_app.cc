// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <chrono>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::app::MouseEvent;
using cinder::Rectf;
using cinder::Color;
using cinder::ColorA;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;
using cinder::TextBox;
using std::chrono::milliseconds;

double RGB_colors[]{1, 1, 0};

MyApp::MyApp() : engine{},
                   leaderboard{cinder::app::getAssetPath(kDbPath).string()} {}

void MyApp::setup() {
  //Set integer and boolean variables
  height_offset = 0;
  speed_can_increase = false;
  added_score_to_table = false;
  on_welcome_screen = true;
  game_started = false;
  timers_have_been_set = false;

  //Set Timers
  game_starting_time = std::chrono::system_clock::now();
  starting_time = std::chrono::system_clock::now();

  //Set engine to correct settings
  engine.GetBlock().SetXPosition(0);
  engine.GetBlock().SetYPosition(0);
  engine.AddRandomInitialFloors();
  engine.PlaceBlockOnLowestSurface();
}

void MyApp::update() {
  if (game_started) {

    if (!timers_have_been_set) {
      //Set timers to proper time
      game_starting_time = std::chrono::system_clock::now();
      starting_time = std::chrono::system_clock::now();
      timers_have_been_set = true;
    }


    auto current_time = std::chrono::system_clock::now();
    double time_since_start =
        duration_cast<milliseconds>(current_time - game_starting_time).count() /
        1000.0;

    double speed_increase_delay =
        duration_cast<milliseconds>(current_time - starting_time).count() /
        1000.0;

    //Increases the speed and changes the color of the floor
    if (speed_increase_delay > kSpeedChangeDelaySeconds && speed_can_increase) {
      engine.IncreaseSpeed(kAnimationSpeed);
      starting_time = std::chrono::system_clock::now();
      RGB_colors[kRed] = (float)rand() / (RAND_MAX);
      RGB_colors[kGreen] = (float)rand() / (RAND_MAX);
      RGB_colors[kBlue] = (float)rand() / (RAND_MAX);
    }

    //Starts the animation after a set amount of time since the game start
    if (time_since_start > kAnimationStartDelaySeconds) {
      height_offset += engine.GetSpeed();
      engine.MoveBlockUp();
      if (!speed_can_increase) {
        starting_time = std::chrono::system_clock::now();
      }
      speed_can_increase = true;
    }
  }

  //Adds a new floor to the game
  if (engine.GetFloors().size() <= engine.GetFloorGeneratorOffset()) {
    engine.AddRandomFloor();
  }

  //Adds score to appropriate leaderboard
  if (engine.IsGameOver() && !added_score_to_table) {
    leaderboard.InsertScoreToLeaderboard(engine.GetScore(), engine.GetGameMode());
    added_score_to_table = true;
  }
}

void MyApp::draw() {
  if (on_welcome_screen) {
    DrawWelcomeScreen();
    return;
  } else if (engine.IsGameOver()) {
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
  cinder::gl::color(RGB_colors[kRed], RGB_colors[kGreen], RGB_colors[kBlue]);
  for (int i = 0; i < engine.GetFloors().size(); i++) {
    cinder::gl::drawSolidRect(Rectf(0,
                                    engine.GetFloors()[i].GetHeight() * kHeightOfFloor - height_offset,
                                    (engine.GetFloors()[i].GetOpenSpot()) * kHeightOfFloor,
                                    engine.GetFloors()[i].GetHeight() * kHeightOfFloor
                                          + kHeightOfFloor - height_offset));

    cinder::gl::drawSolidRect(Rectf((engine.GetFloors()[i].GetOpenSpot() + 1) * kHeightOfFloor,
                                    engine.GetFloors()[i].GetHeight() * kHeightOfFloor - height_offset,
                                    800,
                                    engine.GetFloors()[i].GetHeight() * kHeightOfFloor
                                          + kHeightOfFloor - height_offset));
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

void MyApp::DrawWelcomeScreen() {
  cinder::gl::clear(Color(0, 0, 0));
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  PrintText("Escape the Ceiling", Color::white(), size, {center.x, center.y - 250});
  PrintText("Choose Mode: ", Color::white(), size, {center.x, center.y - 150});
  PrintText("Easy", Color::white(), size, {center.x, center.y - 100});
  PrintText("Medium", Color::white(), size, {center.x, center.y - 50});
  PrintText("Hard", Color::white(), size, {center.x, center.y});

  cinder::gl::color(RGB_colors[kRed], RGB_colors[kGreen], RGB_colors[kBlue]);
  for (int i = 0; i < cosmetic_floors.size(); i++) {
    cinder::gl::drawSolidRect(Rectf(0,
                                    800 - (kFloorYAxisOffset * i * kFloorHeight),
                                    (cosmetic_floors[i]) * kHeightOfFloor,
                                    800 - (kFloorYAxisOffset * i * kFloorHeight) - kFloorHeight));

    cinder::gl::drawSolidRect(Rectf((cosmetic_floors[i] + 1) * kHeightOfFloor,
                                    800 - (kFloorYAxisOffset * i * kFloorHeight),
                                    800,
                                    800 - (kFloorYAxisOffset * i * kFloorHeight) - kFloorHeight));
  }

  cinder::gl::color(0, 1, 0);
  cinder::gl::drawSolidRect(Rectf(kBlockSize * kBlockYAxisMovement,
                                  kBlockSize * 10,
                                  kBlockSize * kBlockYAxisMovement
                                  + kBlockSize,
                                  kBlockSize * 10
                                  + kBlockSize));


}

void MyApp::DrawGameOver() {
  cinder::gl::clear(Color(0.8, 0, 0));
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  PrintText("Game Over", Color::black(), size, {center.x, center.y - 50});

  PrintGameMode();
  PrintPlayerScore();
  PrintTopScores();
}

void MyApp::PrintGameMode() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};

  string display_game_mode = "Your Game Mode: ";
  string game_mode = engine.GetGameMode();
  game_mode[0] = toupper(game_mode[0]);
  display_game_mode.append(game_mode);

  PrintText(display_game_mode, Color::black(), size, {center.x, center.y + 50});
}

void MyApp::PrintPlayerScore() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};

  string player_score = "Your Score: ";
  player_score.append(std::to_string(engine.GetScore()));
  PrintText(player_score, Color::black(), size, {center.x, center.y + 100});
}

void MyApp::PrintTopScores() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  PrintText("Top Scores:", Color::black(), size, {center.x, center.y + 150});
  vector<int> top_scores = leaderboard.GetHighestScores(3, engine.GetGameMode());
  int row = 3;
  int score_rank = 1;
  for (const int score : top_scores) {
    std::stringstream ss;
    ss << score_rank++ << ". " << score;
    PrintText(ss.str(), Color::black(), size, {center.x, center.y + (++row * 50)});
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_a:
    case KeyEvent::KEY_LEFT: {
      engine.GetBlock().MoveLeft();
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_d:
    case KeyEvent::KEY_RIGHT: {
      engine.GetBlock().MoveRight();
      break;
    }
    case KeyEvent::KEY_ESCAPE: {
      engine.ForceGameOver();
      break;
    }
  }
}

void MyApp::mouseDown(MouseEvent event) {
  if (event.isLeft() && on_welcome_screen) {
    if (event.getX() >= 345 && event.getX() <= 450
          && event.getY() >= 280 && event.getY() <= 415) {
      if (event.getY() >= 280 && event.getY() <= 320) {
        engine.SetGameMode(kEasy);
      } else if (event.getY() >= 320 && event.getY() <= 375) {
        engine.SetGameMode(kMedium);
      } else if (event.getY() >= 375 && event.getY() <= 415) {
        engine.SetGameMode(kHard);
      }
      on_welcome_screen = false;
      game_started = true;
    }
  }
}


}  // namespace myapp
