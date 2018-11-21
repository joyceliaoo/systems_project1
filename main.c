#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include "shell.h"
#include "test.h"


int main() {
	
	// testing code:
	printf("testing num_tokens\n");
	printf("expected: 2; actual: %d\n", num_tokens("ahjfdf fsdfdsf", " "));
	printf("expect: 6; actual: %d\n", num_tokens("ahjfdf f sd f d sf", " "));

    while (1) {
		// ask for command line input
		char l[100]; // buffer for what the user enters 
		fgets(l, 100, stdin);		

		/*// testing*/
		/*printf("you entered: %s\n", l);*/

		// parse the input
		int num_lines = num_tokens(l, ";");
		char** cl = parse_line(l, ";", num_lines); // split it uinto the different commands
		
		int i =  num_lines; // placeholder for num of lines
		char** curr_line;
		while (i) { 
			int num_args = num_tokens(	cl[num_lines-i], " ");
			curr_line = parse_line(cl[num_lines-i], " ", num_args); // parse by " "
				
			i --;
		}	


		// fork off a child process to do whatever it needs to do 
			
		// wait for child process to finish

		// rinse and repeat :)
    }
	return 0;
}

