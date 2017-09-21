#include "BankAccount.h"
#include "BankAccountList.h"
#include "HelperFunctions.h"
#include <assert.h>

using namespace std;

void main1();
void testBankAccountClass();
void testBankAccountListClass();

const bool UNIT_TESTING = true;
const bool SYSTEM_TESTING = false;

int main() {
	if (UNIT_TESTING) main1();


}

// Unit Testing Function
void main1() {
	cout << "Starting Unit Tests..." << endl;
	cout << "----------------------------------------------------" << endl;

	testBankAccountClass();
	cout << endl;
	testBankAccountListClass();
	cout << endl;

	cout << "All tests passed" << endl;
	cout << "-----------------------------------------------------" << endl;
}

void testBankAccountClass() {
	cout << "Testing the BankAccount Class..." << endl;
	BankAccount bankAccount1;
	BankAccount bankAccount2("123", "Anthony", "Ghouri", 10);
	BankAccount bankAccount3("12", "George", "Washington", -1);

	// Test Getters
	assert(bankAccount1.getAccountNumber() == "Account Number not set");
	assert(bankAccount1.getFirstName() == "First Name not set");
	assert(bankAccount1.getLastName() == "Last Name not set");
	assert(bankAccount1.getFullName() == "First Name not set Last Name not set");
	assert(bankAccount1.getBalance() == 0);
	assert(bankAccount2.getAccountNumber() == "123");
	assert(bankAccount2.getFirstName() == "Anthony");
	assert(bankAccount2.getFullName() == "Anthony Ghouri");
	assert(bankAccount2.getBalance() == 10);
	assert(bankAccount3.getAccountNumber() == "12");
	assert(bankAccount3.getBalance() == 0);
	assert(bankAccount1.getIsEmpty() == true);
	assert(bankAccount2.getIsEmpty() == false);
	assert(bankAccount3.getIsEmpty() == false);

	// Test Setters
	bankAccount1.setAccountNumber("1");
	assert(bankAccount1.getAccountNumber() == "1");
	bankAccount1.setAccountNumber("");
	assert(bankAccount1.getAccountNumber() == "1");
	bankAccount1.setFirstName("George");
	bankAccount1.setLastName("Ghouri");
	assert(bankAccount1.getFullName() == "George Ghouri");
	bankAccount2.setLastName("Smith");
	assert(bankAccount2.getFullName() == "Anthony Smith");
	bankAccount3.setFirstName("Billy");
	assert(bankAccount3.getFullName() == "Billy Washington");

	// Test toString()
	stringstream sstream;
	sstream << left << setw(28) << "Name" << setw(20) << "Account Number" << setw(16) << "Current Balance" << endl;
	sstream << left << setw(28) << "Anthony Smith" << setw(20) << "123" << '$' << setw(16) << fixed << setprecision(2) << (double)10;

	// Test deposit()
	bankAccount1.deposit(-1);
	assert(bankAccount1.getBalance() == 0);
	bankAccount1.deposit(100);
	assert(bankAccount1.getBalance() == 100);
	bankAccount1.deposit(10);
	assert(bankAccount1.getBalance() == 110);

	// Test withdraw()
	bankAccount1.withdraw(0);
	assert(bankAccount1.getBalance() == 110);
	bankAccount1.withdraw(-10);
	assert(bankAccount1.getBalance() == 110);
	bankAccount1.withdraw(120);
	assert(bankAccount1.getBalance() == 110);
	bankAccount1.withdraw(103);
	assert(bankAccount1.getBalance() == 7);

	//cout << sstream.str() << endl;
	//cout << bankAccount2.toString() << endl;
	assert(bankAccount2.toString() == sstream.str());

	// Test print() w/ cout
	cout << "Testing the BankAccount::print() method: " << endl;
	bankAccount1.print();

	// Test print() w/ output-file
	ofstream outfile("BankAccount_toString()_Test.txt");
	bankAccount1.print(outfile);

	if (SYSTEM_TESTING) {
		// Test getInstance with stdin
		BankAccount bankAccount4;

		BankAccount::getInstance(bankAccount4);
		assert(bankAccount4.getAccountNumber() == "1111");
		assert(bankAccount4.getFullName() == "George Washington");
		assert(bankAccount4.getBalance() == 10);
	}

	// Test getInstance with input-file
	BankAccount bankAccount5;

	BankAccount::getInstance(bankAccount5, ifstream("getInstance_inputfile.txt"));
	assert(bankAccount5.getAccountNumber() == "1234");
	assert(bankAccount5.getFirstName() == "James");
	assert(bankAccount5.getLastName() == "Doe");
	assert(bankAccount5.getBalance() == 20.01);
}
void testBankAccountListClass() {
	cout << "Testing the BankAccountList Class..." << endl;
	
	// Test addAccount() and findAccount()
	BankAccountList bankAccountList1; // FIXME
	int bankAccountList1_i;
	assert(bankAccountList1.findAccount("1234", bankAccountList1_i) == false);
	assert(bankAccountList1_i == -1);
	assert(bankAccountList1.getNumberOfElements() == 0);
	assert(bankAccountList1.isEmpty() == true);
	assert(bankAccountList1.isFull() == false);

	// Test Getters
	BankAccount bankAccount1("1000", "Anthony", "Ghouri", 10);
	bankAccountList1.addAccount(bankAccount1);
	assert(bankAccountList1.getFirstName("1000") == "Anthony");
	assert(bankAccountList1.getLastName("1000") == "Ghouri");
	assert(bankAccountList1.getFullName("1000") == "Anthony Ghouri");
	assert(bankAccountList1.getBalance("1000") == 10);
	assert(bankAccountList1.getNumberOfElements() == 1);
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::UNSORTED);
	assert(BankAccountList::getCapacity() == 30);
	assert(bankAccountList1.isEmpty() == false);
	assert(bankAccountList1.isFull() == false);
	assert(bankAccountList1.findAccount("1000", bankAccountList1_i) == true);
	assert(bankAccountList1_i == 0);

	BankAccount bankAccount2("1010", "George", "Washington", 100);
	bankAccountList1.addAccount(bankAccount2);
	assert(bankAccountList1.getFirstName("1010") == "George");
	assert(bankAccountList1.getLastName("1010") == "Washington");
	assert(bankAccountList1.getFullName("1010") == "George Washington");
	assert(bankAccountList1.getBalance("1010") == 100);
	assert(bankAccountList1.getNumberOfElements() == 2);

	// Test depositMoney()
	assert(bankAccountList1.depositMoney("1000", 50) == true);
	assert(bankAccountList1.getBalance("1000") == 60);
	assert(bankAccountList1.depositMoney("1010", 32) == true);
	assert(bankAccountList1.getBalance("1010") == 132);
	assert(bankAccountList1.depositMoney("9099", 20) == false);
	assert(bankAccountList1.getNumberOfElements() == 2);

	for (int i = 2; i < 30; i++) { // Fill up bankAccountList1 to max capacity
		string stringArgStub = to_string(i);

		BankAccount bankAccount(stringArgStub, "FirstName" + stringArgStub, "LastName" + stringArgStub, i);

		bankAccountList1.addAccount(bankAccount);
		assert(bankAccountList1.getFirstName(stringArgStub) == "FirstName" + stringArgStub);
		assert(bankAccountList1.getLastName(stringArgStub) == "LastName" + stringArgStub);
		assert(bankAccountList1.getFullName(stringArgStub) == ("FirstName" + stringArgStub + " " + "LastName" + stringArgStub));
		assert(bankAccountList1.getBalance(stringArgStub) == i);
		assert(bankAccountList1.getNumberOfElements() == i + 1);

		assert(bankAccountList1.depositMoney(stringArgStub, i) == true);
		assert(bankAccountList1.getBalance(stringArgStub) == (i * 2));
	}

	assert(bankAccountList1.getNumberOfElements() == 30);
	assert(bankAccountList1.isEmpty() == false);
	assert(bankAccountList1.isFull() == true);

	bankAccountList1.addAccount(BankAccount("2002", "Placeholder", "Bob", 100));
	assert(bankAccountList1.getNumberOfElements() == 30);
	assert(bankAccountList1.isEmpty() == false);
	assert(bankAccountList1.isFull() == true);

	// Test withDrawMoney()
	BankAccountList bankAccountList2;
	bankAccountList2.addAccount(BankAccount("9999", "Billy", "Bob", 1.20));
	assert(bankAccountList2.withDrawMoney("9999", 0.21) == true);
	assert(bankAccountList2.getBalance("9999") == 0.99);
	assert(bankAccountList2.getNumberOfElements() == 1);
	bankAccountList2.addAccount(BankAccount("9998", "Billy", "Smith", 1.12));
	assert(bankAccountList2.getNumberOfElements() == 2);

	for (int i = 2; i < 30; i++) { // Fill up bankAccountList2 to max capacity
		string stringArgStub = to_string(i);

		BankAccount bankAccount(stringArgStub, "FirstName" + stringArgStub, "LastName" + stringArgStub, i);

		bankAccountList2.addAccount(bankAccount);
		assert(bankAccountList2.getFirstName(stringArgStub) == "FirstName" + stringArgStub);
		assert(bankAccountList2.getLastName(stringArgStub) == "LastName" + stringArgStub);
		assert(bankAccountList2.getFullName(stringArgStub) == ("FirstName" + stringArgStub + " " + "LastName" + stringArgStub));
		assert(bankAccountList2.getBalance(stringArgStub) == i);
		assert(bankAccountList2.getNumberOfElements() == i + 1);

		assert(bankAccountList2.withDrawMoney(stringArgStub, i) == true);
		assert(bankAccountList2.getBalance(stringArgStub) == 0);
	}

	assert(bankAccountList2.getNumberOfElements() == 30);
	assert(bankAccountList2.isEmpty() == false);
	assert(bankAccountList2.isFull() == true);
	assert(bankAccountList2.withDrawMoney("9099", 20) == false);
	assert(bankAccountList2.getNumberOfElements() == 30);
	assert(bankAccountList2.isEmpty() == false);
	assert(bankAccountList2.isFull() == true);

	// Test toString()
	cout << bankAccountList1.toString() << endl;

	// Test deleteAccount()
	assert(bankAccountList1.getNumberOfElements() == 30);
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::UNSORTED);
	assert(bankAccountList1.deleteAccount("3") == true);
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::UNSORTED);
	assert(bankAccountList1.getNumberOfElements() == 29);
	cout << bankAccountList1.toString();

	for (size_t i = 3; i < 29; i++) {
		string stringArgStub = to_string(i + 1);

		assert(bankAccountList1.getFirstName(stringArgStub) == "FirstName" + stringArgStub);
		assert(bankAccountList1.getLastName(stringArgStub) == "LastName" + stringArgStub);
		assert(bankAccountList1.getFullName(stringArgStub) == ("FirstName" + stringArgStub + " " + "LastName" + stringArgStub));

		assert(bankAccountList1.getBalance(stringArgStub) == ((i + 1) * 2));
	}

	// Test updateAccount()
	if (SYSTEM_TESTING) {
		bankAccountList1.updateAccount();
		assert(bankAccountList1.getLastName("1000") == "SMITHY");
	}

	// Test sort()
	assert(bankAccountList1.deleteAccount("2") == true);
	assert(bankAccountList1.deleteAccount("29") == true);
	assert(bankAccountList1.getNumberOfElements() == 27);
	bankAccountList1.addAccount(BankAccount("2", "Teddy", "Roosevelt", 1000));
	assert(bankAccountList1.getNumberOfElements() == 28);

	bankAccountList1.sort(LIST_STATE_FLAGS::SORTED_BY_ACCOUNT);
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::SORTED_BY_ACCOUNT);
	assert(bankAccountList1.getNumberOfElements() == 28);
	assert(bankAccountList1.deleteAccount("2") == true);
	assert(bankAccountList1.getNumberOfElements() == 27);
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::SORTED_BY_ACCOUNT);
	bankAccountList1.addAccount(BankAccount("22", "Ronald", "Reagan", 1000)); // Should fail
	assert(bankAccountList1.getLastName("22") == "LastName22");
	assert(bankAccountList1.getNumberOfElements() == 27);
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::SORTED_BY_ACCOUNT);
	bankAccountList1.addAccount(BankAccount("221", "Billy", "Cyrus", 10100));
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::UNSORTED);

	bankAccountList1.sort(LIST_STATE_FLAGS::SORTED_BY_BALANCE);
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::SORTED_BY_BALANCE);

	if (SYSTEM_TESTING) {
		bankAccountList1.updateAccount();
		assert(bankAccountList1.getLastName("22") == "Smith");
		assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::SORTED_BY_BALANCE);
	}

	bankAccountList1.sort(LIST_STATE_FLAGS::SORTED_BY_LASTNAME);
	if (SYSTEM_TESTING) {
		bankAccountList1.updateAccount();
		assert(bankAccountList1.getLastName("11") == "Billy");
		assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::UNSORTED);
	}

	// Test makeEmpty()
	bankAccountList1.makeEmpty();
	assert(bankAccountList1.getNumberOfElements() == 0);
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::UNSORTED);
	bankAccountList1.addAccount(BankAccount("22", "Ronald", "Reagan", 1000));
	assert(bankAccountList1.getNumberOfElements() == 1);
	assert(bankAccountList1.getLastName("22") == "Reagan");
	
	// Test setAccountAt()
	bankAccountList1.setAccountAt(BankAccount("21", "Billy", "Reagan", 1000), 1); // Shoud fail
	bankAccountList1.setAccountAt(BankAccount("21", "Billy", "Reagan", 1000), 0);
	assert(bankAccountList1.getFirstName("21") == "Billy");
	assert(bankAccountList1.getNumberOfElements() == 1);

	// Test setLastName()
	bankAccountList1.sort(LIST_STATE_FLAGS::SORTED_BY_LASTNAME);
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::SORTED_BY_LASTNAME);

	bankAccountList1.setLastName("Green", "21");
	assert(bankAccountList1.getLastName("21") == "Green");
	assert(bankAccountList1.getNumberOfElements() == 1);
	assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::UNSORTED);

	// Test getAccountAt()
	BankAccount bankAccount3;
	unsigned int index = 2;
	assert(bankAccountList1.getAccountAt(bankAccount3, index) == false);
	index = 0;
	assert(bankAccountList1.getAccountAt(bankAccount3, index) == true);
	assert(bankAccount3.getFullName() == "Billy Green");

	// Test print() // FIXME
	bankAccountList1.print();

	// Test getInstance() with keyboard input
	if (SYSTEM_TESTING) {
		BankAccountList::getInstance(bankAccountList1);
		bankAccountList1.sort(LIST_STATE_FLAGS::SORTED_BY_LASTNAME);

		assert(bankAccountList1.getFullName("9898") == "Billy Bob");
		assert(bankAccountList1.getNumberOfElements() == 3);
		assert(bankAccountList1.getFullName("1818") == "Jennifer Lopez");
		assert(bankAccountList1.getListState() == LIST_STATE_FLAGS::SORTED_BY_LASTNAME);
	}
	bankAccountList1.makeEmpty();
	assert(bankAccountList1.isEmpty() == true);

	// Test getInstance() from an input file
	BankAccountList::getInstance(bankAccountList1, ifstream());
	assert(bankAccountList1.getNumberOfElements() == 13);
	assert(bankAccountList1.getBalance("1415") == 75.7);
	bankAccountList1.makeEmpty();

	BankAccountList::getInstance(bankAccountList1, ifstream());
	assert(bankAccountList1.getNumberOfElements() == 30);
	assert(bankAccountList1.getBalance("130") == 130);
	assert(bankAccountList1.getBalance("131") == -1); // Testing for nonexistant bank account
	bankAccountList1.makeEmpty();

	BankAccountList::getInstance(bankAccountList1, ifstream());
	assert(bankAccountList1.getNumberOfElements() == 11);
	assert(bankAccountList1.getBalance("112") == -1); // Testing for nonexistant bank account
	bankAccountList1.makeEmpty();

	BankAccountList::getInstance(bankAccountList1, ifstream());
	assert(bankAccountList1.getNumberOfElements() == 7);
	assert(bankAccountList1.getBalance("10s2") == -1); // Testing for nonexistant bank account
	assert(bankAccountList1.getBalance("107") == -1);
	assert(bankAccountList1.getBalance("103") == -1);
	unsigned int index2 = 1;
	BankAccount bankAccount4;
	assert(bankAccountList1.getAccountAt(bankAccount4, index2) == true);
	assert(bankAccount4.getAccountNumber() == "104");
}