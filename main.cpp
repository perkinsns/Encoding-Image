#include<string>
#include<fstream>
#include<cstring>
#include<sstream>
#include<cstdlib>
#include<iostream>
using namespace std;

//Encode and Decode ppm Files
//Nicole Perkins originally written 21Mar2019 updated 16Mar2021

#include "constants.h"
#include "menu.h"
#include "ColorImageClass.h"
#include "ColorClass.h"
#include "RowColumnClass.h"

int main(int argc, char* argv[])
{
  //Checks if 2 arguments are passed in
  if (argc != ARGUMENTS)
  {
    cout << "Usage: ./proj3.exe <startPPM.ppm>" << endl;
    exit (2);
  }

  //Checks that this doesn't have a lock on the file
  string inputFile = argv[1];

  ifstream readFile;
  readFile.open(inputFile.c_str());
  if (readFile.fail())
  {
    cout << "Error: Permission to open file not granted" << endl;
    exit (2);
  }

  //Checks that this is a P3 file
  istringstream readLine;
  string lineInfo;
  // getline(readFile, lineInfo); //modded
  readFile >> lineInfo; //modded
  if (lineInfo != "P3")
  {
    cout << lineInfo << endl;
    cout << "Error: Wrong file type" << endl;
    exit (3);
  }
  getline(readFile,lineInfo); //modded

  //Checks that the dimensions are integers
  //modded: note the double to test if values are floating points
  //can do something similar for all other integer reads
  getline(readFile, lineInfo);
  double columnTest;
  double rowTest;
  int columns = 0;
  int rows = 0;
  readLine.str(lineInfo);
  readLine >> columnTest >> rowTest;
  rows = (int)rowTest;
  columns = (int)columnTest;
  if (readLine.fail() || rows != rowTest || columns != columnTest)
  {
    cout << "Error: Column or row formatted incorrectly" << endl;
    exit (3);
  }
  readLine.clear();

  //Checks that the max color value is 255 and nothing else
  getline(readFile, lineInfo);
  int maxColorValue;
  readLine.str(lineInfo);
  readLine >> maxColorValue;
  if (readLine.fail() || maxColorValue != 255)
  {
    cout << "Error: Max color value formatted incorrectly" << endl;
    exit (2);
  }
  readLine.clear();

  //Reads in image
  ColorImageClass inputImage(rows, columns);
  string extraVals;
  for (int i = 0; i < rows; i++)
  {
    readLine.clear();
    getline(readFile, lineInfo);
    readLine.str(lineInfo);
    for (int j = 0; j < columns; j++)
    {
      RowColumnClass pixelLocation;
      ColorClass pixelColor;
      pixelLocation.setRowCol(i, j);
      int pixelRed = 0;
      int pixelGreen = 0;
      int pixelBlue = 0;
      readLine >> pixelRed >> pixelGreen >> pixelBlue;
      pixelColor.setTo(pixelRed, pixelGreen, pixelBlue);
      inputImage.setColorAtLocation(pixelLocation, pixelColor);
      if (readLine.fail())
      {
        cout << "Error: Invalid pixel at [" << i << ", " << j << "]" << endl;
        exit (3);
      }
    }
    //modded
    readLine >> extraVals;
    if (!readLine.fail()) {
      cout << "Too many pixels in row " << i << endl;
      exit (3);
    }
    extraVals.clear();
  }
  //modded
  readFile >> extraVals;
  if (!readFile.fail()) {
    cout << "Too many rows" << endl;
    exit (3);
  }
  cout << "Image read successful: Yes" << endl;


  int userMenuChoice = 0;
  while (userMenuChoice != EXIT)
  {
    printMenu();
    cin >> userMenuChoice;
    if (userMenuChoice == ENCODE)
    {
      ifstream messageText;
      string textFileName;
      int messagePlaceRow;
      int messagePlaceColumn;
      cout << "Enter name of file containing message:" << endl;
      cin >> textFileName;
      cout << "Enter row and column for message placement:" << endl;    
      cin >> messagePlaceRow >> messagePlaceColumn;
      if (cin.fail())
      {
        cout << "Error: Row and column input not valid" << endl;
      }
      else
      {
        messageText.open(textFileName.c_str());
        if (messageText.fail())
        {
          cout << "Error: failed to open text file" << endl;
        }
        else
        {
          cout << "Encoding Message" << endl;
          int encodeColumnSize = 0;
          int encodeRowSize = 0;
          getline(messageText, lineInfo);
          readLine.clear();
          readLine.str(lineInfo);
          readLine >> encodeColumnSize >> encodeRowSize;
          if (readLine.fail())
          {
            cout << "Error: Column or row formatted incorrectly" << endl;
          }
          int endEncodeRow = encodeRowSize + messagePlaceRow;
          cout << endEncodeRow << endl;
          int endEncodeColumn = encodeColumnSize + messagePlaceColumn;
          cout << endEncodeColumn << endl;
          for (int i = messagePlaceRow; i < endEncodeRow; i++)
          {
            readLine.clear();
            RowColumnClass encodePixelCurrent;
            ColorClass encodePixel;
            getline(messageText, lineInfo);
            readLine.str(lineInfo);
            for (int j = messagePlaceColumn; j < endEncodeColumn; j++)
            {
              int encodeColor = 0;
              encodePixelCurrent.setRowCol(i, j);
              inputImage.getColorAtLocation(encodePixelCurrent, encodePixel);
              readLine >> encodeColor;
              if (readLine.fail())
              {
                cout << "Error: Invalid pixel at [" << i << ", " << j << "]" 
                     << endl;
              }
              encodePixel.encode(encodeColor);
              inputImage.setColorAtLocation(encodePixelCurrent, encodePixel);
            }
          }
        }
      }
      cout << "Message encode successful: Yes" << endl;
    }
    else if (userMenuChoice == DECODE)
    {
      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < columns; j++)
        {
          RowColumnClass currentLocation;
          ColorClass colorAtCurrentLoc;
          currentLocation.setRowCol(i, j);
          inputImage.getColorAtLocation(currentLocation, colorAtCurrentLoc);
          colorAtCurrentLoc.decode();
          inputImage.setColorAtLocation(currentLocation, colorAtCurrentLoc);
        }
      }
      cout << "Image modified to decoded image contents" << endl;
    }
    else if (userMenuChoice == WRITE)
    {
      string writeToFile;
      ofstream outFile;
      cout << "Enter name of file to write image to:" << endl;
      cin >> writeToFile;
      outFile.open(writeToFile.c_str());
      if (outFile.fail())
      {
        cout << "Image write successful: No" << endl;
      }
      else
      {
        outFile << "P3" << endl;
        outFile << columns << " " << rows << endl;
        outFile << maxColorValue << endl;
        for (int i = 0; i < rows; i++)
        {
          for (int j = 0; j < columns; j++)
          {
            RowColumnClass currentLocation;
            ColorClass colorAtCurrentLoc;
            currentLocation.setRowCol(i, j);
            inputImage.getColorAtLocation(currentLocation, colorAtCurrentLoc);
            if (j == columns - 1)
            {
              outFile << colorAtCurrentLoc.getPixelRGB() << endl;
            }
            else
            {
              outFile << colorAtCurrentLoc.getPixelRGB() << " ";
            }        
          }
        }
        cout << "Image write successful: Yes" << endl;
      }
    }
  }
  if (userMenuChoice = EXIT) 
  {
    cout << "Thanks for using this program!" << endl;
    exit (2);
  }
  return (0);
}


