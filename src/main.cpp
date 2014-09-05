#include <p1.h>
#include <validator.h>
#include <client.h>
#include <server.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

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
	}
		//Server s;
		//s.serverListen(2222);
	}
	else {
		cout << sizeof(char) << endl;
		struct addrinfo hints, *res;
		struct packet {
			uint16_t version;
			uint16_t stringLength;
			char data[60];
		};
		int sockfd;

		uint16_t version = 457;
		//unsigned short stringLength = 56;


		memset(&hints, 0, sizeof(hints));
		hints.ai_family = PF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;

		getaddrinfo("129.82.46.233", v.getPortNumberAsString().c_str(), &hints, &res);

		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

		if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
			cerr << "error connecting" << endl;
		}
		char input[140];
		cout << "Connected to a friend! You send first." << endl;
		cin >> input;

		packet newPacket;
		newPacket.version = version;
		newPacket.stringLength = strlen(input);
		memcpy(newPacket.data, input, strlen(input)+1);

		send(sockfd, &newPacket, (uint16_t) 60, 0);

		/*cout << "Running as client." << endl;
		//int portNumber = v.getPortNumber();
		int clientSock;
		if ((clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
			cerr << "error creating socket" << endl;
		}
		cout << "clientSock: " << clientSock << endl;

		ServAddr.sin_addr.s_addr = htonl(inet_addr(v.getServerIP().c_str()));
		ServAddr.sin_port = htons(v.getPortNumber());
		if (connect(clientSock,(struct sockaddr *) &ServAddr,sizeof(ServAddr)) < 0) {
			cerr << "error connecting to server" << endl;
		}
		cout << "connected!" << endl;
		close(clientSock);
		//Client c;
		//c.clientConnect();*/
	}
	return 0;
}