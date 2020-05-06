// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <mylibrary/block.h>
#include <mylibrary/engine.h>

using namespace myapp;

TEST_CASE("Block X Axis Movement", "[block]") {
  SECTION("Block moves left on MoveLeft") {
    Block block;
    block.SetXPosition(5);
    block.MoveLeft();
    REQUIRE(block.GetXPosition() == 4);
  }

  SECTION("Block moves right on MoveRight") {
    Block block;
    block.SetXPosition(9);
    block.MoveRight();
    REQUIRE(block.GetXPosition() == 10);
  }

  SECTION("Block doesn't move left against the left wall") {
    Block block;
    block.SetXPosition(0);
    block.MoveLeft();
    REQUIRE(block.GetXPosition() == 0);
  }

  SECTION("Block doesn't move right against the right wall") {
    Block block;
    block.SetXPosition(19);
    block.MoveRight();
    REQUIRE(block.GetXPosition() == 19);
  }
}

TEST_CASE("Block Y Axis Movement", "[block]") {
  SECTION("Block Moves Down When on an open spot") {
    Engine engine;
    engine.AddRandomInitialFloors();
    int block_current_y_position = engine.GetBlock().GetYPosition();
    int open_spot = engine.GetFloors().back().GetOpenSpot();
    engine.GetBlock().SetXPosition(open_spot);
    engine.BlockCanMoveDown();
    REQUIRE(engine.GetBlock().GetYPosition() == block_current_y_position + 2);
  }

  SECTION("Block Moves Up By the set speed") {
    Engine engine;
    double previous_y = engine.GetBlock().GetYPosition();
    engine.SetGameMode(1);
    engine.MoveBlockUp();
    double current_y = engine.GetBlock().GetYPosition();
    REQUIRE(current_y == previous_y - 0.025);
  }
}

TEST_CASE("Engine Generates Ten Floors At Start of Game", "[engine]") {
  Engine engine;
  engine.AddRandomInitialFloors();
  REQUIRE(engine.GetFloors().size() == 10);
}

TEST_CASE("Floor Open Spot is between 0 - 19", "[floor]") {
  bool number_out_of_range = false;
  for (int i = 0; i < 20; i++) {
    Floor floor;
    if (floor.GetOpenSpot() < 0 || floor.GetOpenSpot() > 19) {
      number_out_of_range = true;
      break;
    }
  }
  REQUIRE(!number_out_of_range);
}

TEST_CASE("Adds One Floor to Game", "[floor]") {
  Engine engine;
  engine.AddRandomInitialFloors();
  engine.AddRandomFloor();
  REQUIRE(engine.GetFloors().size() == 11);
}

TEST_CASE("Game Over", "[engine]") {
  SECTION("Game is Not over at the beginning of a game") {
    Engine engine;
    REQUIRE(!engine.IsGameOver());
  }

  SECTION("Game is Over when Block Y Position Goes under 0") {
    Engine engine;
    engine.MoveBlockUp();
    REQUIRE(engine.IsGameOver());
  }
}

TEST_CASE("Game Speed sets correct game mode", "[engine]") {
  SECTION("Easy Mode") {
    Engine engine;
    engine.SetGameMode(1);
    REQUIRE(engine.GetGameMode() == "easy");
  }

  SECTION("Medium Mode") {
    Engine engine;
    engine.SetGameMode(1.5);
    REQUIRE(engine.GetGameMode() == "medium");
  }

  SECTION("Hard Mode") {
    Engine engine;
    engine.SetGameMode(2);
    REQUIRE(engine.GetGameMode() == "hard");
  }
}

TEST_CASE("Force Quitting Causes Game to be Over", "engine") {
  Engine engine;
  REQUIRE(!engine.IsGameOver());
  engine.ForceGameOver();
  REQUIRE(engine.IsGameOver());
}

TEST_CASE("Speed Increase", "[engine]") {
  SECTION("Speed Increases by the inputted percent for easy game mode") {
    Engine engine;
    engine.SetGameMode(1);
    engine.IncreaseSpeed(0.05);
    REQUIRE(engine.GetSpeed() == 1.05);
  }

  SECTION("Speed Increases by the inputted percent for medium game mode") {
    Engine engine;
    engine.SetGameMode(1.5);
    engine.IncreaseSpeed(0.01);
    REQUIRE(engine.GetSpeed() == 1.5150000000000001);
  }

  SECTION("Speed Increases by the inputted percent for hard game mode") {
    Engine engine;
    engine.SetGameMode(2);
    engine.IncreaseSpeed(0.33);
    REQUIRE(engine.GetSpeed() == 2.66);
  }
}

TEST_CASE("Floor Generator Offset", "[engine]") {
  SECTION("Calculates correct floor generator offset for easy mode") {
    Engine engine;
    engine.SetGameMode(1);
    REQUIRE(engine.GetFloorGeneratorOffset() == 10);
  }

  SECTION("Calculates correct floor generator offset for medium mode") {
    Engine engine;
    engine.SetGameMode(1.5);
    REQUIRE(engine.GetFloorGeneratorOffset() == 5);
  }

  SECTION("Calculates correct floor generator offset for hard mode") {
    Engine engine;
    engine.SetGameMode(2);
    REQUIRE(engine.GetFloorGeneratorOffset() == 0);
  }
}
