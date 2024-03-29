#include <validator.h>

Validator::Validator(int argc, char **argv) {
	validateOptions(argc, argv);
}

void Validator::validateOptions(int argc, char **argv) {
	for (int i = 0; i < argc; i++) {
		string option = (string) argv[i];
		string optionValue = ""; 
		if (i != argc-1) {
			optionValue = (string) argv[i+1];
		}
		if (option == "-h") {
			printUsage();
		}
		if (option == "-p") {
			validatePort(optionValue);
		}
		if (option == "-s") {
			validateServer(optionValue);
		}
	}
}

void Validator::validatePort(string number) {
	for (string::iterator it=number.begin(); it != number.end(); ++it) {
		if (!isdigit(*it)) {
			cerr << "Please enter a valid port number - any integer from 1 - 65535" << endl;
			printUsage();
		}
	}
	portNumber = atoi(number.c_str());
	if (!(portNumber > 0 && portNumber < 65536)) {
		cerr << "Please enter a valid port number; any integer from 1 - 65535" << endl;
		printUsage();
	}
	portNumberAsString = number;
}

void Validator::validateServer(string ip) {
	// TODO: currently says ....11111111111 is a valid IP
	int digitCounter = 0;
	int dotCounter = 0;

	for (string::iterator it=ip.begin(); it != ip.end(); ++it) {
		if (isdigit(*it)) {
			digitCounter++;
		}
		if (*it == '.') {
			dotCounter++;
		}
		if (!(isdigit(*it) || *it == '.')) {
			printUsage();
		}
		if (digitCounter > 12 || dotCounter > 3) {
			printUsage();
		}
	}
	serverIP = ip;
}

int Validator::getPortNumber() {
	return portNumber;
}

string Validator::getPortNumberAsString() {
	return portNumberAsString;
}

string Validator::getServerIP() {
	return serverIP;
}

void Validator::printUsage() {
	cerr << "usage: chat [-p] <portnumber> [-s] <serverip>\t This runs the program as the client." << endl;
	cerr << "\t\t\t\t\t\t'chat' with no arguments runs the program as the server." << endl;
	exit(1);
}