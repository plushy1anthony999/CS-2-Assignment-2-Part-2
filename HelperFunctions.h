#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace HelperFunctions {
	bool isInteger(const std::string & text);

	// Uses getline to read a line from stream into a value and does error checking 
	template <typename T>
	bool readInValueByLine(std::istream in, T & value, std::string promptMessage = "", std::string errorMessage = "") {

		std::string strInput;

		if (!promptMessage.empty())
			std::cout << promptMessage;

		std::getline(in, strInput); // Read user input as string
		std::stringstream sstreamInput(strInput); // turns the string into a stream


											 // Checks for complete conversion to the return type T
		if (
			sstreamInput >> value &&
			!(sstreamInput >> strInput) // Make sure that no garbage is left in sstreamInput
		)
			return true;
		else {
			std::cin.clear(); // just in case if cin entered a bad state

			if (!errorMessage.empty())
				std::cout << errorMessage << std::endl;

			return false;
		}
	}

	// Uses cin to read a token from stream into a value and does error checking 
	template <typename T>
	bool readInValueByToken(std::istream in, T & value, std::string promptMessage = "", std::string errorMessage = "") {

		std::string strInput;

		if (!promptMessage.empty())
			std::cout << promptMessage;

		std::getline(in, strInput); // Read user input as string
		std::stringstream sstreamInput(strInput); // turns the string into a stream


											 // Checks for complete conversion to the return type T
		if (
			sstreamInput >> value &&
			!(sstreamInput >> strInput) // Make sure that no garbage is left in sstreamInput
			)
			return true;
		else {
			std::cin.clear(); // just in case if cin entered a bad state

			if (!errorMessage.empty())
				std::cout << errorMessage << std::endl;

			return false;
		}
	}
}

