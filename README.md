# touristSimulator
CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Installation
 * Descriptions
 * Troubleshooting
 * FAQ
 * Authors


INTRODUCTION
------------
 * The software show the simulations of a resort passage on which tourist can hire bikes 
to pass through. 

 * The software runs in a minute resolution. Each minute something will happen. 

 * When a day passes (1440 mins), the simulations will end and it will show the average 
waiting of all the tourists. 

 * To submit bug reports or feature suggestions, please send me an email: 
   	kamilight94@gmail.com



REQUIREMENTS
------------
This software requires the following things to run :
 * A terminal emulator applicatior, for example, PuTTY.

INSTALLATION
------------
 * If you don't have PuTTY simply download and install with this link: 
	http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html

 * Extract projectTourist.tar file by command: $tar -xvf projectTourist.tar

 * Use make utility to create main file: $make

 * Run the program by entering command: $./main


DESCRIPTIONS
------------

The project.tar includes these files: 
 * main.c	: includes main(), movetruck(), animation ();
	          
 * main.h	: define typedef BIKE, TRUCK and TOURIST and includes all function prototype of main.c 
		  and bike.c

 * vtscreen.h	: define COLORS and includes all function prototype of vtscreen.c 

 * vtscreen.c	: includes all functions related to screen display.
	definescroll()	: define the scroll
	restorescroll()	: restore the scroll
	setcolor()	: background and forground color changing
	clearscreen ()	: clear the screen
	gotoxy ()	: move the cursor
	colorstring ()	: text color changing
	resetcolor ()	: reset color fommatting

 * bike.c	: includes bike_initialize (),  count_free_bike(), all_bikes_are_busy(), count_idle_bike().


 * makefile	: make utility
	using $ make command will create .o files and main.
	using $ make clean command will delete all .o files and main.

TROUBLESHOOTING
---------------


   To display the full simulation and have the best experience, please: 

 * Maximize your PuTTY window
 * Right click mouse at the taskbar of PuTTY. Choose change settings then 
   click Translation, change the Remote character set into UTF-8. 


   The display of the time remaining of the bikes to come to the end of 
the passage, sometimes has error of 1 minute (only when display), which mean
even if it display 0 it still have to move 1 more time to go to finish lines. 
This happens because the gotoxy() function can only go to interger points.   


FAQ
---


Q: Why whenever I compile by using make, I have some warning: universal character names
   are only valid in C++ and C99 ? How can I fix it ? 


A: It's fine if you have that warning. Everything is still run normally. This happens 
   simply bacause I used many Unicode Character to display the simulation.

Q: Why sometimes the time display of the bikes is not correctly (has 1 minute error)?

A: The function gotoxy() can only move the scroll into interger points and the velocity
of the bikes can have values which is not an interget. This makes the coordinate of the 
bikes has to round to a number. 


AUTHORS 
-------

 - Student: Viet Vu 
 - Supervisor: Dr. Gao Chao 
 - Advanced Project of Application Development course in Vaasan Ammattikrokeakoulu. 





