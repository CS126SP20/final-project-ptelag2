//
// Created by Praval Telagi on 4/21/20.
//

#ifndef FINALPROJECT_BLOCK_H
#define FINALPROJECT_BLOCK_H

namespace myapp {
class Block {
 public:
  int GetXBlock();
  int GetYBlock();
  void SetXBlock(int x);
  void SetYBlock(int y);
  void MoveLeft();
  void MoveRight();

 private:
  int x_block;
  int y_block;
};
}



#endif  // FINALPROJECT_BLOCK_H
