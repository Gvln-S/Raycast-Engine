#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533

float player_x, player_y, player_delta_x, player_delta_y, player_angle;

void draw_player() {
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
int map[] = {
  1,1,1,1,1,1,1,1,
  1,0,1,0,0,0,0,1,
  1,0,1,0,0,0,0,1,
  1,0,1,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,1,0,1,
  1,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,
};

void draw_map_2d() {
  int map_x_pos,map_y_pos,map_wall_x,map_wall_y;
  for(map_y_pos = 0; map_y_pos < map_y; map_y_pos++) {
    for(map_x_pos = 0; map_x_pos < map_x; map_x_pos++) {
      if(map[map_y_pos*map_x+map_x_pos] == 1) { glColor3f(1, 1, 1); } else { glColor3f(0, 0, 0); }
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

float dist(float ax, float ay, float bx, float by, float ang) {
  return ( sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) );
}

void draw_rays_2d() {
  int ray, map_ray_x, map_ray_y, map_ray, dof; float ray_x, ray_y, ray_angle, x_offset, y_offset;
  ray_angle = player_angle - DR*30; if(ray_angle<0){ray_angle+=2*PI;} if(ray_angle>2*PI){ray_angle -= 2*PI;}
  for(ray=0; ray<60; ray++) {
    // check horizontal lines
    dof = 0;
    float distance_horizontal= 100000000, horizontal_x = player_x, horizontal_y = player_y;
    float aTan = -1/tan(ray_angle);
    if(ray_angle>PI){ray_y = (((int)player_y>>6)<<6)-0.0001; ray_x = (player_y - ray_y)*aTan+player_x; y_offset =-64; x_offset =-y_offset*aTan;} // looking up
    if(ray_angle<PI){ray_y = (((int)player_y>>6)<<6)+64;     ray_x = (player_y - ray_y)*aTan+player_x; y_offset = 64; x_offset =-y_offset*aTan;} // looking down
    if(ray_angle==0 || ray_angle==PI){ ray_x = player_x; ray_y = player_y; dof = 8;} // looking straight left or right
    while(dof<8) {
      map_ray_x = (int)(ray_x)>>6; map_ray_y = (int)(ray_y)>>6; map_ray = map_ray_y*map_x+map_ray_x;
      if(map_ray>0 && map_ray<map_x*map_y && map[map_ray] == 1){horizontal_x = ray_x; horizontal_y = ray_y; distance_horizontal = dist(player_x, player_y, horizontal_x, horizontal_y, ray_angle); dof = 8;} // hit wall
      else{ray_x += x_offset; ray_y += y_offset; dof += 1;} // next wall
    }

    // check vertical lines
    dof = 0;
    float distance_vertical = 100000000, vertical_x = player_x, vertical_y = player_y;
    float nTan = -tan(ray_angle);
    if(ray_angle>P2 && ray_angle<P3){ray_x = (((int)player_x>>6)<<6)-0.0001; ray_y = (player_x - ray_x)*nTan+player_y; x_offset =-64; y_offset =-x_offset*nTan;} // looking left
    else{ray_x = (((int)player_x>>6)<<6)+64;     ray_y = (player_x - ray_x)*nTan+player_y; x_offset = 64; y_offset =-x_offset*nTan;} // looking rigth
    if(ray_angle== 0|| ray_angle==PI){ ray_x = player_x; ray_y = player_y; dof = 8;} // looking straight up or down
    while(dof<8) {
      map_ray_x = (int)(ray_x)>>6; map_ray_y = (int)(ray_y)>>6; map_ray = map_ray_y*map_x+map_ray_x;
      if(map_ray>0 && map_ray<map_x*map_y && map[map_ray] == 1){vertical_x = ray_x; vertical_y = ray_y; distance_vertical = dist(player_x, player_y, vertical_x, vertical_y, ray_angle); dof = 8;} // hit wall
      else{ray_x += x_offset; ray_y += y_offset; dof += 1;} // next line
    }
    if(distance_vertical<distance_horizontal){ray_x = vertical_x; ray_y = vertical_y;}
    else {ray_x = horizontal_x; ray_y = horizontal_y;}
    glColor3f(1,0,0); glLineWidth(1); glBegin(GL_LINES); glVertex2i(player_x, player_y); glVertex2i(ray_x, ray_y); glEnd();
    ray_angle += DR; if(ray_angle<0){ray_angle+=2*PI;} if(ray_angle>2*PI){ray_angle -= 2*PI;}

  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  draw_map_2d();
  draw_rays_2d();
  draw_player();

  glutSwapBuffers();
}

void buttons(unsigned char key, int position_x, int position_y) {
  if(key == 'a'){ player_angle -= 0.1; if(player_angle <    0){player_angle += 2*PI;} player_delta_x = cos(player_angle)*5; player_delta_y = sin(player_angle)*5;}
  if(key == 'd'){ player_angle += 0.1; if(player_angle > 2*PI){player_angle -= 2*PI;} player_delta_x = cos(player_angle)*5; player_delta_y = sin(player_angle)*5;}
  if(key == 'w'){ player_x += player_delta_x; player_y += player_delta_y;}
  if(key == 's'){ player_x -= player_delta_x; player_y -= player_delta_y;}
  glutPostRedisplay();
}

void init() {
  glClearColor(0.1, 0.1, 0.1, 0);
  gluOrtho2D(0,1024,512,0);

  player_x = 300; player_y = 300; player_delta_x = cos(player_angle)*5; player_delta_y = sin(player_angle)*5;
}

int main(int argc, char** argv)
{ 
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(1024,512);

  glutCreateWindow("RayCast");

  init();

  // reder loop
  glutDisplayFunc(display);

  // keyboard inputs
  glutKeyboardFunc(buttons);

  glutMainLoop();
  return 0;
}
