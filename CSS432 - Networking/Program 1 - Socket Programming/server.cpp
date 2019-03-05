#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <strings.h>
#include <netinet/tcp.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>

using namespace std;

void *respond(void * thread);

int reps = 0;

int main (int argc, char* argv[]) {
  //Get Arguments and set Local Vars 
	const int server_port = atoi(argv[1]);
	const int n = 5; 
	reps = atoi(argv[2]);
 
	// Lets get the data structures set up
	sockaddr_in acceptSockAddr;
	bzero((char*)&acceptSockAddr, sizeof(acceptSockAddr));
	acceptSockAddr.sin_family = AF_INET;
	acceptSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	acceptSockAddr.sin_port = htons(server_port);

	// create a socket
	int serverSd = socket(AF_INET, SOCK_STREAM, 0);

	// make it so that we can keep reusing this socket without waiting for the OS to clean up
	const int on = 1;
	setsockopt(serverSd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(int));

	// bind to the address
	bind(serverSd, (sockaddr*)&acceptSockAddr, sizeof(acceptSockAddr));

	// listen on that socket <-- this is what makes us a server!
	listen(serverSd, n);

	// get read to accept a new connectionf rom a client
	sockaddr_in newSockAddr;
	socklen_t newSockAddrSize = sizeof(newSockAddr);

	while(1) { //Main Loop: Accept New Connections and spawn new threads to handle them
	int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
	printf("Received Connection\n");
	pthread_t newThread;
	pthread_create (&newThread, NULL, respond, (void *) &newSd);

	}	
	close(serverSd);
	return 0;
}

//Called when new Thread is created
//@Param thread = Socket Descriptor of connection being handeled
void *respond(void * thread) {
  //get sd from thread
	int * sd;
	sd = (int *) thread;
	int newSd = *sd;
  //set up buffer
	const int BUFSIZE = 1500;
	char databuf[BUFSIZE];
  bzero((char *) databuf, sizeof(databuf));
  
  int count = 0; //how many times read is called
	int nRead = 0; //keep track of num of bytes read for each read 
  struct timeval startTime, stopTime; //Time Tracking
 
  gettimeofday(&startTime, NULL); //Start
  
  for(int i = 0; i < reps; i++) { //Read for Reps
    for (nRead = 0; 
              ( nRead += read( newSd, databuf , BUFSIZE - nRead ) ) < BUFSIZE; 
              ++count );
  }
  
  gettimeofday(&stopTime, NULL); //Stop time, Time it took to read
  
  long time;
  time = (stopTime.tv_sec - startTime.tv_sec) * 1000000;
  time += (stopTime.tv_usec - startTime.tv_usec);
	cout << "This is count: " << count << endl;
  cout << "This is the time it took to recieve: " << time << " usec" << endl; 

	int nWrite = write(newSd, &count, sizeof(count)); //Send number of times read was called back to client
	if (nWrite < 0) {
		printf("Write Error\n");
		return NULL;
	}
	close(newSd);
}
