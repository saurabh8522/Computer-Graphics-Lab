#include <GL/freeglut.h>
#include <GL/gl.h>
#include <unistd.h>
#include<stdio.h>

void printline() {
  glPointSize(2.0);
  glClearColor(0.0, 0.0, 0.0, 1.0); 
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  int x1=10,x2=80,y1=20,y2=80;
  int dy=y2-y1,dx=x2-x1;
  int slope_error=2*(y2-y1)-(x2-x1);
  int prev_p=2*dx-dy;
  for(int x=x1,y=y1;x<=x2;){
    
    glBegin(GL_POINTS);
    glVertex2f((float)x/(float)100,(float)y/(float)100);
    glEnd();
    glFlush();
    if(prev_p<0){
      x=x+1,y=y;
      int next_p=prev_p+2*dy;
      prev_p=next_p;
    }
    else{
      x=x+1,y=y+1;
      int next_p=prev_p+2*dy-2*dx;
      prev_p=next_p;
    }
  }
  
}

int main(int argc, char* argv[]) {
  int x1,x2,y1,y2;
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("OpenGL - Creating a triangle");
  glutDisplayFunc(printline);
  glutMainLoop();
  return 0;
}