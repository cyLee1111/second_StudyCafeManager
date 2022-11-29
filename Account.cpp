#include "header.h"


void Account::whatTime(string time) {
	T = time;
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

	//totalAccount = Saccount + Oaccount;

}

void Account::writeDB()
{
	ofstream file;
	file.open("account.txt", ios::trunc);

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
	cout << "전체 매출 : " << Saccount + Oaccount << endl;
	cout << "------------------------------" << endl;
}

string Account::int2string(int I)
{
	if (I < 10) return to_string(0) + to_string(I);
	else return to_string(I);

}

string Account::plusDate(int Y, int M, int D, int day) {

	day = day - 1;

	if ((M % 2 == 1)) //odd month 
	{
		if (M <= 7) {  //31까지
			if (31 - day >= D) {  // 달 안넘겨줘도됨

				return to_string(Y) + int2string(M) + int2string(D + day) + "2359";
			}
			else { // 달 넘겨줌

				return to_string(Y) + int2string(M + 1) + int2string((D + day) - 31) + "2359";
			}
		}
		else { // month > 7  30까지
			if (30 - day >= D) {  // 달 안넘겨줘도됨

				return to_string(Y) + int2string(M) + int2string(D + day) + "2359";
			}
			else { // 달 넘겨줌

				return to_string(Y) + int2string(M + 1) + int2string((D + day) - 30) + "2359";
			}
		}
	}
	else //even month
	{
		if (M <= 6) {
			if (M == 2)
			{
				if (((Y % 4 == 0) && (Y % 100 != 0)) || (Y % 400 == 0)) // leap year
				{
					if (29 - day >= D) {  // 달 안넘겨줘도됨

						return to_string(Y) + int2string(M) + int2string(D + day) + "2359";
					}
					else { // 달 넘겨줌

						return to_string(Y) + int2string(M + 1) + int2string((D + day) - 29) + "2359";
					}
				}
				else { //윤달이 아닌 2월

					if (28 - day >= D) {  // 달 안넘겨줘도됨

						return to_string(Y) + int2string(M) + int2string(D + day) + "2359";
					}
					else { // 달 넘겨줌

						return to_string(Y) + int2string(M + 1) + int2string((D + day) - 28) + "2359";
					}
				}

			}
			else { //윤달아닌
				if (M == 12) {//12월일때
					if (31 - day >= D) {  // 달 안넘겨줘도됨

						return to_string(Y) + int2string(M) + int2string(D + day) + "2359";
					}
					else { // 달 넘겨줌
						return to_string(Y + 1) + int2string(1) + int2string((D + day) - 31) + "2359";
					}

				}
				if (30 - day >= D) {  // 달 안넘겨줘도됨

					return to_string(Y) + int2string(M) + int2string(D + day) + "2359";
				}
				else { // 달 넘겨줌

					return to_string(Y) + int2string(M + 1) + int2string((D + day) - 30) + "2359";
				}
			}
		}
		else { // month > 6

			if (25 >= D) {  // 달 안넘겨줘도됨

				return to_string(Y) + int2string(M) + int2string(D + day) + "2359";
			}
			else { // 달 넘겨줌

				return to_string(Y) + int2string(M + 1) + int2string((D + day) - 31) + "2359";
			}
		}
	}

}

string Account::payTicket(string seat)
{
	int num, price = 0;
	int hour, day;


	//날짜
	stringstream ssInt(seat);
	ssInt >> num;
	string sDate, sTime;
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

	retry:

	if (num == 1 || num == 2) {  //정기권
		int choice;
		if (num == 1) {
			cout << "[정기권 - 지정석]\n";
			cout << "1.  7일 -------  70원\n";
			cout << "2. 14일 ------- 140원\n";
			cout << "3. 28일 ------- 280원\n";
			cout << "이용하실 이용권을 선택해주세요 >> ";
			cin >> choice;
			if (cin.fail()) {
				cout << "1,2,3 중에서 입력해주세요.\n" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				goto retry;
			}
			cin.clear();
		}
		if (num == 2) {
			cout << "[정기권 - 자유석]\n";
			cout << "1.  7일 -------  70원\n";
			cout << "2. 14일 ------- 140원\n";
			cout << "3. 28일 ------- 280원\n";
			cout << "이용하실 이용권을 선택해주세요 >> ";
			cin >> choice;
			if (cin.fail()) {
				cout << "1,2,3 중에서 입력해주세요.\n" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				goto retry;
				
			}
			cin.clear();
		}

		if (!(choice == 1 || choice == 2 || choice == 3)) {
			cout << "1,2,3 중에서 입력해주세요. \n" << endl;
			goto retry;
		}

		if (choice == 1) { //7일
			day = 7; price = 70;
			cout << price << "원 결제합니다. (Enter)\n";
			checkEnter();
			while (getchar() != '\n');
			Saccount += price;
			//cout << "돈!!!!!!!1" << Saccount << endl;
			return plusDate(Y, M, D, day);
		}
		else if (choice == 2) {  //14일
			day = 14; price = 140;
			cout << price << "원 결제합니다. (Enter)\n";
			checkEnter();
			while (getchar() != '\n');
			Saccount += price;
			//cout << "돈!!!!!!!1" << Saccount << endl;
			return plusDate(Y, M, D, day);
		}
		else if (choice == 3) {   //28일
			day = 28; price = 280;
			cout << price << "원 결제합니다. (Enter)\n";
			checkEnter();
			while (getchar() != '\n');
			Saccount += price;
			//cout << "돈!!!!!!!1" << Saccount << endl;
			return plusDate(Y, M, D, day);
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
		if (cin.fail()) {
			cout << "1,2,3 중에서 입력해주세요.\n" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			goto retry;
		}
		cin.clear();

		if (!(choice == 1 || choice == 2 || choice == 3)) {
			cout << "1,2,3 중에서 입력해주세요.\n" << endl;
			goto retry;
		}

		if (choice == 1) {
			hour = 8; price = 8;
			if (H >= 16) {
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				while (getchar() != '\n');
				Oaccount += price;
				return to_string(Y) + int2string(M) + int2string(D) + "2359";
			}
			else {
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				while (getchar() != '\n');
				Oaccount += price;
				return to_string(Y) + int2string(M) + int2string(D) + int2string(H + hour) + int2string(min);
			}
		}
		else if (choice == 2) {
			hour = 16; price = 16;
			if (H >= 8) {
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				while (getchar() != '\n');
				Oaccount += price;
				return to_string(Y) + int2string(M) + int2string(D) + "2359";
			}
			else {
				cout << price << "원 결제합니다. (Enter)\n";
				checkEnter();
				while (getchar() != '\n');
				Oaccount += price;
				return to_string(Y) + int2string(M) + int2string(D) + int2string(H + hour) + int2string(min);
			}
		}
		else if (choice == 3) {
			hour = 24; price = 24;
			cout << price << "원 결제합니다. (Enter)\n";
			checkEnter();
			while (getchar() != '\n');
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