/*** GRAPHIC LIBRARY ***/

/// .H ///

#ifndef GRAPHICD2_H_INCLUDED
#define GRAPHICD2_H_INCLUDED

#ifndef CONIO_H_INCLUDED
#define CONIO_H_INCLUDED

#include <conio.h>

#endif // CONIO_H_INCLUDED

#ifndef WINDOWS_H_INCLUDED
#define WINDOWS_H_INCLUDED

#include <windows.h>

#endif // WINDOWS_H_INCLUDED
void color (short val) { // FOR SETTING CONSOLE OUTPUT COLORS
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),val);
}

namespace grph // GRAPHIC LIBRARY NAMESPACE
{
    class Grid;
    class Point;
    class Entity;
    class Pixel;
    class Console;
	const short ESC = 27;
	const short F1=59,F2=60,F3=61,F4=62,F5=63,F6=64,F7=65,F8=66,F9=67,F10=68,F11=-123,F12=-122,ENTER=13;
	const short LEFT_ARROW=75,UP_ARROW=72,RIGHT_ARROW=77,DOWN_ARROW=80;

}

class grph::Point { // CLASS "POINT"
protected:
    short x,y;
public:
    Point (short x_,short y_); // CONSTRUCTOR

	void set(short x_,short y_);

    short getX(); // GET X FUNCTION
    short getY(); // GET Y FUNCTION

    void incrsX(short n);
    void incrsY(short n);

    void decrsX(short n);
    void decrsY(short n);
};

class grph::Entity : public grph::Point { // CLASS "ENTITY"
private:
    short color;
    char txt,facing;
public:
    Entity (short x,short y,short color,char txt,char facing);

    short getColor();
    char  getTxt();
    char  getFacing();

    void  setColor(short color);
    void  setTxt(char txt);
    void  setFacing(char facing);
};

class grph::Pixel { // CLASS "PIXEL"
private:
    short x,y,color;
    char txt;
public:
    Pixel (); // CONSTRUCTOR

    void  setX(short x_);         // SET X     FUNCTION
    void  setY(short y_);         // SET Y     FUNCTION
    void  setColor(short color_); // SET COLOR FUNCTION
    void  setTxt(char txt_);      // SET TEXT  FUNCTION

    short getX();     // GET X     FUNCTION
    short getY();     // GET Y     FUNCTION
    short getColor(); // GET COLOR FUNCTION
    char  getTxt();   // GET TEXT  FUNCTION
};

class grph::Grid { // CLASS "GRID"
private:
    grph::Pixel pixels[100][100];
    short x,y;
public:
    Grid (short x_,short y_); // CONSTRUCTOR

    void  setX(short x_);         // SET X     FUNCTION
    void  setY(short y_);         // SET Y     FUNCTION

    short getX();     // GET X     FUNCTION
    short getY();     // GET Y     FUNCTION

	short getPxlClr(short x_,short y_); // GET PIXEL'S COLOR FUNCTION
	char  getPxlTxt(short x_,short y_); // GET PIXEL'S TEXT  FUNCTION

    void setup(short color_,char txt_); // PIXELS SETUP FUNCTION
    void paint();                       // GRID PAINT   FUNCTION

    void drawpxl(grph::Point p,short color_,char txt_);                // POINT DRAWING  FUNCTION
	void fill(grph::Point p1,grph::Point p2,short color_,char txt_);   // FILLING        FUNCTION

    void xLine(short y_,short x1,short x2,short color_,char txt_);     // X-LINE DRAWING FUNCTION
    void yLine(short x_,short y1,short y2,short color_,char txt_);     // Y-LINE DRAWING FUNCTION
    //void line(grph::Point p1,grph::Point p2);
    void square(grph::Point p1,grph::Point p2,short color_,char txt_); // SQUARE DRAWING FUNCTION

};

class grph::Console { // CLASS "CONSOLE"
public:
    Console ();      // CONSTRUCTOR

    void pause();    // WAIT FOR KEY PRESSING FUNCTION
    void cls();      // CLEAR CONSOLE         FUNCTION
    void close();    // CLOSE CONSOLE         FUNCTION
	char getKey();   // KEY INPUT             FUNCTION
};

/// .CPP ///

//////////////////////////////////////////////////////////
//                    CLASS "POINT"                     //
//////////////////////////////////////////////////////////
grph::Point::Point (short x_,short y_) { // CONSTRUCTOR
    x=x_;
    y=y_;
}

void grph::Point::set (short x_,short y_) {   // SETTING-UP POINT FUNCTION
	x=x_;
	y=y_;
}

short grph::Point::getX () {return x;} // GET X FUNCTION
short grph::Point::getY () {return y;} // GET Y FUNCTION

void grph::Point::incrsX (short n) {x+=n;} // X INCREMENTING FUNCTION
void grph::Point::incrsY (short n) {y+=n;} // Y INCREMENTING FUNCTION

void grph::Point::decrsX (short n) {x-=n;} // X DECREMENTING FUNCTION
void grph::Point::decrsY (short n) {y-=n;} // Y DECREMENTING FUNCTION

//////////////////////////////////////////////////////////
//                    CLASS "ENTITY"                    //
//////////////////////////////////////////////////////////

grph::Entity::Entity (short x,short y,short color,char txt,char facing):grph::Point::Point(x,y) {
    this->x=x;
    this->y=y;
    this->color=color;
    this->txt=txt;
    this->facing=facing;
}

short grph::Entity::getColor () {
    return color;
}
char grph::Entity::getTxt () {
    return txt;
}
char grph::Entity::getFacing () {
    return facing;
}

void grph::Entity::setColor (short color) {
    this->color=color;
}
void grph::Entity::setTxt (char txt) {
    this->txt=txt;
}
void grph::Entity::setFacing (char facing) {
    this->facing=facing;
}
//////////////////////////////////////////////////////////
//                   CLASS "PIXEL"                      //
//////////////////////////////////////////////////////////
grph::Pixel::Pixel () {} // CONSTRUCTOR

void grph::Pixel::setX (short x_) {x = x_;}                 // SET X     FUNCTION
void grph::Pixel::setY (short y_) {y = y_;}                 // SET Y     FUNCTION
void grph::Pixel::setColor (short color_) {color = color_;} // SET COLOR FUNCTION
void grph::Pixel::setTxt (char txt_) {txt = txt_;}          // SET TEXT  FUNCTION

short grph::Pixel::getX () {return x;}         // GET X     FUNCTION
short grph::Pixel::getY () {return y;}         // GET Y     FUNCTION
short grph::Pixel::getColor () {return color;} // GET COLOR FUNCTION
char  grph::Pixel::getTxt () {return txt;}     // GET TEXT  FUNCTION

//////////////////////////////////////////////////////////
//                     CLASS "GRID"                     //
//////////////////////////////////////////////////////////
grph::Grid::Grid (short x_,short y_) { // CONSTRUCTOR
    x=x_;
    y=y_;
}

void grph::Grid::setX (short x_) {x = x_;}    // SET X FUNCTION
void grph::Grid::setY (short y_) {y = y_;}    // SET Y FUNCTION

short grph::Grid::getX () {return x;}         // GET X FUNCTION
short grph::Grid::getY () {return y;}         // GET Y FUNCTION

short grph::Grid::getPxlClr(short x_,short y_) { // GET PIXEL'S COLOR FUNCTION
	return pixels[x_][y_].getColor();
}
char grph::Grid::getPxlTxt(short x_,short y_) { // GET PIXEL'S TEXT  FUNCTION
	return pixels[x_][y_].getTxt();
}
void grph::Grid::setup (short color_,char txt_) { // SETTING-UP FUNCTION
    short i=0,j=0;
    for(j;j<y;j++)
    {
        for(i;i<x;i++)
        {
            pixels[i][j].setColor(color_);
            pixels[i][j].setTxt(txt_);
        }
        i=0;
    }
}
void grph::Grid::paint () { // PAINTING FUNCTION
    short i=0,j=0;
    for(j;j<y;j++)
    {
        for(i;i<x;i++)
        {
            color(pixels[i][j].getColor());
            std::cout<<pixels[i][j].getTxt();
        }
        std::cout<<std::endl;
        i=0;
    }
}
void grph::Grid::drawpxl(grph::Point p,short color_,char txt_) { // POINT DRAWING FUNCTION
    pixels[p.getX()][p.getY()].setColor(color_);
    pixels[p.getX()][p.getY()].setTxt(txt_);
}
void grph::Grid::fill(grph::Point p1,grph::Point p2,short color_,char txt_) { // FILLING FUNCTION
	short x1=p1.getX();
	short x2=p2.getX();
	short y1=p1.getY();
	short y2=p2.getY();
	short i=x1,j=y1;
	for(j;j<y2;j++)
	{
		for(i;i<x2;i++)
		{
			pixels[i][j].setColor(color_);
			pixels[i][j].setTxt(txt_);
		}
		i=x1;
	}
}
void grph::Grid::xLine(short y_,short x1,short x2,short color_,char txt_) {     // X-LINE DRAWING FUNCTION
    x2++;
    for(short i=x1;i<x2;i++)
    {
        pixels[i][y_].setColor(color_);
        pixels[i][y_].setTxt(txt_);
    }
}
void grph::Grid::yLine(short x_,short y1,short y2,short color_,char txt_) {     // Y-LINE DRAWING FUNCTION
    y2++;
    for(short i=y1;i<y2;i++)
    {
        pixels[x_][i].setColor(color_);
        pixels[x_][i].setTxt(txt_);
    }
}
void grph::Grid::square(grph::Point p1,grph::Point p2,short color_,char txt_) { // SQUARE DRAWING FUNCTION
    short x1=p1.getX();
    short x2=p2.getX();
    short y1=p1.getY();
    short y2=p2.getY();
    xLine(y1,x1,x2,color_,txt_);
    yLine(x1,y1,y2,color_,txt_);
    xLine(y2,x1,x2,color_,txt_);
    yLine(x2,y1,y2,color_,txt_);
}

//////////////////////////////////////////////////////////
//                   CLASS "CONSOLE"                   //
//////////////////////////////////////////////////////////
grph::Console::Console () {}    // CONSTRUCTOR

void grph::Console::pause () {  // WAIT FOR KEY PRESSING FUNCTION
    getch();
}
void grph::Console::cls () {    // CLEAR CONSOLE
    system("cls");
}
void grph::Console::close () {  // CLOSE CONSOLE
    exit(0);
}
char grph::Console::getKey () {
	return getch();
}

#endif // GRAPHICD2_H_INCLUDED

