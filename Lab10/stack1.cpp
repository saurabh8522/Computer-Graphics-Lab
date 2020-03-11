#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string.h>
#include <GL/glut.h>
#include <cstdlib>
#include<bits/stdc++.h>
#include <math.h>
#include<stdio.h>
using namespace std;

struct elem
{
	string c;
	
};
int num =1;
int MAX = 6;
int tos = -1;
int width = 200;
int height = 25;
elem a[20];
int SCREEN_WIDTH = 700; 
int SCREEN_HEIGHT = 700; 
bool init()
{
	glClearColor(0, 0, 0, 1); 

	glViewport(0, 0, 500, 500); 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-250, 250, -250, 250, -100, 100); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void show();

void drawBitmap(char *string, int x, int y)
{
	glRasterPos2f(x, y);

	for (int i = 0; i < strlen(string); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
	}
}

void push()
{	
	if (tos >= MAX)
	{
		drawBitmap("STACK IS FULL", -70, 220);
		glutSwapBuffers();
		// sleep(100);
		
	}
	else{
		tos++;
	// 	glBegin(GL_LINES);
 //    	glVertex2f(100, 50*tos+25);
 //    	glVertex2f(120, 50*tos+25);
	// 	glEnd();
	// glBegin(GL_LINES);
 //    	glVertex2f(100, 50*tos+25);
 //    	glVertex2f(105, 50*tos+0.5);
	// 	glEnd();
	// glBegin(GL_LINES);
 //    	glVertex2f(100, 50*tos+25);
 //    	glVertex2f(120, 50*tos-0.5);
	// 	glEnd();
		cout<<num<<" is inserted\n";
		// cout<<"\nEnter the Element: ";
		// cin >> a[tos].c;
		string d="";
		int x=num++;
		num=num%10;
		if(num==0){
			num=1;
		}
		// int i=0;
		while(x>0){
			d+=x+'0';
			x/=10;
		}
		reverse(d.begin(),d.end());
		a[tos].c=d;
		show();

	}
}

void show()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, -200, 0);
	int k = 0;
	glBegin(GL_LINES);
    	glVertex2f(100, 50*tos+25);
    	glVertex2f(120, 50*tos+25);
		glEnd();
	glBegin(GL_LINES);
    	glVertex2f(100, 50*tos+25);
    	glVertex2f(105, 50*tos+0.5);
		glEnd();
	glBegin(GL_LINES);
    	glVertex2f(100, 50*tos+25);
    	glVertex2f(120, 50*tos-0.5);
		glEnd();
	for (int i = 0; i <= tos; i++) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		glVertex2f(-100, k);
		glVertex2f(100, k);
		glVertex2f(100, k + 50);
		glVertex2f(-100, k + 50);
		glEnd();
		
		glRasterPos2f(-2, (k + 10));

		for (int j = 0; j < a[i].c.size(); j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, a[i].c[j]);
		}
		k += 50;
	}
	glutSwapBuffers();
	glPopMatrix();
}

void pop()
{
	// cout<<"tos2="<<tos<<endl;
	if (tos <0)
	{
		// cout<<"tos1="<<tos<<endl;
		char *c = "STACK IS EMPTY";
		cout<<c<<endl;
		glRasterPos2i(-70, 200);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c[i]);
		}
		glutSwapBuffers();

		// sleep(1000);
	}
	else
	{

		cout << "\nElement " << a[tos].c << " is removed from stack\n";
		tos--;
	// 	glBegin(GL_LINES);
 //    	glVertex2f(100, 50*tos+25);
 //    	glVertex2f(120, 50*tos+25);
	// 	glEnd();
	// glBegin(GL_LINES);
 //    	glVertex2f(100, 50*tos+25);
 //    	glVertex2f(105, 50*tos+0.5);
	// 	glEnd();
	// glBegin(GL_LINES);
 //    	glVertex2f(100, 50*tos+25);
 //    	glVertex2f(120, 50*tos-0.5);
	// 	glEnd();
		show();
	}
}

void render() 
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(0, -200, 0);

	int k = 0;

	for (int i = 0; i <= MAX; i++) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		glVertex2f(-100, k);
		glVertex2f(100, k);
		glVertex2f(100, k + 50);
		glVertex2f(-100, k + 50);
		glEnd();

		glRasterPos2f(-2, (k + 10));

		// for (int j = 0; j < strlen(a[i].c); j++)
		// {
		// 	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, a[i].c[j]);
		// }
		k += 50;
	}
	glutSwapBuffers();
	glPopMatrix();
	cout<<"tos= "<<tos<<endl;
	if (tos == -1)
	{
		// char *c = "STACK IS EMPTY";
		// glRasterPos2i(-70, 200);
		// for (int i = 0; i < strlen(c); i++)
		// {
		// 	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c[i]);
		// }
		char *c = "2. Enter d to Pop";
		glRasterPos2i(-70,160);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c[i]);
		}
		c = "1. Enter i to Push";
		glRasterPos2i(-70, 180);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c[i]);
		}
		glFlush();
		glutSwapBuffers();
	}
	else{
		glFlush();
		show();
		}
}

void reshape(int w, int h) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glColor3f(1.0f, 0.99f, 0.0f);
	glViewport(0, 0, w, h); 
	glOrtho(-250, 250, -250, 250, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i': push();
		break;

	case 'd': pop();
		render();
		break;
	case 'q': exit(0);
	}
}


int main(int argc, char*argv[])
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); 
	glutCreateWindow("STACK");

	// if (!init()) //check for the error
	// {
	// 	cout << "Error" << endl;
	// 	return -1;
	// }

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(render);  //register display func
	glutReshapeFunc(reshape); //register reshape func
	glutMainLoop(); //loop the main section

	return 0;
}