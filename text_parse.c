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

char is_redirect_pipe(char* c) {
    if (!strcmp(c, "<") || !strcmp(c, "<<") || !strcmp(c, "2<")) 
        return 1;
    if (!strcmp(c, "|"))
        return 2;
    return 0;
}


