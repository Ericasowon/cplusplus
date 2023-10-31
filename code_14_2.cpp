#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account {
public:
	string name;
	int id;
	double balance;
};

void add_account(vector<Account>& accounts) {
	string name;
	int number;
	double amount;

	cout << "Enter name, account number, and account balance : ";
	cin >> name >> number >> amount;
	Account acc;
	acc.name = name;
	acc.id = number;
	acc.balance = amount;
	accounts.push_back(acc);
}

void print_accounts(const vector<Account>& acc) {
	int n = acc.size();
	for (int i = 0; i < n; i++)
		cout << acc[i].name << ", " << acc[i].id << ", " << acc[i].balance << '\n';
}

void swap(Account& num1, Account& num2) {
	Account temp = num1;
	num1 = num2;
	num2 = temp;
}

bool less_than_by_name(const Account& num1, const Account& num2) {
	return num1.name < num2.name;
}

bool less_than_by_id(const Account& num1, const Account& num2) {
	return num1.id < num2.id;
}

bool less_than_by_balance(const Account& num1, const Account& num2) {
	return num1.balance < num2.balance;
}

void sort(vector<Account>& db, bool (*comp)(const Account&, const Account&)) {
	int size = db.size();
	for (int i = 0; i < size - 1; i++) {
		int smallest = i;
		for (int j = i + 1; j < size; j++)
			if (comp(db[j], db[smallest]))
				smallest = j;
		if (smallest != i)
			swap(db[i], db[smallest]);
	}
}

int main() {
	vector<Account> users;

	char cmd;
	bool done = false;

	do {
		cout << "[A]dd [N]ame [I]D [B]alance [Q]uit ===> ";
		cin >> cmd;
		switch (cmd) {
		case 'A':
		case 'a':
			add_account(users);
			break;
		case 'P':
		case 'p':
			print_accounts(users);
			break;
		case 'N':
		case 'n':
			sort(users, less_than_by_name);
			print_accounts(users);
			break;
		case 'I':
		case 'i':
			sort(users, less_than_by_id);
			print_accounts(users);
			break;
		case 'B':
		case 'b':
			sort(users, less_than_by_balance);
			print_accounts(users);
			break;
		case 'Q':
		case 'q':
			done = true;
			break;
		}
	} while (!done);
}