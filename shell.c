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

#define READ 0
#define WRITE 1



// running things, commands
int run(char** args) {
    //internal commands
    //cd
    if (!strcmp(args[0], "cd")){
        //smth w chdir
        printf("u have chosen to cd. it doesn't work yet\n");
        printf("child is done!\n");
        return 2; //let main know cd is called
    }
    //exit
    else if (!strcmp(args[0], "exit")) {
        printf("child is done!\n");
        return 1; //let main know exit is called
    }
    //external commands
    else {
        execvp(args[0], args);
        printf("child is done!\n");
        return 0;
    }
}

int redirect(char ** args1, char** args2) {
	// output of args1 goes into args2
	// copy stdout so we have a backup
	// set args2 as stdout
	// fork
	// 		child: run first command
	// 		parent: wait
	// change back
	
}

int ter_pipe(char** args1, char** args2) {
	int fds[2];
	pipe(fds);
	int f = fork();
	if (f == 0) { // child; will write output
		// close read 
        close(fds[READ]);
        f = fork();
		// execute args 1
        if (!f) {
            return run(args1);
        } else {
		// take stdout and write it into the pipe	
            int status;
            wait(&status);
            char output[500];  // MAY NEED TO CHANGE PLACEHOLDER`
            read(STDOUT_FILENO, output, 500); 
            write(STDIN_FILENO, output, 500);
        }
		// close write
        close(fds[WRITE]);
	} else { // parent, will take output, and use it to run
		// close write 
        close(fds[WRITE]);
		// take pipe and write it into stdin
        char input[500];  // MAY NEED TO CHANGE PLACEHOLDER`
        read(fds[READ], input, 500); 
        write(STDIN_FILENO, input, 500);
        f = fork();
		// execute args 2 
        if (!f) { 
            return run(args2);
        } 
            
		// close read 
        close(fds[READ]);

	} 
    return 0;
}
