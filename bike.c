#include <stdio.h>
#include "vtscreen.h"
#include "main.h"

//Function to give initial data for bikes
void bike_initialize (BIKE bike[], int j) {
	int i=0;
	for ( i=0; i <= j; i++){
		bike[i].bike_state = FREE; 
		bike[i].x = 11; 
		bike[i].y = 10;
		bike[i].v = 0;
		bike[i].t = 0;
	 }
}

//Function to count the number of bike free
int count_free_bike(BIKE bike[], int a){
	int i;
	int free_bike = 0;
	for(i = 0; i < a; i++){
		if (bike[i].bike_state == FREE){
			free_bike++;
		}
	}
	return free_bike;
}

//Function to detect all bikes are busy 
int all_bikes_are_busy(BIKE bike[], int a){
	int j;
	for ( j=0; j < a; j++){
		if(bike[j].bike_state != FREE)
	return 0;
	}
	return 1;
}

//Function to count the number of idle bike
int count_idle_bike(BIKE bike[], int a){
	int i;
	int idle_bike = 0;
	for(i = 0; i < a; i++){
		if (bike[i].bike_state == IDLE){
			idle_bike++;
		}
	}
	return idle_bike;
}

