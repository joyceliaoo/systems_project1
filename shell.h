#ifndef shell
#define shell


// inputs: char* line, char* delim
// returns: (unsigned int) number of tokens separated by @delim
// counts number of times @delim appears in @line, and adds 1.

unsigned int num_tokens(char* line, char* delim);


// inputs: char* line, char* delim
// returns: array of lineings where each entry is a token (from @str) seperated by @delim
// seperates @line into tokens by @delim, and returns a pointer to an array contining them

char** parse_line(char* line, char* delim);



#endif
