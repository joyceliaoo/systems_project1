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
	args[num_tokens] = NULL; // convience and also exec
	return args;
}

char** trim(char** args) {
    char** ans = malloc( sizeof(args));
    int string_offset = 0;
    while (*args) { // now considering just strings
        int char_offset = 0;
        char* source = args[string_offset];
        //copy each char
        char* dest = malloc(sizeof(source));
        while (source[char_offset]) {
            dest[char_offset] = source[char_offset];
            char_offset++;
        }
        //add terminating null
        dest[char_offset] = '\0';
        ans[string_offset] = dest;
        string_offset++;
    }
    free(args);
    return ans;
}

// running things, commands
void run(char** args) {
    if (!strcmp(args[0], "cd")){
        //smth w chdir
        printf("u have chosen to cd. it doesn't work yet");
    } else if (!strcmp(args[0], "quit")) {
        quit();
    } else {
        execvp(".", args);
    }

}

// commands 

void quit() {
    printf("you have chosen to quit; placeholder");
}
