#include "HelperFunctions.h"

using namespace std;

bool HelperFunctions::isInteger(const string & text) {
	if (text.empty()) return false;

	char * buffer = nullptr;
	strtol(text.c_str(), &buffer, 10);

	return (*buffer == '\0'); // If buffer holds a null-terminator, then text is an integer
}


// FIXME - Implement this as a variadic function template

//BOOL_FUNCTION_POINTER HelperFunctions::invertBoolFunction(BOOL_FUNCTION_POINTER bool_function_pointer) {
//	return [bool_function_pointer]() {
//		//bool originalValue = bool_function_pointer();
//		return (bool_function_pointer());
//	};
//}