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
#include <cstring>
#include <errno.h>
#include <sys/time.h>

using namespace std;

int main (int argc, char* argv[]) {
  //Get Arguments and set Local Vars 
	int server_port = atoi(argv[1]);
  string serverip = argv[5];
 	char server_name[serverip.size() + 1];
  strcpy(server_name, serverip.c_str());
  int reps = atoi(argv[2]);
  int nbufs = atoi(argv[3]);
  const int bufsize = atoi(argv[4]);
  int type = atoi(argv[6]);
  
  cout << "Port: " << server_port << " Repetition: " << reps
     << " Number of Data Buffers: " << nbufs << " Buffer Size: "
     << bufsize << " Server IP Name: " << server_name << " Scenario Type: "
     << type << endl;
  //check buffer sizes nbufs * buffsize
  if(nbufs * bufsize > 1500) {
     cout<< "Buffer size exceeded...Exiting";
     return -1;
  }
  //create buffer
  char databuf[nbufs][bufsize];
  
	// figure out the IP address
	struct hostent* host = gethostbyname(server_name);
 
	// set up the data structure
	sockaddr_in sendSockAddr;
	bzero((char*) &sendSockAddr, sizeof(sendSockAddr));
	sendSockAddr.sin_family = AF_INET;
	sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
	sendSockAddr.sin_port = htons(server_port);

	// create the socket
	int clientSd = socket(AF_INET, SOCK_STREAM, 0);

	// connect <-- this makes me a client!
	int connectStatus = connect(clientSd, (sockaddr*)&sendSockAddr, sizeof(sendSockAddr));
	if(connectStatus < 0) {
		printf("Failed to connect");
		return -1;
	}
 
  //START Test
  struct timeval startTime, lap, stop;
  gettimeofday(&startTime, NULL); //Timer start
  
  for(int j = 0; j < reps; j++) {
    if(type ==1) { //CASE: 1
    	for(int i = 0; i < nbufs; i++) {
       	int write_result = write( clientSd, databuf[i], bufsize );
      }
        
    }else if(type == 2) { //CASE: 2
       struct iovec vector[nbufs];
       for ( int i = 0; i < nbufs; i++ ) {
         vector[i].iov_base = databuf[i];
         vector[i].iov_len = bufsize;
       }
       writev( clientSd, vector, nbufs );  
    }else { //CASE: 3
      write( clientSd, databuf, nbufs * bufsize );
    }
  }
  
  gettimeofday(&lap, NULL);   //lap time'
  
  int count;
  read(clientSd, &count, sizeof(count));
  
  gettimeofday(&stop, NULL);  // stop time
  long lapTime, totalTime;
  lapTime = (lap.tv_sec - startTime.tv_sec) * 1000000;  //gen lap time
  lapTime += (lap.tv_usec - startTime.tv_usec);
  totalTime = (stop.tv_sec - startTime.tv_sec) * 1000000;
  totalTime += (stop.tv_usec - startTime.tv_usec);
  
  
    
	cout << "This is count: " << count << endl;
  cout << "Lap Time: " << lapTime << " usec  Total Time: " << totalTime << " usec" << endl;
	close(clientSd);
	return 0;
}





















