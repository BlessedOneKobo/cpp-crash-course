#include "Logger.h"
#include "InMemoryDatabase.h"
#include "Bank.h"

int main() {
	Bank bank{ new ConsoleLogger{ "cons" }, new InMemoryDatabase };

	bank.add_account(3333, 90);
	bank.add_account(7777, 12);
	bank.add_account(1111, 67);
	bank.show_accounts();
	
	bank.make_transfer(3333, 7777, 34.5);
	bank.set_logger(new FileLogger);
	bank.make_transfer(1111, 7777, 23);
	
	bank.show_accounts();
	
	// Will throw an exception because of insufficient balance
	bank.make_transfer(7777, 1111, 90);
}
