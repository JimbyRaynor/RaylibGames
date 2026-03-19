#include "raylib.h"
#include <string>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// APP name: MathQuix or QuixoMath

// compile: g++ MathAttack.cpp -o MathAttack -lraylib -lm -ldl -lpthread -lGL -lX11
// run:     ./MathAttack
// Ctrl-C to close crashed program

// raylib uses float for most numbers, and so use 2.0f to convert int to float. Note that 2.0 will be a double

// Solitare is fun partly because it looks good. Think Casino.
// E-ink soft colours on cream-white or cream-light-green???
// Look at Tetris for game design and music
// Avoid over-tall stack by only adding from queue when size <= 10 ?? needed ?? how to increase stack size while playing game?
// Score -2 for each sum not on board.
// Load and Fire  or    Aim and Fire?  or Load and Store?

// Same for (a+b)+c, a+(b+c)  ???? add algebra SLOWLY
// Look at expensive watch faces CASIO, SEIKO, etc. for screen design

// bring in the fonts from data files
// draw graphics while balancing
// try led calculator 8 style numbers?
// Draw controls  AIM  : <spacebar>
//                FIRE : <Enter>

// Levels:

// 4. What other types? Look for other famous theorems of number theory
// 4. Big gaps no 20s, 40s, 60s, 80,s
// 4.       no 30,40,50,60s, etc.
// 5. pyramid pattern
// 6. LHS only
// 7. RHS only

// POINTS:
//  Score = 100-y for dropping number
// -1 for firing a number not in stack (gun explode animation?) -  already shield gets decreased

// BUGS:

// bonus level: every number is a sum of two primes

// Level completed when sum = 100. Then 100 explodes into fireworks like peggle
// Char moves across numberline towards 100? Seems good
// Make animation for removing number (frog jump??)

// "Orange Peg" numbers give bonus multipliers, but also give an extra 10-18 number
// Casino style board?

// score = sum of the two numbers (high numbers give best score), and chains can be made naturally.
// the harder the sum, the bigger the score


//  Design fixed, not random, levels on Kindle Scribe

// Think about * level
// Need to remove full board (multiplication table)
// Load gun with primes and 1, all composites get made and so all cases are needed, e.g. 7*8, beacuse we only have a binary operation
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
  drawCharfromArray(x, y, 3,8, CharEnemy1);
  DrawText(to_string(attacknumber).c_str(),x+8,y,40, WHITE);
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
  Enemy Entmp(screenWidth/2-30,-30,value);
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
            if (removefromboard(value1+value2) != -1)
            {
               sumlog.push_back(to_string(value1)+" + "+to_string(value2)+" = "+to_string(value1+value2));
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
            }
          }
          hits++;
        };
    }
  if (!hit) shield--;
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
  int boardx = 700, boardy = 10, cellwidth = 50;
  DrawText(to_string(100).c_str(),boardx+cellwidth*4,boardy+cellwidth*10,60, WHITE);
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
                if (Enemies.size() <= 4)
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
        ClearBackground(BLACK); // these two lines MUST go first when drawing

        DrawRectangleLines(0,0,screenWidth,screenHeight,YELLOW);
        drawboard();
        drawsumlog();
        MousePos = GetMousePosition();
        if (gunvector.size() > gunindex)
         {
          DrawText(to_string(gunvector[gunindex]).c_str(),screenWidth/2-40,screenHeight-100,80, WHITE);
         }
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
