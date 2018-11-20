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


int main() {
	
	// testing code:
	printf("testing num_tokens\n");
	printf("expected: 2; actual: %d\n", num_tokens("ahjfdf fsdfdsf ", " "));
	printf("expect: 6; actual: %d\n", num_tokens("ahjfdf f sd f d sf ", " "));

	return 0;
}

