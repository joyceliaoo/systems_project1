#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <limits.h>
#include "shell.h"
#include "text_parse.h"
#include "test.h"

#define READ 0
#define WRITE 1
#define KCYN  "\x1B[36m"
#define KMAG  "\x1B[35m"
#define KNRM  "\x1B[0m"

void print_prompt() {
    char cwd[PATH_MAX]; //buffer to store cwd
    getcwd(cwd, sizeof(cwd));
    printf("%s%s %s[HJ]%s> ", KCYN, cwd, KMAG, KNRM);
}

// running things, commands
int run(char** args) {
    //internal commands
    //cd
    if (!strcmp(args[0], "cd")){
        return 2; //let main know cd is called
    }
    //exit
    if (!strcmp(args[0], "exit")) {
        return 3; //let main know exit is called
    }
    //external commands
    char num_red = count_redirect(args);
    char num_pipes = count_pipe(args);
    if (num_red) {
        return redirect(args, num_red);
    } else if (num_pipes) {
        return ter_pipe(args, num_pipes);
    } else {
        /*printf("no pipes, redirects found\n");*/
        return execvp(args[0], args);
    }
}

int redirect(char** args, char num) {
    char * cmd[10];
    char * file;
    int args_offset = 0;
    int i = 0;
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
        else if (mode < 3) {// if > or >>
            backup_type[backup_count] = STDOUT_FILENO;
            if (mode == 1) // if <
                fd = open(file, O_CREAT | O_WRONLY, 0777);
            else // if <<
                fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
        }
        backup[backup_count] = dup(backup_type[backup_count]);
        dup2(fd, backup_type[backup_count]);
        backup_count++;
        close(fd);
        num--;
    } // end of while (num)
    int f = fork();
    if (!f) { // if child
        run(cmd);
    }
    else { //change everything back
        int status;
        wait(&status);
        while(backup_count+1){
            dup2(backup[backup_count], backup_type[backup_count]);
            backup_count--;
        }
    }
    return 0;
}

int ter_pipe(char** args, char num) {

    char* args1[20];
    char* args2[20];

    int j = 0;
    while( args[j] && !is_redirect_pipe(args[j])) {
       args1[j] = args[j];
       j ++;
    }
    args1[j] = NULL;

    int k = 0;
    if (args[j]) { // if there is more stuff
       if (is_redirect_pipe(args[j])) {
           j++;
       }
       while( args[j]) {
           args2[k] = args[j];
           k ++;
           j++;
       }
       args2[j] = NULL;
    }

	int fds[2];
	pipe(fds);
	int f = fork();
	if (f == 0) { // child; will write output
		// close read
        close(fds[READ]);
        int backup = dup(STDOUT_FILENO);
        dup2(fds[WRITE], STDOUT_FILENO);
        int g = fork();

		// execute args 1
        if (!g) {
            run(args1);
        }
		// close write
        close(fds[WRITE]);

        // return the backup
        dup2(backup, STDOUT_FILENO);

        exit(0);
	} else { // parent, will take output, and use it to run

		// close write
        close(fds[WRITE]);

        int backup = dup(STDIN_FILENO);
        dup2(fds[READ], STDIN_FILENO);

        int g = fork();

		// execute args 2
        if (!g) {
            /*printf("about to run\n");*/
            run(args2);
        }

        int status;
        waitpid(g, &status, 0);

		// close read
        close(fds[READ]);
        // revert
        dup2(backup, STDIN_FILENO);

	}
    return 0;
}
