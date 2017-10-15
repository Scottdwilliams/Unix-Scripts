/************************************************************************
 * Author: Scott Williams
 * Onid: Williasc
 * Class: CS344
 * Program Name: Program 2 - adventure
 * Description: This program allows the user to navigate through rooms
 * to try to find the ending room. Once the user has found the ending
 * room, they are congratulated and shown their path to the end.
 * *********************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct Room{
	char* name;
	int type;		//1 = start, 2 = middle, and 3 = end
	int number;		//corresponds to the position in the  array of structs
	int connections[6];	//array of the connections to each room number
	int numOfCons;		//how many connections the room currently has
};

int main(){

	//initialize random seed
	srand ( time(NULL) );

	//create structs and assign types and room numbers and create pointers
	struct Room roomZero = { .type = 1, .number = 0};
	struct Room *p0 = &roomZero;
    	struct Room roomOne = { .type = 2, .number = 1};
    	struct Room *p1 = &roomOne;
    	struct Room roomTwo = { .type = 2, .number = 2};
    	struct Room *p2 = &roomTwo;
    	struct Room roomThree = { .type = 2, .number = 3};
    	struct Room *p3 = &roomThree;
    	struct Room roomFour = { .type = 2, .number = 4};
    	struct Room *p4 = &roomFour;
    	struct Room roomFive = { .type = 2, .number = 5};
    	struct Room *p5 = &roomFive;
    	struct Room roomSix = { .type = 3, .number = 6};
    	struct Room *p6 = &roomSix;

	struct Room house[7] = { *p0, *p1, *p2, *p3, *p4, *p5, *p6 };	//create an array of pointers to the 7 structs
	char* roomNames[10] = { "Foyer", "Library", "Hallway", "Dining Room", "Great Hall", "Kitchen", "Ballroom", "Living Room", "Den", "Office" };
	
	//randomly assign room names by usinng the remainder of (rand(0-9) + 7) / 10
	int i;
	int temp = rand() % 10;
	for (i = 0; i < 7; i++){
        	int index = (temp + i) % 10;
        	house[i].name = roomNames[index];
	}

    	//loop through each room to assign random connections
	int j, k, l;	//counters for future for loops
	int randCons;	//random number of connections to assign to each new room
	int randRoom;	//random room number to connect to current room
	for (i = 0; i < 7; i++){
		randCons = rand() % 4 + 3;	//create random number between 3 and 6 for number of connections

		//if the current room has less than randCons connections, add until full
		if (house[i].numOfCons < randCons){
            		int lastUsed = 10;      //reset lastUsed connection to 10 (a number that isn't possible for the rand func)
			for (j = house[i].numOfCons; j < randCons; j++){
				//continue finding random numbers until its not the previously used number, or the current room number
				do {
					randRoom = rand() % 7;
				} while (randRoom == i || randRoom == lastUsed);

				//search for existing connection and go back through until we find one that doesn't exist
				int connectionExists = 0;
				for (k = 0; k < house[i].numOfCons; k++){
                    			if (house[i].numOfCons == 0){
                        		break;
                    			}
                    			if (house[i].connections[k] == randRoom){
                        		connectionExists = 1;
                        		j--;
                        		break;
                    			}
				}

                		if (connectionExists == 0){

                    			house[i].connections[j] = randRoom;	//assign new random room to connections list
                    			lastUsed = randRoom;                //assign lastUsed to current random number
                    			house[i].numOfCons++;

                    			//search the connections of j to try to find i, if not there, add it
                    			int found = 0;	//set trigger for finding the same room to 'false'
                    			for (l = 0; l < house[randRoom].numOfCons; l++){
                        			if (house[randRoom].connections[l] == i){
                            				found = 1;
                        			}
                    			}
                    			//if i isn't found in j's connections, add it
                    			if (found == 0){
                        			int temp;
                        			temp = house[randRoom].numOfCons;
                        			house[randRoom].connections[temp] = i;
                        			house[randRoom].numOfCons++;
                    			}
                		}
			}
		}
	}

/*******************************************************************************
 * 									       *
 * ***********************     Writing to File    ******************************
 *									       *
 * ****************************************************************************/

	//create a struct to test if current directory is already made, otherwise make it
	struct stat st = {0};

	if (stat("./williasc.rooms", &st) == -1){
		mkdir("./williasc.rooms", 0777);
	}

	//write to file zero
	FILE *fptr = fopen("./williasc.rooms/room.zero", "w");
	fprintf(fptr, "ROOM NAME: %s\n", house[0].name);
	for (i = 0; i < house[0].numOfCons; i++){
		int temp = house[0].connections[i];
		fprintf(fptr, "CONNECTION %u: %s\n", i + 1, house[temp].name);
	}	
	temp = house[0].type;
	char* roomType;
	if (temp == 1){
		roomType = "START_ROOM";
	}
	else if (temp == 2){
		roomType = "MID_ROOM";
	}
	else{
		roomType = "END_ROOM";
	}

	fprintf(fptr, "ROOM TYPE: %s\n", roomType);
	fclose(fptr);

	//write to file one
	fptr = fopen("./williasc.rooms/room.one", "w");
	fprintf(fptr, "ROOM NAME: %s\n", house[1].name);
	for (i = 0; i < house[1].numOfCons; i++){
		int temp = house[1].connections[i];
		fprintf(fptr, "CONNECTION %u: %s\n", i + 1, house[temp].name);
	}	
	temp = house[1].type;
	if (temp == 1){
		roomType = "START_ROOM";
	}
	else if (temp == 2){
		roomType = "MID_ROOM";
	}
	else{
		roomType = "END_ROOM";
	}

	fprintf(fptr, "ROOM TYPE: %s\n", roomType);
	fclose(fptr);

	//write to file two
	fptr = fopen("./williasc.rooms/room.two", "w");
	fprintf(fptr, "ROOM NAME: %s\n", house[2].name);
	for (i = 0; i < house[2].numOfCons; i++){
		int temp = house[2].connections[i];
		fprintf(fptr, "CONNECTION %u: %s\n", i + 1, house[temp].name);
	}	
	temp = house[2].type;
	if (temp == 1){
		roomType = "START_ROOM";
	}
	else if (temp == 2){
		roomType = "MID_ROOM";
	}
	else{
		roomType = "END_ROOM";
	}

	fprintf(fptr, "ROOM TYPE: %s\n", roomType);
	fclose(fptr);

	//write to file three
	fptr = fopen("./williasc.rooms/room.three", "w");
	fprintf(fptr, "ROOM NAME: %s\n", house[3].name);
	for (i = 0; i < house[3].numOfCons; i++){
		int temp = house[3].connections[i];
		fprintf(fptr, "CONNECTION %u: %s\n", i + 1, house[temp].name);
	}	
	temp = house[3].type;
	if (temp == 1){
		roomType = "START_ROOM";
	}
	else if (temp == 2){
		roomType = "MID_ROOM";
	}
	else{
		roomType = "END_ROOM";
	}

	fprintf(fptr, "ROOM TYPE: %s\n", roomType);
	fclose(fptr);

	//write to file four
	fptr = fopen("./williasc.rooms/room.four", "w");
	fprintf(fptr, "ROOM NAME: %s\n", house[4].name);
	for (i = 0; i < house[4].numOfCons; i++){
		int temp = house[4].connections[i];
		fprintf(fptr, "CONNECTION %u: %s\n", i + 1, house[temp].name);
	}	
	temp = house[4].type;
	if (temp == 1){
		roomType = "START_ROOM";
	}
	else if (temp == 2){
		roomType = "MID_ROOM";
	}
	else{
		roomType = "END_ROOM";
	}

	fprintf(fptr, "ROOM TYPE: %s\n", roomType);
	fclose(fptr);

	//write to file five
	fptr = fopen("./williasc.rooms/room.five", "w");
	fprintf(fptr, "ROOM NAME: %s\n", house[5].name);
	for (i = 0; i < house[5].numOfCons; i++){
		int temp = house[5].connections[i];
		fprintf(fptr, "CONNECTION %u: %s\n", i + 1, house[temp].name);
	}	
	temp = house[5].type;
	if (temp == 1){
		roomType = "START_ROOM";
	}
	else if (temp == 2){
		roomType = "MID_ROOM";
	}
	else{
		roomType = "END_ROOM";
	}

	fprintf(fptr, "ROOM TYPE: %s\n", roomType);
	fclose(fptr);

	//write to file six
	fptr = fopen("./williasc.rooms/room.six", "w");
	fprintf(fptr, "ROOM NAME: %s\n", house[6].name);
	for (i = 0; i < house[6].numOfCons; i++){
		int temp = house[6].connections[i];
		fprintf(fptr, "CONNECTION %u: %s\n", i + 1, house[temp].name);
	}	
	temp = house[6].type;
	if (temp == 1){
		roomType = "START_ROOM";
	}
	else if (temp == 2){
		roomType = "MID_ROOM";
	}
	else{
		roomType = "END_ROOM";
	}

	fprintf(fptr, "ROOM TYPE: %s\n", roomType);
	fclose(fptr);

/*******************************************************************************
 *                                                                             *
 * ***********************    Start of the Game    *****************************
 *									       *
 * ****************************************************************************/

	
	int currentRoom = 0;
    	int *path;  //array to store the path to the final room
    	path = (int *)malloc(sizeof(int));
    	int steps = 0;  //keeps track of number of rooms in path

    	//print rules and list possible connections of the starting room
    	printf("Try to find where the murder took place by moving between rooms.\n");
    	printf("To enter a new room, type the exact name of the room you wish to enter.\n\n");
    	printf("Current location: %s\n", house[currentRoom].name);
    	printf("Possible connections:\n");
    	for (i = 0; i < house[currentRoom].numOfCons; i++){

        	int temp = house[currentRoom].connections[i];
       		if (i == house[currentRoom].numOfCons - 1){
            		printf("%s\n", house[temp].name);
        	}
        	else{
            		printf("%s, ", house[temp].name);
        	}
    	}

    	//start of the game -- continues until you find the room with type 3, or "end room".
    	do{

        	int goodInput = 0;  //keeps track of whether or not the input was good

        	//gets input from screen until it matches a possible room.
        	do{
            		printf("Where to? ");
            		char str[100];
            		gets(str);

            		for (i = 0; i < 7; i++){
                		if (strcmp(str, house[i].name) == 0){
                    			currentRoom = i;
                    			path[steps] = i;	//add the correct room to the list of rooms on the path
                    			steps++;		//increment the number of rooms entered
                    			goodInput = 1;
					break;
                		}
            		}
            		//print error message if not an exact comparison
            		if (goodInput == 0){
                		printf("I'm sorry, that didn't make sense. Make sure to be exact.\n");
            		}
        	}while (goodInput = 0);

        	//print new current room connections as long as the new room isn't the end room.
        	if (house[currentRoom].type != 3){
            		printf("\nCurrent location: %s\n", house[currentRoom].name);
            		printf("Possible connections:\n");
            		for (i = 0; i < house[currentRoom].numOfCons; i++){

                		int temp = house[currentRoom].connections[i];
                		if (i == house[currentRoom].numOfCons - 1){
                    			printf("%s\n", house[temp].name);
                		}
                		else{
                    			printf("%s, ", house[temp].name);
                		}
            		}
        	}
    	} while (house[currentRoom].type != 3);

    	//congratulations message and printing rooms passed through
    	printf("\n\nCongratulations!!! You made it! You went through %u rooms.\n", steps);
    	printf("Your path was:\n");
    	for (i = 0; i < steps; i++){
        	int temp = path[i];
        	printf("%s\n", house[temp].name);
    	}	

    	free(path);

	return 0;
}
