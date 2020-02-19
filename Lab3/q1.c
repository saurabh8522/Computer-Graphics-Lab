#include <GL/freeglut.h>
#include <GL/gl.h>
#include <unistd.h>
#include<stdio.h>
float max(float a,float b){
  return a>b?a:b;
}
float ab(float a){
  if(a>0){
    return a;
  }
  return -1*a;
}
void printline() {
  glPointSize(2.0);
  glClearColor(0.0, 0.0, 0.0, 1.0); 
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  float x1=0.4,x2=0.5,y1=0.4,y2=0.6;
  float dx=x2-x1,dy=y2-y1;
  if(dx==0||dy==0){
    printf("Cannot print a line!!\n");
    exit(0);
  }
  float np=max(ab(10*dx),ab(10*dy));
  
  float xin=dx/(float)np,yin=dy/(float)np;
  printf("np=%f %f %f %f %f\n",np,dx,dy,xin,yin );
  for(int i=0;i<10*np;i++){
    glBegin(GL_POINTS);
    float f1=(10*x1+i*xin)/(float)10,f2=(10*y1+i*yin)/(float)10;
    printf("%f %f\n",f1,f2 );
    glVertex2f(f1,f2);
    glEnd();
    glFlush();
  }
}

int main(int argc, char* argv[]) {
  
    glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("OpenGL - Creating a line");
  glutDisplayFunc(printline);
  glutMainLoop();
  return 0;
}