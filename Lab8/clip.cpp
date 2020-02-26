// #include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<iostream>

void display();
using namespace std;
float xmin=-100,ymin=-100,xmax=100,ymax=100;
float xd1,yd1,xd2,yd2;

void init(void){
    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300,300,-300,300);
}

int code(float x,float y){
    int c=0;
    if((x+y)>100)c=8;
    if((x+y)<-100)c=4;
    if((x-y)>100)c=c|2;
    if((y-x)>100)c=c|1;
    return c;
}

void crop_Line(float x1,float y1,float x2,float y2){
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m=(y2-y1)/(x2-x1);
    cout<<c1<<" "<<c2<<endl;
    while((c1|c2)>0)
    {   cout<<c1<<" "<<c2<<endl;
        if((c1 & c2)>0)
        {
           exit(0);
        }

    float xi=x1;float yi=y1;
    int c=c1;
    if(c==0)
    {
         c=c2;
         xi=x2;
         yi=y2;
    }
    float x,y;
    if((c & 8)>0)
    {
       x=(100-yi+m*xi)/(float)(m+1);
       y=m*(x-xi)+yi;
       // x=xi+ (1.0/(float)m)*(ymax-yi);
    }
    else
      if((c & 4)>0)
      {
          // y=ymin;
          x=(-100-yi+m*xi)/(float)(m+1);
            y=m*(x-xi)+yi;
      }
      else
       if((c & 2)>0)
       {
           
            x=(-100-yi+m*xi)/(float)(m-1);
            y=m*(x-xi)+yi;
       }
       else
       if((c & 1)>0)
       {
           x=(100-yi+m*xi)/(float)(m-1);
            y=m*(x-xi)+yi;
       }
       cout<<"x="<<x<<" y= "<<y<<endl;
       // break;
       if(c==c1)
       {
           xd1=x;
           yd1=y;
           c1=code(xd1,yd1);
       }

       if(c==c2)
       {
           xd2=x;
           yd2=y;
           c2=code(xd2,yd2);
        }
    }
    // float angle=22.0/28;
    // xd1=xd1*cos(angle)+yd1*sin(angle);
    // yd1=-xd1*sin(angle)+yd1*cos(angle);
    // xd2=xd2*cos(angle)+yd2*sin(angle);
    // yd2=-xd2*sin(angle)+yd2*cos(angle);
    display();
}

void mykey(unsigned char key,int x,int y)
{
    if(key=='c')
    {  
        crop_Line(xd1,yd1,xd2,yd2);
        cout<<xd1<<" "<<yd1<<" "<<xd2<<" "<<yd2<<endl;
        // cout<<"Line Cropped"<<endl;
        glFlush();
    }
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin,0);
    glVertex2i(0,ymax);
    glVertex2i(xmax,0);
    glVertex2i(0,ymin);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(xd1,yd1);
    glVertex2i(xd2,yd2);
    glEnd();
    glFlush();
}


int main(int argc,char** argv)
{
    // printf("Enter the co-ordinates of clipping window\n");
    // cin>>xmin>>ymin>>xmax>>ymax;
    printf("Enter line co-ordinates:");
    cin>>xd1>>yd1>>xd2>>yd2;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Clipping");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykey);
    init();
    glutMainLoop();
    return 0;
}