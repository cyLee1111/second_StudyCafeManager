#include "header.h"


void Account::whatTime(string time){
	T=time;
}

void Account::readDB()
{
	string filename = "account.txt";
	ifstream fileIn(filename);
	if (!fileIn.is_open()) {
		cout << "DB파일이 없습니다. account.txt 파일을 생성합니다...\n";
		ofstream fout(filename);
		fout << "0" << endl;
		fout << "0" << endl;
		fout << "19000101" << endl;
		fout << "0101" << endl;
		fout.close();
	}
	fileIn.close();

	ifstream file(filename);


	//가격 불러오기

	string read;
	file.seekg(0);
	getline(file, read);
	Saccount = stoi(read);

	getline(file, read);
	Oaccount = stoi(read);

	file.close();

	totalAccount = Saccount+Oaccount;

}

void Account::writeDB()
{
	ofstream file;
	file.open("account.txt", ios::out);

	if (!file) { //오류처리
		cout << "account open 오류\n";
		exit(100);
	}

	string write = to_string(Saccount);
	file << write << "\n";
	write = to_string(Oaccount);
	file << write << "\n";

	file.close();

	return;
}

void Account::showAccount()
{
	cout << "정기권 총액 : " << Saccount << endl;
	cout << "단일권 총액 : " << Oaccount << endl;
	cout << "------------------------------" << endl;
	cout << "전체 매출 : " << totalAccount << endl;
	cout << "------------------------------" << endl;
}

string Account::int2string(int I)
{
	if (I < 10) return to_string(0) + to_string(I);
	else return to_string(I);

}

string Account::payTicket(string seat)
{
	int num, price = 0;
//	int fY, fM, fD, fH, fmin;
	int hour, day;


//날짜
	stringstream ssInt(seat);
	ssInt >> num;
	string sDate,sTime; 
	sDate.assign(T, 0, 8);
	sTime.assign(T, 8, 11);

	int Date = stoi(sDate);
	int Time = stoi(sTime);

	Y = Date / 10000;
	M = (Date % 10000) / 100;
	D = (Date % 10000) % 100;

	H = Time / 100;
	min = Time % 100;


	//결제정보입력

	if (num == 1 || num == 2) {  //정기권
		int choice;
		if (num == 1) {
			cout << "[정기권 - 지정석]\n";
			cout << "1.  7일 -------  70원\n";
			cout << "2. 14일 ------- 140원\n";
			cout << "3. 28일 ------- 280원\n";
			cout << "이용하실 이용권을 선택해주세요 >> ";
			cin >> choice;
			cin.clear();
		}
		if (num == 2) {
			cout << "[정기권 - 자유석]\n";
			cout << "1.  7일 -------  70원\n";
			cout << "2. 14일 ------- 140원\n";
			cout << "3. 28일 ------- 280원\n";
			cout << "이용하실 이용권을 선택해주세요 >> ";
			cin >> choice;
			cin.clear();
		}

		if (choice == 1) {
			day = 7; price = 70;
			if (24 <= D) {
				if (M == 12) {
					cout << price << "원 결제합니다. (Enter)\n";
					checkEnter();
					Saccount+=price ;
					return to_string(Y + 1) + to_string(01) + int2string((D + 6) - 30) + "2359";
				}
				else {
					cout << price << "원 결제합니다. (Enter)\n";
					checkEnter();
					Saccount+=price ;
					return to_string(Y) + int2string(M + 1) + int2string((D + 6) - 30) + "2359";
				}
			}
			else {
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				Saccount+=price ;
				return to_string(Y) + int2string(M) + int2string(D + 6) + "2359";
			}
		}
		else if (choice == 2) {
			day = 14; price = 140;
			if (17 <= D) {
				if (M == 12) {
					cout << price << "원 결제합니다. (Enter)\n";
					checkEnter();
					Saccount+=price ;
					return to_string(Y + 1) + to_string(01) + int2string((D + 13) - 30) + "2359";
				}
				else {
					cout << price << "원 결제합니다. (Enter)\n";
					checkEnter();
					Saccount+=price ;
					return to_string(Y) + int2string(M + 1) + int2string((D + 13) - 30) + "2359";
				}
			}
			else {
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				Saccount+=price ;
				return to_string(Y) + int2string(M) + int2string(D + 13) + "2359";
			}
		}
		else if (choice == 3) {
			day = 28; price = 280;
			if (3 <= D) {
				if (M == 12) {
					cout << price << "원 결제합니다. (Enter)\n";
					checkEnter();
					Saccount+=price ;
					return to_string(Y + 1) + to_string(01) + int2string((D + 27) - 30) + "2359";
				}
				else {
					cout << price << "원 결제합니다. (Enter)\n";
					checkEnter();
					Saccount+=price ;
					return to_string(Y) + int2string(M + 1) + int2string((D + 27) - 30) + "2359";
				}
			}
			else {
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				Saccount+=price ;
				return to_string(Y) + int2string(M) + int2string(D + 27) + "2359";
			}
		}


	}
	else if (num == 3) {  //단일권
		int choice;
		cout << "[단일권 - 자유석]\n";
		cout << "1.  8시간 -------  8원\n";
		cout << "2. 16시간 ------- 16원\n";
		cout << "3. 24시간 ------- 24원\n";
		cout << "이용하실 이용권을 선택해주세요 >> ";
		cin >> choice;
		cin.clear();

		if (choice == 1) {
			hour = 8; price = 8;
			if (H >= 16) {
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				Oaccount += price;
				return to_string(Y) + int2string(M) + int2string(D) + "2359";
			}
			else {
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				Oaccount += price;
				return to_string(Y) + int2string(M) + int2string(D) + int2string(H + hour) + int2string(min);
			}
		}
		else if (choice == 2) {
			hour = 16; price = 16;
			if (H >= 8) { 
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				Oaccount += price;
				return to_string(Y) + int2string(M) + int2string(D) + "2359"; 
			}
			else {
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				Oaccount += price;
				return to_string(Y) + int2string(M) + int2string(D) + int2string(H + hour) + int2string(min);
			}
		}
		else if (choice == 3) {
			hour = 24; price = 24;
			cout << price << "원 결제합니다. (Enter)\n";
			checkEnter();
			Oaccount += price;
			return to_string(Y) + int2string(M) + int2string(D) + "2359";
		}
	}

	return "0";
	
}

bool Account::checkEnter()
{
	char s = 0;
	while (s != 13) {
		if (!_kbhit()) {
			s = _getch();
		}
	}
	return true;
}
