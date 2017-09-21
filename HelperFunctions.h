#pragma once
#include <string>
#include <iostream>
#include <fstream>

// FIXME - Break promptForValue into 2 functions

//template<class ... args>
//using BOOL_FUNCTION_POINTER_TEST = bool(*)(args...);
//
////struct BOOL_FUNCTION_POINTER_TEST {
////	using BOOL_FUNCTION_POINTER =  bool(*)();
////
////	BOOL_FUNCTION_POINTER_TEST() {
////		BOOL_FUNCTION_POINTER();
////		std::cout << "Constructor was called" << std::endl;
////	}
////};
////
//using BOOL_FUNCTION_POINTER = bool(*)();


//namespace HelperFunctions {
//	bool isInteger(const std::string & text);
//
	//// Uses getline to read a line from stream into a value and does error checking 
	//template <typename T>
	//bool readInValueByLine(std::istream & in, T & value, std::string promptMessage = "", std::string errorMessage = "") {

	//	std::string strInput;

	//	if (!promptMessage.empty())
	//		std::cout << promptMessage;

	//	std::getline(in, strInput); // Read user input as string
	//	std::stringstream sstreamInput(strInput); // turns the string into a stream


	//											// Checks for complete conversion to the return type T
	//	if (
	//		sstreamInput >> value &&
	//		!(sstreamInput >> strInput) // Make sure that no garbage is left in sstreamInput
	//	)
	//		return true;
	//	else {
	//		std::cin.clear(); // just in case if cin entered a bad state

	//		if (!errorMessage.empty())
	//			std::cout << errorMessage << std::endl;

	//		return false;
	//	}
	//}
//

//}

namespace HelperFunctions {
	bool isInteger(const std::string & text);

	// Can take in an errorCondition function pointer that can also be used in determining if the user-provided value is valid
	// If value is a string, empty strings and whitespace are invalid values
	template <typename T>
	bool promptForValue(T & value, std::string promptMessage = "", std::string errorMessage = "", bool promptAgainOnError = false, bool (*errorCondition)() = nullptr) {
		while (true) {
			string strInput;


			if (!promptMessage.empty())
				cout << promptMessage;

			getline(cin, strInput); // Read user input as string
			stringstream sstreamInput(strInput); // turns the string into a stream

			bool success = false;

			if (
				sstreamInput >> value &&	// Checks for complete conversion to the return type T
				!(sstreamInput >> strInput) // Make sure that no garbage is left in sstreamInput
			) {
				if (errorCondition) {
					if (errorCondition() == true)
						success = false;
					else
						success = true;
				}
				else
					success = true;
			}

			if(!success) {
				cin.clear(); // just in case if cin entered a bad state

				if (!errorMessage.empty())
					cout << errorMessage << endl;

				if (promptAgainOnError)
					continue;

				return false;
			}
			if (success)
				return true;
		}
	}

	// Uses an input file to read a token from stream into a value and does error checking 
	template <typename T>
	bool readInValueByToken(std::ifstream & in, T & value, std::string promptMessage = "", std::string errorMessage = "") {

		std::string strInput;

		if (!promptMessage.empty())
			std::cout << promptMessage;

		in >> strInput; // Read in token input as string
		std::stringstream sstreamInput(strInput); // turns the string into a stream


												  // Checks for complete conversion to the return type T
		if (
			sstreamInput >> value &&
			!(sstreamInput >> strInput) // Make sure that no garbage is left in sstreamInput
			)
			return true;
		else {
			if (!errorMessage.empty())
				std::cout << errorMessage << std::endl;

			return false;
		}
	}

	//// Takes func-pointer that returns bool as a param, and returns that same function except with its bool-result inverted
	//BOOL_FUNCTION_POINTER invertBoolFunction(BOOL_FUNCTION_POINTER);
}