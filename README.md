# JOYCE AND HANNA'S SHELL!!

## currently working:
1. can handle multi-line commands
1. can handle multple redirects in one line
1. can handle: > >> < and |
1. can handle directory changing


## known bugs:

1. cannot handle multiple pipes or pipes mixed with redirects
1. unpredictable behavior when too many arguments are given/ arguments are too long in length
1. prints extra command prompts when run with test_commands

## functions and descriptions:

``` C
//                          IN SHELL.H

//                      SOME AESTHETICS

// inputs: none
// returns: none
// prints out the prompt, with cwd
void print_prompt();

//                      RUNNING THE THING

// inputs: char** args
// returns: 3 if command is exit, 2 if command is cd, execvp otherwise
// executes given args, unless exit or cd, which is handled by the parent

int run(char** args);

// inputs: char ** args, char num (number of redirects there are) 
// returns: 0 if run with no errors
// runs strings of redirects
int redirect(char** args, char num);

// inputs: char ** args, char num 
// returns: 0 if run with no errors
// runs two pipes
int ter_pipe(char** args1, char num);


//                      ACTUAL COMMANDS

// inputs: char* d_name
// returns: nothing
// changes the current working directory to @d_name, will do nothing and print a message if it doesn't work

void cd(char* d_name);

// inputs: none
// returns: nothing
// quits the terminal with an exit message

void quit();

//                  IN TEST.H
//						TESTING

// inputs: char** arr
// returns: nothing
// prints out the elements in arr

void print_arr(char ** arr);

//                  IN TEXT_PARSE.H
//                      DEALING W TEXT
//

// inputs: char* line, char* delim
// returns: (unsigned int) number of tokens separated by @delim
// counts number of times @delim appears in @line, and adds 1.

unsigned int num_tokens(char* line, char* delim);


// inputs: char* line, char* delim, num_tokens
// returns: array of strings where each entry is a token (from @str) seperated by @delim
// seperates @line into tokens by @delim, and returns a pointer to an array contining them

char** parse_line(char* line, char* delim, int num_tokens);

// inputs: char** args
// returns: char** where if there were any redirect or pipe characters in the array, they would be seperated out
// eg: ["ls>hm"] would become ["ls",">","hm"]
char** parse_rp(char** args);


// inputs: char** args
// returns: char** that has everything in args, but with the whitespace trimmed off on either end
// trims off whitespace: \t, spaces, etc and other random stuff

void trim(char** args);

// inputs: char c
// returns: 1 if c is some sort of white space charactere, 0 otherwise
// checks to see if c is '\t' or ' '

char is_space(char c);


// inputs: char *c
// returns: 1 if *c is some sort of redirect, 2, if it is a pipe, 0 otherwise
char is_redirect_pipe(char* c);

// inputs: char* s
// returns: 1 if *s is >, 2 for >>, 3 for <, 4 for |, 0 if not a redirect
int rp_mode( char* s);

// inputs: char** args
// returns: number of redirect characters: (<, >, >>)
char count_redirect(char ** args);

// inputs: char** args
// returns: number of pipe characters 
char count_pipe(char ** args);
```



