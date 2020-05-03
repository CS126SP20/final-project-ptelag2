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
    block.SetYPosition(block.GetYPosition() + 2);
    floors.pop_back();
    score++;
  }
}

void Engine::PlaceBlockOnLowestSurface() {
  block.SetYPosition((kNumOfStartingFloors - floors.size()) * 2);
}

void Engine::AddRandomFloor() {
  Floor new_floor;
  new_floor.SetHeight(floors.front().GetHeight() + 2);
  floors.insert(floors.begin(), new_floor);
}

void Engine::AddInitialFloors() {
  for (size_t i = 0; i < kNumOfStartingFloors; i++) {
    Floor new_floor;
    new_floor.SetHeight(((2 * i) + 1));
    floors.insert(floors.begin(), new_floor);
  }
}

vector<Floor>& Engine::GetFloors() {
  return floors;
}

bool Engine::IsGameOver() {
  return block.GetYPosition() < 0;
}

double GameSpeedToGameMode(double game_speed) {
  return (2 * game_speed - 2);
}

void Engine::SetGameMode(double game_speed) {
  speed = game_speed;
  floor_generator_offset = kNumOfStartingFloors - (kNumOfStartingFloors * (game_speed - 1));
  game_mode = game_modes[GameSpeedToGameMode(game_speed)];
}

double Engine::GetSpeed() {
  return speed;
}

int Engine::GetFloorGeneratorOffset() {
  return floor_generator_offset;
}

void Engine::MoveBlockUp() {
  block.SetYPosition(block.GetYPosition() - (speed / kHeightOfFloor));
}

void Engine::IncreaseSpeed(double percent) {
  speed = (speed * (1 + percent));
}

string Engine::GetGameMode() {
  return game_mode;
}

}