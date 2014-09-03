#ifndef SERVER_H
#define SERVER_H

#include <p1.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Server {
public:
	Server();

	void listen(int portNumber);
};

#endif