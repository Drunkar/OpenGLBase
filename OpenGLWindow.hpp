/*
This is a hpp of procedures to initialize openGL for 2D graphics.
    1. Make main.cpp and include this hpp.
    2. In main.cpp:
           int main(){
	       createWindow(,,,);
	       drow();
	   }

       So you need to write the "draw()" function.
 */

#ifndef _OPENGLWINDOW_HPP_
#define _OPENGLWINDOW_HPP_

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <GL/freeglut.h>
class Drawer;

struct Quaternion{
  double w;
  double x;
  double y;
  double z;
};

class OpenGLWindow{
public:
  int m_width;
  int m_height;
  int m_dimension;
  bool m_idleFlag;
  bool m_mouseFlagL, m_mouseFlagR;
  double m_mouseX, m_mouseY;	// mouse position at click
  int m_wheel;
  double m_scaled;
  double m_translateX, m_translateY, m_translateZ;
  char* m_title;
  double m_backgroundRed;
  double m_backgroundGreen;
  double m_backgroundBlue;

private:
  void (*idleFunc_)();
public:
  OpenGLWindow(int width, int height, int dimension=2, double red=0.97, double green=0.97, double blue=0.95);

public:
  void idle();
  void display1st();
  void display2nd();
  void resize(int w, int h);
  void keyboard(unsigned char key, int x, int y);
  void mouse(int button, int state, int x, int y);
  void mouseMotion(int x,int y);
  void mouseWheel(int wheel_number, int direction, int x, int y);
  void create();
  void start(void (*displayFunc)(),
	     void (*resizeFunc)(int, int),
	     void (*keyboardFunc)(unsigned char, int, int),
	     void (*mouseFunc)(int, int, int, int),
	     void (*mouseMotionFunc)(int, int),
	     void (*mouseWheelFunc)(int, int, int, int),
	     void (*idleFunc)());

// for quaternion
private:
  Quaternion M_Target;
  Quaternion M_Current;
  double m_rotate[16];	// rotate matrix
};  

#endif /* _OPENGLWINDOW_HPP_ */
