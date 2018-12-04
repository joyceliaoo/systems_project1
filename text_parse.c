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
#include "text_parse.h"


//  counts num of args
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

//parse into an array of args
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
	while(args[string_offset]) {
		if (!is_space(args[string_offset][0])) { //only save the args that aren't spaces
			//printf("arg %d is not a space\n", string_offset);
			args[arg_count] = args[string_offset]; //keep if not a space
			arg_count++;
		}
		string_offset++;
	}
	args[arg_count] = NULL;
}

char is_space(char c) {
    return (c == 0 || c == ' ' || c == '\t' || c == '\0');
}

char is_redirect_pipe(char* c) {
    if (!strcmp(c, ">") || !strcmp(c, ">>") || !strcmp(c, "<"))
        return 1;
    if (!strcmp(c, "|"))
        return 2;
    return 0;
}

int rp_mode( char* s) {
    if (!strcmp(s, "|"))
        return 4;
    if (!strcmp(s, ">"))
        return 1;
    if (!strcmp(s, ">>"))
        return 2;
    if (!strcmp(s, "<"))
        return 3;
    return 0; //  not a redirect
}

char count_redirect(char ** args) {
	int i = 0;
	int num = 0;
	while(args[i]) {
		if (is_redirect_pipe(args[i]) == 1){
			num++;
			//printf("redirect found!\n");
		}
		i++;
	}
	return num;
}

char count_pipe(char ** args) {
	int i = 0;
	int num = 0;
	while(args[i]) {
		if (is_redirect_pipe(args[i]) == 2){
			num++;
			//printf("pipe found!\n");
		}
		i++;
	}
	return num;
}
