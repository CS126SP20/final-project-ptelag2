//
// Created by Praval Telagi on 4/19/20.
//

#include <mylibrary/engine.h>

namespace myapp {

Block& Engine::GetBlock() {
  return (Block&)block;
}

int Engine::GetScore() {
  return score;
}

void Engine::BlockCanMoveDown() {
  if (floors.back().GetOpenSpot() == block.GetXPosition()) {
    //Move the block down by kBlockYAxisMovement
    block.SetYPosition(block.GetYPosition() + kBlockYAxisMovement);
    //Remove that floor from the list
    floors.pop_back();
    //If a block goes through the floor add a point to the score
    score++;
  }
}

void Engine::PlaceBlockOnLowestSurface() {
  //block.SetYPosition((kNumOfStartingFloors - floors.size()) * kBlockYAxisMovement);
  block.SetYPosition((kFloorYAxisOffset * kMaxFloorsOnScreen)
                          - (kFloorYAxisOffset * floors.size()));
}

void Engine::AddRandomFloor() {
  Floor new_floor;
  //Sets the height of the new floor to 2 units lower than the current lowest
  new_floor.SetHeight(floors.front().GetHeight() + kFloorYAxisOffset);
  floors.insert(floors.begin(), new_floor);
}

void Engine::AddRandomInitialFloors() {
  for (size_t i = 0; i < kNumOfStartingFloors; i++) {
    Floor new_floor;
    new_floor.SetHeight((kFloorYAxisOffset * kMaxFloorsOnScreen)
                                     - (kFloorYAxisOffset * i) - 1);
    floors.push_back(new_floor);
  }
}

vector<Floor>& Engine::GetFloors() {
  return floors;
}

bool Engine::IsGameOver() {
  //If Block crosses the top of the screen
  return block.GetYPosition() < 0;
}

double GameSpeedToGameMode(double game_speed) {
  //Take the game_speed and converts it to an index that corresponds to a specific
  //Game mode
  return (2 * game_speed - 2);
}

int GameSpeedToFloorGeneratorOffset(double game_speed) {
  //Takes the game_speed and converts it to an index that corresponds to a specific
  //game mode's floor generator offset
  return kMaxFloorsOnScreen - (kMaxFloorsOnScreen * (game_speed - 1));
}

void Engine::SetGameMode(double game_speed) {
  speed = game_speed;
  floor_generator_offset = GameSpeedToFloorGeneratorOffset(game_speed);
  game_mode = game_modes[GameSpeedToGameMode(game_speed)];
}

double Engine::GetSpeed() {
  return speed;
}

int Engine::GetFloorGeneratorOffset() {
  return floor_generator_offset;
}

void Engine::MoveBlockUp() {
  block.SetYPosition(block.GetYPosition() - (speed / kHeightOfBlock));
}

void Engine::IncreaseSpeed(double percent) {
  speed = (speed * (1 + percent));
}

string Engine::GetGameMode() {
  return game_mode;
}

void Engine::ForceGameOver() {
  block.SetYPosition(kGameOverHeight);
}

}