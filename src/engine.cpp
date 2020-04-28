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

vector<int> Engine::GetOpenFloor() {
  return open_floor;
}

void Engine::PlaceBlockOnLowestSurface() {
  block.SetYPosition((10 - floors.size()) * 2);
}
void Engine::AddRandomFloor() {
  Floor new_floor;
  new_floor.SetHeight(floors.front().GetHeight() + 2);
  floors.insert(floors.begin(), new_floor);
}
void Engine::AddInitialFloors() {
  for (int i = 0; i < 10; i++) {
    Floor new_floor;
    new_floor.SetHeight(((2 * i) + 1));
    floors.insert(floors.begin(), new_floor);
  }
}
vector<Floor>& Engine::GetFloors() {
  return floors;
}

bool Engine::IsGameOver() {
  if (block.GetYPosition() < 0) {
    return true;
  }
  return false;
}

}