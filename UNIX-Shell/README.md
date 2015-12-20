
This project consists of designing a C program to serve as a shell interface that accepts user commands and then executes each command in a separate process. 

## BUILDING
After extracting the tarball, run:
	`make cshell`
	
## EXECUTION 

After building is finished, run the program via:
	`./cshell`

##FEATURES
 
- To exit command line: 
	`exit `

* To enter commands (examples tested): 
	`ps, ls -l, top, cal, who, date`

- To create child process: 
	`ls& `

- To list command history (MAX set to 10): 
	`history `

- To execute the most recent command: 
	`!!`

- To execute Nth command in the history: 
	`! followed by an integer N`

- Error handling: 

     If a command is not found, the program will output the command just entered with `"command not found..."`. 

	If user just input Enter key, or input a blank space and then Enter key, no action will be taken except printing the prompt in a new line. 

	If there are no commands in the history, entering `!!` will result in a message `“No commands in history.”` If there is no command corresponding to the number entered with the single !, the program will output `"No such command in history."`
