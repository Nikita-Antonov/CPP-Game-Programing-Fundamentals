#include "raylib.h"
int main(){

    int windowWidth = 500;
    int windowHeight = 500;

    float root_bear = 1.99;
    double cheese_burger{5.99}; // <- Brased Initialization WOW!
    bool shouldHaveLunch{};    //Set to false last i checked 

    bool equal{4 == 9};     //Will return false
    bool notEqual{4 != 9};  //Will return false
    bool less{4 < 9};       //Will return true
    bool greater{4 > 9};    //Will return false
    bool lessEqual{4 <= 9}; //Will reurn true
    bool greaterEqual{4 >= 9};  //Will return false

    //Takes 3 inputs, Width, Height, and Title of the window
    //                  int     int         "String"
    InitWindow(windowWidth, windowHeight, "Nikita's Window");
}