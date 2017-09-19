#pragma once
#include <string>

namespace HelperFunctions {
	bool isInteger(const std::string & text);

	template <typename T>
	bool promptForValue(T & value, std::string promptMessage = "", std::string errorMessage = "") {

		string strInput;

		if (!promptMessage.empty())
			cout << promptMessage;

		getline(cin, strInput); // Read user input as string
		stringstream sstreamInput(strInput); // turns the string into a stream

											 // Checks for complete conversion to the return type T
		if (
			sstreamInput >> value &&
			!(sstreamInput >> strInput) // Make sure that no garbage is left in sstreamInput
			)
			return true;
		else {
			cin.clear(); // just in case if cin entered a bad state

			if (!errorMessage.empty())
				cout << errorMessage << endl;

			return false;
		}
	}
}

