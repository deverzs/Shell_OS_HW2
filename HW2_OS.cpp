#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;
#define MAX_LINE 80 /* The maximum length command */
int main(void)
{
	char* args[MAX_LINE / 2 + 1]; //arguments from command line
	int argc; //argument counter
	int should_run = 1; //flag to determine when to exit program
	char input[256];
	char* token;

	while (should_run) {
		printf("osh>");
		fflush(stdout);
		/*-----Read from the user input------*/
		argc = 0; //reset the argument counter
		cin.getline(input, sizeof(input));
		if (strcmp(input, "exit") == 0) {            //check if command is exit
			should_run = 0;
			continue;
		}
		token = strtok(input, " ");

		while (token != NULL) {
			args[argc] = token;
			argc++;
			token = strtok(NULL, " ");
		}
		args[argc] = token;
		//  for(int i = 0; i<argc;i++){
		//     cout<<args[i]<<endl;
		//   } 
		  /*--------Excuting child process by calling fork()------*/

		pid_t pid = fork();


		if (pid < 0) //check the fork() failure
		{
			fprintf(stderr, "fork failed\n");
			exit(1);
		}
		else if (pid == 0) //child process
		{
			printf("child is now executing\n");
			execvp(args[0], args); //run the command with its parameters
			printf("this should not appear\n"); //check if the execvp is failed or not




		}
		else
		{
			if (strcmp(args[argc - 1], "&") > 0) {
				wait(NULL);
				printf("Parent is now executing\n");
			}
			else
			{
				printf("concurrently\n");
				wait(NULL);
			}

		}
	}
}
