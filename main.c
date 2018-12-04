#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "shell.h"
#include "test.h"
#include "text_parse.h"

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


        /*//  testing the redirect */
    /*char * arg1[2];*/
    /*arg1[0] = "ls";*/
    /*arg1[1] = NULL;*/
    /*char * arg2[3];*/
    /*arg2[0] = "test.txt";*/
    /*arg2[1] = NULL;*/
    /*redirect(arg1, arg2[0], 1);*/


    /*printf("%d", is_redirect_pipe(">"));*/
    /*printf("%d", is_redirect_pipe("|"));*/
    /*printf("%d", is_redirect_pipe(">>"));*/

    /*printf("%d", rp_mode(">"));*/

    while (1) {
          // ask for command line input
          print_prompt();
          char l[200]; // buffer for what the user enters
          fgets(l, 200, stdin); //reads user input
          l[strlen(l)-1] = '\0'; //remove trailing \n character

          // alright so we gotta put in the spaces bcuser is dumb
          char l2[250];

          //in case there was not a space between arg and redirect/pipe symbol
          int a = 0;
          int b = 0;
          while (l[a]) { //adds a space before and after
              if (l[a] == '>') {
                    l2[b++] = ' ';
                    l2[b++] = l[a];
                    if (l[a + 1] == '>' ) {
                        l2[b++] = l[a+1] ;
                        a ++;
                        l2[b++] = ' ';
                    } else {
                        l2[b++] = ' ';
                    }
                    a ++;
              } else if( l[a]  == '|' | l[a] == '<' ) {
                    l2[b++] = ' ';
                    l2[b++] = l[a++];
                    l2[b++] = ' ';
              } else {

                    l2[b++] = l[a++];
              }
          }
          l2[b] = 0;

          // printf("new string: %s\n", l2);

          /*// testing*/
          /*printf("you entered: %s\n", l);*/

          // parse the input
          int num_lines = num_tokens(l2, ";");
          char** lines = parse_line(l2, ";", num_lines); // split it into the different commands

          /*printf("-----parsing for ; -----\n");*/
          // printf("commands received: \n");
          // print_arr(lines);
          //trim(lines);
          /*printf("-----\n\n");*/

          int i =  num_lines; // placeholder for num of lines
          char** curr_line;

          // this while is for multiple arguments
          while (i) {

              /*printf("-----parsing for [ ] -----\n");*/
              //count num of args in each commands
              int num_args = num_tokens(  lines[num_lines-i], " ");
              //take each command and parse into array of args
              curr_line = parse_line(lines[num_lines-i], " ", num_args); // parse by " "
              // printf("before trim: \n");
              // print_arr(curr_line);
              trim(curr_line);
              // printf("after trim: \n");
              // print_arr(curr_line);
              /*printf("-----\n\n");*/



              // curline is the current set of arguments

              if (curr_line[0]) { // if there is an argument...

                  //                          PARENT AND CHILD WILL BE HERE
                  int f = fork();

                  // run the thing given
                  // --------------------------------
                  if (f) { // parent
                      // wait for child process to finish
                      int status;
                      waitpid(f, &status, 0);
                      int child_value = WEXITSTATUS(status); //get return value of run
                      //printf("value returned by child: %d\n", child_value);
                      //if error
                      if (child_value == 1) {
                          printf("error..\n");
                      }
                      //if command is cd
                      if (child_value == 2) {
                          printf("changing working dir...\n");
                          chdir(curr_line[1]);
                      }
                      //if command is "exit"
                      if (child_value == 3) {
                          printf("exiting shell...\n");
                          exit(status);
                      }
                  } else { // child
                          /*printf("command to be run next: [%s]\n", curr_line[0]);*/
                          /*print_arr(curr_line);*/
                          return run(curr_line); //to end child process
                  }
                  // --------------------------------
              } //if currline
              i--;
          } // end while i
          free(curr_line);
      } // end while 1
      // ---------------------------------------------------------
      return 0;
  }
