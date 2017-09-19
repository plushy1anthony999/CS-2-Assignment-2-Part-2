#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "BankAccount.h"

// Tells whether the List array	in BankAccountList Class is currently sorted
namespace LIST_STATE_FLAGS {
	static const unsigned int UNSORTED = 0;
	static const unsigned int SORTED_BY_ACCOUNT = 1;
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

	void addAccount(const BankAccount & BA);

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

	// searches for a BankAccount from List[] based on actNum and returns whether or not it found the account
	// Writes to i the index that the BankAccount was found, or a -1 if no account was found
	bool findAccount(const std::string & actNum, int & i) const;
	const std::string toString() const;

	// Fills in an empty BankAccountList object through keyboard input
	static void getInstance(BankAccountList & BAL);
	// Fills in an empty BankAccountList object through an opened input-file passed in
	static void getInstance(BankAccountList & BAL, std::ifstream & in);
};