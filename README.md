# JOYCE AND HANNA'S SHELL!!

## currently working:
1. can parse text!


## known bugs:

1. a command like echo "hmm help" mght not work 

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



