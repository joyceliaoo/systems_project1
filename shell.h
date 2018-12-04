#ifndef shell
#define shell

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


#endif
