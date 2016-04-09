#ifndef __MAIN_H   //prevent multiple compilers. 
#define __MAIN_H
#define BLOCK "\u2551"
#define ROAD "\u2500"
#define TRUCK1 "\u2554"
#define TRUCK2 "\u2550"
#define TRUCK3 "\u2557"
#define TRUCK4 "\u255A"
#define TRUCK5 "\u255D"
#define RUNNINGBIKE "\u2551"
#define RETURNING 3
#define RUNNING 2
#define FREE 1
#define IDLE 0 
#define WAITING 1
#define GO 0
#define TIME 1440 //1 day 

typedef struct{
	unsigned int bike_state;
	unsigned int x; //horizontal coordinate
	unsigned int y; //vertical coordinate
	double v; 
	unsigned int t;
}BIKE;

typedef struct{
	unsigned int truck_state;
	unsigned int truck_x; //horizontal coordinate
	double truck_v; 
}TRUCK;

typedef struct{
	unsigned int status;
	unsigned int waiting_time ; //horizontal coordinate
}TOURIST;


//Function prototype 
void movetruck(); 
void animation(void);
unsigned int sleep (unsigned int seconds);
void bike_initialize (BIKE bike[], int j);
int count_free_bike(BIKE bike[], int a);
int count_idle_bike(BIKE bike[], int a);
int all_bikes_are_busy(BIKE bike[], int a);

#endif
