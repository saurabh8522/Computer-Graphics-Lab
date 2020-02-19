#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;

int pntX1, pntY1, choice = 0, edges;
vector<int> pntX;
vector<int> pntY;
int transX, transY;
double scaleX, scaleY;
double angle, angleRad;

double round(double d)
{
	return floor(d + 0.5);
}

void drawLine()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(pntX[0], pntY[0]);
	glVertex2f(pntX[1], pntY[1]);
	glEnd();
}


void drawLineTrans(int x, int y)
{
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(pntX[0]+x, pntY[0]+y);
	glVertex2f(pntX[1]+x, pntY[1]+y);
	glEnd();
}

void drawLineScale(double x, double y)
{
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	int a=pntX[0],b=pntY[0];
	pntX[1]-=pntX[0];
	pntY[1]-=pntY[0];
	pntX[0]=pntY[0]=0;
	glVertex2f(round(pntX[0] * x+a), round(pntY[0] * y+b));
	glVertex2f(round(pntX[1] * x+a), round(pntY[1] * y+b));
	glEnd();
}

void drawLineRotation(double angleRad)
{
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(round((pntX[0] * cos(angleRad)) - (pntY[0] * sin(angleRad))), round((pntX[0] * sin(angleRad)) + (pntY[0] * cos(angleRad))));
	glVertex2i(round((pntX[1] * cos(angleRad)) - (pntY[1] * sin(angleRad))), round((pntX[1] * sin(angleRad)) + (pntY[1] * cos(angleRad))));

	glEnd();
}


void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(10.0);
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
		drawLine();
		drawLineTrans(transX, transY);
	}
	else if (choice == 2)
	{
		drawLine();
		drawLineScale(scaleX, scaleY);
	}
	else if (choice == 3)
	{
		drawLine();
		drawLineRotation(angleRad);
	}

	glFlush();
}

int main(int argc, char** argv)
{
	cout << "Enter your choice:\n\n" << endl;

	cout << "1. Translation" << endl;
	cout << "2. Scaling" << endl;
	cout << "3. Rotation" << endl;
	cout << "4. Exit" << endl;

	cin >> choice;

	if (choice == 4) {
		exit(0);
	}

	for (int i = 0; i < 2; i++)
	{
		// cout<<i<<endl;
		cout << "Enter co-ordinates for vertex  " << i + 1 << " : "; cin >> pntX1 >> pntY1;
		pntX.push_back(pntX1);
		pntY.push_back(pntY1);
	}

	if (choice == 1)
	{
		cout << "Enter the translation factor for X and Y: "; cin >> transX >> transY;
	}
	else if (choice == 2)
	{
		cout << "Enter the scaling factor for X and Y: "; cin >> scaleX >> scaleY;
	}
	else if (choice == 3)
	{
		cout << "Enter the angle for rotation: "; cin >> angle;
		angleRad = angle * 3.1416 / 180;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Line Transformations");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

}
