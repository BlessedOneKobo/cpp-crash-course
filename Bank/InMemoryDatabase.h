#ifndef IN_MEMORY_DATABASE_H
#define IN_MEMORY_DATABASE_H

#include <cstdio>
#include <stdexcept>

struct Account {
	long id;
	double amount;
	Account* next{ nullptr };
};

struct AccountDatabase {
private:
	virtual void set_amount(long account_id, double amount) = 0;
	virtual double get_amount(long account_id) = 0;
};

struct InMemoryDatabase : AccountDatabase {
	static long count;

	InMemoryDatabase() {
		first_account = nullptr;
		last_account = nullptr;
	}

	~InMemoryDatabase() {
		Account* iter = first_account;
		Account* next = nullptr;
		while (iter) {
			next = iter->next;
			delete iter;
			iter = next;
		}
	}

	void add_account(long account_id, double initial_amount) {
		Account* new_account = new Account{ account_id, initial_amount };

		if (first_account) {
			last_account->next = new_account;
			last_account = new_account;
		} else {
			first_account = last_account = new_account;
		}
	}

	void make_transfer(long from, long to, double amount) {
		double from_amount_final_value = get_amount(from) - amount;
		bool can_transfer = from_amount_final_value >= 0;

		if (can_transfer) {
			set_amount(from, from_amount_final_value);
			set_amount(to, get_amount(to) + amount);
		} else {
			throw std::runtime_error{ "Insufficient funds in src account" };
		}
	}

	void dump() const {
		printf("\n---| Dump |---:\n");
		for (Account* iter = first_account; iter; iter = iter->next) {
			printf("[%ld]: %f\n", iter->id, iter->amount);
		}
		printf("---|------|---\n\n");
	}
private:
	Account* first_account;
	Account* last_account;

	Account* get_account_by_id(long id) {
		for (Account* iter = first_account; iter; iter = iter->next) {
			if (iter->id == id) {
				return iter;
			}
		}

		throw std::runtime_error{ "get_account_by_id: Could not find account" };
	}

	void set_amount(long account_id, double amount) override {
		Account* account = get_account_by_id(account_id);
		account->amount = amount;
	}

	double get_amount(long account_id) override {
		Account* account = get_account_by_id(account_id);
		return account->amount;
	}
};

#endif
