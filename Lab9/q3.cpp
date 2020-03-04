#include<stdio.h>
//#include<iostream.h>
#include<GL/glut.h>
#include<math.h>
#include <unistd.h>
 
 
int n;
 
 
int max(int a,int b)
{
    // printf("%f %f\n",a,b);
    if(a>b)
        return a;
    return b;
 
}
 
 
void myInit (void)
{
    // making background color black as first  
    // 3 arguments all are 0.0
    glClearColor(1.0, 1.0, 1.0, 1.0);
     
    // making picture color green (in RGB mode), as middle argument is 1.0
    glColor3f(0.0, 1.0, 0.0);
     
    // breadth of picture boundary is 1 pixel
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
     
    // setting window dimension in X- and Y- direction
    gluOrtho2D(-250, 250, -250, 250);
}
 
struct Point{
    int x,y;
};
 
void Print(struct Point bl,struct Point br,struct Point tr,struct Point tl)
{
    printf("%d,%d %d,%d %d,%d %d,%d\n",bl.x,bl.y,br.x,br.y,tr.x,tr.y,tl.x,tl.y);
    return ;
}
 
void myFun(struct Point bl,struct Point br,struct Point tr,struct Point tl,int cnt)
{
    if(cnt==0)
        return;
 
    Print(bl,br,tl,tr);  
 
    struct Point mbl,mbr,mtr,mtl;
 
    mbl.x = mtl.x = bl.x+(-bl.x+br.x)/3;
    mbl.y = mbr.y = bl.y+(-bl.y+tl.y)/3;
    mbr.x = mtr.x = bl.x+2*(-bl.x+br.x)/3;
    mtl.y = mtr.y = bl.y+2*(-bl.y+tl.y)/3;
 
    glBegin(GL_QUADS);          // Each set of 3 vertices form a triangle
      glColor3f(1.0f, 1.0f, 1.0f); // White
      glVertex2i(mbl.x,mbl.y);
      glVertex2i(mbr.x,mbr.y);
      glVertex2i(mtr.x,mtr.y);
      glVertex2i(mtl.x,mtl.y);
     
    glEnd();
 
 
    // myFun(up,left_mid,right_mid,cnt-1);
    // myFun(left_mid,left,down_mid,cnt-1);
    // myFun(right_mid,down_mid,right,cnt-1);
 
    struct Point p1,p2,p3,p4;
    p1 = tl;
    for(int i=0;i<3;i++)
    {
        p1.x = tl.x;
        for(int j=0;j<3;j++)
        {            
            if((i==1)&&(j==1))
            {
                p1.x += (tr.x-tl.x)/3;
                continue;
            }
            p2.x = p1.x + (tr.x-tl.x)/3;
            p2.y = p1.y;
            p3.x=p2.x;
            p3.y = p2.y - (tr.y-br.y)/3;
            p4.x = p1.x;
            p4.y = p3.y;
            myFun(p4,p3,p2,p1,cnt-1);
            p1.x += (tr.x-tl.x)/3;
        }
        p1.y -= (tl.y-bl.y)/3;
    }
 
    return;
 
}
 
 
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);          // Each set of 3 vertices form a triangle
      glColor3f(0.0f, 0.0f, 0.0f); // Black
      glVertex2i(0,0);
      glVertex2i(200,0);
      glVertex2i(200,200);
      glVertex2i(0,200);
 
    glEnd();
 
    struct Point br,bl,tl,tr;
    br={200,0};
    bl={0,0};
    tl={0,200};
    tr={200,200};
    myFun(bl,br,tr,tl,n);
    glFlush();
}
 
 
int main (int argc, char** argv)
{
 
    printf("Enter the number : ");
    scanf("%d",&n);
 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     
    // giving window size in X- and Y- direction
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
     
    // Giving name to window
    glutCreateWindow("Sierpinski Gasket");
    myInit();
     
    glutDisplayFunc(myDisplay);
    //glutIdleFunc(idle);
    glutMainLoop();
}