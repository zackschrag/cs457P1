#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <stdlib.h>
#include <iostream>
#include <string>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;

class Validator {
public:
	Validator(int argc, char **argv); // take command line inputs

private:
	void validateOptions(int argc, char **argv);
	void validatePort(string number);
	void validateServer(string ip);
	void printUsage();

	int portNumber;
	string serverIP;
};

#endif