#include<iostream>
using namespace std;

#include "ColorImageClass.h"
#include "constants.h"

ColorImageClass::ColorImageClass(int inRows, int inColumns)
{
  rows = inRows;
  columns = inColumns;
  pixelMatrix = new ColorClass* [rows];
  for (int i = 0; i < rows; i++)
  {
  pixelMatrix[i] = new ColorClass[columns];
  }
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      pixelMatrix[i][j].setToBlack();
    }
  }
}

ColorImageClass::~ColorImageClass()
{
  for (int i = 0; i < rows; i++)
  {
    delete[] pixelMatrix[i];
  }
  delete [] pixelMatrix;
}

bool ColorImageClass::setColorAtLocation(RowColumnClass &inRowCol, 
                                         ColorClass &inColor)
{
  bool returnVal = false;
  int callRow = inRowCol.getRow();
  int callCol = inRowCol.getCol();
  if (callRow < rows && callRow >= MIN_ROW &&
      callCol < columns && callCol >= MIN_ROW)
  {
    pixelMatrix[inRowCol.getRow()][inRowCol.getCol()].setTo(inColor);
    returnVal = true;
  }
  return (returnVal);
}

bool ColorImageClass::getColorAtLocation(RowColumnClass &inRowCol, 
                                         ColorClass &outColor)
{
  bool returnVal = false;
  int callRow = inRowCol.getRow();
  int callCol = inRowCol.getCol();
  if (callRow < rows && callRow >= MIN_ROW &&
      callCol < columns && callCol >= MIN_ROW)
  {
    outColor.setTo(pixelMatrix[inRowCol.getRow()][inRowCol.getCol()]);
    returnVal = true;
  }
  return (returnVal);
}

