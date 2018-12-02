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
#include <limits.h>
#include "shell.h"
#include "text_parse.h"
#include "test.h"

#define READ 0
#define WRITE 1

void print_prompt() {
    char cwd[PATH_MAX]; //buffer to store cwd
    getcwd(cwd, sizeof(cwd));
    printf("%s HJ> ", cwd);
}

// running things, commands
int run(char** args) {
    //internal commands
    //cd
    if (!strcmp(args[0], "cd")){
        printf("child is done!\n");
        return 2; //let main know cd is called
    }
    //exit
    if (!strcmp(args[0], "exit")) {
        printf("child is done!\n");
        return 3; //let main know exit is called
    }
    //external commands
    char num_red = count_redirect(args);
    if (num_red) {
        return redirect(args, num_red);
    }
    else {
        return execvp(args[0], args);
    }
}

int redirect(char** args, char num) {
    // num = num of redirects
    // mode 1 = >, 2 = >>, 3 = <
	// output of args1 goes into file
	// copy stdout so we have a backup
	// set args2 as stdout
	// fork
	// 		child: run first command
	// 		parent: wait
	// change back
    char * cmd[10];
    char * file;
    char args_offset = 0;
    char i = 0;
    int mode = 0;
    int backup[num];
    int backup_type[num];
    int backup_count = 0;
    int fd;
    while (num) { //there are more redirects
        while(!is_redirect_pipe(args[args_offset])) {
            //printf("next %s\n", args[args_offset]);
            cmd[i++] = args[args_offset++];
        }
        cmd[i] = NULL;
        //print_arr(cmd);
        mode = rp_mode(args[args_offset]);
        //printf("mode : %d \n", mode);
        args_offset++;
        file = args[args_offset++];
        if (mode == 3) {//if <
            backup_type[backup_count] = STDIN_FILENO;
            fd = open(file, O_RDONLY);
            if (fd == -1) return 1; //if not valid file name
        }
        else if (mode == 1) {// if >
            backup_type[backup_count] = STDOUT_FILENO;
            fd = open(file, O_CREAT | O_WRONLY, 0777);
        }
        backup[backup_count] = dup(backup_type[backup_count]);
        dup2(fd, backup_type[backup_count]);
        backup_count++;
        close(fd);
        num--;
    }
    int f = fork();
    if (!f) { // if child
        run(cmd);
    }
    else {
        int status;
        wait(&status);
        while(backup_count+1){
            dup2(backup[backup_count], backup_type[backup_count]);
            backup_count--;
        }
    }
    return 0;
}


//     int backup;
//     int type;
//     int fd;
//     char file[32];
//     char ** cmd;
//     if (mode > 2) {//if <
//         strcpy(file, args1[0]);
//         cmd = args2;
//         type = STDIN_FILENO;
//     }
//     else {//if > or >>
//         strcpy(file, args2[0]);
//         cmd = args1;
//         type = STDOUT_FILENO;
//     }
//     backup = dup(type);
//     if (mode == 1)  //if >
//         fd = open(file, O_CREAT | O_WRONLY, 0777);
//     else if (mode == 2) // if >>
//         fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
//     else  // if <
//         fd = open(file, O_RDONLY);
//
//     dup2(fd, type);
//     int f = fork();
//     if (!f) { // if child
//         run(cmd);
//     }
//     else {
//         int status;
//         wait(&status);
//         dup2(backup, type);
//     }
//
//     close(fd);
//     return 0;
// }


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
