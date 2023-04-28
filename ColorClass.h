#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

#include<string>
#include<fstream>
#include<cstring>
#include<sstream>
#include<cstdlib>
#include<iostream>
using namespace std;
class ColorClass 
{
private:
  int valRed;
  int valGreen;
  int valBlue;
  void clipIt(int &inRed, int &inGreen, int &inBlue);

public:
  ColorClass ();
  ColorClass (int inRed, int inGreen, int inBlue);
  string getPixelRGB();
  void setToBlack();
  void setToRed();
  void setToGreen();
  void setToBlue();
  void setToWhite();
  void setToYellow();
  void setToMagenta();
  void setToCyan();
  void decode();
  void encode(int colorToEncode);
  void encodeToBlack();
  void encodeToRed();
  void encodeToGreen();
  void encodeToBlue();
  void encodeToWhite();
  void encodeToYellow();
  void encodeToMagenta();
  void encodeToCyan();
  bool setTo(int inRed, int inGreen, int inBlue);
  bool setTo(ColorClass &inColor);
  bool addColor(ColorClass &rhs);
  bool subractColor(ColorClass &rhs);
  bool adjustBrightness(double adjFactor);
  void printComponentValues ();
};

#endif
