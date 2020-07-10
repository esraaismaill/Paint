#include "helpers.h"

float logWidth = 100.0;

float phyWidth = 700.0;
float phyHeight = 700.0;

int centerX = logWidth / 2;
int centerY = logHeight / 2;

int xi, yi, xf, yf;
//passiveMouse
int mouseX = centerX;
int mouseY = centerY;
//mouseClick Down
int mouseXX = centerX;
int mouseYY = centerY;

//mouseClick up
int mouseXXU = centerX;
int mouseYYU = centerY;

//Motionmouse
float mouseXXX = centerX;
float mouseYYY = centerY;

int states = 0, filled = 0, ClickFilled =0;
int offset = 1, offset1 = 3, offset2 = 15;

float r = 0, g = 0, b = 0;

int drawing_areaX1, drawing_areaY1, drawing_areaX2, drawing_areaY2;
bool indraw = false;
std::string txt;

void init2D(float r, float g, float b) {
	glClearColor(r, g, b, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, logWidth, 0, logHeight);

	update_history();
}

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		mouseXX = x;
		mouseXX = 0.5 + 1.0*mouseXX*logWidth / phyWidth;
		mouseYY = phyHeight - y;
		mouseYY = 0.5 + 1.0*mouseYY*logHeight / phyHeight;
		if (mouseXX >= 3 && mouseXX <= 12 && mouseYY >= 93 && mouseYY <= 97)//Line
		{
			states = 1;
			printf("line button clicked \n");
		}

		else if (mouseXX >= 3 && mouseXX <= 12 && mouseYY >= 88 && mouseYY <= 92)//pen
		{
			states = 2;
			printf("pen button clicked \n");
		}
		else if (mouseXX >= 14 && mouseXX <= 23 && mouseYY >= 93 && mouseYY <= 97)//rect
		{
			states = 3;
			printf("rect button clicked \n");
		}
		else if (mouseXX >= 14 && mouseXX <= 23 && mouseYY >= 88 && mouseYY <= 92)//Text
		{
			printf("text button clicked \n");
			states = 4;
			MessageBox(0,"\tplease CLICK anywhere in the screen \n   before choosing another button to end your text!", "WARNING!!",48);
		}
		else if (mouseXX >= 25 && mouseXX <= 34 && mouseYY >= 93 && mouseYY <= 97)//Circle
		{
			states = 5;
			printf("circle button clicked \n");
		}
		else if (mouseXX >= 25 && mouseXX <= 34 && mouseYY >= 88 && mouseYY <= 92)//Undo
		{
			states = 6;
			printf("undo button clicked \n");
			undo();
		}
		else if (mouseXX >= 36 && mouseXX <= 45 && mouseYY >= 93 && mouseYY <= 97)//Fill
		{
		    ClickFilled++;
		if(ClickFilled%2==1){filled = 1;} // if you clicked once it will select Fill
		else if(ClickFilled%2==0){filled = 0;} // if you clicked on Fill twice it will set it to the default state "No Fill"
			states = 7;
			printf("fill button clicked \n");
		}
		else if (mouseXX >= 36 && mouseXX <= 45 && mouseYY >= 88 && mouseYY <= 92)//No Fill
		{   ClickFilled=0;
			states = 8; filled = 0;
			printf("no fill button clicked \n");
		}
		else if (mouseXX >= (53 - sideLen / 2) && mouseXX <= (53 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
		{
			r = 255, g = 0.0, b = 0.0;
		} //red
		else if (mouseXX >= (59 - sideLen / 2) && mouseXX <= (59 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
		{
			r = 0.0, g = 255, b = 0.0;
		} //green
		else if (mouseXX >= (65 - sideLen / 2) && mouseXX <= (65 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
		{
			r = 0.0, g = 0.0, b = 255;
		} //blue
		else if (mouseXX >= (71 - sideLen / 2) && mouseXX <= (71 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
		{
			r = 255, g = 255, b = 0.0;
		} //yellow
		else if (mouseXX >= (77 - sideLen / 2) && mouseXX <= (77 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
		{
			r = 255, g = 165, b = 0.0;
		} //orange
		else if (mouseXX >= (83 - sideLen / 2) && mouseXX <= (83 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
		{
			r = 128, g = 0, b = 128;
		} //purple
		else if (mouseXX >= (89 - sideLen / 2) && mouseXX <= (89 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
		{
			r = 255, g = 255, b = 255;
		} //white
		else if (mouseXX >= (95 - sideLen / 2) && mouseXX <= (95 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
		{
			r = 0, g = 0, b = 0;
		} //black
		else if (mouseXX >= drawing_areaX1 &&
			mouseXX <= drawing_areaX2 &&
			mouseYY >= drawing_areaY1 &&
			mouseYY <= drawing_areaY2) //drawing area
		{

			if (states == 1) // draw line
			{
				xi = xf = mouseXX;
				yi = yf = mouseYY;
			}

			if (states == 2) // draw point
			{
				xi = xf = mouseXX;
				yi = yf = mouseYY;
			}

			if (states == 3) // draw rect
			{
				xi = xf = mouseXX;
				yi = yf = mouseYY;
			}

			if (states == 4) // draw text
			{
				Tshapes toshape;
				if (txt.size() > 0)
				{
					Text text;
					text.str = txt;
					text.x = xi;
					text.y = yi;
					strings.push_back(text);
					toshape.Tstrings = strings;
                    Tshape.push_back(Tshapes{4, penSh,lines2,rects2,circles2,toshape.Tstrings});
                    strings.clear();
					update_history();
				}
				txt = "";
				xi = xf = mouseXX;
				yi = yf = mouseYY;
				indraw = true;
			}
			if (states == 5) // draw circle
			{
				xi = xf = mouseXX;
				yi = yf = mouseYY;
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (xi < 3) xi = 3;
		if (xi > 97) xi = 97;
		if (yi < 3) yi = 3;
		if (yi > 85) yi = 85;
		if (xf < 3) xf = 3;
		if (xf > 97) xf = 97;
		if (yf < 3) yf = 3;
		if (yf > 85) yf = 85;
        Tshapes toshape;
		if (states == 1 && indraw == true)
		{
			lines.push_back(Line{xi,yi,xf,yf, r,g,b,Psize });
			toshape.Tlines = lines;
			Tshape.push_back(Tshapes{1, penSh,toshape.Tlines,rects2,circles2,strings2 });
            lines.clear();
			update_history();
		}

		if (states == 3 && indraw == true)
		{
			rects.push_back(rect{ filled,xi,xf,yi,yf , r,g,b,Psize});
			toshape.Trects = rects;
			Tshape.push_back(Tshapes{3, penSh,lines2,toshape.Trects,circles2,strings2} );
			rects.clear();
			update_history();
		}
		if (states == 5 && indraw == true)
		{
			circles.push_back(circle{ filled,xi,yi,xf,yf, r,g,b,Psize});
			toshape.Tcircles = circles;
			Tshape.push_back(Tshapes{5, penSh,lines2,rects2,toshape.Tcircles,strings2});
			circles.clear();
			update_history();
		}

		if (states == 2 && indraw == true)
		{
			toshape.TpenSh = dots;
			Tshape.push_back(Tshapes{2, toshape.TpenSh,lines2,rects2,circles2,strings2});
			dots.clear();
			update_history();
		}

		indraw = false;
	}
	glutPostRedisplay();
}

void passiveMouse(int x, int y)
{
	mouseX = x;
	mouseX = 0.5 + 1.0*mouseX*logWidth / phyWidth;
	mouseY = phyHeight - y;
	mouseY = 0.5 + 1.0*mouseY*logHeight / phyHeight;
	glutPostRedisplay();
}

void MMouse(int x, int y)
{
	if (mouseXX >= drawing_areaX1 &&
		mouseXX <= drawing_areaX2 &&
		mouseYY >= drawing_areaY1 &&
		mouseYY <= drawing_areaY2) //drawing area
	{
		mouseXXX = x;
		mouseXXX = 0.5 + 1.0*mouseXXX*logWidth / phyWidth;
		mouseYYY = phyHeight - y;
		mouseYYY = 0.5 + 1.0*mouseYYY*logHeight / phyHeight;
		float xM = mouseXXX;
		float yM = mouseYYY;
		if (xM < 3) xM = 3;
		if (xM > 97) xM = 97;
		if (yM < 3) yM = 3;
		if (yM > 85) yM = 85;
		glutPostRedisplay();

		if (states == 2 && indraw == true)
			dots.push_back(Dot{ xM,yM, r,g,b, Psize });
		if (states == 5) // draw circle
				indraw = true;
        if (states == 3) // draw rect
				indraw = true;
        if (states == 1) // draw line
				indraw = true;
        if (states == 2) // draw point
				indraw = true;
	}
}


void keyboard(unsigned char key, int x, int y)
{
    if(mouseXX >= drawing_areaX1 &&
		mouseXX <= drawing_areaX2 &&
		mouseYY >= drawing_areaY1 &&
		mouseYY <= drawing_areaY2
		&& states == 4){
		if (key > 31 && key < 127 || key == 13) {
			txt.push_back(key);
		}
		else if (key == 8) {

			txt.pop_back();
		}
	}
	glutPostRedisplay();
}


void draw_ui()
{
	glLineWidth(2.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0 + offset, 0 + offset);
	glVertex2f(0 + offset, logHeight - offset);
	glVertex2f(logWidth - offset, logHeight - offset);
	glVertex2f(logWidth - offset, 0 + offset);
	glEnd();

	// drawing area
	drawing_areaX1 = 0 + offset1;
	drawing_areaY1 = 0 + offset1;
	drawing_areaX2 = logWidth - offset1;
	drawing_areaY2 = logHeight - offset2;


	glBegin(GL_LINE_LOOP);
	glVertex2f(drawing_areaX1, drawing_areaY1);
	glVertex2f(0 + offset1, logHeight - offset2);
	glVertex2f(drawing_areaX2, drawing_areaY2);
	glVertex2f(logWidth - offset1, 0 + offset1);
	glEnd();


	drawPalette(3, 7, 3, 12);
	printStr((char*)"Line", 5, 94);
	drawPalette(3, 12, 8, 12);
	printStr((char*)"Pen", 5, 89);
	drawPalette(14, 7, 3, 23);
	printStr((char*)"Rect", (5 + 10.5), 94);
	drawPalette(14, 12, 8, 23);
	printStr((char*)"Text", (5 + 10.5), 89);
	drawPalette(25, 7, 3, 34);
	printStr((char*)"Circle", (5 + 11 + 10.25), 94);
	drawPalette(25, 12, 8, 34);
	printStr((char*)"Undo", (5 + 11 + 10.5), 89);
	drawPalette(36, 7, 3, 45);
	printStr((char*)"Fill", (5 + 11 + 11 + 11), 94);
	drawPalette(36, 12, 8, 45);
	printStr((char*)"No Fill", (5 + 11 + 11 + 9.5), 89);

	glLineWidth(3.0);
	glColor3f(1.0, 0.0, 0.0);
	drawCenter(53, 93);
	if (mouseXX >= (53 - sideLen / 2) && mouseXX <= (53 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
	{
		r = 255, g = 0.0, b = 0.0;
	} //red
	glColor3f(0.0, 1.0, 0.0);
	drawCenter(55 + 4, 93);
	if (mouseXX >= (59 - sideLen / 2) && mouseXX <= (59 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
	{
		r = 0.0, g = 255, b = 0.0;
	} //green
	glColor3f(0.0, 0.0, 1.0);
	drawCenter(55 + 10, 93);
	if (mouseXX >= (65 - sideLen / 2) && mouseXX <= (65 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
	{
		r = 0.0, g = 0.0, b = 255;
	} //blue
	glColor3ub(255, 255, 0);
	drawCenter(55 + 16, 93);
	if (mouseXX >= (71 - sideLen / 2) && mouseXX <= (71 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
	{
		r = 255, g = 255, b = 0.0;
	} //yellow
	glColor3ub(255, 165, 0);
	drawCenter(55 + 22, 93);
	if (mouseXX >= (77 - sideLen / 2) && mouseXX <= (77 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
	{
		r = 255, g = 165, b = 0.0;
	} //orange
	glColor3ub(128, 0, 128);
	drawCenter(55 + 28, 93);
	if (mouseXX >= (83 - sideLen / 2) && mouseXX <= (83 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
	{
		r = 128, g = 0, b = 128;
	} //purple
	glColor3f(1.0, 1.0, 1.0);
	drawCenter(55 + 34, 93);
	if (mouseXX >= (89 - sideLen / 2) && mouseXX <= (89 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
	{
		r = 255, g = 255, b = 255;
	} //white
	glColor3f(0.0, 0.0, 0.0);
	drawCenter(55 + 40, 93);
	if (mouseXX >= (95 - sideLen / 2) && mouseXX <= (95 + sideLen / 2) && mouseYY >= (93 - sideLen / 2) && mouseYY <= (93 + sideLen / 2))
	{
		r = 0, g = 0, b = 0;
	} //black
    glLineWidth(2.0);
	drawPalette(50.99, 9.1, 5, 55.1); //red
	drawPalette(56.99, 9.1, 5, 61.1);//green
	drawPalette(62.99, 9.1, 5, 67.1); //blue
	drawPalette(68.99, 9.1, 5, 73.1); //yellow
	drawPalette(74.99, 9.1, 5, 79.1); //orange
	drawPalette(80.99, 9.1, 5, 85.1); //purple
	drawPalette(86.99, 9.1, 5, 91.1); //white
	drawPalette(92.99, 9.1, 5, 97.1); //black

}


void CheckButton()
{
	if (mouseX >= 3 && mouseX <= 12 && mouseY >= 93 && mouseY <= 97) { // Line
		drawColoredButton(7.5, 95, 238,232,170);
	}

	if (mouseX >= 3 && mouseX <= 12 && mouseY >= 88 && mouseY <= 92) { //Pen
		drawColoredButton(7.5, 90, 238,232,170);
	}

	if (mouseX >= 14 && mouseX <= 23 && mouseY >= 93 && mouseY <= 97) { // Rect
		drawColoredButton(18.5, 95, 238,232,170);
	}

	if (mouseX >= 14 && mouseX <= 23 && mouseY >= 88 && mouseY <= 92) { //Text
		drawColoredButton(18.5, 90, 238,232,170);
	}

	if (mouseX >= 25 && mouseX <= 34 && mouseY >= 93 && mouseY <= 97) { //Circle
		drawColoredButton(29.5, 95, 238,232,170);
	}

	if (mouseX >= 25 && mouseX <= 34 && mouseY >= 88 && mouseY <= 92) { // Undo
		drawColoredButton(29.5, 90, 238,232,170);
	}

	if (mouseX >= 36 && mouseX <= 45 && mouseY >= 93 && mouseY <= 97) { // Fill
		drawColoredButton(40.5, 95, 238,232,170);
	}

	if (mouseX >= 36 && mouseX <= 45 && mouseY >= 88 && mouseY <= 92) { // No Fill
		drawColoredButton(40.5, 90, 238,232,170);
	}


	if (states == 1) { // Line
		drawColoredButton(7.5, 95, 189, 183, 107);
		if (filled == 1 && ClickFilled%2==1 )
			drawColoredButton(40.5, 95, 189, 183, 107);
		if (filled == 0 || ClickFilled%2==0)
			drawColoredButton(40.5, 90, 189, 183, 107);
	}

	if (states == 2) { //Pen
		drawColoredButton(7.5, 90, 189, 183, 107);
		if (filled == 1 && ClickFilled%2==1 )
			drawColoredButton(40.5, 95, 189, 183, 107);
		if (filled == 0 || ClickFilled%2==0)
			drawColoredButton(40.5, 90, 189, 183, 107);
	}

	if (states == 3) { // Rect
		drawColoredButton(18.5, 95, 189, 183, 107);
		if (filled == 1 && ClickFilled%2==1 )
			drawColoredButton(40.5, 95, 189, 183, 107);
		if (filled == 0 || ClickFilled%2==0)
			drawColoredButton(40.5, 90, 189, 183, 107);
	}

	if (states == 4) { //Text
		drawColoredButton(18.5, 90, 189, 183, 107);
		if (filled == 1 && ClickFilled%2==1 )
			drawColoredButton(40.5, 95, 189, 183, 107);
		if (filled == 0 || ClickFilled%2==0)
			drawColoredButton(40.5, 90, 189, 183, 107);
	}

	if (states == 5) { //Circle
		drawColoredButton(29.5, 95, 189, 183, 107);
		if (filled == 1 && ClickFilled%2==1 )
			drawColoredButton(40.5, 95, 189, 183, 107);
		if (filled == 0 || ClickFilled%2==0)
			drawColoredButton(40.5, 90, 189, 183, 107);
	}

	if (states == 6) { // Undo
		drawColoredButton(29.5, 90, 189, 183, 107);
		if (filled == 1 && ClickFilled%2==1 )
			drawColoredButton(40.5, 95, 189, 183, 107);
		if (filled == 0 || ClickFilled%2==0)
			drawColoredButton(40.5, 90, 189, 183, 107);
	}

	if (states == 7) { // Fill
            if (filled == 0 || ClickFilled%2==0)
            {drawColoredButton(40.5, 95, 255, 255, 255);
            drawColoredButton(40.5, 90, 189, 183, 107);}
            else drawColoredButton(40.5, 95, 189, 183, 107);
	}

	if (states == 8) { // No Fill
		drawColoredButton(40.5, 90, 189, 183, 107);
	}

}


void drawelemnts()
{ Tshapes Toshape;
for (int t = 0; t < Tshape.size(); ++t){
     Toshape = Tshape[t];
	// draw lines
if(Toshape.ID== 1){
	for (int i = 0; i < Toshape.Tlines.size(); ++i)
	{   glLineWidth(Toshape.Tlines[i].Pixsize);
		glColor3ub(Toshape.Tlines[i].r, Toshape.Tlines[i].g, Toshape.Tlines[i].b);
		drawLine(Toshape.Tlines[i].x, Toshape.Tlines[i].y, Toshape.Tlines[i].x2, Toshape.Tlines[i].y2);
	}
}
	// draw rects
if(Toshape.ID== 3){
	for (int i = 0; i < Toshape.Trects.size(); ++i)
	{
		glColor3ub(Toshape.Trects[i].r, Toshape.Trects[i].g, Toshape.Trects[i].b);
		if (Toshape.Trects[i].fill == 1)
		{
		    glLineWidth(Toshape.Trects[i].Pixsize);
			drawFilledRect(Toshape.Trects[i].xi, Toshape.Trects[i].xf, Toshape.Trects[i].yi, Toshape.Trects[i].yf);
		}
		else if (Toshape.Trects[i].fill == 0)
		{
		    glLineWidth(Toshape.Trects[i].Pixsize);
			drawRect(Toshape.Trects[i].xi, Toshape.Trects[i].xf, Toshape.Trects[i].yi, Toshape.Trects[i].yf);
		}
	}
}

if(Toshape.ID== 5){
	// draw circles
	for (int i = 0; i < Toshape.Tcircles.size(); ++i)
	{
		glColor3ub(Toshape.Tcircles[i].r, Toshape.Tcircles[i].g, Toshape.Tcircles[i].b);
		if (Toshape.Tcircles[i].fill == 1)
		{
		    glLineWidth(Toshape.Tcircles[i].Pointsize+1);
			drawFilledCircle(Toshape.Tcircles[i].xi, Toshape.Tcircles[i].xf, Toshape.Tcircles[i].yi, Toshape.Tcircles[i].yf);
		}
		else if (Toshape.Tcircles[i].fill == 0)
		{   glLineWidth(Toshape.Tcircles[i].Pointsize+1);
			drawCircle(Toshape.Tcircles[i].xi, Toshape.Tcircles[i].xf, Toshape.Tcircles[i].yi, Toshape.Tcircles[i].yf);
		}
	}}
if(Toshape.ID== 4){
	// draw text
	for (int i = 0; i < Toshape.Tstrings.size(); ++i)
	{
		printStr(Toshape.Tstrings[i].str, Toshape.Tstrings[i].x, Toshape.Tstrings[i].y);
	}}

if(Toshape.ID== 2){
	// draw pen
	for (int i = 0; i < Toshape.TpenSh.size(); ++i)
	{
            glPointSize(Toshape.TpenSh[i].Pointsize+1);
            glColor3ub(Toshape.TpenSh[i].r, Toshape.TpenSh[i].g, Toshape.TpenSh[i].b);
            drawPoint(Toshape.TpenSh[i].x, Toshape.TpenSh[i].y);
	}}
}
// draw Points
    for (int i = 0; i < dots.size(); ++i)
	{
	    glPointSize(dots[i].Pointsize+1);
		glColor3ub(dots[i].r, dots[i].g, dots[i].b);
		drawPoint(dots[i].x, dots[i].y);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	CheckButton();
	draw_ui();

	xf = mouseXXX;
	yf = mouseYYY;
	if (xf < 3) xf = 3;
	if (xf > 97) xf = 97;
	if (yf < 3) yf = 3;
	if (yf > 85) yf = 85;

	drawelemnts();

if (mouseX >= drawing_areaX1 &&
		mouseX <= drawing_areaX2 &&
		mouseY >= drawing_areaY1 &&
		mouseY <= drawing_areaY2
		&& states == 4){
	glPointSize(3);
	glColor3ub(0, 0, 0);
	glBegin(GL_POINTS);
	glVertex2f(mouseX, mouseY);
	glEnd();}
	glColor3ub(r, g, b);
	if (states == 1 && indraw) {
        glLineWidth(Psize);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xi, yi);
		glVertex2f(xf, yf);
		glEnd();
	}

	else if (states == 3 && filled == 1 && indraw) {
        glLineWidth(Psize);
		drawFilledRect(xi, xf, yi, yf);
	}
	else if (states == 3 && filled == 0 && indraw) {
	    glLineWidth(Psize);
		drawRect(xi, xf, yi, yf);
	}
	else if (states == 4) {
		printStr(txt, xi, yi);
	}
	else if (states == 5 && filled == 1 && indraw) {
	    glLineWidth(Psize+1);
		drawFilledCircle(xi, yi, xf, yf);
	}
	else if (states == 5 && filled == 0 && indraw) {
	    glLineWidth(Psize+1);
		drawCircle(xi, yi, xf, yf);
	}

	glutSwapBuffers();
	glFlush();
}
void GoMenu(int value)
{
    switch(value)
    {
    case 1:
        Psize =1;
        break;
    case 2:
        Psize =2;
        break;
    case 3:
        Psize =3;
        break;
    case 4:
        Psize =4;
        break;
    case 5:
        Psize =5;
        break;
    case 6:
        exit(0);
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(phyWidth, phyHeight);
	glutInitWindowPosition(logWidth+300, logHeight);
	glutCreateWindow("Paint");
	init2D(1.0, 1.0, 1.0);
	glutPassiveMotionFunc(passiveMouse);
	glutMouseFunc(mouseClick);
	glutMotionFunc(MMouse);
	glutKeyboardFunc(keyboard);
	int sub1 = glutCreateMenu(GoMenu);
	glutAddMenuEntry(" 1", 1);
	glutAddMenuEntry(" 2", 2);
	glutAddMenuEntry(" 3", 3);
	glutAddMenuEntry(" 4", 4);
	glutAddMenuEntry(" 5", 5);
	glutCreateMenu(GoMenu);
	glutAddSubMenu("Pixel size", sub1);
	glutAddMenuEntry("Close", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glutMainLoop();
}
