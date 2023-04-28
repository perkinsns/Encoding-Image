#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

#include "constants.h"
#include "ColorClass.h"
#include "RowColumnClass.h"

class ColorImageClass 
{
private:
  int rows;
  int columns; 
  ColorClass** pixelMatrix;

public:
  ColorImageClass(int rows, int columns);
  ~ColorImageClass();
  void initializeTo(ColorClass &inColor);
  bool setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);
  bool getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);
};

#endif
