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
#include "text_parse.h"

//  GENERAL STRUCTURE

// ask for comamnd line inout *
// parse by semicolon *
// fork
// parse by string
// run args until u reach either a > | or the end
// 		if u reach a > or | :
// 			read until the next > or | or the end
// 			put these into the function
//		 else normal *



int main() {
	// testing code:
	// printf("testing num_tokens\n");
	// printf("expected: 2; actual: %d\n", num_tokens("ahjfdf fsdfdsf", " "));
	// printf("expect: 6; actual: %d\n", num_tokens("ahjfdf f sd f d sf", " "));

		/*//  testing the pipe*/
    /*char * arg1[2];*/
    /*arg1[0] = "ls";*/
    /*arg1[1] = NULL;*/
    /*char * arg2[3];*/
    /*arg2[0] = "grep";*/
    /*arg2[1] = ".c";*/
    /*arg2[2] = NULL;*/
    /*ter_pipe(arg1, arg2);*/

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



        printf("-----parsing for [ ] -----\n");
        //count num of args in each commands
        int num_args = num_tokens(	lines[num_lines-i], " ");
        //take each command and parse into array of args
        curr_line = parse_line(lines[num_lines-i], " ", num_args); // parse by " "
        //  print_arr(curr_line);
        trim(curr_line);
        // print_arr(curr_line);
        printf("-----\n\n");


        // curline is the current set of arguments

        if (curr_line[0]) { // if there is an argument...


            int f = fork();

            // copy things into a new string until you hit a null or | or redirect

            char* segment1[100];
            char mode = 0;
            int i = 0;
            while( !is_redirect_pipe(curr_line[i])) {
                segment1[i] = curr_line[i];
                i ++;
            }

            if (is_redirect_pipe(curr_line[i])) {
                mode = *curr_line[i];
                i++;
            }

            char* segment2[100];
            
            while( curr_line[i]) {
                segment2[i] = curr_line[i];
                i++;
            }

            print_arr(segment1);
            print_arr(segment2);


            // 		if theres a | or redirect:
            // 			copy thinggs until you hit a null
            // 			plug it in


            if (mode) { //there is a pipe or redirect
                if (mode == '|')
                    ter_pipe(segment1, segment2);
                redirect(segment1, segment2[0], mode);
            } else {
                // run the thing given
                // --------------------------------
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
                // --------------------------------
            }
          }
              i--;
        } // end while i
    } // end while 1
		// ---------------------------------------------------------
	return 0;
}
