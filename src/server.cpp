#include <server.h>
#define MAXPENDING 5;
Server::Server() {
	cout << "server constructor" << endl;
}

void Server::serverListen(int portNumber) {
	cout << "listening" << endl;
/*	struct sockaddr_in ServAddr;
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServAddr.sin_port = htons(portNumber);
	int servSock;
*/
/*	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) >= 0) {
		cout << "servSock: " << servSock << endl;
		if (bind(servSock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) == 0) {
			if (listen(servSock, MAXPENDING) == 0) {
				cout << "listening on port " << portNumber << endl;
			}
		}
	}*/
}

void Server::serverAccept(int socket, struct sockaddr * clientAddress, int * addressLength) {
	/*clientSock = accept(socket, (struct sockaddr*) &clientAddress, sizeof(clientAddress));
	if (clientSock >= 0) {
		cout << "clientSock = " << clientSock << endl;
	}*/
}