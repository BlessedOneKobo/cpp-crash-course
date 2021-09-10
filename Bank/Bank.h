#ifndef BANK_H
#define BANK_H

#include "Logger.h"
#include "InMemoryDatabase.h"

struct Bank {
	Bank(Logger* logger, InMemoryDatabase* database)
		: logger{ logger }, database{ database } {}

	void set_logger(Logger* new_logger) {
		logger = new_logger;
	}

	void make_transfer(long from, long to, double amount) {
		database->make_transfer(from, to, amount);
		logger->log_transfer(from, to, amount);
	}

	void add_account(long account_id, double initial_amount) {
		database->add_account(account_id, initial_amount);
	}

	void show_accounts() {
		database->dump();
	}
private:
	Logger* logger;
	InMemoryDatabase* database;
};

#endif
