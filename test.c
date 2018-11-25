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
#include "test.h"

void print_arr( char** arr) {
	int i = 0;
	while (arr[i]) {
		printf("arg %d: [%s]\n", i, arr[i]);
        i++;
	}
}
	
