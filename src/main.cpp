#include <p1.h>
#include <validator.h>
#include <client.h>
#include <server.h>

// scp -r P1 zackschr@olympia.cs.colostate.edu:~/cs457/P1/
int main(int argc, char **argv) {
	Validator v(argc, argv);
	if (argc == 1) {
		cout << "Running as server." << endl;
		Server s;
		s.listen(2222);
	}
	else {
		cout << "Running as client." << endl;
	}
	return 0;
}