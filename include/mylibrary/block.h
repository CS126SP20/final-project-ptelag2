//
// Created by Praval Telagi on 4/21/20.
//

#ifndef FINALPROJECT_BLOCK_H
#define FINALPROJECT_BLOCK_H

namespace myapp {
class Block {
 public:
  double GetXPosition();
  double GetYPosition();
  void SetXPosition(double x);
  void SetYPosition(double y);
  void MoveLeft();
  void MoveRight();

 private:
  double x_position;
  double y_position;
};
}



#endif  // FINALPROJECT_BLOCK_H
