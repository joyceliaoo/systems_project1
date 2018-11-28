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

//  dealing w parsing text

unsigned int num_tokens(char* line, char* delim) {
	unsigned int ans = 1;
	while (*line) { // while were still in the string
		if (!strncmp(line, delim, 1)) {
			/*printf("theyre equal!\n");*/
			ans ++;
		}
		line ++;
	}
	return ans;
}



char** parse_line(char* line, char* delim, int num_tokens) {
	char** args = malloc( (num_tokens + 1) * sizeof(char*)); // make some space for the array
	char *s = strsep(&line, delim);
	int i = 0;
	while (s) {
		args[i] = s;
		/*printf("%d : %s", i, ans[i]);*/
		s = strsep(&line, delim);
		i++;
	}
	args[num_tokens] = NULL; // convenience and also exec
	return args;
}

void trim(char** args) {
    int string_offset = 0;
		int arg_count = 0;
    while (args[string_offset]) { // now considering just strings
			  int num_char = strlen(args[string_offset]);
        char trimmed_str[num_char * sizeof(char)];
        int char_offset = 0;
        int trim_index = 0;
        //char found_beginning = 0;
        //char prev_char = 0;
        //  get rid of around and inside
        while(args[string_offset][char_offset]) {
            /*if( is_space(args[string_offset][char_offset]) && !found_beginning) {*/
                /*trimmed_str[trim_index] = args[string_offset][char_offset];*/
                /*trim_index++;*/
                /*found_beginning = 1;*/
            /*} else*/
            if( !is_space(args[string_offset][char_offset]) ) {
                // get rid of multiple spaces in a row
            //     if (!is_space(prev_char)) {
            //         //trimmed_str[trim_index] = ' ';
            //         trim_index ++;
            //         prev_char = args[string_offset][char_offset];
            //     }
            // } else {
            //     //found_beginning = 1;
            //     trimmed_str[trim_index] = args[string_offset][char_offset];
            //     trim_index ++;
            //     prev_char = args[string_offset][char_offset];
            // }
							trimmed_str[trim_index] = args[string_offset][char_offset];
							trim_index++;
						}
            char_offset ++;
        }
				if (trim_index) {
				  trimmed_str[trim_index] = 0;
          printf("%s: trimmed ver\n", trimmed_str);
				  strcpy(args[arg_count++], trimmed_str);
				}
        string_offset++;

    }
		args[arg_count] = NULL;
}

char is_space(char c) {
    return (c == 0 || c == ' ' || c == '\t' || c == '\0');
}



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

int pipe(char ** args1, char** args2) {
	int fds[2];
	pipe(fds);
	f = fork();
	if (f == 0) { // child; will write output
		// close read 
		// execute args 1
		// take stdout and write it into the pipe	
		// close write
	} else { // parent, will take output, and use it to run
		// close write 
		// take pipe and write it into stdin
		// execute args 2 
		// close write

	} 
}
