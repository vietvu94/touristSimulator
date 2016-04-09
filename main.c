#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "vtscreen.h"
#include "main.h"

#define SIZE 10  
#define TOURIST_NUMBER 4320  // max number of tourist in 1 day 

unsigned int i=0, p1, p2, bike_available;
unsigned int waiting_number=0;  //number of tourists who are waiting
unsigned int number_of_tourist=0, total_time=0 ;
unsigned int limit_time=0; 

double average_time=0;

TRUCK truck = {FREE,61,0};
BIKE bike[SIZE]; //declare an array of 10 bikes
TOURIST tourist[TOURIST_NUMBER]; //declare an array of 4320 tourists
size_t j,k,g; //array counter


//function main begins program execution 
void main (){
	unsigned int bike_finish;
	bike_initialize (bike,SIZE);
	
	while (1){
		clearscreen();
		srand(time(NULL));
		
		//40% chance 1-3 tourists come
		p1=1+rand()%10;
		if (p1 <= 4) {
			p2 = 1+ rand()% 3; 
		}
		else p2=0;
		
		// The tourist coming will all
		// have status waiting and waiting time is 0 first
		
		for(i = number_of_tourist+1; i <= number_of_tourist + p2; i++){
			tourist[i].status = WAITING;
			tourist[i].waiting_time = 0;
		}

		number_of_tourist += p2;
		waiting_number += p2;
		
		animation(); //display the resort passage
		
		
		
		// the waiting tourist becomes riding_tourist if bikes are free
		if(count_free_bike(bike, SIZE)>0 && waiting_number>0){
			for(i = 0; i < number_of_tourist; i++){
				int riding_tourist = 0;
				if(tourist[i].status == WAITING){
					tourist[i].status = GO;
					riding_tourist++;
				}
				if(riding_tourist == count_free_bike(bike, SIZE))
					break;
			}
		}		 
		
		for ( j=0; j < SIZE; j++){
			//Bikes with state FREE
			if (bike[j].bike_state == FREE){
					bike[j].x = 11;
					bike[j].y = 16;
					bike[j].v = 0;
			}
			
			// Change the state of bike when there are 
			// tourist waiting and bikes are available
			if (waiting_number > 0 && bike[j].bike_state == FREE){
				bike[j].bike_state = RUNNING;	
				bike[j].v = (int) 55/(10+rand()%11);
				bike[j].t = (int) ceil(55/bike[j].v);
				waiting_number -= 1;	
			}
		
		}
		//Make all bikes moving 
		for ( j=0; j < SIZE; j++){
			if (bike[j].bike_state == RUNNING){
				bike[j].x += bike[j].v;
			}
		}
		
		// If any bike has the same position, one will move up
		for ( g=0; g < SIZE-1; g++){
			for (k=g+1; k < SIZE; k++){
				if (bike[g].x == bike[k].x && bike[g].x != 11 && bike[g].x != 67)
					bike[k].y = bike[k].y - 2;
			}
		}	
		
		for ( j=0; j < SIZE; j++){
			//print the all bikes running
			if (bike[j].bike_state == RUNNING){
				if (bike[j].x < 67){
					gotoxy(bike[j].x, bike[j].y);
					printf("%s\n", RUNNINGBIKE);
					gotoxy(bike[j].x, bike[j].y - 1);
					bike[j].t -= 1;
					printf("%d\n", bike[j].t);
				}
				else{ 
					bike[j].bike_state = IDLE;
				}	
				bike[j].y = 16;	
			}
		
			//Bikes at the end of the passage 
			if (bike[j].bike_state == IDLE){
				bike[j].x = 67;
				bike[j].y = 16;
				bike[j].v = 0;
			}
			
			// Bikes in the truck on the way to the start 
			if (bike[j].bike_state == RETURNING){
				bike[j].x = truck.truck_x;
				bike[j].v = truck.truck_v;
			}
			
			
			
			// Waiting time of tourist who already waiting 
			// when still no bike available will increase
			if(all_bikes_are_busy(bike, SIZE)){
				for(i = 0; i < number_of_tourist; i++){
					if(tourist[i].status == WAITING){
						tourist[i].waiting_time++;
					}
				}
			}
		}
			
		// When the number of idle bike is enough 
		if (count_idle_bike(bike, SIZE)>=8){
			int count = 0; 
			for ( j=0; j < SIZE; j++){
				if(bike[j].bike_state == IDLE){
					bike[j].bike_state = RETURNING;
					count += 1;
					if (count == 8) break;				
				}
			}
			truck.truck_state = RUNNING;
		}
		movetruck();
		
		//Calculate the total that tourists have to wait 
		for(i = 0; i < number_of_tourist; i++){
                total_time += tourist[i].waiting_time;
        }
		
		// Number of people waiting.
		gotoxy(5,16);
		printf ("W:%d\n", waiting_number);
	
		// Count the time the simulation has run 
		// The simulation goes off when it run a day (24h)
		limit_time +=1;
		if (limit_time == TIME) break;
		sleep(3); // The simulation runs in a time resolution of a minute
		
	}	
	
	
	
	clearscreen();
	//The average time tourists have to wait
	if (number_of_tourist !=0){
		average_time = total_time/number_of_tourist; 
		printf("The average time the tourists have to wait is: %f\n",average_time);
	}
	else printf ("No one came to your resort passage. Please renovate it first \n");
	
	
} //end main  


//Function for the moving truck
void movetruck(){
	//Enough bikes at the end. The truck is starting going back the start
	if (truck.truck_state == RUNNING ){
		if (truck.truck_x == 11)
			truck.truck_state = IDLE;
		truck.truck_v = 10;
		truck.truck_x -= truck.truck_v;
		
	} 
	
	// The truck on the back to the ending to wait for bikes
	if (truck.truck_state == RETURNING ){
		truck.truck_v = 10;
		truck.truck_x += truck.truck_v;
		if (truck.truck_x == 61)
			truck.truck_state = FREE;
	} 
	
	//The truck is unloading
	if (truck.truck_state == IDLE ){
		truck.truck_state = RETURNING;
		truck.truck_v = 0;
		truck.truck_x = 11;
		for (j=0; j<SIZE; j++){
			if(bike[j].bike_state == RETURNING){
				bike[j].bike_state = FREE;
				bike[j].x=11;
				bike[j].v=0;
			}
		}
	} 
	
	gotoxy(truck.truck_x,18);
	printf("%s",TRUCK1);
	printf("%s",TRUCK2);
	printf("%s",TRUCK2);
	printf("%s",TRUCK2);
	printf("%s",TRUCK2);
	printf("%s",TRUCK3);
	
	
	//The truck is waiting for enough bikes at the end
	if (truck.truck_state == FREE){
		gotoxy(truck.truck_x-1,20);
		printf("WAITING");
	}
	
	//The truck on the way to starting point
	if (truck.truck_state == RUNNING){
		if (truck.truck_x!=11 && truck.truck_x!=61){
			gotoxy(truck.truck_x+2,20);
			printf("%d",(truck.truck_x-11)/10);
		}
		if (truck.truck_x==11){
			gotoxy(9,20);
			printf("Unloading..");
		}
	}
	
	// The truck on the way to waiting-for-bike point
	if (truck.truck_state == RETURNING){
		gotoxy(truck.truck_x+2,20);
		printf("%d",(61-truck.truck_x)/10);
	}
	gotoxy(truck.truck_x,19);
	printf("%s",TRUCK4);
	printf("%s",TRUCK2);
	printf("%s",TRUCK2);
	printf("%s",TRUCK2);
	printf("%s",TRUCK2);
	printf("%s\n",TRUCK5);
	
		
} 

//Function to display the road 
void animation(void){
	gotoxy(10,16);
	printf("%s",BLOCK);
	gotoxy(67,16);
	printf("%s",BLOCK);
	gotoxy(10,17);
	printf("%s",BLOCK);
	for (i=0;i<=55;i++) {
		printf("%s",ROAD);
	}
	printf("%s",BLOCK);
	gotoxy(5,18);
	printf("Start");
	printf("%s",BLOCK);
	gotoxy(67,18);
	printf("%s",BLOCK);
	printf("End\n");
}




