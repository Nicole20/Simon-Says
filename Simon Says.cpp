// Simon Says.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<glut.h>
#include<freeglut.h>
#include<math.h>
#include<ctime>

using namespace std;

void initialize();
void draw();

vector<int> notes;
int num = 0;
float red_r = 0, green_r = 0, blue_r = 0, red_g = 0, green_g = 0, blue_g = 0, 
red_b = 0, green_b = 0, blue_b = 0, red_y = 0, green_y = 0, blue_y = 0;
bool red = false, green = false, blue = false, yellow = false, lost = false;
void addNote();
void check();

void Timer1(int value);
void Timer2(int value);
void Timer3(int value);
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Simon Says");

	initialize();

	glutDisplayFunc(draw);
	glutMouseFunc(mouse);

	glutTimerFunc(0, Timer2, 0);

	glutMainLoop();

	return 0;
}

void initialize()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, 10, 0, 10);
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (lost)
	{
		glColor3f(1, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(10, 0);
		glVertex2f(10, 10);
		glVertex2f(0, 10);
		glEnd();
	}
	else
	{
		glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(0.7, 0.7);
		glVertex2f(4.3, 0.7);
		glVertex2f(4.3, 4.3);
		glVertex2f(0.7, 4.3);

		glVertex2f(5.7, 0.7);
		glVertex2f(9.3, 0.7);
		glVertex2f(9.3, 4.3);
		glVertex2f(5.7, 4.3);

		glVertex2f(0.7, 5.7);
		glVertex2f(4.3, 5.7);
		glVertex2f(4.3, 9.3);
		glVertex2f(0.7, 9.3);

		glVertex2f(5.7, 5.7);
		glVertex2f(9.3, 5.7);
		glVertex2f(9.3, 9.3);
		glVertex2f(5.7, 9.3);
		glEnd();

		glColor3f(red_r, green_r, blue_r);
		glBegin(GL_QUADS);
		glVertex2f(1, 1);
		glVertex2f(4, 1);
		glVertex2f(4, 4);
		glVertex2f(1, 4);
		glEnd();

		glColor3f(red_g, green_g, blue_g);
		glBegin(GL_QUADS);
		glVertex2f(6, 1);
		glVertex2f(9, 1);
		glVertex2f(9, 4);
		glVertex2f(6, 4);
		glEnd();

		glColor3f(red_b, green_b, blue_b);
		glBegin(GL_QUADS);
		glVertex2f(1, 6);
		glVertex2f(4, 6);
		glVertex2f(4, 9);
		glVertex2f(1, 9);
		glEnd();

		glColor3f(red_y, green_y, blue_y);
		glBegin(GL_QUADS);
		glVertex2f(6, 6);
		glVertex2f(9, 6);
		glVertex2f(9, 9);
		glVertex2f(6, 9);
		glEnd();
	}

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void addNote()
{
	srand(time(NULL));

	int note = rand() % 4;
	notes.push_back(note);
}

void Timer1(int value)
{
	lost = false;

	if (notes[num] == 0)
	{
		red_r = 1;
	}
	else if (notes[num] == 1)
	{
		red_y = 1;
		green_y = 1;
	}
	else if (notes[num] == 2)
	{
		green_g = 1;
	}
	else if (notes[num] == 3)
	{
		blue_b = 1;
	}

	num++;

	glutTimerFunc(500, Timer2, 0);
}

void Timer2(int value)
{
	red_r = 0.5;
	red_y = 0.5;
	green_y = 0.5;
	green_g = 0.5;
	blue_b = 0.5;

	if (notes.size() == 0)
	{
		addNote();
	}

	if (num < notes.size())
	{
		glutTimerFunc(500, Timer1, 0);
	}
	else
	{
		num = 0;
	}
}

void Timer3(int value)
{
	red_r = 0.5;
	red_y = 0.5;
	green_y = 0.5;
	green_g = 0.5;
	blue_b = 0.5;

	if (num == notes.size())
	{
		addNote();
		num = 0;
		glutTimerFunc(500, Timer1, 0);
	}
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (x > 50 && x < 200)
			{
				if (y > 300 && y < 450)
				{
					red = true;
				}
				else if (y > 50 && y < 200)
				{
					blue = true;
				}
			}
			else if (x > 300 && x < 450)
			{
				if (y > 300 && y < 450)
				{
					green = true;
				}
				else if (y > 50 && y < 200)
				{
					yellow = true;
				}
			}

			check();
			red = false;
			green = false;
			blue = false;
			yellow = false;

			if (!lost)
			{
				num++;
				glutTimerFunc(500, Timer3, 0);
			}
			else
			{
				glutTimerFunc(0, Timer2, 0);
			}
		}
	}
}

void check()
{
	if (num < notes.size())
	{
		if (notes[num] == 0 && red)
		{
			red_r = 1;
		}
		else if (notes[num] == 1 && yellow)
		{
			red_y = 1;
			green_y = 1;
		}
		else if (notes[num] == 2 && green)
		{
			green_g = 1;
		}
		else if (notes[num] == 3 && blue)
		{
			blue_b = 1;
		}
		else
		{
			notes.clear();
			lost = true;
			num = 0;
		}
	}
}
