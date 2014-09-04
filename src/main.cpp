#include <p1.h>
#include <validator.h>
#include <client.h>
#include <server.h>

#define MAXPENDING 5
#define SERVPORT 2222

// scp -r P1 zackschr@olympia.cs.colostate.edu:~/cs457/P1/
int main(int argc, char **argv) {
	Validator v(argc, argv);
	//int portNumber = v.getPortNumber();
	socklen_t ClientLen;
	struct sockaddr_in ServAddr, ClientAddr;
	ServAddr.sin_family = PF_INET;
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServAddr.sin_port = htons(SERVPORT);
	int servSock;

	if (argc == 1) {
		//while (1) {
			cout << "Running as server." << endl;
			if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) >= 0) {
			cout << "servSock: " << servSock << endl;
			if (bind(servSock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) == 0) {
				cout << "binded" << endl;
				listen(servSock, MAXPENDING);
				cout << "listening on port " << SERVPORT << endl;
				ClientLen = sizeof(ClientAddr);
				if (accept(servSock, (struct sockaddr *) &ClientAddr, &ClientLen) < 0) {
					cerr << "Error accepting" << endl;
				}
				cout << "Accepted connection!" << endl;
				close(servSock);
			}
			else {
				cerr << "error binding" << endl;
			}
		//}
	}
		//Server s;
		//s.serverListen(2222);
	}
	else {
		cout << "Running as client." << endl;
		//int portNumber = v.getPortNumber();
		int clientSock;
		if ((clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
			cerr << "error creating socket" << endl;
		}
		cout << "clientSock: " << clientSock << endl;

		if (connect(clientSock,(struct sockaddr *) &ServAddr,sizeof(ServAddr)) < 0) {
			cerr << "error connecting to server" << endl;
		}
		cout << "connected!" << endl;
		close(clientSock);
		//Client c;
		//c.clientConnect();
	}
	return 0;
}