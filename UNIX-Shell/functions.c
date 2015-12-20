#include "header.h"

int parse(char *buffer, char *args[]){

	int count = 0;
	while(*buffer != '\0'){ //if not the end of line
		while(*buffer == ' ' || *buffer == '\t'){
			*buffer = '\0'; buffer ++; // replace white spaces with 0
		}
		if(*buffer == '\0') break;
		args[count] = buffer; // save the argument position
		count ++;
		while (*buffer != '\0' && *buffer != ' ' &&
		                 *buffer != '\t' ){
			buffer ++;
		}
	}

	args[count] =  NULL; // **  mark the end of argument list
	return count; // return numbder of arguments
}

int hasAmpersand(char *buffer){

	int i = strlen(buffer) - 1;
	while(i >= 0 && (buffer[i] == ' ' || buffer[i] == '\n')){
		i --;
	}

	if(buffer[i] == '&'){
		buffer[i] = '\0';
		return 1;
	}
	return 0;
}

void execute(int background, char *args[]){

	pid_t pid;
	pid = fork();
	if(pid < 0){
		printf("Fork Child Process Failed!\n");
		return;
	}else if(pid == 0){ // child process

		int res = execvp(args[0], args);

		if (res < 0) {  // handle command not found
		    printf("%s: command not found...\n", args[0]);
		    return;
		}
	}else if(background == 1){
		printf("[%d]\n", getpid());
	}else if(background == 0) {
		// parent process:  only wait if no ampersand;
		// if background == 0, parent will wait child process
		waitpid(pid, NULL, 0);
		// printf("Child Completed\n");
	}
}

void getHistory(){
	int count = history_count;

	count --;

	int j;
	for(j = 0; j < MAX_HISTORY ; j ++ ){
		int i = count%MAX_HISTORY;

		if(count >= 0 && history[i] != NULL){
			printf("%d %s\n", count + 1, history[i]);
		}
		count --;
	}
}

int parseNthCommand(char *arg){
	char *c = arg;
	c++;
	return atoi(c);
}

char* getNthCommand(char *history[], int N){
	int i = (N - 1)%MAX_HISTORY;
	return history[i];
}

void putIntoHistory(char* arg){
	char *copy;
	copy = malloc(sizeof(char) * strlen(arg));
	strcpy(copy,arg);
	int curr = (history_count) % MAX_HISTORY;
	history[curr] = strdup(arg);
}

void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("\nquit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y'){
    	 exit(0);
     }
     else{
    	 signal(SIGINT, INThandler);
     }
}
