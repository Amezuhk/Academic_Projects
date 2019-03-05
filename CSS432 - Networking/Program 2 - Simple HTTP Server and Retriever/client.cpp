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
#include <vector>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <sys/time.h>

using namespace std;

int main (int argc, char* argv[]) {
  //Get Arguments and set Local Vars 
	int server_port = 80;
  string serverip = argv[1];
 	char server_name[serverip.size() + 1];
  strcpy(server_name, serverip.c_str());
  
  string fileName = argv[2];
 	char file_name[fileName.size() + 1];
  strcpy(file_name, fileName.c_str());
  

  
  //cout << "Port: " << server_port << " Server Name: " << server_name << " fileName: "
     //<< fileName << endl;

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
  
  string get = "GET /" + fileName + " HTTP/1.1\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\nHost: " + serverip + "\r\nAccept-Language: en-us\r\nConnection: Keep-Alive\r\n\r\n";
  //cout << get;
  char getReq[get.size() + 1];
  strcpy(getReq, get.c_str());
  
  int written = write( clientSd, getReq, (get.size() + 1) );
  ofstream myfile;
  myfile.open("example1.html");
  char buf[3000];
  string response = "";
  while (read(clientSd, buf, 3000) > 0) {
    response += buf;
  }
  cout << response << endl;
  string toFile = response; 
  int toF = toFile.find("\r\n\r\n");
  toFile.replace(0, toF, "");
  myfile << toFile;
  myfile.close();
  //cout << buf << endl;
 // cout <<response;
  vector<string> toGet;
  //cout << response;
  string temp = "";
  
	while (true) { //find all image tags 
		int left = response.find("<img");
		if (left < 0) {
			break;
		}
		int right = response.find('>', left);
		temp = response.substr(left, (right - left) + 1);
		response.replace(left, temp.size(), "X");
		toGet.push_back(temp);
	}
 
	/*while (true) { //find all script tags
  	int left = response.find("<script");
  	if (left < 0) {
  		break;
  	}
  	int right = response.find('>', left);
  	temp = response.substr(left, (right - left) + 1);
  	response.replace(left, temp.size(), "X");
  	toGet.push_back(temp);
	}*/
 
 for (int i = 0; i < toGet.size(); i++) { //parse img tags to get image name to get
		string toget = toGet[i];
		int left = toget.find("src=");
		int right = toget.find('"', (left + 5));
		temp = toget.substr(left + 5, (right - left) - 5);
    cout << temp << endl;
    }
	/*for (int i = 0; i < toGet.size(); i++) { //issue a get for img, does not work
		string toget = toGet[i];
		int left = toget.find("src=");
		int right = toget.find('"', (left + 5));
    cout << left << "  " << right << endl;
		temp = toget.substr(left + 5, (right - left) - 5);
    cout << temp << endl;
    get = "GET " + temp + " HTTP/1.1\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\nHost: " + serverip + "\r\nAccept-Language: en-us\r\nConnection: Keep-Alive\r\n\r\n";
    char togetReq[get.size() + 1];
    strcpy(togetReq, get.c_str());
    cout << togetReq << endl;
    int writ = write( clientSd, togetReq, (get.size() + 1) );
    toget = "";
    while (read(clientSd, buf, 3000) > 0) {
      toget += buf;
   }
   cout << toget << endl;
   /*toF = toget.find("\r\n\r\n");
   toget.replace(0, toF, "");
   ofstream getfile;
   getfile.open("example3.html");
   getfile << toget;
   getfile.close();
   
  //cout << get;
	}*/
  
	close(clientSd);
	return 0;
}





















