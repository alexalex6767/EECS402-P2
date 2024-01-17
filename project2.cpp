#include <iostream>
using namespace std;

//Programmer: Tzu-Yu Peng, typeng
//Date: September 2023
//This project aims at presenting images and colors using classes

//constant declarations and initializations
const int INIT_COLOR_VALUE = 1000;
const int MAX_COLOR_VALUE = 1000;
const int MIN_COLOR_VALUE = 0;
//This is the default row and column numbers.
const int DEFAULT_ROW_COL = -99999;
//These are the max row and column numbers.
const int MAX_ROW_NUM = 10;
const int MAX_COL_NUM = 18;
//to know when to print -- we need to know whether it is the last one
const int MAX_COL_NUM_FOR_PRINT = MAX_COL_NUM - 1;

//class definitions (method prototypes w/ comments, no implementations)
//ColorClass is a class for desribing a color.
class ColorClass{
  private:
    int redAmount;
    int greenAmount;
    int blueAmount;
    //Color in range check tool
    int colorClip(int colorInput);
    bool colorInRange(int colorInput);

  public:
    //constructor
    ColorClass();//Default is to full white, means RGB are all full
    ColorClass(int inRed, int inGreen, int inBlue);
  
    //set to specific colors
    void setToBlack();
    void setToRed();
    void setToGreen();
    void setToBlue();
    void setToWhite();
  
    //set colors by the value you want
    bool setTo(int inRed, int inGreen, int inBlue);
  
    //set colors by the other object's color
    bool setTo(ColorClass &inColor);
  
    //addColors mean each color will be added the amount
    bool addColor(ColorClass &rhs);
  
    //addColors mean each color will be added the amount
    bool subtractColor(ColorClass &rhs);
  
    //adjustBrightness mean each color will multiply the given number
    bool adjustBrightness(double adjFactor);
  
    //print each color's amount out
    void printComponentValues();
};

//This class is used to set columns and rows
class RowColumnClass{
  private:
    int rowIndex;
    int colIndex;
  
  public:
    //constructor
    RowColumnClass();//Default is to set row and column to -99999
    RowColumnClass(int inRow, int inCol);
  
    //This member function is to set Row and Col at the same time
    void setRowCol(int inRow, int inCol);
  
    //This member function is to set Row
    void setRow(int inRow);
  
    //This member function is to set Col
    void setCol(int inCol);
  
    //These two member function are to get the Row and Col value
    int getRow();
    int getCol();
  
    //This function is to add row and col value to the object
    void addRowColTo(RowColumnClass &inRowCol);
  
    //print row and col value out
    void printRowCol();
};


//This class is used to represent a small image
class ColorImageClass{
  private:
    ColorClass colorClassArrayObject[MAX_ROW_NUM][MAX_COL_NUM];
    //This function is used to check location
    bool checkLocation(int locRow, int locCol);
  public:
    //Default constructor simply sets all pixels in the image to full black.
    ColorImageClass();
  
    //This initializes all pixels to the color provided via the input parameter
    void initializeTo(ColorClass &inColor);
  
    //This fumction will let the pixels added by the corresponding 
    //pixel's of input image
    bool addImageTo(ColorImageClass &rhsImg);
  
    //This function sets the image's pixel values to the sum of the 
    //corresponding pixels in each imagesTOAdd input parameter
    bool addImages(int numImgsToAdd, ColorImageClass imagesToAdd[]);
  
    //This function sets pixel at inRowCol and color  of inColor
    bool setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);
  
    //If input row/col is valid, the output outColor will be assigned the
    //color of the pixelat the position
    bool getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);
  
    void printImage();
};


#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);
  ColorImageClass testImage;
  ColorImageClass testImages[3];

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;

  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;

  //Test some basic ColorImageClass operations...
  testColor.setToRed();
  testImage.initializeTo(testColor);

  testRowCol.setRowCol(555, 5);
  cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  testRowCol.setRow(4);
  cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  //Set up an array of images of different colors
  testColor.setToRed();
  testColor.adjustBrightness(0.25);
  testImages[0].initializeTo(testColor);
  testColor.setToBlue();
  testColor.adjustBrightness(0.75);
  testImages[1].initializeTo(testColor);
  testColor.setToGreen();
  testImages[2].initializeTo(testColor);

  //Modify a few individual pixel colors
  testRowCol.setRowCol(4, 2);
  testColor.setToWhite();
  testImages[1].setColorAtLocation(testRowCol, testColor);

  testRowCol.setRowCol(2, 4);
  testColor.setToBlack();
  testImages[2].setColorAtLocation(testRowCol, testColor);

  //Add up all images in testImages array and assign result
  //to the testImage image
  testImage.addImages(3, testImages);
  
  //Check some certain values
  cout << "Added values:" << endl;
  for (int colInd = 0; colInd < 8; colInd += 2)
  {
    testRowCol.setRowCol(4, colInd);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  for (int rowInd = 0; rowInd < 8; rowInd += 2)
  {
    testRowCol.setRowCol(rowInd, 4);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  cout << "Printing entire test image:" << endl;
  testImage.printImage();
  return 0;
}
#endif

//class method definitions
//ColorClass
//check Color in range
bool ColorClass::colorInRange(int colorInput){
  if((colorInput <= MAX_COLOR_VALUE) && (colorInput >= MIN_COLOR_VALUE)){
    return true;
  }
  else{
    return false;
  }
};
//Change Color to the value in range
int ColorClass::colorClip(int colorInput){
  int colorOutput;
  if(colorInRange(colorInput)){
    colorOutput = colorInput;
  }
  else if(colorInput > MAX_COLOR_VALUE){
    colorOutput = MAX_COLOR_VALUE;
  }
  else{
    colorOutput = MIN_COLOR_VALUE;
  }
  return colorOutput;
};

//constructor
//Default is to full white, means RGB are all full
ColorClass::ColorClass(){
  redAmount = INIT_COLOR_VALUE;
  greenAmount = INIT_COLOR_VALUE;
  blueAmount = INIT_COLOR_VALUE;
};
ColorClass::ColorClass(int inRed, int inGreen, int inBlue){
  redAmount = colorClip(inRed);
  greenAmount = colorClip(inGreen);
  blueAmount = colorClip(inBlue);
};

//set to specific colors
void ColorClass::setToBlack(){
  redAmount = MIN_COLOR_VALUE;
  greenAmount = MIN_COLOR_VALUE;
  blueAmount = MIN_COLOR_VALUE;
};
void ColorClass::setToRed(){
  redAmount = MAX_COLOR_VALUE;
  greenAmount = MIN_COLOR_VALUE;
  blueAmount = MIN_COLOR_VALUE;
};
void ColorClass::setToGreen(){
  redAmount = MIN_COLOR_VALUE;
  greenAmount = MAX_COLOR_VALUE;
  blueAmount = MIN_COLOR_VALUE;
};
void ColorClass::setToBlue(){
  redAmount = MIN_COLOR_VALUE;
  greenAmount = MIN_COLOR_VALUE;
  blueAmount = MAX_COLOR_VALUE;
};
void ColorClass::setToWhite(){
  redAmount = MAX_COLOR_VALUE;
  greenAmount = MAX_COLOR_VALUE;
  blueAmount = MAX_COLOR_VALUE;
};

//set colors by the value you want
bool ColorClass::setTo(int inRed, int inGreen, int inBlue){
  //If all input color value are in range, will set color as input 
  //and retrun false
  if (colorInRange(inRed) && colorInRange(inGreen) && colorInRange(inBlue)){
    redAmount = inRed;
    greenAmount = inGreen;
    blueAmount = inBlue;
    return false;
  }
  //if one of the color is not in range, use the change color tool to change
  else{
    redAmount = colorClip(inRed);
    greenAmount = colorClip(inGreen);
    blueAmount = colorClip(inBlue);
    return true;
  }
};
//overload function, use the other pixel's color
bool ColorClass::setTo(ColorClass &inColor){
  redAmount = inColor.redAmount;
  greenAmount = inColor.greenAmount;
  blueAmount = inColor.blueAmount;
  return false;
};

//add or subtract color to our destination from the input we put
bool ColorClass::addColor(ColorClass &rhs){
  bool changeOrNot;
  redAmount += rhs.redAmount;
  greenAmount += rhs.greenAmount;
  blueAmount += rhs.blueAmount;
  
  changeOrNot = setTo(redAmount, greenAmount, blueAmount);
  return changeOrNot;
};
bool ColorClass::subtractColor(ColorClass &rhs){
  bool changeOrNot;
  redAmount -= rhs.redAmount;
  greenAmount -= rhs.greenAmount;
  blueAmount -= rhs.blueAmount;
  
  changeOrNot = setTo(redAmount, greenAmount, blueAmount);
  return changeOrNot;
};

//adjustBrightness mean each color will multiply the given number
bool ColorClass::adjustBrightness(double adjFactor){
  bool changeOrNot;
  redAmount = static_cast<int>(redAmount * adjFactor);
  greenAmount = static_cast<int>(greenAmount * adjFactor);
  blueAmount = static_cast<int>(blueAmount * adjFactor);
  
  changeOrNot = setTo(redAmount, greenAmount, blueAmount);
  return changeOrNot;
};

//print out each color's value
void ColorClass::printComponentValues(){
  cout << "R: " << redAmount << " G: " << greenAmount <<
          " B: " << blueAmount;
};


//RowColumnClass
//Constructor
//Default is to set row and column to -99999
RowColumnClass::RowColumnClass(){
  rowIndex = DEFAULT_ROW_COL;
  colIndex = DEFAULT_ROW_COL;
};
RowColumnClass::RowColumnClass(int inRow, int inCol){
  rowIndex = inRow;
  colIndex = inCol;
};

//This member function is to set Row and Col at the same time
void RowColumnClass::setRowCol(int inRow, int inCol){
  rowIndex = inRow;
  colIndex = inCol;
};

//This member function is to set Row
void RowColumnClass::setRow(int inRow){
  rowIndex = inRow;
};

//This member function is to set Col
void RowColumnClass::setCol(int inCol){
  colIndex = inCol;
};

//These two member function are to get the Row and Col value
int RowColumnClass::getRow(){
  return rowIndex;
};
int RowColumnClass::getCol(){
  return colIndex;
};

//This function is to add row and col value to the object
void RowColumnClass::addRowColTo(RowColumnClass &inRowCol){
  rowIndex += inRowCol.rowIndex;
  colIndex += inRowCol.colIndex;
};

//print row and col value out
void RowColumnClass::printRowCol(){
  cout << "[" << rowIndex << "," << colIndex << "]";
};


//ColorImageClass
//private function, check the location is aval=ilable
bool ColorImageClass::checkLocation(int locRow, int locCol){
  if(locRow >= MAX_ROW_NUM || locCol >= MAX_COL_NUM){
    return false;
  }
  else{
    return true;
  }
}
//Constructor
//Default constructor simply sets all pixels in the image to full black.
ColorImageClass::ColorImageClass(){
  int i;
  int j;
  for(i = 0; i < MAX_ROW_NUM; i++){
    for(j = 0; j < MAX_COL_NUM; j++){
      colorClassArrayObject[i][j].setToBlack();
    }
  }
};

//This initializes all pixels to the color provided via the input parameter
void ColorImageClass::initializeTo(ColorClass &inColor){
  int i;
  int j;
  for(i = 0; i < MAX_ROW_NUM; i++){
    for(j = 0; j < MAX_COL_NUM; j++){
      colorClassArrayObject[i][j].setTo(inColor);
    }
  }
};

//This fumction will let the pixels added by the corresponding pixel's 
//of input image
bool ColorImageClass::addImageTo(ColorImageClass &rhsImg){
  int i;
  int j;
  bool changeOrNot = false;
  for(i = 0; i < MAX_ROW_NUM; i++){
    for(j = 0; j < MAX_COL_NUM; j++){
      if((colorClassArrayObject[i][j].
           addColor(rhsImg.colorClassArrayObject[i][j]))){
        changeOrNot = true;
      };
    }
  }
  return changeOrNot;
};

//This function sets the image's pixel values to the sum of the corresponding
//pixels in each imagesTOAdd input parameter
bool ColorImageClass::addImages(int numImgsToAdd,
                                ColorImageClass imagesToAdd[]){
  int i;
  int j;
  int k;
  bool changeOrNot = false;
  //First set them to 0
  for(i = 0; i < MAX_ROW_NUM; i++){
    for(j = 0; j < MAX_COL_NUM; j++){
      colorClassArrayObject[i][j].setToBlack();
      }
    }
  for(k = 0; k < numImgsToAdd; k++){
    if ((addImageTo(imagesToAdd[k]))){
      changeOrNot = true;
    }
  }
  return changeOrNot;
};

//This function sets pixel at inRowCol and color  of inColor
bool ColorImageClass::setColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &inColor){
  int rowValue = inRowCol.getRow();
  int colValue = inRowCol.getCol();
  
  if(checkLocation(rowValue, colValue)){
    colorClassArrayObject[rowValue][colValue].setTo(inColor);
    return true;
  }
  else{
    return false;
  }
};

//If input row/col is valid, the output outColor will be assigned the 
//color of the pixelat the position
bool ColorImageClass::getColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &outColor){
  int rowValue = inRowCol.getRow();
  int colValue = inRowCol.getCol();
  
  if(checkLocation(rowValue, colValue)){
    outColor.setTo(colorClassArrayObject[rowValue][colValue]);
    return true;
  }
  else{
    return false;
  }
};

//print the array out
void ColorImageClass::printImage(){
  int i;
  int j;
  for(i = 0; i < MAX_ROW_NUM; i++){
    for(j = 0; j < MAX_COL_NUM; j++){
      colorClassArrayObject[i][j].printComponentValues();
      if(j < MAX_COL_NUM_FOR_PRINT){
        cout << "--";
      }
    }
    cout << endl;
  }
};

