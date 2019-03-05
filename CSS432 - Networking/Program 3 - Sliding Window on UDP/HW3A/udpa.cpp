#include <iostream>
#include "UdpSocket.h"
#include "Timer.h"
#include <vector>
#include <stdlib.h> 
#include "udp.h"
using namespace std;


void sayHello() {
	cerr << "hello" << endl;
}

int clientStopWait(UdpSocket &sock, const int max, int message[]) {
	Timer time;
	cerr << "client: reliable test:" << endl;
	int resend = 0;
	// transfer message[] max times
	for (int i = 0; i < max; i++) {
		message[0] = i;                            // message[0] has a sequence #
		sock.sendTo((char *)message, MSGSIZE);// udp message send

		while (sock.pollRecvFrom() <= 0) {
			time.start();
			while (time.lap() < 1500) {
				if (sock.pollRecvFrom() > 0) {
					break;
				}
			}
			if (sock.pollRecvFrom() > 0) {
				break;
			}
			resend++;
			cerr << "sending again" << endl;
			sock.sendTo((char *)message, MSGSIZE);
		}
		sock.recvFrom((char *)message, MSGSIZE);

		cerr << "ACK = " << message[0] << endl;
	}
	return resend;
}
void serverReliable(UdpSocket &sock, const int max, int message[]) {
	cerr << "server reliable test:" << endl;

	// receive message[] max times
	for (int i = 0; i < max; i++) {
		sock.recvFrom((char *)message, MSGSIZE);   // udp message receive
												   /*if( i == 200 || i == 2000 || i == 15000) {
												   cerr << "waiting" << endl;
												   usleep((1500) + i);
												   } //TO TEST FAKE DROPS AT 200 2000 and 15000!*/
		while (message[0] != i) {
			sock.recvFrom((char *)message, MSGSIZE);
		}
		sock.ackTo((char *)message, MSGSIZE); //sendAck
		cerr << "ACK sent = " << message[0] << endl;                     // print out message
	}
}


int clientSlidingWindow(UdpSocket &sock, const int max, int message[],
	int windowSize) {
	// repeats sending message[] and receiving an acknowledgment at a
	// client side max (=20,000) times using the sock object.
	cerr << "Client Sliding Window..." << endl;
	int resend = 0;
	int i = 0;
	int unacked = 0;
	int lastAcked = 0;
	Timer time;
	while (i < max - 1) {
		// the client can continuously send a new message[] as incrementing
		// its sequence number as far as the number of in-transit messages
		while (unacked <= windowSize) {   // window has space
			if (i > max) {
				break;
			}
			message[0] = i;
			sock.sendTo((char *)message, sizeof(&message));
			//cerr << "Sending " << message[0] << endl;
			i++;
			unacked++;   //decrease window space
      
      
			if (sock.pollRecvFrom() > 0) {
				sock.recvFrom((char *)message, sizeof(&message));
				// cerr << "Received " << message[0] << endl;
				lastAcked = message[0];
				unacked--;   //increase open space once receieved
			}
		}
		while (unacked >= windowSize) {
			time.start();
			while (time.lap() < 1500) {
				if (sock.pollRecvFrom() > 0) {
					break;
				}
			}
			if (sock.pollRecvFrom() > 0) {
				sock.recvFrom((char *)message, sizeof(&message));
				// cerr << "Received " << message[0] << endl;
				lastAcked = message[0];
				unacked--;   //increase open space once receieved
			}
			else {
				resend++;
				message[0] = lastAcked + 1;
				if (message[0] >= max) {
					message[0] = 19999;
				}
				//cerr << "sending again" << endl;
				sock.sendTo((char *)message, sizeof(&message));
			}
		}
	}
	// The function must count the number of messages retransmitted
	// and return it to the main function as its return value.
	return resend;
}


void serverEarlyRetrans(UdpSocket &sock, const int max, int message[],
	int windowSize, int n) {
	cerr << "server Early Retransmit..." << endl;
	int lam = 0;    // Last Acknowledged message
	int wStart = 0;
	int wEnd = wStart + windowSize;
	cerr << "wStart: " << wStart << " wEnd: " << wEnd << "  windowSize: " << windowSize << endl;
	vector<int> window(max); // cumulative acknowledgement
	for (int i = 0; i < max; i++) { 	//init window
		window[i] = -1;
	}
	// repeats receiving message[] and sending an acknowledgment at a
	// server side max (=20,000) times using the sock object.
	while (lam < max - 1) {
		while (sock.pollRecvFrom() <= 0) {
			usleep(1);
		}				// pause until message

		sock.recvFrom((char *)message, MSGSIZE);   	// udp message receive
													//cerr << "recieving: " << message[0] << "  ";
		window[message[0]] = 1;    
                                                          
    
		// Every time the server receives a new message[], it must memorizes this
		// message's sequence number in its array and
		// returns a cumulative acknowledgment
		for (int i = wStart; i <= wEnd; i++) {
			//cerr << i << " "  << window[i] << "  ";
			if (window[i] > 0) {
				lam = i;
			}
			else if (window[i] < 0) {
				break;
			}
		}
    int R = rand() % 100;  //randomly drop n% packets
    if(R < n) {
    } else {
  		message[0] = lam;
      
  		sock.ackTo((char *)message, MSGSIZE); //sendAck
  		wStart = lam;
  		wEnd = wStart + windowSize;
  		if (wEnd > max) {
  			wEnd = max - 1;
  		}
   }


	}
}