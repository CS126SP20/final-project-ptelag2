//
// Created by Praval Telagi on 4/18/20.
//

#ifndef FINALPROJECT_FLOOR_H
#define FINALPROJECT_FLOOR_H

const int kLengthOfFloor = 20;

namespace myapp {

class Floor {

 public:
  /**
   * Default constructor for a Floor;
   * Randomly sets the open spot location
   */
  Floor();

  /**
   * Gets the current height of the floor
   * @return Height as a double
   */
  double GetHeight() const;

  /**
   * Gets the spot on the floor where there is an open spot
   * @return Open Spot as an integer
   */
  int GetOpenSpot() const;

  /**
   * Sets the height of a floor to the inputted value
   * @param new_height Desired height of floor
   */
  void SetHeight(double new_height);

 private:
  int open_spot;
  double height;
};

}



#endif  // FINALPROJECT_FLOOR_H
