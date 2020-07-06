#define _CRT_SECURE_NO_WARNINGS 
#define MAX_ACC 100
#include <iostream>
#include <string.h> 
#define NAME_LEN 20
#define Comon_Ratio 100
#define Deposit_Ratio 50
using namespace std;
int makeacclan =0;


class Common_Account {
public:
	int Ratio = Comon_Ratio;
};

class Deposit_Account {
public:
	int Ratio = Deposit_Ratio;
};

class Account : public Common_Account,public Deposit_Account  {
private:
	const int accID;
	int balance;
	char* cusName;
	const long long SSN;
	int acctype;
public:


	Account(int accID, int balance, char* cusName, long long SSN,int acctype) :accID(accID), SSN(SSN) {
		this->acctype = acctype;
		this->balance = balance;
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, cusName);
	}

	Account(const Account& ref) :accID(ref.accID), SSN(ref.SSN) {
		balance = ref.balance;
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, ref.cusName);
		cout << "���������" << endl;
	}

	~Account() {
		if (cusName != nullptr)
			delete[] cusName;
	}
	void accpl(int mon) {
		balance += mon;
		if (acctype == 1) {
			balance += balance / Common_Account::Ratio;
			cout << "�߻��� ���ھ� : " << balance / Common_Account::Ratio << endl;
		}
		else if (acctype == 2) {
			balance += balance / Deposit_Account::Ratio;
			cout << "�߻��� ���ھ� : " << balance / Deposit_Account::Ratio << endl;
		}
		
	}
	bool accmin(int mon) {
		if (balance < mon) {
			return false;
		}
		balance -= mon;
		return true;
	}
	void print_info() {
		cout << "���� Id : " << accID << endl;
		cout << "��   �� :  " << cusName << endl;
		cout << "���� �ܾ�: " << balance << endl << endl;
	}
	bool checkID(int id) {
		return accID == id;
	}
	bool checkSSN(int ssn) {
		return this->SSN == ssn;
	}
};

class Account_Deposit : public Account {

};
enum eCheckType{
	ID, SSN, SSNVAL
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

	void selwhichacc() {
		int typewhatacc =0;
		cout << "---� ���¸� �����Ͻðڽ��ϱ�?---" << endl;
		cout << "	 1.�������" << endl;
		cout << "         2.���� ����" << endl << endl;
		cout << "���� : ";
		cin >> typewhatacc;
		if (typewhatacc == 1 || typewhatacc == 2)accmake(typewhatacc);
		else cout << "         ����� �����ϼ���" << endl << endl;
		return;
	}

	void accmake(int tomakeacc) {
		int accID;
		int a;
		char cusName[NAME_LEN];
		long long SSN;
		cout << "[ ���� ���� ]" << endl;
		cout << "���� ID : ";
		cin >> accID;
		if (check(accID, ID) != -1) {
			cout << "�̹� �����ϴ� ����ID�Դϴ�" << endl;
			return;
		}
		cout << "��  �� : ";
		cin >> cusName;
		cout << "�Աݾ� : ";
		cin >> a;
		if (a < 10) {
			cout << "10�� �̻� �־��ּ���." << endl;
			return;
		}
		cout << "�ֹε�� ��ȣ �Է�(-����) : ";
		cin >> SSN;
		if (check(SSN, eCheckType::SSN) == -1 && tomakeacc == 2) {
			cout << "���� ���¸� 1�� �̻� ���� �Ͽ��� ���ݰ��� ������ �����մϴ�." << endl;
			return;
		}
		if (tomakeacc == 1)  a += a / Comon_Ratio;
		else if (tomakeacc == 2)  a += a / Deposit_Ratio;
		acclist[Max] = new Account(accID, a, cusName, SSN,tomakeacc);
		Max++;
		return;
	}
	void accplus() {
		int accId;
		int a;
		cout << "���� ID : ";
		cin >> accId;
		cout << "�Աݾ� : ";
		cin >> a;
		if (check(accId, ID) == -1) {
			cout << "��ȿ���� ���� ID�Դϴ�." << endl;
			return;
		}
		acclist[check(accId, ID)]->accpl(a);
	}
	void accmina() {
		int accId;
		int a;

		cout << "���� ID : ";
		cin >> accId;
		cout << "�Աݾ� : ";
		cin >> a;
		if (check(accId, ID) == -1) {
			cout << "��ȿ���� ���� ID�Դϴ�." << endl;
			return;
		}
		bool cright = acclist[check(accId, ID)]->accmin(a);
		if (cright == false) {
			cout << "�ܾ׺���" << endl;
		}
	}
	void printinfo() {
		for (int i = 0; i < Max; i++) {
			acclist[i]->print_info();
		}
	}
	template<typename T>
	int check(T a, eCheckType type) {
		int howmanyssn = 0;
		for (int i = 0; i < Max; i++) {

			if (type == ID)
				if (acclist[i]->checkID(a))
					return i;
			if (type == SSN)
				if (acclist[i]->checkSSN(a))
					return i;
			if (type == SSNVAL)
				if (acclist[i]->checkSSN(a))
					howmanyssn++;
		}
		if (type == SSNVAL)
			return howmanyssn;

		return -1;
	}
};


int main() {
	int selnum;
	AccountManager* manager = new AccountManager();
	while (true)
	{
		cout << "--------MENU--------" << endl;
		cout << "   1.���°���" << endl;
		cout << "   2.��     ��" << endl;
		cout << "   3.��     ��" << endl;
		cout << "4.�������� ��ü ���" << endl;
		cout << "   5.��     ��" << endl << endl;

		cout << "���� : ";
		cin >> selnum;
		switch (selnum)
		{
		case 1: {
			manager->selwhichacc();
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
			cout << "����ε� ���� �����ϼ���" << endl;
		}
	}
}