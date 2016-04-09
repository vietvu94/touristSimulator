#ifndef __VTSCREEN_H   //prevent multiple compilers. 
#define __VTSCREEN_H

enum COLORS{BLACK=30,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE}; // Declare an enumerated type  
#define bg(a) a+10

//Function prototype 
void setcolor(short,short);
void resetcolor(void);
void clearscreen(void);
void gotoxy(short,short);
void colorstring (char *, short, short);
void defineScroll(short,short);
void restoreScroll(void);

#endif

