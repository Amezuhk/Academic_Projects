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
#include <fstream>
#include <cstdlib>
#include <pthread.h>
#include <cstring>
#include <errno.h>
#include <sys/time.h>
#include <iterator>

using namespace std;

void *respond(void * thread);

string badReq = "HTTP/1.0 400 Bad Request\r\nContent-Length: 54\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
string notFound = "HTTP/1.0 404 File Not Found\r\nContent-Length: 54\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";

string ok = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";

int main (int argc, char* argv[]) {
  //Get Arguments and set Local Vars 
	const int server_port = 5555;
 
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
	listen(serverSd, 5);

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
 string toSend = "";
  //set up buffer
	char databuf[3000];
  bzero((char *) databuf, sizeof(databuf));
  read( newSd, databuf , 3000 );
  string msg = databuf;
  int written;
  cout << msg;
  int left = msg.find("GET");
		if (left < 0) {
			//not a valid request
   //   cout << "not found" << endl;
      toSend = badReq;
        ifstream myfile("badReq.html");
        string str((istreambuf_iterator<char>(myfile)),
                 istreambuf_iterator<char>());
        toSend += str;
        char toWrit[toSend.size() + 1];
    //    cout << toSend << endl;
        strcpy(toWrit, toSend.c_str());
        written = write( newSd, toWrit, (toSend.size() + 1));
        close(newSd);
        return NULL;
		}
    left = msg.find("/");
		int right = msg.find(" ", left);
  //  cout << left << "  " << right << endl;
		string temp = msg.substr(left + 1, (right - left) - 1);
   // cout <<"Temp is: " << temp << endl;
    //cout << "found" << endl;
    ifstream myfile1(temp.c_str());
    if(myfile1.good()) {
      //cout << "is good" << endl;
      toSend = ok;
      string str1((istreambuf_iterator<char>(myfile1)),
             istreambuf_iterator<char>());
      toSend += str1;
      char toWrit1[toSend.size() + 1];
      //cout << toSend << endl;
      strcpy(toWrit1, toSend.c_str());
      written = write( newSd, toWrit1, (toSend.size() + 1));
      close(newSd);
      return NULL;
    }else {
      toSend = notFound;
     // cout << "is not good" << endl;
      ifstream myfile2("notFound.html");
      string str2((istreambuf_iterator<char>(myfile2)),
             istreambuf_iterator<char>());
      toSend += str2;
      char toWrit2[toSend.size() + 1];
      //cout << toSend << endl;
      strcpy(toWrit2, toSend.c_str());
      written = write( newSd, toWrit2, (toSend.size() + 1));
  	  close(newSd);
       return NULL;
    }

}
