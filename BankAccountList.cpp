#include "BankAccountList.h"
#include "HelperFunctions.h"

using namespace std;
using namespace HelperFunctions;

BankAccountList::BankAccountList() {
	num_elements = 0;
	list_state = LIST_STATE_FLAGS::UNSORTED;
}

bool BankAccountList::findAccount(const string & actNum, int & i) const {
	// Only go through the indexes in List[] that have Bank Accounts
	for (size_t j = 0; j < num_elements; j++) {
		if (List[j].getAccountNumber() == actNum) {
			i = j;
			return true;
		}
	}
	i = -1;
	return false;
}

void BankAccountList::addAccount(const BankAccount & BA) {
	if (num_elements < MAX) {
		int tmp; // unused

		if (!findAccount(BA.getAccountNumber(), tmp)) { // Check that the account doesn't already exist in List[]
			List[num_elements] = BA; // Adds account to the first unused spot in the array
			num_elements++;
			list_state = LIST_STATE_FLAGS::UNSORTED;

			cout << "Bank Account #" << BA.getAccountNumber() << " Was added to the list" << endl;
		}
		else
			cout << "Bank Account #" << BA.getAccountNumber() << " already exists in the list" << endl;
	}
	else
		cout << "Can't add Account #" << BA.getAccountNumber() << " since the BankAccountList has reached its max capacity of " << MAX << " accounts" << endl;
}
bool BankAccountList::deleteAccount(const string & actNum) {
	int	position;

	if (findAccount(actNum, position)) {
		for (size_t i = position; i < num_elements - 1; i++) { // The minus 1 prevents looking past array bounds
			List[i] = List[i + 1]; // Shift elements to the right of the found account left,
								   // Causing the account to be overwrittend while maintaing current sorting order
		}
		num_elements--;
		return true;
	} 
	else {
		cout << "The Account #" << actNum << " couldn't be found" << endl;
		return false;
	}
}
bool BankAccountList::updateAccount() {
	string accountNumber;

	if (readInValueByToken(cin, accountNumber, "Please provide the Account Number for the account you wish to update: ")) {
		int position;
		
		if (findAccount(accountNumber, position)) {
			cout << List[position].toString() << endl;
			
			string newLastName;
			if (readInValueByToken(cin, newLastName, "Please provide a new Last Name for this account: ")) {
				List[position].setLastName(newLastName);
				cout << "The Account has been update successfully" << endl;

				if (list_state == LIST_STATE_FLAGS::SORTED_BY_LASTNAME)
					list_state = LIST_STATE_FLAGS::UNSORTED;

				return true;
			}
			else {
				cout << "The Last Name provided is invalid" << endl;
				return false;
			}
		}
		else {
			cout << "The Account #" << accountNumber << " could not be found" << endl;
			return false;
		}
	}
	else {
		cout << "The Account #" << accountNumber << " is invalid" << endl;
		return false;
	}
	
}


void BankAccountList::sort(int flag) {
	switch (flag) {
	case LIST_STATE_FLAGS::SORTED_BY_ACCOUNT:
		sortByAccountNumber();
		break;
	case LIST_STATE_FLAGS::SORTED_BY_LASTNAME:
		sortByLastName();
		break;
	case LIST_STATE_FLAGS::SORTED_BY_BALANCE:
		sortByBalance();
		break;
	
	default:
		cout << "Invalid sort flag was given";
		break;
	}
}
void BankAccountList::sortByAccountNumber() {
	for (size_t i = 0; i < num_elements; i++) {

		// Minus 'i' is done so the loop doesn't look at elements already sorted and moved to the end
		for (size_t j = 0; j < num_elements - 1 - i; j++) {
			int leftAccountNumber = atoi(List[j].getAccountNumber().c_str());
			int rightAccountNumber = atoi(List[j + 1].getAccountNumber().c_str());

			if (leftAccountNumber > rightAccountNumber) {
				BankAccount rightBankAccount = List[j + 1];
				List[j + 1] = List[j]; // Move left element close to the end of the array
				List[j] = rightBankAccount;
			}
		}
	}
	list_state = LIST_STATE_FLAGS::SORTED_BY_ACCOUNT;
}
void BankAccountList::sortByLastName() {
	for (size_t i = 0; i < num_elements; i++) {

		// Minus 'i' is done so the loop doesn't look at elements already sorted and moved to the end
		for (size_t j = 0; j < num_elements - 1 - i; j++) {
			string capitalizedLastName1; // Used for non-case-sensitive sorting
			string capitalizedLastName2;

			for (const char & letter : List[j].getLastName())
				capitalizedLastName1 += toupper(letter);
			for (const char & letter : List[j + 1].getLastName())
				capitalizedLastName2 += toupper(letter);

			if (capitalizedLastName1 > capitalizedLastName2) {
				BankAccount rightBankAccount = List[j + 1];
				List[j + 1] = List[j]; // Move left element close to the end of the array
				List[j] = rightBankAccount;
			}
		}
	}
	list_state = LIST_STATE_FLAGS::SORTED_BY_LASTNAME;
}
void BankAccountList::sortByBalance() {
	for (size_t i = 0; i < num_elements; i++) {

		// Minus 'i' is done so the loop doesn't look at elements already sorted and moved to the end
		for (size_t j = 0; j < num_elements - 1 - i; j++) {
			double leftBalance = List[j].getBalance();
			double rightBalance = List[j + 1].getBalance();

			if (leftBalance > rightBalance) {
				BankAccount rightBankAccount = List[j + 1];
				List[j + 1] = List[j]; // Move left element close to the end of the array
				List[j] = rightBankAccount;
			}
		}
	}
	list_state = LIST_STATE_FLAGS::SORTED_BY_BALANCE;
}


bool BankAccountList::depositMoney(const string & actNum, double money) {
	int position;	

	if (findAccount(actNum, position)) {
		double oldBalance = List[position].getBalance();
		List[position].deposit(money);

		if (oldBalance != List[position].getBalance()) { // Check if balance was updated
			if (list_state == LIST_STATE_FLAGS::SORTED_BY_BALANCE) // FIXME - Test if this handle the list_state correctly
				list_state = LIST_STATE_FLAGS::UNSORTED;

			return true;
		}
		else
			return false;
	}
	else {
		cout << "The Account #" << actNum << " could not be found" << endl;
		return false;
	}
}
bool BankAccountList::withDrawMoney(const string & actNum, double money) {
	int position;

	if (findAccount(actNum, position)) {
		// Validate that the current balance is greater than the amount being withdrawn
		if (List[position].getBalance() >= money) {
			double oldBalance = List[position].getBalance();
			List[position].withdraw(money);

			if (oldBalance != List[position].getBalance()) { // Check if balance was updated
				if (list_state == LIST_STATE_FLAGS::SORTED_BY_BALANCE) // FIXME - Test if this handle the list_state correctly
					list_state = LIST_STATE_FLAGS::UNSORTED;

				return true;
			}
			else
				return false;
		}
		else {
			cout << "You have tried to withdraw $" << fixed << setprecision(2) << money << ", which is greater than your current balance of $" << fixed << setprecision(2) << List[position].getBalance() << endl;
			cout << "Please provide a lower amount to withdraw." << endl;
			return false;
		}
	}
	else {
		cout << "The Account #" << actNum << " could not be found" << endl;
		return false;
	}
}

// Getters
const string BankAccountList::getFirstName(const string & actNum) const { // FIXME - Add exception handling
	int position;

	if (findAccount(actNum, position)) {
		return List[position].getFirstName();
	}
	else
		return "";
}
const string BankAccountList::getLastName(const string & actNum) const {
	int position;

	if (findAccount(actNum, position)) {
		return List[position].getLastName();
	}
	else
		return "";
}
const string BankAccountList::getFullName(const string & actNum) const {
	int position;

	if (findAccount(actNum, position)) {
		return List[position].getFullName();
	}
	else
		return "";
}
double BankAccountList::getBalance(const string & actNum) const { // Returns -1 on failure
	int position;

	if (findAccount(actNum, position)) {
		return List[position].getBalance();
	}
	else
		return -1;
}
int BankAccountList::getNumberOfElements() const {
	return num_elements;
}
int BankAccountList::getListState() const {
	return list_state;
}
bool BankAccountList::isEmpty() const {
	return (num_elements == 0);
}
bool BankAccountList::isFull() const {
	return (num_elements == MAX);
}

int BankAccountList::getCapacity() {
	return MAX;
}

// Sets last name of an account based on the account number passed
// Sets list_state to unsorted if list was already sorted by last name
void BankAccountList::setLastName(const string & lname, const string & actNum) {
	int position;
	if (findAccount(actNum, position)) {
		List[position].setLastName(lname);

		if (list_state == LIST_STATE_FLAGS::SORTED_BY_LASTNAME)
			list_state = LIST_STATE_FLAGS::UNSORTED;
	}
}

bool BankAccountList::getAccountAt(BankAccount & BA, unsigned int & index) const {
	if (num_elements > index) {// Makes sure index isn't out of range
		BA = List[index];
		return true;
	}
	else {
		cout << "The index " << index << " is outside the range of the BankAccountList" << endl;
		return false;
	}
}
void BankAccountList::setAccountAt(BankAccount & BA, unsigned int index) {
	if (num_elements > index) // Makes sure index isn't out of range
		List[index] = BA;
	else 
		cout << "The index " << index << " is outside the range of the BankAccountList" << endl;
}

const string BankAccountList::toString() const {
	stringstream result;

	// Only go through the indexes in List[] that have Bank Accounts
	for (size_t i = 0; i < num_elements; i++) {
		result << List[i].toString() << endl;
	}

	return result.str();
}
void BankAccountList::print(ostream & out) const { // FIXME: Try casting to check if out is an ofstream object
												   // FIXME: Make sure outfile is written in Append Mode
}

void BankAccountList::makeEmpty() {
	num_elements = 0;
	list_state = LIST_STATE_FLAGS::UNSORTED;
}

void BankAccountList::getInstance(BankAccountList & BAL) {
	while (true) {
		cout << "Please fill out the details for a new Bank Account object to be added" << endl;

		string accountNumber;
		string firstName;
		string lastName;
		double balance;

		readInValueByToken(cin, accountNumber, "Account Number: ", "Invalid Account Number was given");
		readInValueByToken(cin, firstName, "First Name: ", "Invalid First Name was given");
		readInValueByToken(cin, lastName, "Last Name: ", "Invalid Last Name was given");
		readInValueByToken(cin, balance, "Initial Balance: ", "Invalid Initial Balance was given");

		if (!isInteger(accountNumber)) {
			cout << "Invalid Account Number was given" << endl;
			continue;
		}

		BAL.addAccount(BankAccount(accountNumber, firstName, lastName, balance));

		char addAnotherAccount;
		while(true) {
			readInValueByToken(cin, addAnotherAccount, "Add another account? ('y' or 'n'): ");

			if (addAnotherAccount != 'y' && addAnotherAccount != 'n') {
				cout << "Please type either 'y' or 'n'" << endl;
				continue;
			}

			if (addAnotherAccount == 'y') // Prompt for Bank Account Info
				break;
			if (addAnotherAccount == 'n') // Stop adding Bank Accounts
				return;
		}
	}
}
void BankAccountList::getInstance(BankAccountList & BAL, ifstream & in) { // FIXME
	string filePath;
	readInValueByToken(cin, filePath, "Please provide a filepath to the input file: ");
	in.open(filePath);
	if (in.is_open()) {
		unsigned int numOfBankAccountsRead = 0;
		
		while (!in.eof()) {
			string accountNumber;
			string lastName;
			string firstName;
			double balance = -1;

			for (size_t i = 0; i < 4; i++) { // Reads in 4 tokens per bank account
				switch (i) {
				case 0:
					readInValueByToken(cin, accountNumber);
					break;
				case 1:
					readInValueByToken(cin, lastName);
					break;					
				case 2:
					readInValueByToken(cin, firstName);
					break;
				case 3:
					readInValueByToken(cin, balance);
					break;
				}
			}
			

			if (numOfBankAccountsRead != MAX) {
				if (  // If Bank Account has bad data, skip to next account
					!isInteger(accountNumber) ||
					accountNumber.empty()	  ||
					lastName.empty()		  ||
					firstName.empty()		  ||
					(balance == -1)
				)
					continue;

				BAL.addAccount(BankAccount(accountNumber, firstName, lastName, balance));
				numOfBankAccountsRead++;
			}
			else 
				cout << "The input file contains more than the max amount of 30 Bank Accounts" << endl;
		}

		cout << numOfBankAccountsRead << " Bank Accounts were processed and stored" << endl;
		in.close();
	}
	else
		cout << "The file couldn't be opened";
}