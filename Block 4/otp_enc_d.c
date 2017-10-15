/******************************************************************
 *
 * Author: Scott Williams
 *
 * CS 344 - Program 4 "OTP"
 *
 * 3/14/2016
 *
 ******************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void readTextFiles(){

	FILE *fp = fopen("./plaintext1", "r");
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

	//encode each letter.
	for (i = 0; i < numOfArgs; i++){
		//encode each letter.
	}

}


int main(){

	readTextFiles();

	return 0;

}
