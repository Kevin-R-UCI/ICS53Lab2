/* $begin shellmain */
#include "csapp.h"
#define MAXARGS   128

/* function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv, char **redirect_in, char **redirect_out);
int builtin_command(char **argv); 

int main() 
{
    char cmdline[MAXLINE]; /* Command line */

    while (1) {
	/* Read */
	printf("> ");                   
	Fgets(cmdline, MAXLINE, stdin); 
	if (feof(stdin))
	    exit(0);

	/* Evaluate */
	eval(cmdline);
    } 
}
/* $end shellmain */
  
/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline) 
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    
    strcpy(buf, cmdline);
    char *redirect_in = NULL, *redirect_out = NULL;
    bg = parseline(buf, argv, &redirect_in, &redirect_out); 
    if (argv[0] == NULL)  
	return;   /* Ignore empty lines */

    if (!builtin_command(argv)) { 
	if ((pid = Fork()) == 0) {   /* Child runs user job */
		if(redirect_in != NULL) {
			FILE *in = Fopen(redirect_in, "r");
			dup2(fileno(in), fileno(stdin));
		}
		if(redirect_out != NULL) {
			FILE *out = Fopen(redirect_out, "w");
			dup2(fileno(out), fileno(stdout));
		}
	    if (execve(argv[0], argv, environ) < 0) {
		printf("%s: Command not found.\n", argv[0]);
		exit(0);
	    }
	}

	/* Parent waits for foreground job to terminate */
	if (!bg) {
	    int status;
	    if (waitpid(pid, &status, 0) < 0)
		unix_error("waitfg: waitpid error");
	}
	else
	    printf("%d %s", pid, cmdline);
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
    if (!strcmp(argv[0], "quit")) /* quit command */
	exit(0);  
    if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
	return 1;
    return 0;                     /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv, char **redirect_in, char **redirect_out) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* Ignore spaces */
	       buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* Ignore blank line */
	return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;
	
	//redirect input/output
	if(argc > 2) {
		if(*argv[argc-2] == '<' || *argv[argc-2] == '>') {
			printf("redirecting ");
			if(*argv[argc-2] == '<') {
				printf("input to %s\n", argv[argc-1]);
				*redirect_in = argv[--argc];
				argv[--argc] = NULL;
			} else if(*argv[argc-2] == '>') {
				printf("output to %s\n", argv[argc-1]);
				*redirect_out = argv[--argc];
				argv[--argc] = NULL;
			}
		}
	}
	if(argc > 2) {
		if(*argv[argc-2] == '<' || *argv[argc-2] == '>') {
			if(*argv[argc-2] == '<') {
				*redirect_in = argv[--argc];
				argv[--argc] = NULL;
			} else if(*argv[argc-2] == '>') {
				*redirect_out = argv[--argc];
				argv[--argc] = NULL;
			}
		}
	}
    
    return bg;
}
/* $end parseline */


