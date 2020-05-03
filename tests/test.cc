// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/block.h>

using namespace myapp;

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

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