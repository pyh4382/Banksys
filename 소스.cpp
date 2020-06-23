#define _CRT_SECURE_NO_WARNINGS 
#define MAX_ACC 100
#include <iostream>
#include <string.h> 
#define NAME_LEN 20
using namespace std;

class Account {
private:
	const int accID;
	int balance;
	char* cusName;
	const long long SSN;
public:


	Account(int accID, int balance, char* cusName, long long SSN) :accID(accID), SSN(SSN) {

		this->balance = balance;
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, cusName);
	}

	Account(const Account& ref) :accID(ref.accID), SSN(ref.SSN) {
		balance = ref.balance;
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, ref.cusName);
		cout << "복사생성자" << endl;
	}

	~Account() {
		if (cusName != nullptr)
			delete[] cusName;
	}
	void accpl(int mon) {
		balance += mon;
	}
	bool accmin(int mon) {
		if (balance < mon) {
			return false;
		}
		balance -= mon;
		return true;
	}
	void print_info() {
		cout << "계좌 Id : " << accID << endl;
		cout << "이   름 :  " << cusName << endl;
		cout << "계좌 잔액: " << balance << endl << endl;
	}
	bool checkID(int id) {
		return accID == id;
	}
	bool checkSSN(int ssn) {
		return this->SSN == ssn;
	}
};
enum eCheckType {
	ID, SSN
};

class AccountManager {
private:
	Account* acclist[MAX_ACC];
	int Max = 0;
public:
	~AccountManager() {
		for (int a = 0; a < Max; a++)
			delete acclist[a];
	}
	void accmake() {
		int accID;
		int a;
		char cusName[NAME_LEN];
		long long SSN;
		cout << "[ 계좌 개설 ]" << endl;
		cout << "계좌 ID : ";
		cin >> accID;
		if (check(accID, ID) != -1) {
			cout << "이미 존재하는 계좌ID입니다" << endl;
			return;
		}
		cout << "이  름 : ";
		cin >> cusName;
		cout << "입금액 : ";
		cin >> a;
		if (a < 10) {
			cout << "10원 이상 넣어주세요." << endl;
			return;
		}
		cout << "주민등록 번호 입력(-제외) : ";
		cin >> SSN;
		if (check(SSN, eCheckType::SSN) != -1) {
			cout << "이미 가입된 주민등록번호 입니다" << endl;
			return;
		}
		acclist[Max] = new Account(accID, a, cusName, SSN);
		Max++;
		return;
	}
	void accplus() {
		int accId;
		int a;
		cout << "계좌 ID : ";
		cin >> accId;
		cout << "입금액 : ";
		cin >> a;
		if (check(accId, ID) == -1) {
			cout << "유효하지 않은 ID입니다." << endl;
			return;
		}
		acclist[check(accId, ID)]->accpl(a);
	}
	void accmina() {
		int accId;
		int a;

		cout << "계좌 ID : ";
		cin >> accId;
		cout << "입금액 : ";
		cin >> a;
		if (check(accId, ID) == -1) {
			cout << "유효하지 않은 ID입니다." << endl;
			return;
		}
		bool cright = acclist[check(accId, ID)]->accmin(a);
		if (cright == false) {
			cout << "잔액부족" << endl;
		}
	}
	void printinfo() {
		for (int i = 0; i < Max; i++) {
			acclist[i]->print_info();
		}
	}
	template<typename T>
	int check(T a, eCheckType type) {
		for (int i = 0; i < Max; i++) {

			if (type == ID)
				if (acclist[i]->checkID(a))
					return i;
			if (type == SSN)
				if (acclist[i]->checkSSN(a))
					return i;

		}
		return -1;
	}
};


int main() {
	int selnum;
	AccountManager* manager = new AccountManager();
	while (true)
	{
		cout << "--------MENU--------" << endl;
		cout << "   1.계좌개설" << endl;
		cout << "   2.입     금" << endl;
		cout << "   3.출     금" << endl;
		cout << "4.계좌정보 전체 출력" << endl;
		cout << "   5.종     료" << endl << endl;

		cout << "선택 : ";
		cin >> selnum;
		switch (selnum)
		{
		case 1: {
			manager->accmake();
			break;
		}
		case 2: {
			manager->accplus();
			break;
		}
		case 3: {
			manager->accmina();
			break;
		}
		case 4: {
			manager->printinfo();
			break;
		}
		case 5: {
			delete manager;
			return 0;
		}
		default:
			cout << "제대로된 수를 선택하세요" << endl;
		}
	}
}