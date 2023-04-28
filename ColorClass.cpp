#include "ColorClass.h"
#include <iostream>

using namespace std;
#include "constants.h"

ColorClass::ColorClass ()
{
  setToWhite();
}

ColorClass::ColorClass (int inRed, int inGreen, int inBlue)
{
  clipIt(inRed, inGreen, inBlue);
  valRed = inRed;
  valGreen = inGreen;
  valBlue = inBlue;
}

void ColorClass::clipIt(int &inRed, int &inGreen, int &inBlue)
{ 
  while (inRed > COLOR_MAX || inRed < COLOR_MIN ||
         inGreen > COLOR_MAX || inGreen < COLOR_MIN ||
         inBlue > COLOR_MAX || inBlue < COLOR_MIN)
  {
    if (inRed > COLOR_MAX)
    { 
      inRed = COLOR_MAX;
    }
    else if (inRed < COLOR_MIN)
    { 
      inRed = COLOR_MIN;
    }
    else if (inGreen > COLOR_MAX)
    { 
      inGreen = COLOR_MAX;
    }
    else if (inGreen < COLOR_MIN)
    { 
      inGreen = COLOR_MIN;
    }
    else if (inBlue > COLOR_MAX)
    { 
      inBlue = COLOR_MAX;
    }
    else if (inBlue < COLOR_MIN)
    { 
      inBlue = COLOR_MIN;
    }
  }
}

void ColorClass::setToBlack()
{
  valRed = COLOR_MIN;
  valGreen = COLOR_MIN;
  valBlue = COLOR_MIN;
}

void ColorClass::setToRed()
{
  valRed = COLOR_MAX;
  valGreen = COLOR_MIN;
  valBlue = COLOR_MIN;
}

void ColorClass::setToGreen()
{
  valRed = COLOR_MIN;
  valGreen = COLOR_MAX;
  valBlue = COLOR_MIN;
}

void ColorClass::setToBlue()
{
  valRed = COLOR_MIN;
  valGreen = COLOR_MIN;
  valBlue = COLOR_MAX;
}

void ColorClass::setToWhite()
{
  valRed = COLOR_MAX;
  valGreen = COLOR_MAX;
  valBlue = COLOR_MAX;
}

void ColorClass::setToYellow()
{
  valRed = COLOR_MAX;
  valGreen = COLOR_MAX;
  valBlue = COLOR_MIN;
}

void ColorClass::setToMagenta()
{
  valRed = COLOR_MAX;
  valGreen = COLOR_MIN;
  valBlue = COLOR_MAX;
}

void ColorClass::setToCyan()
{
  valRed = COLOR_MIN;
  valGreen = COLOR_MAX;
  valBlue = COLOR_MAX;
}


bool ColorClass::setTo(int inRed, int inGreen, int inBlue)
{
  bool returnVal = false;
  if (COLOR_MAX < inRed || COLOR_MIN > inRed ||
      COLOR_MAX < inGreen || COLOR_MIN > inGreen ||
      COLOR_MAX < inBlue || COLOR_MIN > inBlue)
  {
    clipIt(inRed, inGreen, inBlue); 
    returnVal = true;
  }
  valRed = inRed;
  valGreen = inGreen;
  valBlue = inBlue;
  return (returnVal);
}

bool ColorClass::setTo(ColorClass &inColor)
{
  clipIt(inColor.valRed, inColor.valGreen, inColor.valBlue);
  valRed = inColor.valRed;
  valGreen = inColor.valGreen; 
  valBlue = inColor.valBlue;
  return (0);
}

bool ColorClass::addColor(ColorClass &rhs)
{
  valRed = valRed + rhs.valRed;
  valGreen = valGreen + rhs.valGreen;
  valBlue = valBlue + rhs.valBlue;
  clipIt(valRed,  valGreen, valBlue);
  return (0);
}

bool ColorClass::subractColor(ColorClass &rhs)
{
  valRed = valRed - rhs.valRed;
  valGreen = valGreen - rhs.valGreen;
  valBlue = valBlue - rhs.valBlue;
  clipIt(valRed, valGreen, valBlue);
  return (0);
}

bool ColorClass::adjustBrightness(double adjFactor)
{
  valRed = valRed * adjFactor;
  valBlue = valBlue * adjFactor;
  valGreen = valGreen * adjFactor;
  clipIt(valRed, valGreen, valBlue);
  return (0);
}

void ColorClass::printComponentValues ()
{
  cout << "R: " << valRed << " G: " << valGreen << " B: " << valBlue;
}

string ColorClass::getPixelRGB()
{
  stringstream colorHolder;
  string returnColor;
  colorHolder << valRed << " " << valGreen << " " << valBlue;
  returnColor = colorHolder.str();
  return (returnColor);
}

void ColorClass::decode()
{
  int redLeftOver = valRed%2;
  int greenLeftOver = valGreen%2;
  int blueLeftOver = valBlue%2;
  if (redLeftOver == 0 && greenLeftOver == 0 && blueLeftOver == 0)
  {
    setToBlack();
  }
  if (redLeftOver == 1 && greenLeftOver == 0 && blueLeftOver == 0)
  {
    setToRed();
  }
  if (redLeftOver == 0 && greenLeftOver == 1 && blueLeftOver == 0)
  {
    setToGreen();
  }
  if (redLeftOver == 0 && greenLeftOver == 0 && blueLeftOver == 1)
  {
    setToBlue();
  }
  if (redLeftOver == 1 && greenLeftOver == 1 && blueLeftOver == 1)
  {
    setToWhite();
  }
  if (redLeftOver == 1 && greenLeftOver == 1 && blueLeftOver == 0)
  {
    setToYellow();
  }
  if (redLeftOver == 1 && greenLeftOver == 0 && blueLeftOver == 1)
  {
    setToMagenta();
  }
  if (redLeftOver == 0 && greenLeftOver == 1 && blueLeftOver == 1)
  {
    setToCyan();
  }
}

void ColorClass::encodeToBlack()
{
  int redLeftOver = valRed%2;
  int greenLeftOver = valGreen%2;
  int blueLeftOver = valBlue%2;
  if (redLeftOver == 1)
  {
    valRed = valRed - 1;
  }
  if (greenLeftOver == 1)
  {
    valGreen = valGreen - 1;
  }
  if (blueLeftOver == 1)
  {
    valBlue = valBlue - 1;
  }
}

void ColorClass::encodeToRed()
{
  int redLeftOver = valRed%2;
  int greenLeftOver = valGreen%2;
  int blueLeftOver = valBlue%2;
  if (redLeftOver == 0)
  {
    valRed = valRed + 1;
  }
  if (greenLeftOver == 1)
  {
    valGreen = valGreen - 1;
  }
  if (blueLeftOver == 1)
  {
    valBlue = valBlue - 1;
  }
}

void ColorClass::encodeToGreen()
{
  int redLeftOver = valRed%2;
  int greenLeftOver = valGreen%2;
  int blueLeftOver = valBlue%2;
  if (redLeftOver == 1)
  {
    valRed = valRed - 1;
  }
  if (greenLeftOver == 0)
  {
    valGreen = valGreen + 1;
  }
  if (blueLeftOver == 1)
  {
    valBlue = valBlue - 1;
  }
}

void ColorClass::encodeToBlue()
{
  int redLeftOver = valRed%2;
  int greenLeftOver = valGreen%2;
  int blueLeftOver = valBlue%2;
  if (redLeftOver == 1)
  {
    valRed = valRed - 1;
  }
  if (greenLeftOver == 1)
  {
    valGreen = valGreen - 1;
  }
  if (blueLeftOver == 0)
  {
    valBlue = valBlue + 1;
  }
}

void ColorClass::encodeToWhite()
{
  int redLeftOver = valRed%2;
  int greenLeftOver = valGreen%2;
  int blueLeftOver = valBlue%2;
  if (redLeftOver == 0)
  {
    valRed = valRed + 1;
  }
  if (greenLeftOver == 0)
  {
    valGreen = valGreen + 1;
  }
  if (blueLeftOver == 0)
  {
    valBlue = valBlue + 1;
  }
}

void ColorClass::encodeToYellow()
{
  int redLeftOver = valRed%2;
  int greenLeftOver = valGreen%2;
  int blueLeftOver = valBlue%2;
  if (redLeftOver == 0)
  {
    valRed = valRed + 1;
  }
  if (greenLeftOver == 0)
  {
    valGreen = valGreen + 1;
  }
  if (blueLeftOver == 1)
  {
    valBlue = valBlue - 1;
  }
}

void ColorClass::encodeToMagenta()
{
  int redLeftOver = valRed%2;
  int greenLeftOver = valGreen%2;
  int blueLeftOver = valBlue%2;
  if (redLeftOver == 0)
  {
    valRed = valRed + 1;
  }
  if (greenLeftOver == 1)
  {
    valGreen = valGreen - 1;
  }
  if (blueLeftOver == 0)
  {
    valBlue = valBlue + 1;
  }
}

void ColorClass::encodeToCyan()
{
  int redLeftOver = valRed%2;
  int greenLeftOver = valGreen%2;
  int blueLeftOver = valBlue%2;
  if (redLeftOver == 1)
  {
    valRed = valRed - 1;
  }
  if (greenLeftOver == 0)
  {
    valGreen = valGreen + 1;
  }
  if (blueLeftOver == 0)
  {
    valBlue = valBlue + 1;
  }
}
void ColorClass::encode(int colorToEncode)
{
  if (colorToEncode == 0)
  {
    encodeToBlack();
  }
  else if (colorToEncode == 1)
  {
    encodeToRed();
  }
  else if (colorToEncode == 2)
  {
    encodeToGreen();
  }
  else if (colorToEncode == 3)
  {
    encodeToBlue();
  }
  else if (colorToEncode == 4)
  {
    encodeToWhite();
  }
  else if (colorToEncode == 5)
  {
    encodeToYellow();
  }
  else if (colorToEncode == 6)
  {
    encodeToMagenta();
  }
  else if (colorToEncode == 7)
  {
    encodeToCyan();
  }
  else
  {
    cout << "Error: Encode value outside the accepted range";
  }
}








