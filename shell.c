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
	args[num_tokens] = NULL; // convenience and also exec
	return args;
}

void trim(char** args) {
    int string_offset = 0;
    while (args[string_offset]) { // now considering just strings
        char* trimmed_str = malloc(500); //malloc(sizeof(args[string_offset]));
        int char_offset = 0;
        int trim_index = 0;
        char found_beginning = 0;
        char prev_char = 0;
        //  get rid of around and inside
        while(args[string_offset][char_offset]) {         
            /*if( is_space(args[string_offset][char_offset]) && !found_beginning) {*/
                /*trimmed_str[trim_index] = args[string_offset][char_offset];*/
                /*trim_index++;*/
                /*found_beginning = 1;*/
            /*} else*/
            if( is_space(args[string_offset][char_offset]) ) {
                // get rid of multiple spaces in a row
                if (!is_space(prev_char)) {
                    trimmed_str[trim_index] = ' ';
                    trim_index ++;
                    prev_char = args[string_offset][char_offset];
                }
            } else {
                found_beginning = 1;
                trimmed_str[trim_index] = args[string_offset][char_offset];
                trim_index ++;
                prev_char = args[string_offset][char_offset];
            }
            char_offset ++;
        }
        printf("%s: trimmed ver\n", trimmed_str);
        args[string_offset] = trimmed_str; // this part is giving me issues but i dont rlly get it lmao
        free(args[string_offset]);
        string_offset++;

    }
}

char is_space(char c) {
    return (c == 0 || c == ' ' || c == '\t');
}    

/*void trim(char **args, int num_args) {*/
    /*int cur = 0;*/
    /*int extra = 0; //count how many extra spaces there are*/
    /*//go through the array*/
    /*while (cur < num_args - 1) {*/
        /*//if an arg is a space or \0 char, shift next arg to where the space is*/
        /*if (args[cur][0] == '\0' || args[cur][0] == ' ') {*/
            /*extra++;*/
            /*strcpy(args[cur], args[cur+1]);*/
            /*//arg that has been shifted is replaced by space*/
            /*strcpy(args[cur+1], " ");*/
        /*}*/
        /*cur++;*/
    /*}*/
    /*//check last string in arr*/
    /*if (args[cur][0] == '\0' || args[cur][0] == ' ') extra++;*/
    /*//get rid of all extra spaces but cutting the end off*/
    /*args[num_args - extra] = NULL;*/
/*}*/


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
