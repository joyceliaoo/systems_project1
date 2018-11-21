#ifndef shell
#define shell


//                      DEALING W TEXT

// inputs: char* line, char* delim
// returns: (unsigned int) number of tokens separated by @delim
// counts number of times @delim appears in @line, and adds 1.

unsigned int num_tokens(char* line, char* delim);


// inputs: char* line, char* delim
// returns: array of lineings where each entry is a token (from @str) seperated by @delim
// seperates @line into tokens by @delim, and returns a pointer to an array contining them

char** parse_line(char* line, char* delim, int num_tokens);

//                      ACTUAL COMMANDS

// inputs: char* d_name
// returns: nothing
// changes the current working directory to @d_name, will do nothing and print a message if it doesn't work 

void cd(char* d_name);

// inputs: none
// returns: nothing
// quits the terminal with an exit message

void quit();


#endif
