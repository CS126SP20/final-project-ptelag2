// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>


namespace myapp {

using cinder::app::KeyEvent;
using cinder::Rectf;
using cinder::Color;

MyApp::MyApp() : engine{} { }

void MyApp::setup() {
  cinder::gl::color(0, 0, 0);
}

void MyApp::update() { }

void MyApp::draw() {
  DrawBackground();
  cinder::gl::color(0, 1, 0);
  cinder::gl::drawSolidRect(Rectf(block_size * engine.GetXBlock(),
                                  block_size * engine.GetYBlock(),
                                  block_size * engine.GetXBlock()
                                  + block_size,
                                  block_size * engine.GetYBlock()
                                  + block_size));
}

void MyApp::DrawBackground() {
  cinder::gl::clear(Color(0, 0, 0));
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_LEFT: {
      engine.SetXBlock(engine.GetXBlock() - 1);
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      engine.SetXBlock(engine.GetXBlock() + 1);
      break;
    }
  }
}

}  // namespace myapp
