#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;

int pntX1, pntY1, choice = 0, edges;
float cx,cy,r;
int transX, transY;
double scaleX, scaleY;

double round(double d)
{
	return floor(d + 0.5);
}

void drawCircle()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
    for (int ii = 0; ii < 1000; ii++){
        float theta = 2.0f * 3.14f * float(ii) / float(1000);
        float x = r * cosf(theta);
        float y = r * sinf(theta); 
        glVertex2f(x + cx, y + cy); 
    }
    glEnd();
}


void drawCircleTrans(int t1, int t2)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
    for (int ii = 0; ii < 1000; ii++)   {
        float theta = 2.0f * 3.14f * float(ii) / float(1000); 
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx+t1, y + cy+t2);
    }
    glEnd();
}

void drawCircleScale(double t1, double t2)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
    for (int ii = 0; ii < 1000; ii++)   {
        float theta = 2.0f * 3.14f * float(ii) / float(1000);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(round((x)*t1+cx), round((y)*t2+cy));
    }
    glEnd();
}


void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
}


void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	if (choice == 1)
	{
		drawCircle();
		drawCircleTrans(transX, transY);
	}
	else if (choice == 2)
	{
		drawCircle();
		drawCircleScale(scaleX, scaleY);
	}

	glFlush();
}

int main(int argc, char** argv)
{
	cout << "Enter your choice:\n\n" << endl;

	cout << "1. Translation" << endl;
	cout << "2. Scaling" << endl;
	cout << "3. Exit" << endl;

	cin >> choice;

	if (choice == 3) {
		return 0;
	}

	cout<<"Enter center co-ordinates and radius of circle"<<endl;
	cin>>cx>>cy>>r;

	if (choice == 1)
	{
		cout << "Enter the translation factor for X and Y: "; cin >> transX >> transY;
	}
	else if (choice == 2)
	{
		cout << "Enter the scaling factor for X and Y: "; cin >> scaleX >> scaleY;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Circle Transformations");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

}
