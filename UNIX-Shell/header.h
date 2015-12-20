/*
 * header.h
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_LINE 80
#define MAX_HISTORY 10 /* maximum number of commands stored in history */

#define EXIT "exit"
#define HISTORY "history"

extern char *history[MAX_HISTORY]; /* store command line input history */
extern int history_count; /* store the number of command line already input by user */

int parse(char*, char*[]); /* parse command line into separate argument */
int hasAmpersand(char*); /* check if command line included ampersand */
void execute(int, char*[]); /* execute command line */
void INThandler(int); /* handle Ctrl + C signal */

void getHistory(); /* list command history */
int parseNthCommand(char*); /* parse command line if starting with '!', return integer N */
char* getNthCommand(char*[], int); /* fetch Nth command line from history */
void putIntoHistory(char*); /* insert last executed command line into history */
