#include <server.h>

Server::Server() {
	cout << "server constructor" << endl;
}

void Server::listen(int portNumber) {
	cout << "listening" << endl;
	struct sockaddr_in ServAddr;
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServAddr.sin_port = htons(portNumber);
	int servSock;

	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		cout << "servSock: " << servSock << endl;
	}
	else {
		cout << "servSock: " << servSock << endl;
		if (bind(servSock, (struct sockaddr *) &ServAddr, sizeof(echoServAddr)) < 0) {
			cout << "bind < 0" << endl;
		}
		else {
			cout << "bind >= 0" << endl;
		}
	}
}