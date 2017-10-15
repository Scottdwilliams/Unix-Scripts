/******************************************************************
 *
 * Author: Scott Williams
 *
 * CS 344 - Program 3 "smallsh"
 *
 * 2/28/16
 * 
 ******************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void getInput(){

	FILE *fp = fopen("./commands", "w");
	printf(": ");
	char str[2048];
	gets(str);
	fprintf(fp,"%s", str);
	fclose(fp);
}

void changeDir(){

	pid_t spawnpid = -5;
	spawnpid = fork();
	switch (spawnpid){

		case -1:
			perror("Something went very wrong!\n");
			exit(1);
			break;
		case 0:
			execl("/bin/sh", "-c", "cd", (const char *)0);
			char cwd[1024];
			if (getcwd(cwd, sizeof(cwd)) != NULL){
				printf("Current working dir: %s\n", cwd);
			}
			else{
				perror("getcwd() error");
			}
		default:
			printf("We both do this!\n");
			break;
	}	

}

void parseCommands(){

	FILE *fp = fopen("./commands", "r");
	char input[2048];
	fgets(input, 2048,fp);
	char *token = strtok(input, " ");
	fclose(fp);
	
	//create an array of strings to hold the delimited tokens
	char *args[512];
	int numOfArgs;
	int i = 0;
	for (i = 0; i < 510; i++){
		args[i] = malloc(30);
	}

	//store each token into the array of arguments
	i = 0;
	while(token){
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	numOfArgs = i;
	for (i = 0; i < numOfArgs; i++){
		printf("%s\n", args[i]);
	}

	//go through each argument to complete each command.
	for (i = 0; i < numOfArgs; i++){
		if (strcmp(args[i], "exit") == 0){
			exit(1);
		}
		else if (strcmp(args[i], "cd") == 0){
			changeDir();
		}
		else if (strcmp(args[i], "status") == 0){
			//do something
		}
	}

}


int main(){
	
	getInput();
	parseCommands();

	return 0;

}

