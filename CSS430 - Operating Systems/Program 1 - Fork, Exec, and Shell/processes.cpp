#include <stdio.h>
#include <iostream>
#include <unistd.h>    //for fork, pipe
#include <stdlib.h>    //for exit
#include <sys/wait.h>  //for wait
#include <string.h>
using namespace std;

int main(int argc, char ** argv) {

	int fd1[2], fd2[2], status; // file descriptors for pipes
	enum { RD, WR, ER }; //0 , 1 , 2
	pid_t pid, pid2;     //program id's

	if ((pipe(fd1)) < 0)  //create pipe
		perror("pipe error");
	else if ((pid = fork()) < 0) //child 1 forked
		perror("fork error");

	else if (pid == 0) { //child process

		if ((pipe(fd2)) < 0) //create pipe 2
			perror("pipe error");
		else if ((pid2 = fork()) < 0) //create child 2
			perror("fork error");

		else if (pid2 == 0) {//child 2 process 
			close(fd1[WR]);
			close(fd1[RD]);
			close(fd2[WR]);
			dup2(fd2[RD], 0); //child 2's read dupped to standard in
			execlp("wc", "wc", "-l", NULL);
		}
		else { //child 2 parent (child)
		close(fd1[WR]); 
		close(fd2[RD]);
		dup2(fd2[WR], 1); //write dupped to standard out for child 2
		dup2(fd1[RD], 0); //childs read dupped to standard input
		execlp("grep", "grep", argv[1], NULL);
		cout << "childs done" << endl;
		}
	}
	else { // parent process
		close(fd1[RD]); //Parents read closed
		dup2(fd1[WR], 1); //Parents write dupped to standard out for child
		execlp("ps", "ps", "-A" , NULL);
		wait( NULL);
		cout << "parents Done" << endl;
	}

	exit(EXIT_SUCCESS);
}
