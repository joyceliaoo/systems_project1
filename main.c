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

//  GENERAL STRUCTURE

// ask for comamnd line inout *
// parse by semicolon *
// fork
// parse by space
//      read args until we find either a redirect or a pipe or end of array
//      if there is either: then continue until the next redirect or pipe or end of array
//          put them into the redirect/pipe functions
//          execute functions
//      else normal *



int main() {
	// testing code:
	// printf("testing num_tokens\n");
	// printf("expected: 2; actual: %d\n", num_tokens("ahjfdf fsdfdsf", " "));
	// printf("expect: 6; actual: %d\n", num_tokens("ahjfdf f sd f d sf", " "));

    while (1) {
		// ask for command line input
        printf("> ");
  		char l[100]; // buffer for what the user enters
  		fgets(l, 100, stdin); //reads user input
  		l[strlen(l)-1] = '\0'; //remove trailing \n character

  		/*// testing*/
  		/*printf("you entered: %s\n", l);*/

  		// parse the input
  		int num_lines = num_tokens(l, ";");
  		char** lines = parse_line(l, ";", num_lines); // split it into the different commands

        printf("-----parsing for ; -----\n");
  		printf("commands received: \n");
  		print_arr(lines);
        //trim(lines);
        printf("-----\n\n");

  		int i =  num_lines; // placeholder for num of lines
  		char** curr_line;
  		while (i) {


		// REDIRECT
		// ---------------------------------------------------------
		


		// ---------------------------------------------------------







		// PIPE
		// ---------------------------------------------------------

        printf("-----parsing for [>] -----\n");
        


		// ---------------------------------------------------------













		// NORMAL FUNCTION, no pipe, no redirect
		// ---------------------------------------------------------
          printf("-----parsing for [ ] -----\n");
          //count num of args in each commands
          int num_args = num_tokens(	lines[num_lines-i], " ");
          //take each command and parse into array of args
          curr_line = parse_line(lines[num_lines-i], " ", num_args); // parse by " "
          print_arr(curr_line);
          trim(curr_line);
          print_arr(curr_line);
          printf("-----\n\n");
          if (curr_line[0]) {
            int f = fork();
            // run
            if (f) { // parent
            	// wait for child process to finish
                int status;
                wait(&status);
                int child_value = WEXITSTATUS(status); //get return value of run
                printf("value returned by child: %d\n", child_value);
                //if command is "exit"
                if (child_value == 1) {
                	printf("exiting shell...\n");
                	exit(status);
                }
            } else { // child
                printf("command to be run next: [%s]\n", curr_line[0]);
                print_arr(curr_line);
                return run(curr_line); //to end child process
            }
          }
			  i--;
		}

		// ---------------------------------------------------------

    }
	return 0;
}
