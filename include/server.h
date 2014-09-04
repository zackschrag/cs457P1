#ifndef SERVER_H
#define SERVER_H

#include <p1.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Server {
public:
	Server();

	void serverListen(int portNumber);
	void serverAccept(int socket, struct sockaddr * clientAddress, int * addressLength);
};

#endif