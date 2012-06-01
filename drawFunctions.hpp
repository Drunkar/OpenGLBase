#ifndef _DRAWFUNCTIONS_HPP_
#define _DRAWFUNCTIONS_HPP_
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <GL/freeglut.h>

void myglBitmapString(double x, double y, double z, std::string const& str);
void myglStrokeString(double x, double y, double z, std::string const& str);

void myglDrawEllipse(double center_x, double center_y, double radius);

void myglDrawArrowd(double x0, double y0, double z0, double x1, double y1, double z1);

#endif