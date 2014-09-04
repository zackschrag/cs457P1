#include <client.h>

Client::Client() {
	cout << "client constructor" << endl;
}

void Client::clientConnect(int socket, struct sockaddr * clientAddress) {
	/*if (connect(socket, clientAddress) < 0) {
		cerr << "connection failed" << endl;
	}
	else {
		cout << "connected!" << endl;
	}*/
}