#ifndef CLIENT_H
#define CLIENT_H

#include <p1.h>

class Client {
public:
	Client();

	void clientConnect(int portNumber, struct sockaddr * clientAddress);
};

#endif