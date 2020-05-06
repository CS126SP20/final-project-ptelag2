//
// Created by Praval Telagi on 4/21/20.
//

#ifndef FINALPROJECT_BLOCK_H
#define FINALPROJECT_BLOCK_H

const int kLeftWallPosition = 0;
const int kRightWallPosition = 19;

namespace myapp {

class Block {

 public:

  /**
   * Gets the X position of the block
   * @return X position of the block as a double
   */
  double GetXPosition() const;

  /**
   * Gets the Y position of the block
   * @return Y position of the block as a double
   */
  double GetYPosition() const;

  /**
   * Sets the X position of the block to the inputted value
   * @param x Desired X position of the block
   */
  void SetXPosition(double x);

  /**
   * Sets the Y Position of the block to the inputted value
   * @param y Desired Y position of the block
   */
  void SetYPosition(double y);

  /**
   * Moves the block left by 1 unit
   */
  void MoveLeft();

  /**
   * Moves the block right by 1 unit
   */
  void MoveRight();

 private:
  double x_position;
  double y_position;
};

}



#endif  // FINALPROJECT_BLOCK_H
