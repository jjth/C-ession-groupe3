/*
readLines.h
-----
By Julien Couillard
Role : prototypes of the functions of the parser of rules.
*/

// main function
void ask_lines();

// send function 
void send_to_network(char* line, int id);

// utils 
void fflush_stdin();
static void purge(void);
static void clean (char *str);