#include <iostream>
#include "UdpSocket.h"
using namespace std;
#pragma once
//method declarations
void sayHello();
int clientStopWait(UdpSocket &sock, const int max, int message[]);
void serverReliable(UdpSocket &sock, const int max, int message[]);
int clientSlidingWindow(UdpSocket &sock, const int max, int message[],
	int windowSize);
 void serverEarlyRetrans(UdpSocket &sock, const int max, int message[],
	int windowSize, int n);
