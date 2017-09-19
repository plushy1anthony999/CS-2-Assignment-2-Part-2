#include "HelperFunctions.h"

using namespace std;

bool HelperFunctions::isInteger(const string & text) {
	if (text.empty()) return false;

	char * buffer = nullptr;
	strtol(text.c_str(), &buffer, 10);

	return (*buffer == '\0'); // If buffer holds a null-terminator, then text is an integer
}