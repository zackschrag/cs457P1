#ifndef SERVER_H
#define SERVER_H

#include <p1.h>

class Server {
public:
	Server();

	void serverListen(int portNumber);
	void serverAccept(int socket, struct sockaddr * clientAddress, int * addressLength);
};

#endif