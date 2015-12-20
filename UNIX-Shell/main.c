
#include "header.h"

int history_count = 0;
char *history[MAX_HISTORY];

int main(void){

	// argvs parameter is the array of character string of
	// each command line argument passed to executable on execution
	char *args[MAX_LINE/2 + 1]; // store the command line arguments
	char *buffer; // store an entire line from input stream
	size_t buffer_size = MAX_LINE;

	buffer = NULL;

	int should_run = 1;  // flag to determine when to exit program
	int N; // Nth command

	int i;
	for(i = 0; i < MAX_HISTORY; i ++){
		history[i] = NULL;
	}

	while(should_run){ // repeat until done
		/* display a prompt */
		printf("osh>");
		fflush(stdout);

		/* read in user input */
		getline(&buffer, &buffer_size, stdin);

		/* check if user just input Enter key */
		if(strlen(buffer) == 1 && buffer[strlen(buffer) - 1] == '\n') continue;

		/* check if user input a blank space and then Enter key */
		if(strcmp(buffer, " \n") == 0) continue;

		/* check if child needs to be run in background */
		int background = hasAmpersand(buffer); // equals 1 if a command is followed by '&' /

		if(buffer[strlen(buffer) - 1] == '\n'){
			buffer[strlen(buffer) - 1] = '\0'; // get rid of the '\n'
		}

		/* parse user input into arguments */
		parse(buffer, args);

		signal(SIGINT, INThandler);

		if(strcmp(args[0], EXIT) == 0){
			/* signal exit when use input is "exit" */
			should_run = 0;
		}
		else if(strcmp(args[0], HISTORY) == 0){
			/* print the last MAX_HISTORY history */
			getHistory();
		}
		else if(strcmp(args[0], "!!") == 0) {
			/* fetch most recent command from history */
			if(history_count == 0){
				printf("No commands in history.\n");
			}else{
				char *arg = getNthCommand(history, history_count);
				parse(arg, args); // parse command fetched from history into arguments

				putIntoHistory(arg); // place command into history
				history_count ++;
				execute(background, args);
			}
		}
		else if(args[0][0] == '!' && (N = parseNthCommand(args[0])) > 0){
			/* fetch Nth command from history */
			if(N > history_count){
				printf("No such command in history.\n");
			}else{
				char *arg = getNthCommand(history, N);
				parse(arg, args); // parse command fetched from history into arguments

				putIntoHistory(arg); // place command into history
				history_count ++;
				execute(background, args);
			}
		}
		else{
			/* otherwise, execute command from user input */
			putIntoHistory(buffer);
			history_count ++;
			execute(background, args);
		}
	}

	printf("Goodbye!\n");

	return 0;
}
