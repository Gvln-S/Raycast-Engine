#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926535

float deg_to_rad(int a) {return a*PI/180;}
int fix_angle(int a) {if(a>329) {a-=360;} if(a<0) {a+=360;} return a;}
float distance(float ax, float ay, float bx, float by, float angle) {return cos(deg_to_rad(angle))*(bx-ax)-sin(deg_to_rad(angle))*(by-ay);}
float player_x, player_y, player_delta_x, player_delta_y, player_angle;
float frame_one, frame_two, fps;
bool keys[256] = {false};

int All_Textures[]=
{
  //Checkerboard
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
  //Brick
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  //Window
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,    

  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 

  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,   

  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
  //Door
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
  0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  
  0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
  0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
  0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,     

  0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
  0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
  0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
  0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
  0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
  0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
  0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
  0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  

  0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,1, 1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
  0,0,0,0,0,0,0,0, 0,0,1,1,1,1,0,1, 1,0,1,1,1,1,0,0, 0,0,0,0,0,0,0,0,   
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 

  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,     
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,   
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,  
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
  0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,         
};

void draw_player_2d() {
  glColor3f(1, 1, 0);
  glPointSize(8);
  glBegin(GL_POINTS);
  glVertex2i(player_x, player_y);
  glEnd();

  glLineWidth(3);
  glBegin(GL_LINES);
  glVertex2i(player_x, player_y);
  glVertex2i(player_x+player_delta_x*5, player_y+player_delta_y*5);
  glEnd();
}

int map_x = 8, map_y = 8, map_superfice = 64;
int map_walls[] = {
  1,1,1,1,1,1,1,1,
  1,0,0,1,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,1,1,1,4,1,1,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,
};

int map_ceiling[] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};

int map_floors[] = {
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
  0,0,0,1,1,0,0,0,
};

void draw_map_2d() {
  int map_x_pos,map_y_pos,map_wall_x,map_wall_y;
  for(map_y_pos = 0; map_y_pos < map_y; map_y_pos++) {
    for(map_x_pos = 0; map_x_pos < map_x; map_x_pos++) {
      if(map_walls[map_y_pos*map_x+map_x_pos]>0) { glColor3f(1, 1, 1); } else { glColor3f(0, 0, 0); }
      map_wall_x = map_x_pos*map_superfice; map_wall_y = map_y_pos*map_superfice;
      glBegin(GL_QUADS);
      glVertex2i(map_wall_x              +1, map_wall_y              +1);
      glVertex2i(map_wall_x              +1, map_wall_y+map_superfice-1);
      glVertex2i(map_wall_x+map_superfice-1, map_wall_y+map_superfice-1);
      glVertex2i(map_wall_x+map_superfice-1, map_wall_y              +1);
      glEnd();
    }
  }
}

void draw_rays_2d() {
  glColor3f(0.1,0.1,0.5); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();	
  glColor3f(0,0,0); glBegin(GL_QUADS); glVertex2i(526,160); glVertex2i(1006,160); glVertex2i(1006,320); glVertex2i(526,320); glEnd();

  int ray, map_ray_x, map_ray_y, map_ray, depth_field, side; 
  float vertical_x, vertical_y, ray_x, ray_y, ray_angle, x_offset, y_offset, distance_horizontal, distance_vertical;

  ray_angle = fix_angle(player_angle+30);

  for(ray=0; ray<80; ray++) {
    int vertical_map_texture = 0, horizontal_map_texture = 0; // map texture number

    // vertical lines
    depth_field = 0; side = 0; distance_vertical = 100000000;
    float Tan = tan(deg_to_rad(ray_angle));
         if(cos(deg_to_rad(ray_angle))> 0.001) {ray_x = (((int)player_x>>6)<<6)+64;    ray_y = (player_x - ray_x)*Tan+player_y; x_offset = 64; y_offset =-x_offset*Tan;} // looking left
    else if(cos(deg_to_rad(ray_angle))<-0.001) {ray_x = (((int)player_x>>6)<<6)-0.001; ray_y = (player_x - ray_x)*Tan+player_y; x_offset =-64; y_offset =-x_offset*Tan;} // looking rigth
    else {ray_x=player_x; ray_y=player_y; depth_field=8;}

    while(depth_field<8) {
      map_ray_x = (int)(ray_x)>>6; map_ray_y = (int)(ray_y)>>6; map_ray = map_ray_y*map_x+map_ray_x;
      if(map_ray>0 && map_ray<map_x*map_y && map_walls[map_ray]>0){vertical_map_texture = map_walls[map_ray]-1; depth_field= 8; distance_vertical = cos(deg_to_rad(ray_angle))*(ray_x - player_x)-sin(deg_to_rad(ray_angle))*(ray_y - player_y);} // hit wall
      else{ray_x+=x_offset; ray_y+=y_offset; depth_field+=1;} // next line
    }
    vertical_x=ray_x; vertical_y=ray_y;

    // horizontal lines
    depth_field = 0, distance_horizontal= 100000000;
    Tan = 1.0/Tan;
         if(sin(deg_to_rad(ray_angle))> 0.001) {ray_y = (((int)player_y>>6)<<6)-0.001; ray_x = (player_y - ray_y)*Tan+player_x; y_offset =-64; x_offset =-y_offset*Tan;} // looking up
    else if(sin(deg_to_rad(ray_angle))<-0.001) {ray_y = (((int)player_y>>6)<<6)+64;    ray_x = (player_y - ray_y)*Tan+player_x; y_offset = 64; x_offset =-y_offset*Tan;} // looking down
    else {ray_x=player_x; ray_y=player_y; depth_field=8;}

    while(depth_field<8) {
      map_ray_x = (int)(ray_x)>>6; map_ray_y = (int)(ray_y)>>6; map_ray = map_ray_y*map_x+map_ray_x;
      if(map_ray>0 && map_ray<map_x*map_y && map_walls[map_ray]>0){horizontal_map_texture = map_walls[map_ray]-1; depth_field= 8; distance_horizontal=cos(deg_to_rad(ray_angle))*(ray_x - player_x)-sin(deg_to_rad(ray_angle))*(ray_y-player_y);} // hit wall
      else{ray_x += x_offset; ray_y += y_offset; depth_field+=1;} // next wall
    }

    float shade=1;
    glColor3f(0.8,0.8,0.8);
    if(distance_vertical<distance_horizontal){horizontal_map_texture = vertical_map_texture; shade = 0.5; ray_x = vertical_x; ray_y = vertical_y; distance_horizontal = distance_vertical; glColor3f(0.6,0.6,0.6);}
    glLineWidth(2); glBegin(GL_LINES); glVertex2i(player_x, player_y); glVertex2i(ray_x, ray_y); glEnd();

    // draw walls
    int ca=fix_angle(player_angle-ray_angle); distance_horizontal=distance_horizontal*cos(deg_to_rad(ca));
    int line_horizontal = (map_superfice*320)/(distance_horizontal); if(line_horizontal>320) {line_horizontal=320;}
    float texture_y_step = 32.0/(float)line_horizontal;
    float texture_y_offset = 0;
    if(line_horizontal>320){texture_y_offset = (line_horizontal-320)/2.0; line_horizontal=320;}   // line height and limit
    float line_offset = 160 - (line_horizontal>>1);                                               // line offset
                                                                                                                                                            
    int thing_y;
    float texture_y = texture_y_offset*texture_y_step+horizontal_map_texture*32;
    float texture_x; 
    if(shade==1) {texture_x = (int)(ray_x/2.0)%32; if (ray_angle>180) {texture_x = 31-texture_x;}}
    else         {texture_x = (int)(ray_y/2.0)%32; if (ray_angle>90 && ray_angle<270) {texture_x = 31-texture_x;}}

    for(thing_y = 0; thing_y<line_horizontal; thing_y++){
      float c=All_Textures[(int)(texture_y)*32+(int)(texture_x)]*shade;
      if(horizontal_map_texture==0) {glColor3f(c/1.5, c/1.5, c/1.5);}
      if(horizontal_map_texture==1) {glColor3f(c,     c    , c/2.0);}
      if(horizontal_map_texture==2) {glColor3f(c/2.0, c/2.0, c    );}
      if(horizontal_map_texture==3) {glColor3f(c/2.0, c    , c/2.0);}
      glLineWidth(8); glBegin(GL_POINTS); glVertex2i(ray*8+530,thing_y+line_offset); glEnd();
      texture_y+=texture_y_step;
    }
    
    // draw floors
    for(thing_y=line_offset+line_horizontal;thing_y<320;thing_y++) {
      float delta_y = thing_y-(320/2.0), degrees=deg_to_rad(ray_angle), ray_angle_fix(cos(deg_to_rad(fix_angle(player_angle-ray_angle))));
      texture_x= player_x/2+cos(degrees)*158*32/delta_y/ray_angle_fix;
      texture_y= player_y/2-sin(degrees)*158*32/delta_y/ray_angle_fix;
      int map_ray_short=map_floors[(int)(texture_y/32.0)*map_x+(int)(texture_x/32.0)]*32*32;
      float c=All_Textures[((int)(texture_y)&31)*32+((int)(texture_x)&31)]*0.7;
      glColor3f(c/1.3,c/1.3,c); glLineWidth(8); glBegin(GL_POINTS); glVertex2i(ray*8+530,thing_y); glEnd();

      // draw ceiling
      map_ray=map_ceiling[(int)(texture_y/32.0)*map_x+(int)(texture_x/32.0)]*32*32;
      c=All_Textures[((int)(texture_y)&31)*32+((int)(texture_x)&31)+map_ray]*0.7;
      glColor3f(c/1.3, c/1.3, c/1.3); glLineWidth(8); glBegin(GL_POINTS); glVertex2i(ray*8+530,320-thing_y); glEnd();
    }
    ray_angle = fix_angle(ray_angle-1);
  }
}

void key_down(unsigned char key, int position_x, int position_y) {keys[key] = true;}
void key_up(unsigned char key, int position_x, int position_y  ) {keys[key] = false;}

void display()
{
  frame_two = glutGet(GLUT_ELAPSED_TIME); fps = (frame_two-frame_one); frame_one = glutGet(GLUT_ELAPSED_TIME);

  int x_equalize = 0; if(player_delta_x<0) {x_equalize=-20;} else{x_equalize=20;}
  int y_equalize = 0; if(player_delta_y<0) {y_equalize=-20;} else{y_equalize=20;}
  int player_grip_x = player_x/64.0, player_grip_add_x_equilize = (player_x+x_equalize)/64.0, player_grip_sub_x_equilize = (player_x-x_equalize)/64.0;
  int player_grip_y = player_y/64.0, player_grip_add_y_equilize = (player_y+y_equalize)/64.0, player_grip_sub_y_equilize = (player_y-y_equalize)/64.0;

  if(keys['w']) {
    if(map_walls[player_grip_y*map_x              + player_grip_add_x_equilize]==0){player_x+=player_delta_x*0.025*fps;}
    if(map_walls[player_grip_add_y_equilize*map_x + player_grip_x             ]==0){player_y+=player_delta_y*0.025*fps;}
  }
  if(keys['s']) {
    if(map_walls[player_grip_y*map_x              + player_grip_sub_x_equilize]==0){player_x-=player_delta_x*0.025*fps;}
    if(map_walls[player_grip_sub_y_equilize*map_x + player_grip_x             ]==0){player_y-=player_delta_y*0.025*fps;}
  }
  if(keys['a']) {
    float angle = fix_angle(player_angle+90);
    float strafe_x =  cos(deg_to_rad(angle));
    float strafe_y = -sin(deg_to_rad(angle));

    if(map_walls[player_grip_y*map_x+player_grip_add_x_equilize] == 0) {player_x+=strafe_x*0.08f*fps;}
    if(map_walls[player_grip_add_y_equilize*map_x+player_grip_x] == 0) {player_y+=strafe_y*0.08f*fps;}
  }
  if(keys['d']) {
    float angle = fix_angle(player_angle-90);
    float strafe_x =  cos(deg_to_rad(angle));
    float strafe_y = -sin(deg_to_rad(angle));

    if(map_walls[player_grip_y*map_x+player_grip_sub_x_equilize] == 0) {player_x+=strafe_x*0.08f*fps;}
    if(map_walls[player_grip_sub_y_equilize*map_x+player_grip_x] == 0) {player_y+=strafe_y*0.08f*fps;}
  }
  if(keys['e']) {
    int x_equalize = 0; if(player_delta_x<0) {x_equalize=-25;} else{x_equalize=25;}
    int y_equalize = 0; if(player_delta_y<0) {y_equalize=-25;} else{y_equalize=25;} 
    int player_grip_x = player_x/64.0, player_grip_add_x_equilize = (player_x+x_equalize)/64.0;
    int player_grip_y = player_y/64.0, player_grip_add_y_equilize = (player_y+y_equalize)/64.0;
    if(map_walls[player_grip_add_y_equilize*map_x+player_grip_add_x_equilize]==4) {map_walls[player_grip_add_y_equilize*map_x+player_grip_add_x_equilize]=0;}
    
  }

  glutPostRedisplay();
  glClear(GL_COLOR_BUFFER_BIT);

  draw_map_2d();
  draw_rays_2d();
  draw_player_2d();

  glutSwapBuffers();
}

void resize(int width, int height) {
  glutReshapeWindow(1024, 512);
}

void mouse_move(int mouse_x, int mouse_y) {
  static int last_x = 512;
  int delta_x = mouse_x - last_x;
  float sensitivity = 0.2f;

  last_x = mouse_x;

  player_angle += delta_x * sensitivity;
  player_angle = fix_angle((int)player_angle);

  player_delta_x =  cos(deg_to_rad(player_angle))*5;
  player_delta_y = -sin(deg_to_rad(player_angle))*5; 

  glutPostRedisplay();
}

void init() {
  gluOrtho2D(0,1024,512,0);
  player_x = 400; player_y = 400; player_delta_x = cos(player_angle)*5; player_delta_y = sin(player_angle)*5;
}

int main(int argc, char** argv)
{ 
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(1024,512);
  glutInitWindowPosition(200, 200);

  glutCreateWindow("RayCast");

  init();

  // reder loop
  glutDisplayFunc(display);

  // resize
  glutReshapeFunc(resize);

  // keyboard and mouse inputs
  glutKeyboardFunc(key_down);
  glutKeyboardUpFunc(key_up);
  glutPassiveMotionFunc(mouse_move);

  glutMainLoop();
  return 0;
}
