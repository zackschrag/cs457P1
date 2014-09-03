#ifndef SERVER_H
#define SERVER_H

#include <p1.h>

class Server {
public:
	Server();

	void listen(int portNumber);
};

#endif