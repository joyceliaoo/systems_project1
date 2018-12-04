# JOYCE AND HANNA'S SHELL!!

## currently working:
1. can handle multi-line commands
2. can handle two redirects in one line
3. can handle >, >>, <, and |
4. can change current working directory
5. can handle weird spacing and tabs in given commands
6. can exit

## attempted but unsuccessful:
1. handling more than 1 pipe

## known bugs:
1. cannot handle multiple pipes or pipes mixed with redirects
2. unpredictable behavior when too many arguments are given/ arguments are too long in length
3. prints extra command prompts when running `./shell < test_commands`
4. (maybe not a bug) doesn't treat a string like "ls\t\t-l" as "ls -l"

## functions and descriptions:
### text_parse.c
``` C
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
```
### test.c
``` C
//						TESTING

// inputs: char** arr
// returns: nothing
// prints out the elements in arr

void print_arr(char ** arr);
```
### shell.c
``` C
//                      SOME AESTHETICS

// inputs: none
// returns: none
// prints out the prompt, with cwd
void print_prompt();

//                      RUNNING THE THING

// inputs: char** args
// returns: 3 if command is exit, 2 if command is cd, values returned by redirect(), ter_pipe(), or execvp()
// executes given args, unless exit or cd, which is handled by the parent
int run(char** args);

// inputs: char ** args, char num (number of redirects there are)
// returns: 0 if run with no errors, 1 if redirect type is < and given file does not exist
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
```
