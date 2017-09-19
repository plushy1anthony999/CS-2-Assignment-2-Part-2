#include "BankAccountList.h"

using namespace std;

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
	cout << "Please provide the Account Number for the account you wish to update:";
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
}
const string BankAccountList::getLastName(const string & actNum) const {
	int position;

	if (findAccount(actNum, position)) {
		return List[position].getLastName();
	}
}
const string BankAccountList::getFullName(const string & actNum) const {
	int position;

	if (findAccount(actNum, position)) {
		return List[position].getFullName();
	}
}
double BankAccountList::getBalance(const string & actNum) const {
	int position;

	if (findAccount(actNum, position)) {
		return List[position].getBalance();
	}
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


const string BankAccountList::toString() const {
	stringstream result;

	// Only go through the indexes in List[] that have Bank Accounts
	for (size_t i = 0; i < num_elements; i++) {
		result << List[i].toString() << endl;
	}

	return result.str();
}