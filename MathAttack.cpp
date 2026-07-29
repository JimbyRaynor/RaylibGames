#include "raylib.h"
#include <string>
#include <cstring>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// compile: g++ MathAttack.cpp -o MathAttack -lraylib -lm -ldl -lpthread -lGL -lX11
// run:     ./MathAttack
// Ctrl-C to close crashed program
// raylib uses float for most numbers, and so use 2.0f to convert int to float. Note that 2.0 will be a double
// Only use GameMaker for final animations and sound. Make full game (o/w animations) with raylib


#pragma region TODO
// refactor
// design levels . . . can actually make pictures with goldcard binary patterns, just like peggle
// like peggle. Blue numbers optional. All orange numbers must be hit. Similar bonuses?
// consequtive hits of orange numbers gets a chain bonus

// store game state in enum

// make like a card game
// Look at minesweeper/Majong/card games for tile ideas
// Bonus (blue) tiles give extra random tiles (and other options like peggle, double score etc)

// Can change selector arrows to balls, or even small numbers
// Flowers for level progress?

// New name: 8-bit Math Game
// Create new universe of Math characters and scenes. Base on famous mathematicians/diagrams. Graph Theory. Four colour Theorem, etc.

// Bright math colours: Yellow, Green, Blue, Red
// Kangaroo jimby?

// Can do ternary operations as well !!!
// Simulate 6502 CPU??

// Big bonus for hitting a board number since 
// (a) this is fun
// (b) helps to have 3 or more big numbers in crates
// (c) encourages adding in head since a mistakes leads to the big number being removed from drops

// Name things:
  // Dropping number - 
  // Big (orange) numbers - 
  // Green numbers - Atoms?
  // Crates - Crates?

// Tutorial level needs to be very fast and painless. Just add to 10.

// Long animation at end of each level (like Peggle)

// Give each level a name like "clear the board", "even numbers", "even numbers 2", etc
// look at number theory book for ideas 

// +,-,*,/  can also drop from sky. If selected, the operation changes!!!  risky????


// Draw a finite state machine (on Kindle) for difficult logic problems while programming

// This shooting mechanic can be used for many different games +-*/:
//   (a) Table filled with all 8s
//   (b) Invaders/tower defense numbers falling from sky

// draw peggle balls/pegs. a + b = c: a spawns a balls, b spawns b balls and all move into c. If there is a match in the table, then all move into table
// spot

// Scrolling message telling what to do ...

// Think freecell for random type games


// Make the screen come alive even if not playing the game
// lots of animations 

// hires Battery meter progress bar?

// make points for each shot float UP

// Look at Tetris for game design and music
// Avoid over-tall stack by only adding from queue when size <= 10 ?? needed ?? how to increase stack size while playing game?
// mistakes decrease bonus by 1000

// send in some bonus numbers now and then which are worth a lot of points


// Same for (a+b)+c, a+(b+c)  ???? add algebra SLOWLY
// Look at expensive watch faces CASIO, SEIKO, etc. for screen design
// Look at CASIO 8-attack and invaders videos for level progression

// small Chars running on top of big "Math Addition Game" sign is fun (look at jumpman, gunner)

// Draw controls  AIM  : <spacebar>
//                FIRE : <Enter>

// Just remove bonus for mistakes

// Attractor screen (like in arcades) shows demo game how to play AIM + FIRE

// Take photos of arcade buttons: white (AIM Spacebar) + red (FIRE Enter)
// Put game inside arcade cabinet 1920*1080 so that smaller screen resolutions can still see game 1600 x 800

// THEMES:
// 2. Standard dark mode with green text
// 2. Retro Themes: White text, Green Text, Red Text, Rainbow Text
// 3. Minesweeper style
// 5. Latex - everything in LaTeX
// 6. The Matrix screensaver theme?

// LEVELS:
// Levels are chosen like in peggle, with intro etc.
// Draw a picture of each level on Kindle Scribe
//        Make puzzle levels where there is only one solution.
// 0. Training: numbers do not get removed from board, and ONLY need to get to a sum of 30
// 4. What other types? Look for other famous theorems of number theory
// 4. Big gaps no 20s, 40s, 60s, 80,s
// 4.       no 30,40,50,60s, etc.
// 5. pyramid pattern
// 6. LHS only
// 7. RHS only
// bonus level: every natural number > 3 is a sum of two primes
// Level completed when sum = 100. Then 100 explodes into fireworks like peggle
// FireWorks Clock type of rockets/fireworks - find code :)
// Orange numbers give bonus?

// POINTS:
//  Score = 100-y for dropping number ** cannot so this** since then just let numbers accumulate at top!!!

// BONUS:
// colourful bonus number moves around in pattern on table
// Bonus hit repairs a removed tile
// Bonus for shorter path to 100

// BUGS
// dropping numbers overlap on fast game 

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

// BINGO style
// Complete row or column gives a bonus score

// "Orange Peg" numbers give bonus multipliers, but also give an extra 10-18 number
// Casino style board?

// score = sum of the two numbers (high numbers give best score), and chains can be made naturally.
// the harder the sum, the bigger the score


//  Design fixed, not random, levels on Kindle Scribe
// use Theme/inverse text for *big* explosion effect

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

// levels for +,-,/,*, etc
//  / splits into divisor + reminder ?

// chars walking across screen to show progress ?
// Look at Donut Dodo for ideas of background animations
#pragma endregion
using namespace std;

int screenWidth = 1200; 
int screenHeight = 800;
string theme = "dark";    // dark, CASIO


//string mystring;
// note that mystring.c_str() converts the C++ string mystring to the C array of characters

Color HexToColour(int hexValue) {
    Color c;
    c.r = (hexValue >> 16) & 0xFF;  // red
    c.g = (hexValue >> 8) & 0xFF;   // green
    c.b = hexValue & 0xFF;          // blue
    c.a = 255;                      // default opaque
    return c;
}


#pragma region png sprite textures
  Texture2D diamondgreenpng, diamondwhitepng;
  Texture2D selectorgreenpng, selectorwhitepng;
  Texture2D downarrowgreenpng, downarrowyellowpng, connectorgreenpng, connectoryellowpng;
  Texture2D goldcardpng;
  Rectangle selectorrect;
  float selectorheight, selectorwidth;
#pragma endregion




#pragma region fixed LED Colours
 // DO NOT CHANGE
 // needed for LEDColour pixel editor
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

Color rbgray00 = HexToColour(0x666666);
Color rbgray0 = HexToColour(0x999999);
Color rbgray1 = HexToColour(0xAAAAAA);
Color rbgray2 = HexToColour(0xCCCCCC);
Color rbgraytext = HexToColour(0x1E1E1E);
Color rbgray24 = HexToColour(0xC8C8C8);
Color rbgray3 = HexToColour(0xEEEEEE);


 // DO NOT CHANGE
 // needed for LEDColour pixel editor
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

//Color ColourRainbow[10] = { rbwhite, rblightgreen, rbdarkyellow,
//                              rbdarkpink, rbblue, rbred, rbgreen, rbbrown, rbaqua, rbpurple};

Color ColourRainbow[10] = {  rblightgreen, rblightgreen, rblightgreen, rblightgreen, rblightgreen, rblightgreen, rblightgreen, 
                             rblightgreen, rblightgreen, rblightgreen};

Color ColourCASIOArray[10] = { rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext};


Color EnemyColourArray[10];

Color resultcolour = rblightgreen;
#pragma endregion


// There is a Raylib native version: ColorIsEqual
bool ColorsEqual(Color a, Color b) {
    return a.r == b.r &&
           a.g == b.g &&
           a.b == b.b &&
           a.a == b.a;
}

// from CoPilot
bool ShowMessageBox(const char* title, const char* message)
{
    const int boxW = 300;
    const int boxH = 150;

    while (true)
    {
        BeginDrawing();
        //ClearBackground(BLACK);

        // Dim background
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0,0,0,150});

        // Box
        int x = GetScreenWidth()/2 - boxW/2;
        int y = GetScreenHeight()/2 - boxH/2;
        DrawRectangleRounded({(float)x, (float)y, (float)boxW, (float)boxH}, 0.2f, 8, RAYWHITE);

        DrawText(title, x + 20, y + 10, 20, DARKGRAY);
        DrawText(message, x + 20, y + 50, 18, GRAY);

        // OK button
        Rectangle btn = { (float)x + boxW/2 - 40, (float)y + boxH - 40, 80, 30 };
        DrawRectangleRounded(btn, 0.3f, 8, LIGHTGRAY);
        DrawText("OK", btn.x + 25, btn.y + 7, 20, DARKGRAY);

        // Click detection
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetMousePosition(), btn))
        {
            EndDrawing();
            return true;
        }

        EndDrawing();
    }
}



#pragma region Themes
string themearray[2] = {"dark", "CASIO"}; // uparrow to change
int themearrayindex = 0;
Color rbbackgroundcolour = BLACK;

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
#pragma endregion




#pragma region LED graphics arrays
int CharBob[64] = {1,18,23,23,23,23,18,18,1,18,18,23,23,23,18,18,14,16,16,16,16,16,16,16,17,16,0,0,16,0,0,16,0,16,0,0,16,0,0,16,0,16,16,16,16,16,16,16,0,18,1,1,1,1,17,17,23,23,23,18,18,18,23,23};
int CharEnemy1[64] = {5,0,0,17,0,0,0,5,0,5,0,0,17,0,5,0,5,0,11,17,0,11,0,5,0,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5,5,5,24,33,24,33,5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5,0};
int CharBall[64] = {0,0,0,21,21,0,0,0,0,0,19,19,19,19,0,0,0,19,16,16,16,16,19,0,21,19,16,33,33,16,19,21,21,19,16,33,33,16,19,21,0,19,16,16,16,16,19,0,0,0,19,19,19,19,0,0,0,0,0,21,21,0,0,0};
int CharBallSmall[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,19,21,0,0,0,0,0,19,33,19,0,0,0,0,0,21,19,21,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharCrate[256] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,17,0,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17};
int CharCrateWide[1024] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,17,0,0,0,0,0,0,0,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int CharBlock[576] = {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19};

int CharA[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharB[64] = {0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int CharC[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharD[64] = {0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int CharE[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharF[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharG[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharH[64] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharI[64] = {0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int CharJ[64] = {0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int CharK[64] = {0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharL[64] = {0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharM[64] = {1,1,0,0,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharN[64] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharO[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharP[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharQ[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1};
int CharR[64] = {0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharS[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharT[64] = {0,1,1,1,1,1,1,0,0,1,0,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0};
int CharU[64] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharV[64] = {1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,0,1,1,1,0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0};
int CharW[64] = {1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharX[64] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharY[64] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0};
int CharZ[64] = {0,1,1,1,1,1,1,0,0,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};

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
int CharUnderline[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0};
int CharEquals[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharUpArrow[64] = {0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};
int CharColon[64] = {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharRightArrow[64] = {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};

int CharLEDRightArrow[64] = {0,0,16,17,0,0,0,0,0,0,0,16,17,0,0,0,0,0,0,0,16,17,0,0,0,0,0,0,0,16,16,0,0,0,0,0,16,17,0,0,0,0,0,16,17,0,0,0,0,0,16,17,0,0,0,0,0,0,0,0,0,0,0,0};
int CharLEDDownArrow[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0,16,0,17,16,0,0,0,16,17,0,0,17,16,0,16,17,0,0,0,0,17,16,17,0,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0};
int CharLEDUpArrow[64] = {0,0,0,16,0,0,0,0,0,0,17,16,17,0,0,0,0,17,16,0,16,17,0,0,17,16,0,0,0,16,17,0,16,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharLEDGreenRightArrow[64] = {0,0,10,11,0,0,0,0,0,0,0,10,11,0,0,0,0,0,0,0,10,11,0,0,0,0,0,0,0,10,10,0,0,0,0,0,10,11,0,0,0,0,0,10,11,0,0,0,0,0,10,11,0,0,0,0,0,0,0,0,0,0,0,0};
int CharLEDGreenDownArrow[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,10,0,11,10,0,0,0,10,11,0,0,11,10,0,10,11,0,0,0,0,11,10,11,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0};
int CharLEDGreenUpArrow[64] = {0,0,0,10,0,0,0,0,0,0,11,10,11,0,0,0,0,11,10,0,10,11,0,0,11,10,0,0,0,10,11,0,10,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int CharLEDSelector[1024] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,17,0,0,0,0,0,0,10,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,10,17,0,0,0,0,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,0,0,0,0,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,0,17,17,0,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,17,11,11,17,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,11,10,10,11,17,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,10,16,16,10,11,17,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,16,16,16,16,10,11,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,17,17,17,17,10,11,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,10,17,17,10,11,17,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,11,10,10,11,17,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,17,11,11,17,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,0,17,17,0,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,17,0,0,0,0,0,0,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int* digitarray[10] = {Char0, Char1, Char2, Char3,  // array of pointers to chars, this works well! Access with digitarray[charnum][bitnum] 
                       Char4, Char5, Char6, Char7, Char8, Char9};  

int* alphaarray[26] = {CharA, CharB, CharC, CharD, CharE, CharF, CharG, CharH, CharI, CharJ, CharK, CharL, CharM, CharN, CharO, CharP, CharQ, 
                       CharR, CharS, CharT, CharU, CharV, CharW, CharX, CharY, CharZ}; 
#pragma endregion




#pragma region GLOBALS
int deciseconds = 0; // 1/60 of a second timer for animations
int targetarrow = 0; 
int selectorframes = 32;
int selectorcount = 20;
int herox = 20;
int heroy = 20;
float cratex =  20;
float cratey = screenHeight-96;
float resultx = cratex+246+3*14-1+96;
float resulty = 650-15;
int numcrates = 7;
int numberfallx = cratex+8;
int numberfallbottom = cratey-(numcrates)*(16*3+6)+20;
int traily = -30;
int totalenemies = 20;
int createdenemies = 0;
int enemymovement = 0;
int movementstep = 1;
int hits = 0;
int value1 = 0;
int value2 = 0;
bool value1picked = false;
bool value2picked = false;
bool resultdisplayed = false;
bool sumisonboard = false;
bool levelcomplete = false;
int EnterCount = 0;
int shootnumber = 1;
int shield = 3;
int level = 2;
int maxnumber = 2;
int levels[] = {0,3,9,14,14,20,33,32,32,32}; // Extra enemies added in each level; 
struct Tboarditem
{
  int number; // number = 0 if not available
  Color colour; // rbblue or rborange or rbyellow
                // rbblue is optional
                // rborange is required
                // rbyellow is "hit" and goldcard is displayed
};

Tboarditem Board[20][20];
int boardx = 238, boardy = 60, cellwidth = 70, cellheight = 40;
string operation = "+";
vector <int> gunvector;
vector <string> sumlog;
int gunindex = 1;
int MAXstacksize = 4;
int score = 0;
#pragma endregion
// create objects **after** defining them




bool TestPrime(int n)
{
  if (n <= 1) return 0;
  bool  isprime = true;
  for (int i = 2; i < n; i++)
       if (n % i == 0)
          isprime = false;
  return isprime;

}




#pragma region Draw Functions
void drawLine3Colour(float fromx, float fromy, float tox, float toy, int psize, int xstep, int ystep, Color Mycolour1, Color Mycolour2, Color Mycolour3)
{
  Vector2 vstart = { fromx, fromy};
  Vector2 vend = { tox, toy};
  DrawLineEx(vstart, vend, psize, Mycolour1);
  vstart.x = vstart.x + xstep;
  vstart.y = vstart.y + ystep;
  vend.x = vend.x + xstep;
  vend.y = vend.y + ystep;
  DrawLineEx(vstart, vend, psize, Mycolour2);
  vstart.x = vstart.x + xstep;
  vstart.y = vstart.y + ystep;
  vend.x = vend.x + xstep;
  vend.y = vend.y + ystep;
  DrawLineEx(vstart, vend, psize, Mycolour3);
}

void drawRect3Colour(float fromx, float fromy, float tox, float toy, int psize, Color Mycolour1, Color Mycolour2, Color Mycolour3)
{
  
  //drawLine3Colour(fromx, fromy, fromx, toy,psize,psize,0, Mycolour1, Mycolour2, Mycolour3);
  //drawLine3Colour(fromx, toy-psize*2, tox, toy-psize*2,psize,0,psize, Mycolour1, Mycolour2, Mycolour3);
  //drawLine3Colour(tox, fromy, tox, toy,psize,psize,0, Mycolour1, Mycolour2, Mycolour3);
  //;drawLine3Colour(fromx+psize*2, fromy, tox, fromy,psize,0,psize, Mycolour1, Mycolour2, Mycolour3);

  Rectangle rect1={fromx,fromy,tox-fromx,toy-fromy};
  DrawRectangleLinesEx(rect1,psize*3,Mycolour3);
  DrawRectangleLinesEx(rect1,psize*2,Mycolour2);
  DrawRectangleLinesEx(rect1,psize*1,Mycolour1);
}

void drawCharfromArray(int previewx, int previewy, int psize, int width, int myarray[])
     {
       Color Mycolour;
       int loc = 0;
       for (int i=0;i < width; i++ )
         for (int j=0; j < width; j++)
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

void drawChar3Colour(int previewx, int previewy, int psize, int bitwidth, int myarray[], Color Mycolour1, Color Mycolour2, Color Mycolour3)
     {
       int loc = 0;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              if (myarray[loc] != 0)
              {
               if (i<2) 
                  DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour1);  
               else if (i>3) 
                  DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour3);
               else 
                  DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour2);     
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

void draw2digits3colour(int locx, int locy, int mynum, int psize, Color Mycolour1, Color Mycolour2, Color Mycolour3)
{
  int first = mynum / 10;
  int second = mynum % 10;
  if (first > 0) 
   { 
    drawChar3Colour(locx, locy, psize, 8, digitarray[first], Mycolour1, Mycolour2, Mycolour3 );
   }
  drawChar3Colour(locx+ 8*(psize), locy, psize, 8, digitarray[second], Mycolour1, Mycolour2, Mycolour3);
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

void draw2digitsSolid2(int locx, int locy, int mynum, int psize, Color Mycolour)
{
  int first = mynum / 10;
  int second = mynum % 10;
  if (first > 0) 
   { 
    drawCharOneColour(locx, locy, psize, 8, digitarray[first], Mycolour);
   }
  drawCharOneColour(locx+ 6*psize, locy, psize, 8, digitarray[second], Mycolour);
}

void ShowColourScore2(int locx, int locy, int myscore, int psize, Color Mycolour,  int numzeros=9)
{
string stringscore="";
string num = to_string(myscore);
for (int i = num.length(); i < numzeros; i++) // Add leading zeros until the string reaches numzeros length
{
    stringscore += '0';
}
stringscore += num;
 
for (int i = 0; i < stringscore.size(); i++) 
{
    char c = stringscore[i];
    int index = c - '0';
    auto value = digitarray[0];
    if (c >= '0' && c <= '9')  
       {
        value = digitarray[c - '0'];
       }
    drawRetroCharOneColour(locx+ i*8*(psize+1), locy, psize, 8, value, Mycolour);
}
}

string ToUpperCase(string mystring)
{
  char c;
  string resultstring = mystring;
  for (int i = 0; i < mystring.size(); i++)
  {
    c = mystring[i];
    if (c >= 'a' and c <= 'z')
       c = c - 32; // convert to UpperCase character;
    resultstring[i] = c;
  }
  return resultstring;
}

void ShowColourText(int locx, int locy, string mytext, int psize, Color Mycolour)
{
   char c;
   string UPtext;
   UPtext = ToUpperCase(mytext);
   for (int i = 0; i < UPtext.size(); i++) 
   {
     c = UPtext[i];
     auto value = alphaarray[0];
     if (c >= 'A' && c <= 'Z')  
       {
        value = alphaarray[c - 'A'];
       }
     if (c == ':') value = CharColon;
     drawRetroCharOneColour(locx+ i*8*(psize+1), locy, psize, 8, value, Mycolour);
   }
}
#pragma endregion




#pragma region paths (from CoPilot)

double lerp(double a, double b, double t) {
    return a + (b - a) * t;
}

std::vector<std::pair<double, double>> interpolate(
        const std::pair<double, double>& p0,
        const std::pair<double, double>& p1,
        int steps) 
{
    std::vector<std::pair<double, double>> result;
    result.reserve(steps);

    for (int i = 0; i < steps; ++i) {
        double t = static_cast<double>(i) / steps;
        double x = lerp(p0.first,  p1.first,  t);
        double y = lerp(p0.second, p1.second, t);
        result.emplace_back(x, y);
    }

    return result;
}

std::vector<std::pair<double,double>> interpolatePath(
        const std::vector<std::pair<double,double>>& path,
        int stepsPerSegment)
{
    std::vector<std::pair<double,double>> full;

    for (size_t i = 0; i + 1 < path.size(); ++i) {
        auto segment = interpolate(path[i], path[i+1], stepsPerSegment);
        full.insert(full.end(), segment.begin(), segment.end());
    }

    return full;
}


// defender path
std::vector<std::pair<double, double>> PATHG = {
    {-30, 250},
    {370, 250},
    {390, -30}
};

// other paths
std::vector<std::pair<double, double>> PATHPARADE = {
    {700, 700},
    {1000, 700},
    {1000, 200},
    {200, 200},
    {200,250}
};

auto fullPath = interpolatePath(PATHPARADE, 200);
#pragma endregion




#pragma region board functions
int fillboard() // all orange numbers must be removed, so make 100 an orange number (if 100 is a valid target)
{
  Board[10][10].number = 0;
  Board[10][10].colour = rbblue;
  for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
   {
     Board[i][j].colour = rbblue; // not required for level completion
     Board[i][j].number = 0; // not available, do not draw
     if (level == 9)
     {
        if (GetRandomValue(0,9) >= 7)   // hardest level 7 (random)
        {
           Board[i][j].number = i*10+j;
           Board[i][j].colour = rborange; // required number for level completion
        }
     }
     if (level == 1) // all numbers
     {
          Board[i][j].number = i*10+j;
          Board[i][j].colour = rborange; // required number for level completion
     }
     if (level == 2) // evens
     {
       if ((i*10+j) % 2 == 0 and i<=0 and j<= 4) 
       {
          Board[i][j].number = i*10+j;
          Board[i][j].colour = rborange; // required number for level completion
       }
     }
     if (level == 3)  // odds
     {
       if ((i*10+j) % 2 == 1) 
       {
          Board[i][j].number = i*10+j;
          Board[i][j].colour = rborange; // required number for level completion
       }
     }
    if (level == 4)  // primes
     {
          if ( TestPrime(i*10+j) == true )
          {
           Board[i][j].number = i*10+j;
           Board[i][j].colour = rborange; // required number for level completion
          }
     }
   }
  Board[0][0].colour = rbblue; // (0,0) is not a valid target (number 0)
  Board[0][0].number = 0; 
  Board[0][1].colour = rbblue; // (0,1) is not a valid target (number 1)
  Board[0][1].number = 0; 
  return 0;
}

void drawfilledtablecell(int i, int j, int num)
{
  drawCharfromArray(boardx+j*cellwidth, boardy+i*cellwidth, 2,24, CharBlock); 
  draw2digitsSolid2(boardx+j*cellwidth+5, boardy+i*cellwidth+12, num, 3, BLACK);
}


int drawboard()
{
  // draw 100
  drawRetroCharOneColour(boardx+cellwidth*2.7,boardy+cellheight*10,10,8,Char1, rbwhite);
  drawRetroCharOneColour(boardx+cellwidth*2.7+100,boardy+cellheight*10,10,8,Char0, rbwhite);
  drawRetroCharOneColour(boardx+cellwidth*2.7+200,boardy+cellheight*10,10,8,Char0, rbwhite);

  //cells
  for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
   {
     
    if ( ColorsEqual(Board[i][j].colour, rbyellow) ) // goldcard
       {
        DrawTextureEx(goldcardpng,{(float) boardx+cellwidth*j-16,(float) boardy+cellheight*i-15},0,1,WHITE);
        if (Board[i][j].number < 10)
          draw2digits3colour(boardx+cellwidth*j-26,boardy+cellheight*i-9,Board[i][j].number,4,rblightyellow,rbyellow,rbdarkyellow);
        else
          draw2digits3colour(boardx+cellwidth*j-12,boardy+cellheight*i-9,Board[i][j].number,4,rblightyellow,rbyellow,rbdarkyellow);
       }
    else if (Board[i][j].number > 1)
          draw2digits(boardx+cellwidth*j,boardy+cellheight*i,Board[i][j].number,1,Board[i][j].colour);

  } 
  
   //border  
   //drawRect3Colour(boardx-50,boardy-50, boardx+cellwidth*9+100, boardy+cellheight*9+50+100, 3, rblightyellow,rbyellow,rbdarkyellow);
  return 0;
}

int findonboard(int number)
{
if (number == 100) return 0;
for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
     if (Board[i][j].number == number)
     {
          return 0;
     }
return -1;
}

bool testlevelend()
{
  bool result = true;
  for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
       if ( ColorIsEqual(Board[i][j].colour, rborange) ) 
       {
        result = false;
        //ShowMessageBox("testlevelend()", ("Found number at "+to_string(i)+","+to_string(j)).c_str());
       }
  return result;
} 

int removefromboard(int number)
{
if (number == 100) 
{
  Board[100][100].colour = rbyellow; // gold card
  return 0;
}
for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
     if (Board[i][j].number == number)
     {
          // ShowMessageBox("removefromboard()", ("Found number at "+to_string(i)+","+to_string(j)).c_str());
          Board[i][j].colour = rbyellow; // gold card
          // examine Board[][] for level completion
          if (testlevelend() == true)  
          {
            levelcomplete = true;
            // ShowMessageBox("removefromboard()", "Level Completed");
          }
          return 0;
     }
return -1;
}

int findminboard()
{
  int min = 99;
  for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
       if (Board[i][j].number < min and Board[i][j].number != 0) min = Board[i][j].number;
  return min;
}

Vector2 boardnumbertopoint(int boardnumber)
{
  Vector2 mypoint;
  int row, col;
  col = boardnumber % 10;
  row = boardnumber / 10;
  return {(float) boardx+(col+0.5f)*cellwidth, (float) boardy+(row-1+0.7f)*cellheight};
}
#pragma endregion





#pragma region Classes and Objects
class Ball
{
   public:
    Ball(int startx, int starty, int targetx, int targety);  // constructor, *must* be named the same as the class
    int draw();
    int move();
    int x,y;
    int tagx, tagy;
    int ipath;
    int dx = 1;
    int dy = 0;
   private:
};
Ball::Ball(int startx, int starty, int targetx, int targety) // constructor code
{
  x = startx;
  y = starty;
  ipath = 0;
  tagx = targetx;
  tagy = targety;
}
int Ball::draw()
{
  drawCharfromArray(x, y, 1,8, CharBall);
  return 0;
}
int Ball::move()
{
    //y = y + dy;
    //x = x + dx;
    if (ipath++ >= fullPath.size()) ipath = 0;
    x = fullPath[ipath].first;
    y = fullPath[ipath].second;
    return 0;
}

// SpriteObj is for loading and displaying pngs
class SpriteObj
{
    public:
    SpriteObj(float startx, float starty, float myscale, float myrotation);  // constructor, *must* be named the same as the class
    int draw();
    int move();
    int movetotarget(float myspeed);
    int loadtexture(string filename);
    bool textureloaded = false;
    bool alive = false;
    int targetnumber = 0;
    float x = 0,y = 0;
    float targetx = 0, targety = 0;
    float dx = 1;
    float dy = 0;
    Texture2D pngtexture; // actually a bitmap (Raylib calls it a texture)
      // cannot create texture until after initwindow ...
      // so load manually after initwindow 
    float scale = 1;
    float angle = 0;
   private:
};
SpriteObj::SpriteObj(float startx, float starty, float myscale, float myrotation) // constructor code
{
  x = startx;
  y = starty;
  scale = myscale;
  angle = myrotation;
}

int SpriteObj::loadtexture(string filename)
{
  if (textureloaded == false)
  {
    pngtexture = LoadTexture(filename.c_str()); // LoadTexture() MUST be called AFTER InitWindow
    SetTextureFilter(pngtexture, TEXTURE_FILTER_POINT); // pixel perfect scaling
    textureloaded = true;
  }
  return 0;
}

int SpriteObj::draw()
{
  if (textureloaded and alive)
   { 
     DrawTextureEx(pngtexture,{x,y},angle,scale,WHITE);
    if (targetnumber < 10)
          draw2digits3colour(x-10,y+6,targetnumber,4,rblightyellow,rbyellow,rbdarkyellow);
       else
          draw2digits3colour(x+5,y+6,targetnumber,4,rblightyellow,rbyellow,rbdarkyellow); 
   }
  return 0;
}
int SpriteObj::move()
{
    y = y + dy;
    x = x + dx;
    return 0;
}
int SpriteObj::movetotarget(float myspeed)
{
    
    float mdx = targetx-x;
    float mdy = targety-y;
    float length = sqrtf(mdx*mdx+mdy*mdy);
    dx = mdx/length*myspeed;
    dy = mdy/length*myspeed;
    move();
    if ( sqrtf((x-targetx)*(x-targetx) + (y-targety)*(y-targety)) < myspeed )
    {
       alive = false;
       removefromboard(targetnumber);
    }
    return 0;
}


// create objects *after* defining them!
SpriteObj goldcard(resultx+6*5*8+8*2+24+12, resulty, 1.0, 0); 

class Arrow
{
  public:
   Arrow(int startx, int starty, int mydrawnumber); // constructor *must* be named the same as the class
   int draw();
   int x,y;
   int drawnumber;
  private:
};

Arrow::Arrow(int startx, int starty, int mydrawnumber) // constructor
{
  x = startx;
  y = starty;
  drawnumber = mydrawnumber;
}

int Arrow::draw()
{
  if (drawnumber++ >= 60) {drawnumber = 0;}
  if (drawnumber < 50)
     drawCharfromArray(x, y, 3,8, CharLEDRightArrow);
  else
     drawCharfromArray(x, y, 3,8, CharLEDGreenRightArrow);
  return 0;
}

class Crate
{
  public:
    Crate(float startx, float starty); // constructor *must* be named the same as the class
    int draw();
    float x,y;
    int number;
  private:
};

Crate::Crate(float startx, float starty) // constructor code
{
  x = startx;
  y = starty;
  number = 1;
}
int Crate::draw()
{
  drawCharfromArray(x, y, 3,32, CharCrateWide);
  if (number != 0)
    {
      Color Mycolour;
      if (number < 10)
         Mycolour = EnemyColourArray[number];
      else
         Mycolour = rbdarkorange;
      draw2digits(x+8, y+9, number, 3, Mycolour);
    }
  return 0;
}



vector <Crate> Crates;
int makecrates()
{
  for (int i=0; i < numcrates; i++)
   {
    Crate cratetmp(cratex,cratey-(16*3+0)*i);
    Crates.push_back(cratetmp);
   }
  return 0;
}

int stackincrate(int mynumber)
{
  for (int i=0; i < numcrates; i++)
   {
    if (Crates[i].number == 0)
    {
       Crates[i].number = mynumber;
       return 1;
    }
   }
  return -1;
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
Enemy::Enemy(int startx, int starty, int number) // constructor code
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
    if (y <= numberfallbottom)
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
    if (i != index and (Enemies[index].y+42 - Enemies[i].y <= 24) and (Enemies[index].y+42 - Enemies[i].y >= 0) )
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
          if (Enemies[i].y > cratey-(16*3+6)*numcrates)
           if (stackincrate(Enemies[i].attacknumber) >= 0)
           {
            Enemies.erase(Enemies.begin()+i);
            i--;
           }
         }
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
#pragma endregion



int createnewenemyinqueue(int value)
{
  Enemy Entmp(numberfallx,-30,value);
  if (value > maxnumber and value < 10)
  {
    maxnumber = value;
  }
  Enemyqueue.push_back(Entmp);
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
     hits = 0;
     EnterCount = 0;
     resultdisplayed = false;
     maxnumber = 2;
     createdenemies = 0;
     createnewenemyinqueue(GetRandomValue(1,maxnumber));
     fillboard();
     return 0;
  }

int removeenemyatgunindex()
{
  int hitscore;
  int shotnumber;
  hitscore = 10;
  score = score + hitscore;
  shotnumber = Crates[gunindex].number;
  if (shotnumber == 0) return -1;
  Crates[gunindex].number = 0;
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
            if (findonboard(value1+value2) > -1) // found in board
            {
               resultcolour = rblightgreen; // hit board number
               if (goldcard.alive) // goldcard already flying
                {
                  if (goldcard.targetnumber == value1+value2) resultcolour = rbred; // board number already gold, so a miss!
                }    
               if (ColorsEqual(resultcolour,rblightgreen))
               {        
                    //removefromboard(goldcard.targetnumber); // set board number to gold
                    // will remove when goldcard reaches target
                  goldcard.x = resultx+6*5*8+8*2+24+12+24;
                  goldcard.y = resulty;
               } 
               goldcard.targetx = boardnumbertopoint(value1+value2).x-50;
               goldcard.targety = boardnumbertopoint(value1+value2).y;
               goldcard.alive = true;
               goldcard.targetnumber = value1+value2;
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
               sumisonboard = true;
            }
            else 
            {
              resultcolour = rbred;
              sumlog.push_back(to_string(value1)+" + "+to_string(value2)+" = "+to_string(value1+value2)+" *not on board* ");
              createnewenemyinqueue(GetRandomValue(1,maxnumber));
              if (MAXstacksize >= 3) MAXstacksize--;
              sumisonboard = false;
            }
          }
          hits++;
return 0;
};

int ReadKeys()
{
   int c = 0;
   if (IsKeyPressed(KEY_ENTER))
        {
          //ShowMessageBox("Note:", "Enter Pressed");
             //Enemies[gunindex].attacknumber
            // if (removeenemy(gunvector[gunindex]) >= 0) // enemy number found in descending list
            if (removeenemyatgunindex() >= 0)
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
        }
   if (IsKeyPressed(KEY_SPACE))
        {        
              gunindex++;
              if (gunindex >= numcrates) gunindex = 1;
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


#pragma region Arrow functions
int* arrowrightanimate(int loc)
{
  if (loc == targetarrow)
    return CharLEDRightArrow;
  else
    return CharLEDGreenRightArrow;
}

int* arrowdownanimate(int loc)
{
  if (loc == targetarrow)
    return CharLEDDownArrow;
  else
    return CharLEDGreenDownArrow;
}

Texture2D arrowdownanimatepng(int loc)
{
  if (loc == targetarrow)
    return downarrowyellowpng;
  else
    return downarrowgreenpng;
}

Texture2D connectoranimatepng(int loc)
{
  if (loc == targetarrow)
    return connectoryellowpng;
  else
    return connectorgreenpng;
}

Texture2D selectoranimatepng(int loc)
{
  if (loc == targetarrow)
    return selectorwhitepng;
  else
    return selectorgreenpng;
}

Texture2D diamondanimatepng(int loc)
{
  if (loc == targetarrow)
    return diamondwhitepng;
  else
    return diamondgreenpng;
}

int* arrowupanimate(int loc)
{
  if (loc == targetarrow)
    return CharLEDUpArrow;
  else
    return CharLEDGreenUpArrow;
}

int drawarrowchainright(int x, int y, int count)
{
  for (int i = 0; i < count; i++)
   {
      drawCharfromArray(x+i*24*2, y,3,8,arrowrightanimate(1));
      drawCharfromArray(x+i*24*2+12, y,3,8,arrowrightanimate(2));
      drawCharfromArray(x+i*24*2+24, y,3,8,arrowrightanimate(3));
      drawCharfromArray(x+i*24*2+36, y,3,8,arrowrightanimate(4));
   }
  return x+(count-1)*24*2+36+22; // use this for x value of downarrows that start at end of this arrow system 
} 

int drawarrowchainrightpng(float x, float y, int count)
{
  for (int i = 0; i < count; i++)
   {
      DrawTextureEx(arrowdownanimatepng(1),{x+i*24*2,   y+3*7},   270.0f,3.0f,WHITE);
      DrawTextureEx(arrowdownanimatepng(2),{x+i*24*2+12,y+3*7},270.0f,3.0f,WHITE);
      DrawTextureEx(arrowdownanimatepng(3),{x+i*24*2+24,y+3*7},270.0f,3.0f,WHITE);
      DrawTextureEx(arrowdownanimatepng(4),{x+i*24*2+36,y+3*7},270.0f,3.0f,WHITE);
   }
  return x+(count-1)*24*2+36+22; // use this for x value of downarrows that start at end of this arrow system 
} 

int drawarrowchaindown(int x, int y, int count)
{
  for (int i = 0; i < count; i++)
   {
      drawCharfromArray(x, y+i*24*2,3,8,arrowdownanimate(1));
      drawCharfromArray(x, y+i*24*2+12,3,8,arrowdownanimate(2));
      drawCharfromArray(x, y+i*24*2+24,3,8,arrowdownanimate(3));
      drawCharfromArray(x, y+i*24*2+36,3,8,arrowdownanimate(4));
   }
  return y+(count-1)*24*2+36+22; // use this for y value of rightarrows that start at end of this arrow system 
} 

int drawarrowchaindownpng(float x, float y, int count)
{
  for (int i = 0; i < count; i++)
   {
      DrawTextureEx(arrowdownanimatepng(1),{x,y+i*24*2},0.0f,3.0f,WHITE);
      DrawTextureEx(arrowdownanimatepng(2),{x,y+i*24*2+12},0.0f,3.0f,WHITE);
      DrawTextureEx(arrowdownanimatepng(3),{x,y+i*24*2+24},0.0f,3.0f,WHITE);
      DrawTextureEx(arrowdownanimatepng(4),{x,y+i*24*2+36},0.0f,3.0f,WHITE);
   }
  return y+(count-1)*24*2+36+22; // use this for y value of rightarrows that start at end of this arrow system 
} 

int drawarrowchainup(int x, int y, int count)
{
  for (int i = 0; i < count; i++)
   {
      drawCharfromArray(x, y-i*24*2   ,3,8,arrowupanimate(1));
      drawCharfromArray(x, y-i*24*2-12,3,8,arrowupanimate(2));
      drawCharfromArray(x, y-i*24*2-24,3,8,arrowupanimate(3));
      drawCharfromArray(x, y-i*24*2-36,3,8,arrowupanimate(4));
   }
  return y-(count-1)*24*2-36-22; // use this for y value of rightarrows that start at end of this arrow system 
} 

int drawarrowchainuppng(float x, float y, int count)
{
  for (int i = 0; i < count; i++)
   {
      DrawTextureEx(arrowdownanimatepng(1),{x+3*7,y-i*24*2   +3*7 },   180.0f,3.0f,WHITE);
      DrawTextureEx(arrowdownanimatepng(2),{x+3*7,y-i*24*2-12+3*7},180.0f,3.0f,WHITE);
      DrawTextureEx(arrowdownanimatepng(3),{x+3*7,y-i*24*2-24+3*7},180.0f,3.0f,WHITE);
      DrawTextureEx(arrowdownanimatepng(4),{x+3*7,y-i*24*2-36+3*7},180.0f,3.0f,WHITE);
   }
  return y-(count-1)*24*2-36-22; // use this for y value of rightarrows that start at end of this arrow system 
} 
#pragma endregion

void drawarrowsandinput()
{
  int inputstep = 0;

  if (value1picked == false or resultdisplayed == true)
       {
        inputstep = 6;
      }
  else
      {
        inputstep = 6+3;
      }

  float arrowsx = cratex+96+6+9; // start of arrow system
  float arrowsy = Crates[gunindex].y+12; // start of arrow system
  float arrows2x = 0, arrows2y = 0;
  //int arrowsdownx = 0;
  //int arrowsdowny = arrowsy-6;
  //arrows2x = drawarrowchainright(arrowsx,arrowsy,1);
  //arrows2y = arrowsy-6;
  
  //arrows2y = drawarrowchaindown(arrowsx,arrowsy,gunindex);
  arrows2y = drawarrowchaindownpng(arrowsx,arrowsy,gunindex)-1;
  arrows2x = arrowsx-6+18;
  //DrawLineEx({arrowsx+11,arrowsy}, {arrowsx+11,arrows2y+12}, 4, GREEN);
  DrawTextureEx(connectoranimatepng(1),{arrows2x-2*7+2,arrows2y},0.0f,3.0f,WHITE);
  arrowsx = drawarrowchainrightpng(arrows2x,arrows2y,inputstep)-3;
  arrowsy = arrows2y-15;
  //DrawLineEx({arrows2x-3,arrowsy+5+3*7}, {arrowsx+11,arrowsy+5+3*7}, 4, GREEN);
  DrawTextureEx(connectoranimatepng(1),{arrowsx,arrowsy+5*7+1},270.0f,3.0f,WHITE);
  drawarrowchainuppng(arrowsx,arrowsy,1);
  //DrawLineEx({arrowsx+11,arrowsy+5+3*7}, {arrowsx+11,arrowsy+5+3*7-60}, 4, GREEN);
  drawRetroCharOneColour(resultx, resulty+4,3,8,CharUnderline,rbgray00);
  drawRetroCharOneColour(resultx+5*8-8, resulty+4,3,8,CharUnderline,rbgray00);
  drawRetroCharOneColour(resultx+2*5*8+6, resulty,4,8,CharPlus2,rblightgreen);
  drawRetroCharOneColour(resultx+3*5*8+24, resulty+4,3,8,CharUnderline,rbgray00);
  drawRetroCharOneColour(resultx+4*5*8-8+24, resulty+4,3,8,CharUnderline,rbgray00);


  drawRetroCharOneColour(resultx+5*5*8+8+24+6, resulty,3,8,CharEquals,rblightgreen);
  if (value1picked == true)
        {
          draw2digits(resultx,resulty,value1,3,rblightgreen);
        }
  if (resultdisplayed  == true)
        {
          draw2digits(resultx,resulty,value1,3,rblightgreen);
          draw2digits(resultx+3*5*8+24,resulty,value2,3,rblightgreen);
          draw2digits(resultx+6*5*8+8*2+24+12,resulty,value1+value2,3,resultcolour);             
        }
}

void drawgunvector() // draw selector
{
  DrawTextureEx(diamondanimatepng(1),{cratex+96+6+9,Crates[gunindex].y+9},0.0f,3.0f,WHITE);
  selectorrect.x = selectorcount*selectorwidth;
  DrawTexturePro(selectorgreenpng, selectorrect,{cratex,Crates[gunindex].y-3,selectorwidth*3, // scale by 3
                                                                            selectorheight*3},{0,0},0.0f, WHITE);
}

#pragma region load textures
void rbcreatetexture(Texture2D &mytexture, string filename)
{
 mytexture = LoadTexture(filename.c_str()); // LoadTexture() MUST be called AFTER InitWindow
 SetTextureFilter(mytexture, TEXTURE_FILTER_POINT); // pixel perfect scaling
}

void rbloadtextures()
{
 rbcreatetexture(diamondgreenpng,"png/diamond1.png"); // make object?
 rbcreatetexture(diamondwhitepng,"png/diamond2.png");
 rbcreatetexture(selectorgreenpng,"png/selector.png");
 selectorwidth = selectorgreenpng.width/selectorframes;
 selectorheight = selectorgreenpng.height;
 selectorrect = {0.0f, 0.0f, selectorwidth, selectorheight}; 
 rbcreatetexture(selectorwhitepng,"png/selector2.png");
 rbcreatetexture(downarrowgreenpng,"png/downarrowgreen1.png");
 rbcreatetexture(downarrowyellowpng,"png/downarrowgreen2.png");
 rbcreatetexture(connectorgreenpng,"png/connector1.png");
 rbcreatetexture(connectoryellowpng,"png/connector2.png");
 rbcreatetexture(goldcardpng,"png/goldcard.png");
 goldcard.loadtexture("png/goldcard.png"); // call After initwindow ... 
}
#pragma endregion


int main() {
    settheme();
    InitWindow(screenWidth, screenHeight, "Math Addition Game"); // RNG seed is set randomly in InitWindow !!
    rbloadtextures(); // Must load textures after InitWindow
                      // Same for SpriteObj !!!
    //createsprites(); 
    float moveInterval = 0.01f; // 10ms b/w move
    float moveTimer = 0.0f;
    int boby = 0;
    Vector2 MousePos;
    SetTargetFPS(60);
    fillboard();
    sumlog.clear();


    makecrates();
    while (!WindowShouldClose()) 
    {
        ReadKeys();
        deciseconds++;
        if ( deciseconds % 4 == 0)
        {
          selectorcount++;
          if (selectorcount >= selectorframes) selectorcount = 0;
        }
         if (deciseconds % 32 == 0)
         {
           targetarrow++;
           if (targetarrow > 4) targetarrow = 1;
         }
        float dt = GetFrameTime(); // seconds since last frame 
        moveTimer += dt; 
        if (moveTimer >= moveInterval) 
          { 
            if (goldcard.alive) goldcard.movetotarget(8);
            moveenemies();                   
            if (enemymovement >= 40)
            {      
                enemymovement = 0;
                if (Enemies.size() <= MAXstacksize)
                {
                  createnewenemyinqueue(GetRandomValue(1,maxnumber));
                  createdenemies++;   
                }  
                if (Enemyqueue.size() > 0)
                {
                  Enemies.push_back(Enemyqueue.back());
                  Enemyqueue.pop_back();
                }     
            }
            moveTimer = 0.0f; // reset timer 
          }
        if (levelcomplete == true)
        {
          levelcomplete = false;
          level++;
          createnewlevel();
        }
        BeginDrawing();         // these two lines MUST go first when drawing
        ClearBackground(rbbackgroundcolour); // these two lines MUST go first when drawing

        DrawRectangleLines(0,0,screenWidth,screenHeight,YELLOW);
        drawboard();
        
        MousePos = GetMousePosition();
        
       

        ShowColourText(990, 20, "Score", 3, YELLOW);
        ShowColourScore2(960, 60, score, 3, YELLOW, 7);

      
        ShowColourText(990, 200, "Level", 3, YELLOW);
        ShowColourScore2(1026, 240, level, 3, YELLOW, 3);

        
        drawarrowsandinput();
        drawnemies();
        goldcard.draw();
        for (int i = 1;i < Crates.size(); i++)
          Crates[i].draw();
        drawgunvector(); // this is draw selector now!
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
