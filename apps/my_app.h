// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/engine.h>
#include <mylibrary/scores.h>

#include <chrono>

using std::chrono::system_clock;

const int kBlockSize = 40;
const int kFloorHeight = 40;
const char kDbPath[] = "leaderboard.db";
const char kNormalFont[] = "Arial";
const double kEasy = 1.0;
const double kMedium = 1.5;
const double kHard = 2.0;
const int kRed = 0;
const int kGreen = 1;
const int kBlue = 2;
const vector<int> cosmetic_floors{19, 6, 13, 3, 1};

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;

  /**
   * Draws the background for the game
   */
  void DrawBackground();

  /**
   * Draws the Block the user controls
   */
  void DrawBlock();

  /**
   * Draws all the floors in present in the engine
   */
  void DrawFloors();

  /**
   * Draws the Game over screen
   */
  void DrawGameOver();

  /**
   * Draws the welcome screen
   */
  void DrawWelcomeScreen();

  /**
   * Prints the game mode as text
   */
  void PrintGameMode();

  /**
   * Prints the user's score as text
   */
  void PrintPlayerScore();

  /**
   * Prints the Top scores in the leaderboard as text
   */
  void PrintTopScores();

 private:
  SQL_Leaderboard leaderboard;
  Engine engine;
  std::chrono::time_point<system_clock> game_starting_time;
  std::chrono::time_point<system_clock> starting_time;

  double height_offset;
  bool speed_can_increase;
  bool added_score_to_table;
  bool on_welcome_screen;
  bool game_started;
  bool timers_have_been_set;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
