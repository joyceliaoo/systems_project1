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


unsigned int num_tokens(char* line, char* delim) {
	unsigned int ans = 0;
	while (*line) { // while were still in the string
		if (!strncmp(line, delim, 1)) {
			ans ++;
		}
		line ++;
	}
	return ans;
}



char** parse_line(char* line, char* delim) {
	char** args = malloc( num_tokens(line, delim) * sizeof(char*)); // make some space for the array
	char *s = strsep(&line, " ");
	int i = 0;
	while (s) {
		args[i] = s;	
		/*printf("%d : %s", i, ans[i]);*/
		s = strsep(&line, " ");
		i++;
	}
	return args;
}

	

