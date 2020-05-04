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
const int kHeightOfBlock = 40;
const int kHeightOfFloor = 40;
const int kBlockYAxisMovement = 2;
const int kGameOverHeight = -1;

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
  /**
   * Gets the Vector that holds each floor in the game
   * @return Vector of Floor objects
   */
  vector<Floor>& GetFloors();

  /**
   * Gets the current score of the game
   * @return score as an integer
   */
  int GetScore();

  /**
   * Gets the user controllable block
   * @return block as a reference to block
   */
  Block& GetBlock();

  /**
   * Determines if the block can move down through a hole in the floor
   * Moves the block down if it can move down
   */
  void BlockCanMoveDown();

  /**
   * Called at the beginning of the game to place the block on the lowest
   * surface if floors do not reach the top of the screen
   */
  void PlaceBlockOnLowestSurface();

  /**
   * Adds a random floor to the vector of floors
   */
  void AddRandomFloor();

  /**
   * Adds the initial random floors to the game at the start of a game
   */
  void AddRandomInitialFloors();

  /**
   * Determines if the game is over
   * @return True if game is over; False if otherwise
   */
  bool IsGameOver();

  /**
   * Sets the game mode from the game speed
   * @param game_speed Starting speed of the blocks when they begin to move up
   *                   the screen
   */
  void SetGameMode(double game_speed);

  /**
   * Gets the current speed of the blocks
   * @return speed as a double
   */
  double GetSpeed();

  /**
   * Determines the minimum amount of floors that should exist when
   * generating a new floor
   * @return floor generator offset as an integer
   */
  int GetFloorGeneratorOffset();

  /**
   * Moves the block up at the current speed
   */
  void MoveBlockUp();

  /**
   * Increases the speed by the inputted percent
   * @param percent decimal percent of how much to increase the speed by
   */
  void IncreaseSpeed(double percent);

  /**
   * Gets the game mode
   * @return game mode as a string
   */
  string GetGameMode();

  /**
   * Forces the game to finish
   */
  void ForceGameOver();
};

}







#endif  // FINALPROJECT_ENGINE_H
