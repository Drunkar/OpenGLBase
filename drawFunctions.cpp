#include "drawFunctions.hpp"
void myglBitmapString(double x, double y, double z, std::string const& str){
  glRasterPos3d(x, y, z);

  for(unsigned int i=0; i<str.size(); ++i){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
  }
}

void myglStrokeString(double x, double y, double z, std::string const& str){
  glPushMatrix();
  glRasterPos3d(x, y, z);
  glScaled(0.1, 0.1, 0.1);

  for(unsigned int i=0; i<str.size(); ++i){
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[i]);
  }
  glPopMatrix();
}

void myglDrawEllipse(double center_x, double center_y, double radius){
  for (double th1 = 0.0;  th1 <= 360.0;  th1 = th1 + 1.0){             
    double th2 = th1 + 10.0;
    double th1_rad = (th1 / 180.0 )* 3.1415926; 
    double th2_rad = (th2 / 180.0 )* 3.1415926;

    double x1 = radius * cos(th1_rad);
    double y1 = radius * sin(th1_rad);
    double x2 = radius * cos(th2_rad);
    double y2 = radius * sin(th2_rad);

    glBegin(GL_TRIANGLES); 
    glVertex2d( center_x, center_y);
    glVertex2d( x1+center_x, y1+center_y );     
    glVertex2d( x2+center_x, y2+center_y );
    glEnd();
  }
}

void myglDrawArrowd(double x0, double y0, double z0, double x1, double y1, double z1){
  GLUquadricObj *arrows[2];
  double x2, y2, z2, len, ang;

  x2 = x1-x0; y2 = y1-y0; z2 = z1-z0;
  len = sqrt(x2*x2 + y2*y2 + z2*z2);
  if(len != 0.0){
    ang = acos(z2*len/(sqrt(x2*x2+y2*y2+z2*z2)*len))/M_PI*180.0;

    glPushMatrix();
    glTranslated( x0, y0, z0);
    glRotated( ang, -y2*len, x2*len, 0.0);
    arrows[0] = gluNewQuadric();
    gluQuadricDrawStyle(arrows[0], GLU_FILL);
    gluCylinder(arrows[0], len/80, len/80, len*0.9, 8, 8);
    glPushMatrix();
    glTranslated( 0.0, 0.0, len*0.9);
    arrows[1] = gluNewQuadric();
    gluQuadricDrawStyle(arrows[1], GLU_FILL);
    gluCylinder(arrows[1], len/30, 0.0f, len/10, 8, 8);
    glPopMatrix();
    glPopMatrix();
  }
}
