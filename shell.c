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

int redirect(char** args1, char* file, char mode) {
  // mode 1 = WRONLY, 2 = APPEND
	// output of args1 goes into file
	// copy stdout so we have a backup
	// set args2 as stdout
	// fork
	// 		child: run first command
	// 		parent: wait
	// change back
    int redirect_type; //distinguish between < and <<
    if (mode == 2) redirect_type = O_APPEND;
    else redirect_type = O_WRONLY;

    int backup = dup(STDOUT_FILENO);
    int fd = open(file, redirect_type);
    dup2(fd, STDOUT_FILENO);
    int f = fork();
    if (!f) { // if child
        run(args1);
    }
    else {
        int status;
        wait(&status);
        dup2(backup, STDOUT_FILENO);
    }
    return 0;
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
            printf("child\n");
            run(args1);
        } else {
		// take stdout and write it into the pipe
            int status;
            waitpid(f, &status, f);

            /*int child_value = WEXITSTATUS(status); //get return value of run*/
            /*if (child_value == 1) {*/
                /*printf("exiting shell...\n");*/
                /*exit(status);*/
            /*}*/

            char output[500];  // MAY NEED TO CHANGE PLACEHOLDER`
            read(STDOUT_FILENO, output, 500);
            printf("output: %s\n", output);
            write(fds[WRITE], output, 500);
            printf("child2\n");
        }
		// close write
        close(fds[WRITE]);
        return 0;
	} else { // parent, will take output, and use it to run
        int status;
        waitpid(f, &status, f);
        printf("parent");
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
