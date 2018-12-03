# JOYCE AND HANNA'S SHELL!!

## currently working:
1. can handle multi-line commands
1. can handle multple redirects in one line
1. can handle: > >> < and |
1. can handle directory changing


## known bugs:

1. cannot handle multiple pipes or pipes mixed with redirects

## functions and descriptions:

``` C
// inputs: char* line, char* delim
// returns: (unsigned int) number of tokens separated by @delim
// counts number of times @delim appears in @line, and adds 1.

unsigned int num_tokens(char* line, char* delim);

// inputs: char* line, char* delim
// returns: array of lineings where each entry is a token (from @str) seperated by @delim
// seperates @line into tokens by @delim, and returns a pointer to an array contining them

char** parse_line(char* line, char* delim);

```



