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
	cout << "   1.계좌개설" << endl;
	cout << "   2.입     금" << endl;
	cout << "   3.출     금" << endl;
	cout << "4.계좌정보 전체 출력" << endl;
	cout << "   5.종     료" << endl<<endl;

	cout << "선택 : ";
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
			cout << "제대로된 수를 선택하세요" << endl;
			mainpage();
			break;
	}
	mainpage();
}
void accmake() {
	int accID;
	int a;
	char cusName[NAME_LEN];
	cout << "[ 계좌 개설 ]" << endl;
	cout << "계좌 ID : ";
	cin >> accID;
	if(check(accID)==-1)acclist[Max].accID=accID;
	else{
		 cout << "이미 존재하는 계좌ID입니다" <<endl;
		 return; 
	}
	cout << "이  름 : ";
	cin >> acclist[Max].cusName;
	cout << "입금액 : ";
	cin >> a;
	if (a < 10){
		 cout << "10원 이상 넣어주세요." << endl;
		 return;
	} 
	else acclist[Max].balance = a;
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
	if(check(accId)==-1){
		cout << "유효하지 않은 ID입니다." << endl;
		return;
	}
	acclist[check(accId)].balance += a;
}
void accmina() {
	int accId;
	int a;
	cout << "계좌 ID : ";
	cin >> accId;
	cout << "입금액 : ";
	cin >> a;
	if(check(accId)==-1){
		cout << "유효하지 않은 ID입니다." << endl;
		return;
	}
	acclist[check(accId)].balance -= a;
}
void printinfo() {
	for(int i =0;i < Max;i++){
			cout << "계좌 Id : " << acclist[i].accID <<endl;
			cout << "이   름 : : " << acclist[i].cusName <<endl;
			cout << "계좌 Id : " << acclist[i].balance <<endl<<endl;
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
