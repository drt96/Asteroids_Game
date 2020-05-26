/***********************************************************************
* Header File:
*    FUELCELL : Can refuel anything that has fuel
* Author:
*    Daniel R. Thomson
* Summary:
*    When you fly into the fuelcell you get 150 units of extra fuel.
************************************************************************/

#include "fuelcell.h"

/*********************************************
* Fuelcell: DEFUALT CONSTRUCTOR 
*********************************************/
Fuelcell :: Fuelcell(): taken(false)
{
  pos.setX(90);
  pos.setY(100);
}

/*********************************************
* Fuelcell: NON-DEFUALT CONSTRUCTOR 
*********************************************/
Fuelcell :: Fuelcell(Point p): taken(false)
{
  pos.setX(p.getX());
  pos.setY(p.getY());
}

/*********************************************
* Fuelcell: isTaken
* Checks to see if the cell has been touched
*********************************************/
bool Fuelcell :: isTaken()
{
  return taken;
}

/*********************************************
* Fuelcell: Draw
* Draws the text based cell.
*********************************************/
void Fuelcell :: draw()
{  
  drawText(pos, "REFUEL");
}


