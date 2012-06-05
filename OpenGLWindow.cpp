#include "OpenGLWindow.hpp"

// prototype
//演算子のオーバーロード Quaternionの積
Quaternion & operator *( Quaternion &q1, Quaternion &q2 );
Quaternion & operator -( Quaternion &q1, Quaternion &q2 );
// calc a rotate matrix from qtor
void qtor(double *r , Quaternion q);

OpenGLWindow::OpenGLWindow(int width, int height, int dimension, double red, double green, double blue){
  int argc = 1;
  m_title = (char*)"openGLWindow";
  glutInit(&argc, &m_title);

  m_width = width, m_height = height;
  m_dimension = dimension;
  m_backgroundRed = red;
  m_backgroundGreen = green;
  m_backgroundBlue = blue;
  m_idleFlag = GL_FALSE;
  m_mouseFlagL = GL_FALSE, m_mouseFlagR = GL_FALSE;
  m_wheel = 0;
  m_scaled = 1.0;

  m_translateX = 0;
  m_translateY = 0;
  m_translateZ = 0;

  M_Current.w = 1.0;
  M_Current.x = 0.0;
  M_Current.y = 0.0;
  M_Current.z = 0.0;
}

//init ----------------------------------------------------------------------------------------
void OpenGLWindow::create(){
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(m_width, m_height);	//call size before create
  
  glutCreateWindow(m_title);	//call func after create
    
}

void OpenGLWindow::start(void (*displayFunc)(),
			 void (*resizeFunc)(int, int),
			 void (*keyboardFunc)(unsigned char, int, int),
			 void (*mouseFunc)(int, int, int, int),
			 void (*mouseMotionFunc)(int, int),
			 void (*mouseWheelFunc)(int, int, int, int),
			 void (*idleFunc)()){

			   
  glClearColor(m_backgroundRed, m_backgroundGreen, m_backgroundBlue, 1.0);
			   
  glutDisplayFunc(displayFunc);
  glutReshapeFunc(resizeFunc);
  glutKeyboardFunc(keyboardFunc);
  glutMouseFunc(mouseFunc);
  glutMotionFunc(mouseMotionFunc);
  glutMouseWheelFunc(mouseWheelFunc); // commentout if mac
  idleFunc_ = idleFunc;
  
  // anti-aliasing
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);

  if(m_dimension == 3){
    // for light
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    qtor(m_rotate, M_Current);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //視野角,アスペクト比(ウィンドウの幅/高さ),描画する範囲(最も近い距離,最も遠い距離)
    gluPerspective(30.0, m_width / m_height, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //視点の設定
    gluLookAt(0,100.0,200.0, //カメラの座標
	      0.0,0.0,0.0, // 注視点の座標
	      0.0,1.0,0.0); // 画面の上方向を指すベクトル
  } else if (m_dimension == 2){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100*m_width/m_height , 100*m_width/m_height , -100 , 100 , 1 , 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //視点の設定
    gluLookAt(0,100.0,200.0, //カメラの座標
	      0.0,0.0,0.0, // 注視点の座標
	      0.0,1.0,0.0); // 画面の上方向を指すベクトル
  }
  
  glutMainLoop();

}

// openGL function ------------------------------------------------------------------------------
void OpenGLWindow::idle(){
  glutPostRedisplay();
}
// draw the window ------------------------------------------------------------------------------
void OpenGLWindow::display1st(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// draw whole the window
  glMatrixMode(GL_MODELVIEW);

  //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  //glEnable(GL_BLEND);
}

void OpenGLWindow::display2nd(){
  glFlush();
  glutSwapBuffers();
}

// event handler for scaling the window -------------------------------------------------------
void OpenGLWindow::resize(int w, int h){
  // set whole the window to the viewport
  glViewport(0, 0, w, h);
}
// keyboard event -----------------------------------------------------------------------------
void OpenGLWindow::keyboard(unsigned char key, int x, int y){
  switch (key){
  case 's':
    if(m_idleFlag){
      glutIdleFunc(0);		//stop idle
      m_idleFlag = GL_FALSE;
    } else {
      glutIdleFunc(idleFunc_);	//start idle
      m_idleFlag = GL_TRUE;
    }
    break;
  case 'z':
    m_scaled *= 1.1;
    glScaled(1.1, 1.1, 1.1);
    m_wheel++;
    glutPostRedisplay();
    break;
  case 'x':
    m_scaled *= 0.9;
    glScaled(0.9, 0.9, 0.9);
    m_wheel--;
    glutPostRedisplay();
    break;
  case 'r':
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,100.0,200.0, //カメラの座標
	      0.0,0.0,0.0, // 注視点の座標
	      0.0,1.0,0.0); // 画面の上方向を指すベクトル
    glutPostRedisplay();
    break;
  case '\033':			//ESC
    exit(0);
  default:
    break;
  }
}
// mouse click event --------------------------------------------------------------------------
void OpenGLWindow::mouse(int button, int state, int x, int y){
  if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
    m_mouseFlagR = GL_TRUE;
    m_mouseFlagL = GL_FALSE;
    m_mouseX = x;
    m_mouseY = y;
  } else if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    m_mouseFlagR = GL_FALSE;
    m_mouseFlagL = GL_TRUE;
    m_mouseX = x;
    m_mouseY = y;
  } else if(m_mouseFlagL == GL_TRUE && state == GLUT_UP){
    m_mouseFlagR = GL_FALSE;
    m_mouseFlagL = GL_FALSE;
  } else if(m_mouseFlagR == GL_TRUE && state == GLUT_UP){
	M_Current = M_Target;
    m_mouseFlagR = GL_FALSE;
    m_mouseFlagL = GL_FALSE;
  }
}
// mouse motion event ------------------------------------------------------------------------
void OpenGLWindow::mouseMotion(int x, int y){
  if(m_mouseFlagR == GL_FALSE && m_mouseFlagL == GL_FALSE) return;
  if(m_mouseFlagR == GL_TRUE){
    //移動量を計算
    double dx = (x - m_mouseX) * 1.33/m_width;
    double dy = (y - m_mouseY) * 1.0/m_height;
    m_mouseX = x;
    m_mouseY = y;

    //クォータニオンの長さ
    double length = sqrt(dx * dx + dy * dy);

    if (length != 0.0) {
      double radian = length * M_PI;
      double theta = sin(radian) / length;
      Quaternion After={ cos(radian), -dy * theta, dx * theta, 0.0};//回転後の姿勢

      M_Target = After;
      qtor(m_rotate, M_Target);
      M_Current = M_Target;
    }

    glMatrixMode(GL_MODELVIEW);
    glMultMatrixd(m_rotate);
  } else if(m_mouseFlagL == GL_TRUE) {
    m_translateX += (m_mouseX - x)*0.5/sqrt(m_scaled);
    m_translateY += (m_mouseY - y)*0.5/sqrt(m_scaled);
    m_translateZ += 0;
    glTranslated(-(m_mouseX - x)*0.5/sqrt(m_scaled), (m_mouseY - y)*0.5/sqrt(m_scaled), 0);
    m_mouseX = x;
    m_mouseY = y;
  }
  glutPostRedisplay();
}

void OpenGLWindow::mouseWheel(int wheel_number, int direction, int x, int y)
{
 if(direction==1){
	 m_scaled *= 1.1;
	 glScaled(1.1, 1.1, 1.1);
	 m_wheel++;
 } else {
	 m_scaled *= 0.9;
	 glScaled(0.9, 0.9, 0.9);
	 m_wheel--;
 }
 glutPostRedisplay();
}

// calc a rotate matrix from qtor
void qtor(double *r , Quaternion q){
  double xx = q.x * q.x * 2.0;
  double yy = q.y * q.y * 2.0;
  double zz = q.z * q.z * 2.0;
  double xy = q.x * q.y * 2.0;
  double yz = q.y * q.z * 2.0;
  double zx = q.z * q.x * 2.0;
  double xw = q.x * q.w * 2.0;
  double yw = q.y * q.w * 2.0;
  double zw = q.z * q.w * 2.0;
  double r1[16]={ (1.0 - yy - zz), xy + zw, (zx - yw), 0.0,
		  (xy - zw), 1.0 - zz - xx, (yz + xw), 0.0,
		  (zx + yw), yz - xw, (1.0 - xx - yy), 0.0,
		  0.0, 0.0, 0.0, 1.0};
  for (int i = 0;i < 16;i++) {
    r[i]=r1[i];
  }
}

//演算子のオーバーロード Quaternionの積
Quaternion & operator *( Quaternion &q1, Quaternion &q2 ){
  Quaternion q0={
    q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
    q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
    q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
    q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
  };
  q1=q0;
  return q1;
}
Quaternion & operator -( Quaternion &q1, Quaternion &q2 ){
  Quaternion q0={
    q1.w - q2.w,
    q1.x - q2.x,
    q1.y - q2.y,
    q1.z - q2.z,
  };
  q1=q0;
  return q1;
}
