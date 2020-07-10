#pragma once
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include <windows.h>

float Psize = 2.0;
void GoMenu(int value);
float logHeight = 100.0;

void drawPalette(float v1, float v2, float v3, float v4)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(v1, logHeight - (v2));
	glVertex2f(v1, logHeight - (v3));
	glVertex2f(v4, logHeight - (v3));
	glVertex2f(v4, logHeight - (v2));
	glEnd();
}

void drawFilledCircle(int x1, int y1, int x2, int y2) {
	int num_segments = 360;
	if (x2 < 3) x2 = 3;
	if (x2 > 97) x2 = 97;
	if (y2 < 3) y2 = 3;
	if (y2 > 85) y2 = 85;
	glBegin(GL_TRIANGLE_FAN);
    float r1 = (x2 - x1) / 2;
    float r2 = (y2 - y1) / 2;

    float centerX = x1 + r1;
    float centerY = y1 + r2;

for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = centerX + (cos(theta) * r1);
        float y = centerY + (sin(theta) * r2);
        glVertex2f(x, y);
    }
    glEnd();
}

float currVertex[8];
float sideLen = 4.0;
void drawColoredButton(float centerx, float centery, int r, int g, int b)
{

	float size1 = 9.4 / 2;
	float size2 = 4 / 2;
	currVertex[0] = centerx - size1;
	currVertex[1] = centery - size2;
	currVertex[2] = centerx + size1;
	currVertex[3] = centery + size2;
	glColor3ub(r, g, b);
	glBegin(GL_POLYGON);
	glVertex2f(currVertex[0], currVertex[1]);
	glVertex2f(currVertex[2], currVertex[1]);
	glVertex2f(currVertex[2], currVertex[3]);
	glVertex2f(currVertex[0], currVertex[3]);
	glEnd();

}
void drawCenter(float centerx, float centery)
{

	float size = sideLen / 2;
	currVertex[0] = centerx - size;
	currVertex[1] = centery - size;
	currVertex[2] = centerx + size;
	currVertex[3] = centery + size;

	glBegin(GL_POLYGON);
	glVertex2f(currVertex[0], currVertex[1]);
	glVertex2f(currVertex[2], currVertex[1]);
	glVertex2f(currVertex[2], currVertex[3]);
	glVertex2f(currVertex[0], currVertex[3]);
	glEnd();

}

void drawFilledRect(int xi, int xf, int yi, int yf) {
	glBegin(GL_POLYGON);
	glVertex2i(xi, yi);
	glVertex2i(xi, yf);
	glVertex2i(xf, yf);
	glVertex2i(xf, yi);
	glEnd();
}

void drawRect(int xi, int xf, int yi, int yf)
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(xi, yi);
	glVertex2i(xi, yf);
	glVertex2i(xf, yf);
	glVertex2i(xf, yi);
	glEnd();
}

void printStr(std::string str, float x, float y)
{
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2d(x, y);

	int counter = 0;

	for (int i = 0; i < str.size(); i++) {
		++counter;

		GLint vertex[4];
		glGetIntegerv(GL_CURRENT_RASTER_POSITION, vertex);
		if (vertex[0] > 665 || str[i] == 13)
		{
			glRasterPos2d(x, y -= 3);
        counter = 0;
		}
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}

void drawCircle(int x1, int y1, int x2, int y2)
{
	int num_segments = 360;
	if (x2 < 3) x2 = 3;
	if (x2 > 97) x2 = 97;
	if (y2 < 3) y2 = 3;
	if (y2 > 85) y2 = 85;
	glBegin(GL_LINE_LOOP);
    float r1 = (x2 - x1) / 2;
    float r2 = (y2 - y1) / 2;

    float centerX = x1 + r1;
    float centerY = y1 + r2;

for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = centerX + (cos(theta) * r1);
        float y = centerY + (sin(theta) * r2);
        glVertex2f(x, y);
    }
    glEnd();
}


void drawLine(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void drawPoint(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}
struct Dot
{
	float x, y;
	float r, g, b;
	float Pointsize;
};
std::vector<Dot> dots;
std::vector<Dot> penSh;

struct Line
{
	int x, y, x2, y2;
	float r, g, b;
	float Pixsize;
};
std::vector<Line> lines;
std::vector<Line> lines2;

struct rect
{
	int fill;
	int xi, xf, yi, yf;
	float r, g, b;
	float Pixsize;
};
std::vector<rect> rects;
std::vector<rect> rects2;

struct circle
{
	int fill;
	int xi, xf, yi, yf;
	float r, g, b;
	float Pointsize;
};
std::vector<circle> circles;
std::vector<circle> circles2;

struct Text
{
	std::string str;
	int x, y;
};
std::vector<Text> strings;
std::vector<Text> strings2;

struct Tshapes
{   int ID;
    std::vector<Dot> TpenSh;
    std::vector<Line> Tlines;
    std::vector<rect> Trects;
    std::vector<circle> Tcircles;
    std::vector<Text> Tstrings;
};
std::vector<Tshapes> Tshape;

struct History
{
	int Tshape;
};
std::vector<History> call_stack;

void update_history()
{
	History history;
	history.Tshape = Tshape.size();
	call_stack.push_back(history);
}

void undo()
{
	if (call_stack.size() == 1) return;
	call_stack.pop_back();
	History history = call_stack[call_stack.size()-1];
	if (history.Tshape != Tshape.size())
	{
		Tshape.pop_back();
	}
}
