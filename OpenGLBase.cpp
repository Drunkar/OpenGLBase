#include "OpenGLWindow.hpp"
#include "drawFunctions.hpp"
#include "drawer.cpp"
	
class Drawer;

OpenGLWindow *window;
Drawer       *drawer;
const int DIMENSION = 2;

void callDisplayFunc(){
  window->display1st();
  drawer->draw();
  window->display2nd();
}
void callResizeFunc(int w, int h){
  window->resize(w, h);
}
void callKeyboardFunc(unsigned char key, int x, int y){
  window->keyboard(key, x, y);
}
void callMouseFunc(int button, int state, int x, int y){
  window->mouse(button, state, x, y);
}
void callMouseMotionFunc(int x, int y){
  window->mouseMotion(x, y);
}
void callMouseWheelFunc(int wheel_number, int direction, int x, int y){
	window->mouseWheel(wheel_number, direction, x, y);
}
void callIdleFunc(){
  drawer->update();
  window->idle();
}


int main(){
  window = new OpenGLWindow(1200, 750, DIMENSION, 0.97, 0.97, 0.95);
  drawer = new Drawer(DIMENSION);
  window->create();

  window->start(callDisplayFunc,
		  callResizeFunc,
		  callKeyboardFunc,
		  callMouseFunc,
		  callMouseMotionFunc,
		  callMouseWheelFunc,
		  callIdleFunc);
  
  
  delete window;
  delete drawer;

  return 0;
}
