#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

class BankAccount {
	std::string ActNum;
	std::string FirstName;
	std::string LastName;
	double balance;

	bool isEmpty = true;

	bool isInteger(const std::string & text) const;

public:
	BankAccount();
	BankAccount(const std::string & actN, const std::string & fname, const std::string & lname, double bal);

	void deposit(double money);
	void withdraw(double money);

	const std::string toString() const;
	void print(std::ostream & out = std::cout) const;

	// Setters
	void setAccountNumber(const std::string & actN);
	void setFirstName(const std::string & fname);
	void setLastName(const std::string & lname);

	// Getters
	std::string getAccountNumber() const;
	const std::string getFirstName() const;
	const std::string getLastName() const;
	const std::string getFullName() const;
	double getBalance() const;
	bool getIsEmpty() const;

	// Expects an empty BankAccount object that will be filled through keyboard input
	static void getInstance(BankAccount & BA);
	// Expects an empty BankAccount object that will be filled with an opened-input-file
	static void getInstance(BankAccount & BA, std::ifstream & in);
};

