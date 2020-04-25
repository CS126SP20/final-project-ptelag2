//
// Created by Praval Telagi on 4/18/20.
//

#ifndef FINALPROJECT_FLOOR_H
#define FINALPROJECT_FLOOR_H



namespace myapp {

class Floor {

 public:
  Floor();
  //bool GetFloor();
  double GetHeight();
  int GetOpenSpot();
  void SetHeight(double new_height);

 private:
  int open_spot;
  double height;


};

}



#endif  // FINALPROJECT_FLOOR_H
