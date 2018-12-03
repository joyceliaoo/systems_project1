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
//      if u reach a > or | :
//          read until the next > or | or the end
//          put these into the function
//       else normal *



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
          char l[100]; // buffer for what the user enters
          fgets(l, 100, stdin); //reads user input
          l[strlen(l)-1] = '\0'; //remove trailing \n character

          /*// testing*/
          /*printf("you entered: %s\n", l);*/

          // parse the input
          int num_lines = num_tokens(l, ";");
          char** lines = parse_line(l, ";", num_lines); // split it into the different commands

          /*printf("-----parsing for ; -----\n");*/
          /*printf("commands received: \n");*/
          /*print_arr(lines);*/
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
              //  print_arr(curr_line);
              trim(curr_line);
              /*print_arr(curr_line);*/
              /*printf("-----\n\n");*/


              char ** free_this = curr_line;
              curr_line = parse_rp(curr_line); 

              // curline is the current set of arguments

              if (curr_line[0]) { // if there is an argument...

                  // // copy things into a new string until you hit a null or | or redirect
                  // char* segment1[10];
                  // int mode = 0;
                  // int j = 0;
                  //
                  // while( curr_line[j] && !is_redirect_pipe(curr_line[j])) {
                  //     /*printf("%s (currline)\n", curr_line[j]);*/
                  //     segment1[j] = curr_line[j];
                  //     /*printf("%s (segment)\n", segment1[j]);*/
                  //     j ++;
                  //     /*printf("mad it to the end\n");*/
                  // }
                  // segment1[j] = NULL;
                  //
                  // printf("segment1:\n");
                  // print_arr(segment1);
                  //
                  // char* segment2[10];
                  //
                  // int k = 0;
                  // if (curr_line[j]) { // if there is more stuff
                  //     if (is_redirect_pipe(curr_line[j])) {
                  //         mode = rp_mode( curr_line[j] ); // mode
                  //         printf("redirect was found, mode: [%d]\n", mode);
                  //         j++;
                  //     }
                  //
                  //     while( curr_line[j]) {
                  //         printf("segment2 added\n");
                  //         segment2[k] = curr_line[j];
                  //         k ++;
                  //         j++;
                  //     }
                  //     segment2[j] = NULL;
                  // }
                  //
                  // /*printf("segment2 copied\n");*/
                  //
                  // printf("segment2:\n");
                  // print_arr(segment2);


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
                      // printf("mode: %d\n", mode);
                      // if (mode) { //there is a pipe or redirect
                      //     if (mode == 4) {
                      //         return ter_pipe(segment1, segment2);
                      //     } else {
                      //         return redirect(segment1, segment2, mode);
                      //     }
                      // } else {
                          /*printf("command to be run next: [%s]\n", curr_line[0]);*/
                          /*print_arr(curr_line);*/
                          return run(curr_line); //to end child process
                      //}
                  }
                  // --------------------------------
              } //if currline
              i--;
              free(free_this);
          } // end while i
          free(curr_line);
      } // end while 1
      // ---------------------------------------------------------
      return 0;
  }
