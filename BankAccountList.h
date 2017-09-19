#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "BankAccount.h"

// Tells whether the List array	in BankAccountList Class is currently sorted
namespace LIST_STATE_FLAGS {
	static const unsigned int UNSORTED = 0; // All in ascending order
	static const unsigned int SORTED_BY_ACCOUNT = 1; // Account Number
	static const unsigned int SORTED_BY_LASTNAME = 2; 
	static const unsigned int SORTED_BY_BALANCE = 3;
};


class BankAccountList {
	const static int MAX = 30;

	BankAccount List[MAX];
	int list_state;
	int num_elements; // Number of active elelments in List[] i.e. its logical length

public:
	BankAccountList();

	// searches for a BankAccount from List[] based on actNum and returns whether or not it found the account
	// Writes to i the index that the BankAccount was found, or a -1 if no account was found
	bool findAccount(const std::string & actNum, int & i) const;

	// Adds an account based on a unique ID. The list sort order will be unsorted after adding
	void addAccount(const BankAccount & BA);
	// Deletes an account while maintaing the list's current sort order
	bool deleteAccount(const std::string & actNum);
	// Prompts user to change the account's Last Name. Sort Order becomes unsorted if previously sorted by Last Name
	bool updateAccount();


	// relies on LIST_STATE_FLAGS for sorting List[]
	void sort(int flag);

	bool depositMoney(const std::string & actNum, double money);
	bool withDrawMoney(const std::string & actNum, double money);

	// Getters
	const std::string getFirstName(const std::string & actNum) const;
	const std::string getLastName(const std::string & actNum) const;
	const std::string getFullName(const std::string & actNum) const;
	double getBalance(const std::string & actNum) const;
	int getNumberOfElements() const; // returns number of accounts in bank
	int getListState() const; // returns an integer indicating what sorted state the list is in
	bool isEmpty() const;
	bool isFull() const;

	static int getCapacity(); // returns the max capacity that BankAccountList can hold

	// Sets last name of an account based on the account number passed
	// Sets list_state to unsorted if list was already sorted by last name
	void setLastName(const std::string & lname, const std::string & actNum);

	// Retrieves a BankAccount object and assigns it to BA
	bool getAccountAt(BankAccount & BA, unsigned int & index) const;
	// Replaces the BankAccount at the given index. Does bounds checking
	void setAccountAt(BankAccount & BA, unsigned int index);
	const std::string toString() const;
	void print(std::ostream & out = cout) const;

	void makeEmpty(); // Makes List[] empty by setting the number of elements to 0 and list_state to unsorted

	// Fills in an empty BankAccountList object through keyboard input
	static void getInstance(BankAccountList & BAL);
	// Fills in an empty BankAccountList object through an opened input-file passed in
	static void getInstance(BankAccountList & BAL, std::ifstream & in);

	// Private Helper Methods
private:
	void sortByAccountNumber();
	void sortByLastName();
	void sortByBalance();
};