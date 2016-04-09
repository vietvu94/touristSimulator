
#include <stdio.h>
#include "vtscreen.h"

//Function to enable scrolling from row start to row end
void definescroll(short start, short end){
	if(start > 0 && end > start){
		printf("\033[%d;%dr",start,end);
		fflush (stdout);
	}//end function
}

//Function to enble scrolling for entire display 
void restorescroll (void){
	printf("\033[r");
	fflush(stdout);
}//end function

//Function to change the colors of the foreground and background
void setcolor (short fg, short bg){
	printf ("\033[%d;%d;1m", fg, bg);
	fflush(stdout);
}//end function

// Function to clear the screen.
void clearscreen(void){
	printf("\033[2J");
	fflush(stdout);
}//end function

// Function to move the cursor to row y, column z.
void gotoxy(short x,short y){
	printf ("\033[%d;%dH",y,x);
	fflush(stdout);
}//end function

//Function to change the color of the given text
void colorstring (char *s, short fg, short bg){
	setcolor(fg,bg);
	printf("%s", s);
	resetcolor();
}//end function

// Function to reset colour formatting
void resetcolor(void){
	printf("\033[0m");
	fflush(stdout);
}//end function

