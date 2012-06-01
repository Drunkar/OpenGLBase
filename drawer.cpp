#include "drawFunctions.hpp"
#include <GL/freeglut.h>

class Drawer{
public:
  int dimension;
  double x;

  Drawer(int d=2){
	dimension = d;
    x = 0;
  };

  void draw(){
	if(dimension==3){
	  //オレンジ
      GLfloat orange[] = { 1.0f, 0.6f, 0.0f, 1.0f };
      //ライトの位置
      GLfloat lightpos[] = { 200.0, 150.0, -500.0, 1.0 };
      //ライトの設定
      glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
      //マテリアルの設定
      glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);
      glutSolidTorus(20.0,40.0,16,16);
	} else if(dimension==2) {
	  glColor4d(0.2, 0.2, 0.2, 1.0);
      glBegin(GL_QUADS);
		glVertex2d(-0.5+x, -0.5);
		glVertex2d(-0.5+x, 0.5);
		glVertex2d(0.5+x, 0.5);
        glVertex2d(0.5+x, -0.5);
      glEnd();

      myglDrawEllipse(10, 10, 30);
      glColor4d(0.97, 0.97, 0.98, 1.0);
      myglDrawEllipse(10, 10, 28);
      glColor4d(0.2, 0.2, 0.2, 1.0);
      myglDrawArrowd(-10, -10, 0, 10, 10, 0);
	}

    glColor4d(0.2, 0.2, 0.2, 1.0);
    //myglBitmapString(0, 0, 0, "hogehoge");
    myglStrokeString(0, 0, 0, "piyopiyo");
  };

  void update(){
    x += 0.01;
  };
};
