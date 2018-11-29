#ifndef shell
#define shell

//                      SOME AESTHETICS

// inputs: none
// returns: none
// prints out the prompt, with cwd
void print_prompt();

//                      RUNNING THE THING

// inputs: char** args
// returns: 1 if command is exit, 2 if command is cd
// executes given args otherwise
// runs the commands given

int run(char** args);

int redirect(char** args1, char* file, char mode);

int ter_pipe(char** args1, char** args2);


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
