# ICS53Lab2

Hi there. Okay, so this is the git repo for the second project for ICS53.
We're going to be writing a shell that basically launches other programs.

There's code that the textbook provides that we can modify to suit our needs.
I'm going to check it out, and then commit it to this repo if that's the
route that we end up taking. I think that's a likely outcome, but I'll make 
sure that it's the case.

Relevant files from the text:
-csapp.h
-csapp.c
-shellex.c

The first two are a library of wrappers around C library functions.

You can find a link to the assignment description [here](https://eee.uci.edu/15s/36670/labs/lab2_shell.pdf).

The 4 main tasks of this project are as follows:
* Quit built-in command
* Foreground execution of external programs
* Background execution of external programs
* Redirection of standard input and output

Additionally, we must make sure that our shell is robust. The requirements are as follows:
* Input and command line format errors should not cause crashes
* Blank lines and extra white space should be handled without error
* Output an error if command executable does not exist in the local directory.

The first two tasks must be completed before the latter two. However, the latter two tasks can be done concurrently.

Changes will be *pushed* by each contributor. Keep in mind: this makes it easy to mess up the repository. Please use good
practices when developing. This includes (but is certainly not limited to): making (local) branches for features/fixes.
And only pushing your code to the repository when your fix or feature is completed. Remember to commit often ;).
