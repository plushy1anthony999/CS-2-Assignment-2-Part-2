#include "BankAccountList.h"

using namespace std;

BankAccountList::BankAccountList() {
	num_elements = 0;
	list_state = LIST_STATE_FLAGS::UNSORTED;
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

const string BankAccountList::toString() const {
	stringstream result;

	// Only go through the indexes in List[] that have Bank Accounts
	for (size_t i = 0; i < num_elements; i++) {
		result << List[i].toString() << endl;
	}

	return result.str();
}