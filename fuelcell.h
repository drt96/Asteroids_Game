/***********************************************************************
* Header File:
*    FUELCELL : Can refuel anything with fuel
* Author:
*    Daniel R. Thomson
* Summary:
*    When you fly into the fuelcell you get 150 units of extra fuel.
************************************************************************/

#ifndef FUELCELL_H
#define FUELCELL_H

#include "point.h"
#include "uiDraw.h"

/*********************************************
* Fuelcell
* Get yourself some extra juice, you deserve it.
*********************************************/
class Fuelcell
{
 public:

  Fuelcell();  
  Fuelcell(Point p); 
  
  ~Fuelcell() { }

  //getters
  Point getPoint() const { return pos; }
  bool isTaken();
  
  //setters
  void setTaken(bool taken)   { this->taken = taken; }

  //methods
  void draw();

 private: 
  
  Point pos;
  bool taken;
};

#endif //fuelcell.h
