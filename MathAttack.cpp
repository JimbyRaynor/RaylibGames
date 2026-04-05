#include "raylib.h"
#include <string>
#include <cstring>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// APP name: MathQuix or QuixoMath or Math Addition Game

// compile: g++ MathAttack.cpp -o MathAttack -lraylib -lm -ldl -lpthread -lGL -lX11
// run:     ./MathAttack
// Ctrl-C to close crashed program

// raylib uses float for most numbers, and so use 2.0f to convert int to float. Note that 2.0 will be a double

// Keep short! just +
// Side panel of Bob, graphics, 3s, 1+2=3 current sum, etc, just like arcade games
// 1+2=3 should appear in a box somewhere


// draw round japanese style characters with little arms and legs, and flowy hair
// released number should be displayed on LHS 
// Tidy up code!

// hires Battery meter progress bar?
// good board numbers:green
// bad (used board numbers): red
// gunvector: number available green
//          : number not available greyed out


// draw boxes with animated dots moving around
// Look at Tetris for game design and music
// Avoid over-tall stack by only adding from queue when size <= 10 ?? needed ?? how to increase stack size while playing game?
// mistakes decrease bonus by 1000


// Same for (a+b)+c, a+(b+c)  ???? add algebra SLOWLY
// Look at expensive watch faces CASIO, SEIKO, etc. for screen design

// draw graphics while balancing

// Draw controls  AIM  : <spacebar>
//                FIRE : <Enter>
// Removing a tile should be satisfying. Candy Crush?


// write = MISS if value1+value2 NOT on board
// Trailing headlights (particles) on moving numbers
// Just remove bonus for mistakes


// THEMES:
// 2. Standard dark mode with green text
// 3. Minesweeper style
// 5. Latex - everything in LaTeX

// LEVELS:
// Levels are chosen like in peggle, with intro etc.
// 0. Training: numbers do not get removed from board, and ONLY need to get to a sum of 30
// 4. What other types? Look for other famous theorems of number theory
// 4. Big gaps no 20s, 40s, 60s, 80,s
// 4.       no 30,40,50,60s, etc.
// 5. pyramid pattern
// 6. LHS only
// 7. RHS only
// bonus level: every natural number > 3 is a sum of two primes
// Level completed when sum = 100. Then 100 explodes into fireworks like peggle
// Orange numbers give bonus?

// POINTS:
//  Score = 100-y for dropping number

// BONUS:
// colourful bonus number moves around in pattern on table
// Bonus hit repairs a removed tile
// Bonus for shorter path to 100

// BUGS:


// retro arrow -> points to place where number is placed _ + _  


// Bonus mission board like casino roulette table
// Give me 
// (a) even
// (b) odd
// (c) prime
// (d) mersenne prime
// (e) red number
// (f) 2 evens in a row
// (g) 2 odds in a row, etc
// (h) think poker
//    (1) straight 2,3,4,5,6
//    (2) full house?
// Char moves across numberline towards 100? Seems good
// Make animation for removing number (frog jump??)

// "Orange Peg" numbers give bonus multipliers, but also give an extra 10-18 number
// Casino style board?

// score = sum of the two numbers (high numbers give best score), and chains can be made naturally.
// the harder the sum, the bigger the score


//  Design fixed, not random, levels on Kindle Scribe


// For multiplication just give random numbers from 1 to 10
//  Goal is just to remove all numbers from the board 
//    Board should be spatse to avoid randomly multiplying two numbers
// Similar for minus and divide

// Think about * level
// Need to remove full board (multiplication table)
// Load gun with primes and 1, all composites get made and so all cases are needed, e.g. 7*8, because we only have a binary operation
// Two columns, one for primes, one for composites (max 10), limited memory ! ? Then 4 gets loaded 4*2,4*3,4*5,4*7,4*9, 4*11, 4*13, 4*17
// 4*11 = 2*22 = prime x 22, so 4 is not needed when we have 22 in gun vector, good puzzle! Just add 4 then minimum number of times!/
// so mistakes can be made. If it is tricky to set up, then it makes a good puzzle!
// how to build 16 = 2x2x2x2 ?
// 2x4 = 8 , so need 4 to come back
// 2x8 = 16, so need 8 to come back, etc
// 100 = 25*4
//  50 = 25*2, but there is only one 25
// 9*4 = 36
// 72 = 9*4*2, will run out of 4s as well
// so once a number is loaded into gun, it stays there.
// Now how to make the level difficult
//    only three missses allowed?
//    how to stop spamming?



// levels for +,-,/,*, etc
//  / splits into divisor + reminder ?

// The Matrix screensaver theme?

// chars walking across screen to show progress ?
// Look at Donut Dodo for ideas of background animations


using namespace std;

int screenWidth = 1200; 
int screenHeight = 800;
string theme = "dark";    // dark, CASIO
string themearray[2] = {"dark", "CASIO"}; // uparrow to change
int themearrayindex = 0;
Color rbbackgroundcolour = BLACK;

string mystring;
// note that mystring.c_str() converts the C++ string mystring to the C array of characters

Color HexToColour(int hexValue) {
    Color c;
    c.r = (hexValue >> 16) & 0xFF;  // red
    c.g = (hexValue >> 8) & 0xFF;   // green
    c.b = hexValue & 0xFF;          // blue
    c.a = 255;                      // default opaque
    return c;
}

Color rbblack = HexToColour(0x000000);
Color rberaser = HexToColour(0x000001); 
Color rbwhite = HexToColour(0xFFFFFF);
Color rblightblue = HexToColour(0xB5B3F5);
Color rbblue = HexToColour(0x0000FF);
Color rbdarkblue = HexToColour(0x00008B);
Color rblightred = HexToColour(0xFF6666);
Color rbred = HexToColour(0xFF0000);
Color rbdarkred = HexToColour(0x8B0000);
Color rborange = HexToColour(0xFF5900);
Color rblightorange = HexToColour(0xFFD580);
Color rbdarkorange = HexToColour(0xFF8C00);  
Color rblightgreen = HexToColour(0x66C266);
Color rbgreen = HexToColour(0x279627);  
Color rbdarkgreen = HexToColour(0x006400);
Color rblightpink = HexToColour(0xFFD1F0);
Color rbpink = HexToColour(0xF498EC);  
Color rbdarkpink = HexToColour(0xC71585);
Color rblightyellow = HexToColour(0xFFFFE0);
Color rbyellow = HexToColour(0xFFFF00);
Color rbdarkyellow = HexToColour(0xB8860B);  
Color rblightgrey = HexToColour(0xDDDDDD);
Color rbgrey = HexToColour(0xAAAAAA);
Color rbdarkgrey = HexToColour(0x777777);
Color rblightbrown = HexToColour(0xC19153);
Color rbbrown = HexToColour(0x8B4513);
Color rbdarkbrown = HexToColour(0x4C3A23);
Color rblightaqua = HexToColour(0xE0FFFF);
Color rbaqua = HexToColour(0x00FFFF);
Color rbdarkaqua = HexToColour(0x008B8B);
Color rblightpurple = HexToColour(0xE6E6FA);
Color rbpurple = HexToColour(0xBE1CBE);
Color rbdarkpurple = HexToColour(0x4B0082);

Color rbgray0 = HexToColour(0x999999);
Color rbgray1 = HexToColour(0xAAAAAA);
Color rbgray2 = HexToColour(0xCCCCCC);
Color rbgraytext = HexToColour(0x1E1E1E);
Color rbgray24 = HexToColour(0xC8C8C8);
Color rbgray3 = HexToColour(0xEEEEEE);

 // DO NOT CHANGE
 // for LEDColour pixel editor
Color AllColours[60] = {rblightblue, rbblue, rbdarkblue, rblightred, rbred, rbdarkred, rblightorange, rborange, rbdarkorange,
                       rblightgreen, rbgreen, rbdarkgreen, rblightpink, rbpink, rbdarkpink, rblightyellow, rbyellow, rbdarkyellow,
                       rblightgrey, rbgrey, rbdarkgrey, rblightbrown, rbbrown, rbdarkbrown, rblightaqua, rbaqua, rbdarkaqua,
                       rblightpurple, rbpurple, rbdarkpurple, rbblack, rberaser, rbwhite};                    
 // for LEDColour pixel editor
Color getColour(int myindex)
{
  if ( (myindex >= 1) and (myindex <= 33))
    return AllColours[myindex-1];
  else
    return rbblack; 
}

Color ColourRainbow[10] = { rbwhite, rblightgreen, rbdarkyellow,
                              rbdarkpink, rbblue, rbred, rbgreen, rbbrown, rbaqua, rbpurple};

Color ColourCASIOArray[10] = { rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext};


Color EnemyColourArray[10];


void settheme()
{
  if (theme == "dark")
    {
      rbbackgroundcolour = BLACK;
      memcpy(EnemyColourArray, ColourRainbow, sizeof(ColourRainbow));
    }
   if (theme == "CASIO")
    {
      rbbackgroundcolour = rbgray24;
       memcpy(EnemyColourArray, ColourCASIOArray, sizeof(ColourCASIOArray));
    }
}

int CharBob[64] = {1,18,23,23,23,23,18,18,1,18,18,23,23,23,18,18,14,16,16,16,16,16,16,16,17,16,0,0,16,0,0,16,0,16,0,0,16,0,0,16,0,16,16,16,16,16,16,16,0,18,1,1,1,1,17,17,23,23,23,18,18,18,23,23};
int CharBlock[576] = {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19};
int CharEnemy1[64] = {5,0,0,17,0,0,0,5,0,5,0,0,17,0,5,0,5,0,11,17,0,11,0,5,0,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5,5,5,24,33,24,33,5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5,0};
int Char0[64] = {0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int Char1[64] = {0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int Char2[64] = {0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int Char3[64] = {0,16,16,16,16,16,0,0,16,16,0,0,0,16,16,0,0,0,0,0,0,16,16,0,0,0,0,16,16,16,0,0,0,0,0,0,0,16,16,0,16,16,0,0,0,16,16,0,0,16,16,16,16,16,0,0,0,0,0,0,0,0,0,0};
int Char4[64] = {0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0};
int Char5[64] = {1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int Char6[64] = {0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int Char7[64] = {1,1,1,1,1,1,1,0,1,1,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0};
int Char8[64] = {0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int Char9[64] = {0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0};
int CharPlus1[64] = {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0};
int CharPlus2[64] = {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharUnderline[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
int CharEquals[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharUpArrow[64] = {0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};



int* digitarray[10] = {Char0, Char1, Char2, Char3,  // array of pointers to chars, this works well! Access with digitarray[charnum][bitnum] 
                       Char4, Char5, Char6, Char7, Char8, Char9};  


int herox = 20;
int heroy = 20;
int resultx = 600;
int resulty = 400;
int traily = -30;
int totalenemies = 20;
int createdenemies = 0;
int enemymovement = 0;
int movementstep = 1;
int hits = 0;
int value1 = 0;
bool value1picked = false;
int value2 = 0;
bool value2picked = false;
bool resultdisplayed = false;
int EnterCount = 0;
int shootnumber = 1;
int shield = 3;
int level = 1;
int maxnumber = 2;
int levels[] = {0,3,9,14,14,20,33,32,32,32}; // Extra enemies added in each level; 
int Board[20][20];
string operation = "+";
vector <int> gunvector;
vector <string> sumlog;
int gunindex = 0;
int MAXstacksize = 4;

bool TestPrime(int n)
{
  if (n <= 1) return 0;
  bool  isprime = true;
  for (int i = 2; i < n; i++)
       if (n % i == 0)
          isprime = false;
  return isprime;

}

int fillboard()
{
  for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
   {
     if (level == 9)
     {
        if (GetRandomValue(0,9) >= 7)   // hardest level 7 (random)
           Board[i][j] = i*10+j;
           else
           Board[i][j] = -1;
     }
     if (level == 1) // all numbers
     {
          Board[i][j] = i*10+j;
     }
     if (level == 2) // evens
     {
       if ((i*10+j) % 2 == 0) 
          Board[i][j] = i*10+j;
           else
           Board[i][j] = -1;
     }
     if (level == 3)  // odds
     {
       if ((i*10+j) % 2 == 1) 
          Board[i][j] = i*10+j;
           else
           Board[i][j] = -1;
     }
    if (level == 4)  // primes
     {
          if ( TestPrime(i*10+j) == true )
          Board[i][j] = i*10+j;
           else
           Board[i][j] = -1; 
     }
   }
  return 0;
}

void drawCharfromArray(int previewx, int previewy, int psize, int bitwidth, int myarray[])
     {
       Color Mycolour;
       int loc = 0;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              if (myarray[loc] != 0)
              {
               Mycolour = getColour(myarray[loc]);
               DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour);    
              }
              loc++;
            }        
     }

void drawCharOneColour(int previewx, int previewy, int psize, int bitwidth, int myarray[], Color Mycolour)
     {
       int loc = 0;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              if (myarray[loc] != 0)
              {
               DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour);    
              }
              loc++;
            }        
     }

void drawRetroCharOneColour(int previewx, int previewy, int psize, int bitwidth, int myarray[], Color Mycolour)
     {
       int loc = 0;
       int gap = 1;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              if (myarray[loc] != 0)
              {
               DrawRectangle(previewx+j*(psize+gap),previewy+i*(psize+gap),psize,psize,Mycolour);    
              }
              loc++;
            }        
     }

void drawRetroChar(int previewx, int previewy, int psize, int bitwidth, int myarray[])
     {
       Color Mycolour;
       int loc = 0;
       int gap = 1;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              if (myarray[loc] != 0)
              {
               Mycolour = getColour(myarray[loc]);
               DrawRectangle(previewx+j*(psize+gap),previewy+i*(psize+gap),psize,psize,Mycolour);    
              }
              loc++;
            }        
     }

void draw2digits(int locx, int locy, int mynum, int psize, Color Mycolour)
{
  int first = mynum / 10;
  int second = mynum % 10;
  if (first > 0) 
   { 
    drawRetroCharOneColour(locx, locy, psize, 8, digitarray[first], Mycolour);
   }
  drawRetroCharOneColour(locx+ 8*(psize+1), locy, psize, 8, digitarray[second], Mycolour);
}

void draw2digitsSolid(int locx, int locy, int mynum, int psize, Color Mycolour)
{
  int first = mynum / 10;
  int second = mynum % 10;
  if (first > 0) 
   { 
    drawCharOneColour(locx, locy, psize, 8, digitarray[first], Mycolour);
   }
  drawCharOneColour(locx+ 8*(psize+1), locy, psize, 8, digitarray[second], Mycolour);
}

class Enemy  
{
     public:
       Enemy(int startx, int starty, int number); // constructor, *must* be named the same as the class Enemy
       int spawn();
       int move();
       int draw();
       int x,y;
       int attacknumber;
       bool alive;
     private:
};

Enemy::Enemy(int startx, int starty, int number) // constructor
{
     alive = true;
     x = startx;
     y = starty;
     attacknumber = number;
}

int Enemy::spawn()
{
     int count = 0;
     return 0;
}

int Enemy::move()
{
    if (y <= 600)
       y = y + movementstep;
    return 0;
}

int Enemy::draw()
{
  Color Mycolour;
  if (attacknumber < 10)
     Mycolour = EnemyColourArray[attacknumber];
  else
     Mycolour = rbdarkorange;
  if (theme == "dark")
      draw2digits(x, y, attacknumber, 3, Mycolour);
  else
      draw2digitsSolid(x, y, attacknumber, 4, Mycolour);
  return 0;
}
vector <Enemy> Enemies;
vector <Enemy> Enemyqueue;

bool checkenemycollision(int index)
{
 bool collide = false;
 for (int i=0;i<Enemies.size();i++)
 {
    if (i != index and Enemies[index].y+40 == Enemies[i].y )
     collide = true;
 }
 return collide;
}

int moveenemies()
{
  traily += movementstep;
  enemymovement += movementstep;
  for (int i=0;i<Enemies.size();i++)
        if (!checkenemycollision(i)) 
         {
          Enemies[i].move();
         }
  return 0;
}

int loadgunvector()
{
  gunvector.clear();
  for (int i=1;i<10;i++)
     gunvector.push_back(i);
  for (int i=0;i<Enemies.size();i++)
        if (find(gunvector.begin(),gunvector.end(),Enemies[i].attacknumber) == gunvector.end() and Enemies[i].attacknumber > 9)  // need unique
              gunvector.push_back(Enemies[i].attacknumber);
  if (gunvector.size() > 0)  
       sort(gunvector.begin(),gunvector.end());
  return 0;
}

int resetenemyloc()
{ int n = Enemies.size();
  for (int i=0; i< n; i++)
    {  
       Enemies[n-i-1].y = i*40+traily;
    }
  enemymovement = 0;
  return 0;
}

int removefromboard(int number)
{
if (number == 100) return 0;
for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
     if (Board[i][j] == number)
     {
          Board[i][j] = -1;
          return 0;
     }
return -1;
}

int findminboard()
{
  int min = 99;
  for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
       if (Board[i][j] < min and Board[i][j] != -1) min = Board[i][j];
  return min;
}

int createnewenemyinqueue(int value)
{
  Enemy Entmp(screenWidth/2-50,-30,value);
  if (value > maxnumber and value < 10)
  {
    maxnumber = value;
  }
  Enemyqueue.push_back(Entmp);
  loadgunvector();
  return 0;
}

int drawnemies()
{
  for (int i=0; i< Enemies.size(); i++)
    {  
       Enemies[i].draw();
    }
  return 0;
}


int createnewlevel()
{
     level++;
     hits = 0;
     EnterCount = 0;
     resultdisplayed = false;
     maxnumber = 2;
     createdenemies = 0;
     createnewenemyinqueue(GetRandomValue(1,maxnumber));
     fillboard();
     return 0;
  }


int removeenemy(int shotnumber)
{
  bool hit = false;
  if (Enemies.size() == 0) return 0;
  for (int i=Enemies.size()-1;i >= 0; i--) // go backwards to avoid index shifting when element is removed
    {  
       if (Enemies[i].attacknumber == shotnumber and hit == false)
        {
          Enemies.erase(Enemies.begin()+i);
          if (shotnumber > 9) gunindex--;
          hit = true;
          if (value1picked == false)
          {
            value1 = shotnumber;
            value1picked = true;
          }
          else
          {
            value2 = shotnumber;
            value1picked = false;     
            value2picked = true;   
            if (removefromboard(value1+value2) != -1)
            {
               sumlog.push_back(to_string(value1)+" + "+to_string(value2)+" = "+to_string(value1+value2));
               if (MAXstacksize <= 10) MAXstacksize++;
               if (value1+value2 < 90)
                    {
                      createnewenemyinqueue(value1+value2);
                    }
               if (value1+value2 >= 90 and value1+value2 <= 99)  
                  {
                   createnewenemyinqueue(GetRandomValue(10,19));
                   createnewenemyinqueue(value1+value2);
                  }                
               if (value1+value2 == 100)  createnewlevel();
            }
            else 
            {
              sumlog.push_back(to_string(value1)+" + "+to_string(value2)+" = "+to_string(value1+value2)+" *not on board* ");
              createnewenemyinqueue(GetRandomValue(1,maxnumber));
              if (MAXstacksize >= 3) MAXstacksize--;
            }
          }
          hits++;
        };
    }
  if (!hit) 
    return -1;
  else
    return 0;
}

int ReadKeys()
{
   int c = 0;
   if (IsKeyPressed(KEY_ENTER))
        {
             if (removeenemy(gunvector[gunindex]) >= 0) // number found
             {
              EnterCount++;
              if (EnterCount == 2)
              {
              resultdisplayed = true;
              }
              if (EnterCount == 3)
              {
              resultdisplayed = false;
              value2picked = false;
              EnterCount = 1;
              }           
             }
             loadgunvector();  
        }
   if (IsKeyPressed(KEY_SPACE))
        {        
              gunindex++;
              if (gunindex >= gunvector.size()) gunindex = 0;
              //resultdisplayed = false; 
              if (EnterCount == 2)
              {
              resultdisplayed = false;
              value2picked = false;
              EnterCount = 0;
              }
        }
   if (IsKeyPressed(KEY_UP))
        {
              themearrayindex++;
              if (themearrayindex > 1) themearrayindex = 0;
              theme =  themearray[themearrayindex];
              settheme();

        }
    if (IsKeyPressed(KEY_LEFT))
        {
      
              herox--;

        }
    if (IsKeyPressed(KEY_DOWN))
        {

              heroy++;

        }
        if (IsKeyPressed(KEY_ONE))
        {
          c++;
        }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
         c++;
        }
    return 0;
}

int drawboard()
{
  int boardx = 700, boardy = 10, cellwidth = 50;
  //DrawText(to_string(100).c_str(),boardx+cellwidth*4,boardy+cellwidth*10,60, WHITE);
  drawRetroCharOneColour(boardx+cellwidth*2,boardy+cellwidth*10,10,8,Char1, rbwhite);
  drawRetroCharOneColour(boardx+cellwidth*2+100,boardy+cellwidth*10,10,8,Char0, rbwhite);
  drawRetroCharOneColour(boardx+cellwidth*2+200,boardy+cellwidth*10,10,8,Char0, rbwhite);
  for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
     if (Board[i][j] != -1)
                draw2digits(boardx+cellwidth*j,boardy+cellwidth*i,Board[i][j],1,rblightpink);
  return 0;
}

int drawsumlog()
{
  int j = 0;
  for (int i=sumlog.size()-1; i >= 0 and j <= 10 ; i--)
    {  
       DrawText(sumlog[i].c_str(),40,j*30,30, WHITE);
       j++;
    }
  return 0;
}

int main() {
    settheme();
    InitWindow(screenWidth, screenHeight, "Math Attack! or MathQuix"); // RNG seed is set randomly in InitWindow !!
    float moveInterval = 0.01f; // 10ms b/w move
    float moveTimer = 0.0f;
    Vector2 MousePos;
    SetTargetFPS(60);
    fillboard();
    loadgunvector();
    sumlog.clear();
    while (!WindowShouldClose()) 
    {
        ReadKeys();
        float dt = GetFrameTime(); // seconds since last frame 
        moveTimer += dt; 
        if (moveTimer >= moveInterval) 
          { 
            moveenemies();            
            if (enemymovement >= 40)
            {      
                enemymovement = 0;
                if (Enemies.size() <= MAXstacksize)
                {
                  createnewenemyinqueue(GetRandomValue(1,maxnumber));
                  loadgunvector();
                  createdenemies++;   
                }  
                if (Enemyqueue.size() > 0)
                {
                  Enemies.push_back(Enemyqueue.back());
                  Enemyqueue.pop_back();
                  loadgunvector();
                }     
            }
            moveTimer = 0.0f; // reset timer 
          }

        BeginDrawing();         // these two lines MUST go first when drawing
        ClearBackground(rbbackgroundcolour); // these two lines MUST go first when drawing

        DrawRectangleLines(0,0,screenWidth,screenHeight,YELLOW);
        drawboard();
        drawsumlog();
        MousePos = GetMousePosition();
        if (gunvector.size() > gunindex)
         {
          if  (gunvector[gunindex] < 10)
                draw2digits(screenWidth/2-100,screenHeight-100, gunvector[gunindex], 7, rblightgreen);
              else
               draw2digits(screenWidth/2-70,screenHeight-100, gunvector[gunindex], 7, rblightgreen);  
         }
        DrawText(("Enemies: "+to_string(9+levels[level]-hits)).c_str(),screenWidth/2-40,screenHeight-40,40, WHITE);
        DrawText(("EnterCount: "+to_string(EnterCount)).c_str(),screenWidth*0.75,screenHeight-40,40, WHITE);
        DrawText(("Level: "+to_string(level)).c_str(),screenWidth*0.25,screenHeight-40,40, WHITE);

        resultx = 800;
        resulty = 650;
        if (value1picked == true)
        {
          draw2digits(resultx,resulty,value1,3,rblightgreen);
        }
         if (resultdisplayed  == true)
        {
          draw2digits(resultx,resulty,value1,3,rblightgreen);
          draw2digits(resultx+3*5*8,resulty,value2,3,rblightgreen);
          draw2digits(resultx+6*5*8+8*2,resulty,value1+value2,3,rblightgreen);
        }
        
        drawCharfromArray(herox, heroy, 3,8, CharBob);
        for (int i = 0; i< 10;i++)
            draw2digits(herox+300, heroy+i*8*(3+i), 88, i, rblightgrey);
        drawRetroChar(herox+300, heroy+200, 2,8, Char9);
        for (int i = 1; i < 10; i++)
            drawRetroChar(herox, heroy+i*80, 3,8, CharBob); 

        for (int i = 1; i < 10; i++)
            drawRetroChar(200, 10+i*80, i,8, Char3); 

        
        drawRetroCharOneColour(resultx, resulty+4,3,8,CharUnderline,rbgray24);
        drawRetroCharOneColour(resultx+5*8, resulty+4,3,8,CharUnderline,rbgray24);
        drawRetroCharOneColour(resultx+2*5*8, resulty,4,8,CharPlus2,rblightgreen);
          drawRetroCharOneColour(resultx+3*5*8-2, resulty+4,3,8,CharUnderline,rbgray24);
          drawRetroCharOneColour(resultx+4*5*8-8, resulty+4,3,8,CharUnderline,rbgray24);
          drawRetroCharOneColour(resultx+4*5*8+2-8, resulty+40,3,8,CharUpArrow,rbgray24);
        drawRetroCharOneColour(resultx+5*5*8+8, resulty,3,8,CharEquals,rblightgreen);
        drawnemies();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
