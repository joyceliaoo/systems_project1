#ifndef text
#define text


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


// inputs:
// returns:
//
char is_redirect_pipe(char* c);

// inputs:
// returns:
//
int rp_mode( char* s);

// inputs:
// returns:
//
char count_redirect(char ** args);

// inputs:
// returns:
//
char count_pipe(char ** args);

char ** parse_rd_pipe(char ** args);

#endif
