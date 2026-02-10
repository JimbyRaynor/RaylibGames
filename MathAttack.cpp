#include "raylib.h"
#include <string>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>

//compile: g++ MathAttack.cpp -o MathAttack -lraylib -lm -ldl -lpthread -lGL -lX11
//run:     ./MathAttack
// raylib uses float for most numbers, and so use 2.0f to convert int to float. Note that 2.0 will be a double

// Make level editor



using namespace std;

int screenWidth = 1200; 
int screenHeight = 800;

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

Color rbgray1 = HexToColour(0xAAAAAA);
Color rbgray2 = HexToColour(0xCCCCCC);
Color rbgray3 = HexToColour(0xEEEEEE);

Color AllColours[60] = {rblightblue, rbblue, rbdarkblue, rblightred, rbred, rbdarkred, rblightorange, rborange, rbdarkorange,
                       rblightgreen, rbgreen, rbdarkgreen, rblightpink, rbpink, rbdarkpink, rblightyellow, rbyellow, rbdarkyellow,
                       rblightgrey, rbgrey, rbdarkgrey, rblightbrown, rbbrown, rbdarkbrown, rblightaqua, rbaqua, rbdarkaqua,
                       rblightpurple, rbpurple, rbdarkpurple, rbblack, rberaser, rbwhite};                    


Color getColour(int myindex)
{
  if ( (myindex >= 1) and (myindex <= 33))
    return AllColours[myindex-1];
  else
    return rbblack; 
}

int Char1[64] = {1,18,23,23,23,23,18,18,1,18,18,23,23,23,18,18,14,16,16,16,16,16,16,16,17,16,0,0,16,0,0,16,0,16,0,0,16,0,0,16,0,16,16,16,16,16,16,16,0,18,1,1,1,1,17,17,23,23,23,18,18,18,23,23};
int CharBlock[576] = {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19};
int CharEnemy1[64] = {5,0,0,17,0,0,0,5,0,5,0,0,17,0,5,0,5,0,11,17,0,11,0,5,0,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5,5,5,24,33,24,33,5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5,0};

int Grid[100][100]; // Grid is not needed just remove all blocks with same value
int gridsize = 16;
int gridwidth = 50;
float griddensity = 0.35f;

int herox = gridsize-1;
int heroy = gridsize-1;

int gridtoxy(int gridloc)
{
     return gridloc*gridwidth+(gridwidth-24)/2;
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
     x = GetRandomValue(0,gridsize-6); // 0 to including gridsize-1
     y = GetRandomValue(0,gridsize-6); // 0 to including gridsize-1
     while (Grid[y][x] != 0 and count < 1000)
     {
       x = GetRandomValue(0,gridsize-6); // 0 to including gridsize-1
       y = GetRandomValue(0,gridsize-6); // 0 to including gridsize-1 
       count++;   
     }
     Grid[y][x] = 10;
     return 0;
}

int Enemy::move()
{
     if (x < herox and Grid[y][x+1]  == 0) {Grid[y][x] = 0; x++; Grid[y][x] = 10; return 0; }
     if (x > herox and Grid[y][x-1]  == 0)
     {
          Grid[y][x] = 0;
          x--;
          Grid[y][x] = 10;
          return 0; 
     }
     if (y < heroy and Grid[y+1][x]  == 0)
     { 
          Grid[y][x] = 0;
          y++;
          Grid[y][x] = 10;
          return 0; 
     }
     if (y > heroy and Grid[y-1][x]  == 0)
     {
          Grid[y][x] = 0;
          y--;
          Grid[y][x] = 10;
          return 0; 
     }
    return 0;
}

int Enemy::draw()
{
  drawCharfromArray(gridtoxy(x), gridtoxy(y), 3,8, CharEnemy1);
  return 0;
}
vector <Enemy> Enemies;

int moveenemy()
{
  for (int i=0;i<Enemies.size();i++)
        Enemies[i].move();
  return 0;
}

void fillgrid(float density)
{
     for (int i = 0; i < gridsize; i++)
       for (int j = 0; j < gridsize; j++)
       {
          if (GetRandomValue(0,100)/100.0f < density  and i+j != 2*gridsize-2) 
          {
              Grid[j][i] = 1;
          }
       }
}

void cleargrid()
{
     for (int i = 0; i < gridsize; i++)
       for (int j = 0; j < gridsize; j++)
              Grid[j][i] = 0;
}

void drawgrid()
{
     for (int i = 0; i < gridsize; i++)
       for (int j = 0; j < gridsize; j++)
       {
            if ( Grid[j][i] == 1 )  drawCharfromArray(i*gridwidth, j*gridwidth, 2,24, CharBlock); 
            if ( Grid[j][i] == 10 ) drawCharfromArray(gridtoxy(i), gridtoxy(j), 3,8, CharEnemy1);
       }
}

int pushblock(int x, int y, int dx, int dy)
{
   if (x+2*dx >= 0 and y+2*dy >=0 and x+2*dx < gridsize and  y+2*dy < gridsize) 
    if (Grid[y+dy][x+dx] == 1)
    {
      if  (Grid[y+2*dy][x+2*dx] == 0 )
      {
       Grid[y+2*dy][x+2*dx]  = 1;
       Grid[y+dy][x+dx]  = 0; 
       return 0;
      }
      else return -1;
    }
   if (x+dx >= 0 and y+dy >=0 and x+dx < gridsize and  y+dy < gridsize)
    {
     if (Grid[y+dy][x+dx] == 1) return -1;
         else return 0;
    } 
   return 0;
}

int createnemies()
{
  for (int i=0; i< 1; i++)
    {  Enemy Entmp(1,1,1);
       Entmp.spawn();
       Enemies.push_back(Entmp);
    }
  return 0;
}

int ReadKeys()
{
   int c = 0;
   if (IsKeyPressed(KEY_SPACE))
        {
             c++;
        }
   if (IsKeyPressed(KEY_RIGHT))
        {    
             if (pushblock(herox, heroy, 1, 0) >= 0 and herox < gridsize -1)
             {
              herox++;
             }
             moveenemy();
        }
   if (IsKeyPressed(KEY_UP))
        {
             if (pushblock(herox, heroy, 0, -1) >= 0 and heroy > 0)
             { 
              heroy--;
             }
             moveenemy();
        }
    if (IsKeyPressed(KEY_LEFT))
        {
             if (pushblock(herox, heroy, -1, 0) >= 0 and herox > 0)
             {           
              herox--;
             }
             moveenemy();
        }
    if (IsKeyPressed(KEY_DOWN))
        {
             if (pushblock(herox, heroy, 0, 1) >= 0 and heroy < gridsize -1)
             {
              heroy++;
             }
             moveenemy();
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

int main() {
    InitWindow(screenWidth, screenHeight, "Math Attack!"); // RNG seed is set randomly in InitWindow !!

    Vector2 MousePos;
    SetTargetFPS(60);
    cleargrid();
    fillgrid(griddensity);
    createnemies(); // RNG seed is set randomly in InitWindow !!
    Enemy Enday(1,1,1);
    while (!WindowShouldClose()) 
    {
        ReadKeys();

        BeginDrawing();         // these two lines MUST go first when drawing
        ClearBackground(BLACK); // these two lines MUST go first when drawing

        drawgrid(); 
        DrawRectangleLines(0,0,screenWidth,screenHeight,YELLOW);
        MousePos = GetMousePosition();
        DrawText("<Space> - Save",800,200,20, WHITE);
        drawCharfromArray(gridtoxy(herox), gridtoxy(heroy), 3,8, Char1);
        Enday.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
