#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <p1.h>

class Validator {
public:
	Validator(int argc, char **argv); // take command line inputs
	int getPortNumber();
	string getPortNumberAsString();
	string getServerIP();

private:
	void validateOptions(int argc, char **argv);
	void validatePort(string number);
	void validateServer(string ip);
	void printUsage();

	int portNumber;
	string portNumberAsString;
	string serverIP;
};

#endif