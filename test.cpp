#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string.h> 
#define NAME_LEN 20
using namespace std;
typedef struct {
	int accID;
	int balance;
	char cusName[NAME_LEN];
}Account;
void accmake();
void accplus();
void accmina();
void printinfo();

template<typename T>
int check(T a);
Account acclist[100];
int Max = 0;
void mainpage() {
	int selnum;
	cout << "--------MENU--------"<<endl ;
	cout << "   1.���°���" << endl;
	cout << "   2.��     ��" << endl;
	cout << "   3.��     ��" << endl;
	cout << "4.�������� ��ü ���" << endl;
	cout << "   5.��     ��" << endl<<endl;

	cout << "���� : ";
	cin >> selnum;
	switch (selnum)
	{
	case 1: {
		accmake();
		break;
	}
	case 2: {
		accplus();
		break;
	}
	case 3: {
		accmina();
		break;
	}
	case 4: {
		printinfo();
		break;
	}
	case 5: {
		return;
	}
		default:
			cout << "����ε� ���� �����ϼ���" << endl;
			mainpage();
			break;
	}
	mainpage();
}
void accmake() {
	int accID;
	int a;
	char cusName[NAME_LEN];
	cout << "[ ���� ���� ]" << endl;
	cout << "���� ID : ";
	cin >> accID;
	if(check(accID)==-1)acclist[Max].accID=accID;
	else{
		 cout << "�̹� �����ϴ� ����ID�Դϴ�" <<endl;
		 return; 
	}
	cout << "��  �� : ";
	cin >> acclist[Max].cusName;
	cout << "�Աݾ� : ";
	cin >> a;
	if (a < 10){
		 cout << "10�� �̻� �־��ּ���." << endl;
		 return;
	} 
	else acclist[Max].balance = a;
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
	if(check(accId)==-1){
		cout << "��ȿ���� ���� ID�Դϴ�." << endl;
		return;
	}
	acclist[check(accId)].balance += a;
}
void accmina() {
	int accId;
	int a;
	cout << "���� ID : ";
	cin >> accId;
	cout << "�Աݾ� : ";
	cin >> a;
	if(check(accId)==-1){
		cout << "��ȿ���� ���� ID�Դϴ�." << endl;
		return;
	}
	acclist[check(accId)].balance -= a;
}
void printinfo() {
	for(int i =0;i < Max;i++){
			cout << "���� Id : " << acclist[i].accID <<endl;
			cout << "��   �� : : " << acclist[i].cusName <<endl;
			cout << "���� Id : " << acclist[i].balance <<endl<<endl;
	}
}
template<typename T>
int check(T a){
	for(int i = 0;i < Max;i++){
		if (a==acclist[i].accID)return i;
	}
	return -1;
}
int main() {
	mainpage();
}
