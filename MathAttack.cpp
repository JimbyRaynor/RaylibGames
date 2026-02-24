#include "raylib.h"
#include <string>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//compile: g++ MathAttack.cpp -o MathAttack -lraylib -lm -ldl -lpthread -lGL -lX11
//run:     ./MathAttack

// raylib uses float for most numbers, and so use 2.0f to convert int to float. Note that 2.0 will be a double


// Same for (a+b)+c, a+(b+c)  ???? add algebra SLOWLY
// Look at expensive watch faces CASIO, SEIKO, etc. for screen design


// keep 1-9 but have sparse board 

// Next level when 10-18 are all gone AND all numbers in gunvector <= 9 Just check for "No More Moves".
// "Orange Peg" numbers give bonus multipliers, but also give an extra 10-18 number
// Then next level: bonus for removing all
// score = sum of the two numbers (high numbers give best score), and chains can be made naturally.
// Log of sums on left hand side of screen

// remove numbers from board at start, so level is quicker to finish, like a peg board. Design on Kindle Scribe



// every number is a sum of two primes? side track?
// just input primes?

// levels for +,-,/,*, etc

// The Matrix screensaver theme?

// Make xmas theme :) !!
// Chinese New Year Theme with dragons and red envelopes

// chars walking across screen to show progress ?


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


int herox = 20;
int heroy = 20;
int traily = -40;
int totalenemies = 20;
int createdenemies = 0;
int enemymovement = 0;
int movementstep = 1;
int hits = 0;
int value1 = 0;
bool value1picked = false;
int value2 = 0;
bool value2picked = false;

int shootnumber = 1;
int shield = 3;
int level = 1;
int levels[] = {0,3,9,14,14,20,33,32,32,32}; // Extra enemies added in each level; 
int Board[20][20];
string operation = "+";
vector <int> gunvector;
vector <string> sumlog;
int gunindex = 0;

int fillboard()
{
  for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
     if (GetRandomValue(0,9) >= 7)
           Board[i][j] = i*10+j;
           else
           Board[i][j] = -1;

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
    y = y + movementstep;
    return 0;
}

int Enemy::draw()
{
  drawCharfromArray(x, y, 3,8, CharEnemy1);
  DrawText(to_string(attacknumber).c_str(),x+8,y,40, WHITE);
  return 0;
}
vector <Enemy> Enemies;

int moveenemies()
{
  traily += movementstep;
  enemymovement += movementstep;

  for (int i=0;i<Enemies.size();i++)
        Enemies[i].move();
  return 0;
}

int loadgunvector()
{
  gunvector.clear();
  for (int i=0;i<Enemies.size();i++)
        if (find(gunvector.begin(),gunvector.end(),Enemies[i].attacknumber) == gunvector.end())  // need unique
              gunvector.push_back(Enemies[i].attacknumber);
  sort(gunvector.begin(),gunvector.end());
  return 0;
}

int createnemies()
{
  for (int i=0; i< 4; i++)
    {  
       Enemy Entmp(screenWidth/2-30,(17-i)*40+traily,GetRandomValue(0,9));
       Enemies.push_back(Entmp);
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

int removefromboard(int number)
{
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

int createnewnemy()
{
  int min, newnumber;
  min = findminboard();
  if (min > 9) return 0;
  newnumber = GetRandomValue(min,9);
  removefromboard(newnumber);
  traily = -40;
  Enemy Entmp(screenWidth/2-30,-40,newnumber);
  Enemies.push_back(Entmp);
  return 0;
}

int createnewnemysum(int sum)
{
  traily = -40;
  Enemy Entmp(screenWidth/2-30,-40,sum);
  Enemies.push_back(Entmp);
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


int removeenemy(int shotnumber)
{
  bool hit = false;
  for (int i=Enemies.size()-1;i >= 0; i--) // go backwards to avoid index shifting when element is removed
    {  
       if (Enemies[i].attacknumber == shotnumber and hit == false)
        {
          Enemies.erase(Enemies.begin()+i);
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
            if (removefromboard(value1+value2) != -1)
            {
               createnewnemysum(value1+value2);
               sumlog.push_back(to_string(value1)+" + "+to_string(value2)+" = "+to_string(value1+value2));
               if (value1+value2 >= 90)  createnewnemysum(GetRandomValue(10,18));

            }
            else sumlog.push_back(to_string(value1)+" + "+to_string(value2)+" = "+to_string(value1+value2)+" *not on board* ");
          }
          hits++;
        };
    }
  if (hit == true)
  {  
     if (createdenemies < levels[level]) traily = -40;
     resetenemyloc();
  }
  else shield--;
  if (Enemies.size() == 0)
  {
     level++;
     traily = -40;
     hits = 0;
     createdenemies = 0;
     createnemies();
  }
  return 0;
}

int ReadKeys()
{
   int c = 0;
   if (IsKeyPressed(KEY_ENTER))
        {
             removeenemy(gunvector[gunindex]);
             loadgunvector();
        }
   if (IsKeyPressed(KEY_SPACE))
        {         
              gunindex++;
              if (gunindex >= gunvector.size()) gunindex = 0;
        }
   if (IsKeyPressed(KEY_UP))
        {

              heroy--;

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
  int boardx = 700, boardy = 100, cellwidth = 50;
  for (int i = 0;i<10; i++)
   for (int j = 0; j <10; j++)
     if (Board[i][j] != -1)
                DrawText(to_string(Board[i][j]).c_str(),boardx+cellwidth*j,boardy+cellwidth*i,30, WHITE);
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
    InitWindow(screenWidth, screenHeight, "Math Attack!"); // RNG seed is set randomly in InitWindow !!
   
    float moveInterval = 0.01f; // 1000ms b/w move
    float moveTimer = 0.0f;
    Vector2 MousePos;
    SetTargetFPS(60);
    createnemies(); // RNG seed is set randomly in InitWindow !!
    fillboard();
    loadgunvector();
    sumlog.clear();
    while (!WindowShouldClose()) 
    {
        ReadKeys();
        float dt = GetFrameTime(); // seconds since last frame 
        moveTimer += dt; 
        if (moveTimer >= moveInterval and Enemies[0].y < 500) 
          { 
            moveenemies(); 
            if (enemymovement >= 40)
            {      
                createnewnemy();
                createdenemies++;         
                enemymovement = 0;
            }
            moveTimer = 0.0f; // reset timer 
          }

        BeginDrawing();         // these two lines MUST go first when drawing
        ClearBackground(BLACK); // these two lines MUST go first when drawing

        DrawRectangleLines(0,0,screenWidth,screenHeight,YELLOW);
        drawboard();
        drawsumlog();
        MousePos = GetMousePosition();
        DrawText(to_string(gunvector[gunindex]).c_str(),screenWidth/2-40,screenHeight-100,80, WHITE);
        DrawText(("Enemies: "+to_string(9+levels[level]-hits)).c_str(),screenWidth/2-40,screenHeight-40,40, WHITE);
        DrawText(("Shield: "+to_string(shield)).c_str(),screenWidth*0.75,screenHeight-40,40, WHITE);
        DrawText(("Level: "+to_string(level)).c_str(),screenWidth*0.25,screenHeight-40,40, WHITE);
        DrawText(operation.c_str(),840,screenHeight-200,40, WHITE);
        if (value1picked == true)
        {
          DrawText((to_string(value1)).c_str(),800,screenHeight-200,40, WHITE);
        }
         if (value2picked == true)
        {
          DrawText((to_string(value2)+" =").c_str(),880,screenHeight-200,40, WHITE);
        }
        
        //drawCharfromArray(herox, heroy, 3,8, Char1);
        drawnemies();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
