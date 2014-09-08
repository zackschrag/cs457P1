#include <validator.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXPENDING 5
#define SERVPORT 2000

int main(int argc, char **argv) {
	Validator v(argc, argv);
	socklen_t ClientLen;
	struct sockaddr_in ServAddr, ClientAddr;
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServAddr.sin_port = htons(SERVPORT);
	int serverPort = SERVPORT;
	int servSock;
	short version = 457;

	struct packet {
		short version;
		short stringLength;
		char data[140];
	};

	if (argc == 1) {
		cout << "Welcome to Chat!" << endl;
		char ipAddress[128];
		gethostname(ipAddress, sizeof(ipAddress));
		struct hostent *h;
		if((h=gethostbyname(ipAddress) ) == NULL ){
     		cerr << "Error getting IP address. Please try again." << endl;
     		v.printUsage();
      		exit(1);
    	}

		if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
			cerr << "Error creating socket." << endl;
			v.printUsage();
			exit(1);
		}
		while (bind(servSock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0) {
			serverPort++;
			ServAddr.sin_port = htons(serverPort);
		}
		cout << "Waiting for a connection on " <<  inet_ntoa(*((struct in_addr *)h->h_addr)) << " port " << serverPort << endl;
		listen(servSock, MAXPENDING);
		ClientLen = sizeof(ClientAddr);
		int newSock;
		if ((newSock = accept(servSock, (struct sockaddr *) &ClientAddr, &ClientLen)) < 0) {
			cerr << "Error accepting connection." << endl;
			v.printUsage();
			exit(1);
		}

		int ctr = 0;

		while (1) {
			char incomingBuffer[144];
			char outgoingBuffer[144];
			char input[140];
			string tempInput;
			
			packet incomingPacket;
			packet outgoingPacket;
			if (ctr == 0) {
				cout << "Found a friend! You receive first." << endl;
			}
			cout << "Friend: ";
			recv(newSock, incomingBuffer, sizeof(incomingBuffer), 0);
			memcpy(&incomingPacket.version, incomingBuffer, 2);
			memcpy(&incomingPacket.stringLength, incomingBuffer+2, 2);
			incomingPacket.version = ntohs(incomingPacket.version);
			incomingPacket.stringLength = ntohs(incomingPacket.stringLength);
			memcpy(incomingPacket.data, incomingBuffer+4, incomingPacket.stringLength);
			for (int i = 0; i < incomingPacket.stringLength; i++) {
				cout << incomingPacket.data[i];
			}
			cout << endl;
			cout << "You: ";
			getline(cin, tempInput);
			memcpy(input, tempInput.c_str(), sizeof(input));

			while (strlen(input) > 140) {
				cerr << "Error: message needs to be less than 140 characters. Try again." << endl;
				cout << endl;
				fflush(stdin);
				cout << "You: ";
				getline(cin, tempInput);
				memcpy(input, tempInput.c_str(), sizeof(input));
				ctr++;
			}

			outgoingPacket.version = htons(version);
			outgoingPacket.stringLength = htons(strlen(input));
			memcpy(outgoingPacket.data, input, sizeof(input));

			// copy incomingPacket struct to incomingBuffer
			memcpy(outgoingBuffer, &outgoingPacket, sizeof(outgoingBuffer));
			send(newSock, outgoingBuffer, sizeof(outgoingBuffer), 0);
			ctr++;
		}
		close(servSock);
	}
	else {
		cout << "Connecting to server... ";
		struct addrinfo hints, *res;
		int sockfd;

		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = 6;

		getaddrinfo(v.getServerIP().c_str(), v.getPortNumberAsString().c_str(), &hints, &res);

		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

		if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
			cerr << "\nError connecting. Please try again." << endl;
			v.printUsage();
			exit(1);
		}
		cout << "Connected!" << endl;
		int ctr = 0;
		while (1) {
			char incomingBuffer[144];
			char outgoingBuffer[144];
			char input[140];
			string tempInput;
			packet incomingPacket;
			packet outgoingPacket;
			if (ctr == 0) {
				cout << "Connected to a friend! You send first." << endl;
			}
			cout << "You: ";
			getline(cin, tempInput);
			memcpy(input, tempInput.c_str(), sizeof(input));

			if (strlen(input) > 140) {
				cerr << "Error: message needs to be less than 140 characters. Try again." << endl;
				memset(input, 0, sizeof(input));
				fflush(stdin);
				ctr++;
				continue;
			}

			outgoingPacket.version = htons(version);
			outgoingPacket.stringLength = htons(strlen(input));
			memcpy(outgoingPacket.data, input, sizeof(input));

			// copy incomingPacket struct to incomingBuffer
			memcpy(outgoingBuffer, &outgoingPacket, sizeof(outgoingBuffer));

			send(sockfd, outgoingBuffer, sizeof(outgoingBuffer), 0);
			recv(sockfd, incomingBuffer, sizeof(incomingBuffer), 0);

			memcpy(&incomingPacket.version, incomingBuffer, 2);
			memcpy(&incomingPacket.stringLength, incomingBuffer+2, 2);
			incomingPacket.version = ntohs(incomingPacket.version);
			incomingPacket.stringLength = ntohs(incomingPacket.stringLength);
			memcpy(incomingPacket.data, incomingBuffer+4, incomingPacket.stringLength);

			cout << "Friend: ";
			for (int i = 0; i < incomingPacket.stringLength; i++) {
				cout << incomingPacket.data[i];
			}
			cout << endl;
			ctr++;
		}
		delete res;
	}
	return 0;
}