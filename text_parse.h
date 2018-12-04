#ifndef text
#define text


//                      DEALING W TEXT

// inputs: char* line, char* delim
// returns: (unsigned int) number of tokens separated by @delim
// counts number of times @delim appears in @line, and adds 1.

unsigned int num_tokens(char* line, char* delim);


// inputs: char* line, char* delim, num_tokens
// returns: array of strings where each entry is a token (from @str) seperated by @delim
// seperates @line into tokens by @delim, and returns a pointer to an array contining them

char** parse_line(char* line, char* delim, int num_tokens);

// inputs: char** args
// returns: char** that has everything in args, but with the whitespace trimmed off on either end
// trims off whitespace: \t, spaces, etc and other random stuff

void trim(char** args);

// inputs: char c
// returns: 1 if c is some sort of white space charactere, 0 otherwise
// checks to see if c is '\t' or ' '

char is_space(char c);


// inputs: char *c
// returns: 1 if c is a redirect, 2 if c is a pipe, 0 otherwise
// checks if the given string is a redirect or pipe
char is_redirect_pipe(char* c);

// inputs: char *s
// returns: 1 if s is >, 2 if s is >>, 3 if s is <, 4 if s is |, 0 otherwise
// identifies the presence and type of a redirect or pipe
int rp_mode( char* s);

// inputs: char **args
// returns: sum of how many times is_redirect_pipe() returns 1 when each element in given array is passed as an argument
// counts total number of any type of redirection in the given array of args
char count_redirect(char ** args);

// inputs: char **args
// returns: sum of how many times is_redirect_pipe() returns 2 when each element in given array is passed as an argument
//counts total number of pipes in the given array of args
char count_pipe(char ** args);

#endif
