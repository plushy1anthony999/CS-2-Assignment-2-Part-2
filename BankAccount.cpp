#include "BankAccount.h"

using namespace std;

template <typename T> // FIXME
bool promptForValue(T & value, string promptMessage, string errorMessage) {

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


BankAccount::BankAccount() {
	ActNum = "Account Number not set";
	FirstName = "First Name not set";
	LastName = "Last Name not set";
	balance = 0;

	isEmpty = true;
}

BankAccount::BankAccount(const std::string & actN, const std::string & fname, const std::string & lname, double bal) :
	ActNum(actN), FirstName(fname), LastName(lname), balance(bal) 
{
	if (balance < 0) {
		cout << "The balance can not be negative. It's been set to 0" << endl;
		balance = 0;
	}

	isEmpty = false;
}

void BankAccount::deposit(double money) {
	if (money == 0) 
		cout << "You have tried to deposit $0.00. Your balance is unchanged" << endl;
	if (money < 0) 
		cout << "Please provide a positive amount to deposit." << endl;
	if (money > 0) {
		balance += money;
		cout << "You have deposited $" << fixed << setprecision(2) << money << endl;
		cout << "Your new balance is $" << fixed << setprecision(2) << balance << endl;
	}
}
void BankAccount::withdraw(double money) {
	if (money == 0)
		cout << "You have tried to withdraw $0.00. Your balance is unchanged" << endl;
	if (money < 0)
		cout << "Please provide a positive amount to withdraw." << endl;
	if (money > 0) {
		if (money > balance) {
			cout << "You have tried to withdraw $" << fixed << setprecision(2) << money << ", which is greater than your current balance of $" << fixed << setprecision(2) << balance << endl;
			cout << "Please provide a lower amount to withdraw." << endl;
		}
		else {
			cout << "You have withdrawn $" << fixed << setprecision(2) << money << endl;
			balance -= money;
			cout << "Your current balance is $" << fixed << setprecision(2) << balance << endl;
		}
	}
}

bool BankAccount::isInteger(const string & text) const {
	if (text.empty()) return false;

	char * buffer = nullptr;
	strtol(text.c_str(), &buffer, 10);

	return (*buffer == '\0'); // If buffer holds a null-terminator, then text is an integer						  
}

const string BankAccount::toString() const { // FIXME
	stringstream sstream;
	sstream << left << setw(20) << "Name" << setw(20) << "Account Number" << setw(16) << "Current Balance" <<  endl;
	sstream << left << setw(20) << getFullName() << setw(20) << getAccountNumber() << '$' << setw(16) << fixed << setprecision(2) << getBalance();
	return sstream.str();
}

// Will write BankAccount info to either an opened-out-file or stdout
void BankAccount::print(ostream & out) const { // FIXME: Try casting to check if out is an ofstream object
	//if (&out == &cout) { // if writing to stdout
	//	out << "Account Number: " << ActNum << endl;
	//	out << "First Name: " << FirstName << endl;
	//	out << "Last Name: " << LastName << endl;
	//	out << "Balance: " << balance << endl;
	//}
	//else {
		out << "Account Number: " << ActNum << endl;
		out << "First Name: " << FirstName << endl;
		out << "Last Name: " << LastName << endl;
		out << "Balance: $" << fixed << setprecision(2) << balance << endl;
	//}
}

// Setters
void BankAccount::setAccountNumber(const string & actN) {
	if (!isInteger(actN)) {
		cout << "The account number \"" << actN << "\" is not valid." << endl;
		return;
	}

	ActNum = actN;
}
void BankAccount::setFirstName(const string & fname) {
	FirstName = fname;
}
void BankAccount::setLastName(const string & lname) {
	LastName = lname;
}

// Getters
string BankAccount::getAccountNumber() const {
	return ActNum;
}
const string BankAccount::getFirstName() const {
	return FirstName;
}
const string BankAccount::getLastName() const {
	return LastName;
}
const string BankAccount::getFullName() const {
	return getFirstName() + " " + getLastName();
}
double BankAccount::getBalance() const {
	return balance;
}
bool BankAccount::getIsEmpty() const {
	return isEmpty;
}

void BankAccount::getInstance(BankAccount & BA) { // FIXME
	cout << "New Bank Account" << endl;
	cout << "-----------------" << endl;

	string accountNumber;
	cout << "Account Number: ";
	if (!promptForValue(accountNumber, "", "")) {
		cout << "Invalid accountNumber given" << endl;
		return;
	}
	else if (!BA.isInteger(accountNumber)) {
		cout << "Invalid accountNumber given" << endl;
		return;
	}

	string firstName;
	cout << "First Name: ";
	if (!promptForValue(firstName, "", "")) {
		cout << "Invalid First Name given" << endl;
		return;
	}
	
	string lastName;
	cout << "Last Name: ";
	if (!promptForValue(lastName, "", "")) {
		cout << "Invalid Last Name given" << endl;
		return;
	}

	double balance;
	cout << "Balance: ";
	if (!promptForValue(balance, "", "")) {
		cout << "Invalid Initial Balance was given" << endl;
		return;
	}

	BA = BankAccount(accountNumber, firstName, lastName, balance);
}
void BankAccount::getInstance(BankAccount & BA, ifstream & in) {
	if (in.is_open()) {
		// BankAccount info to be passed in when constructing a BankAccount to replace the one passed in
		string accountNumber;
		string lastName;
		string firstName;
		double balance;

		// Read in 4 tokens to fill out BankAccount info variables
		// Assume input file is formatted properly
		for (size_t currentToken = 0; currentToken < 4; currentToken++) {
			switch (currentToken) {
			case 0:
				in >> accountNumber;
				break;

			case 1:
				in >> lastName;
				break;

			case 2:
				in >> firstName;
				break;

			case 3:
				in >> balance;
				break;
			}
		}

		BA = BankAccount(accountNumber, firstName, lastName, balance);
	}
	else
		cout << "The file could not be opened" << endl;
}
