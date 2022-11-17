#include "header.h"


void Time::readData()
{
	ifstream file;
	file.open("account.txt");

	if (!file) { //오류처리
		cout << "AccountDB open 오류\n";
		exit(100);
	}


	string read;
	file.seekg(0);

	getline(file, read); // 정기권 쓰루
	getline(file, read); // 단일권 쓰루

	//Date읽기
	getline(file, read);

	int D = stoi(read);

	//Time읽기
	getline(file, read);

	int T = stoi(read);

	file.close();


	bY = D / 10000;
	bM = (D % 10000) / 100;
	bD = (D % 10000) % 100;
	bH = T / 100;
	bmin = T % 100;
}

void Time::writeData()
{
	ofstream file;
	file.open("account.txt", ios::app);

	if (!file) { //오류처리
		cout << "account open 오류\n";
		exit(100);
	}

	file << int2string(Y) + int2string(M) + int2string(D) << "\n";
	file << int2string(H) + int2string(min) << "\n";

	file.close();

	return;
}

int Time::checkDate(int year, int month, int day)
{
	/* return 값 의미
	0 성공
	1 31일이 없어요
	2 2월 29은 없어요(!윤달)
	3.2월 30,31은 없어요 (윤달)
	*/
	if ((month % 2 == 1)) //odd month 
	{
		if (month <= 7) {
			//if (day <= 0 || day > 31) return 0;
		}
		else { // month > 7 
			if (day <= 0 || day > 30) return 1;
		}
	}
	else //even month
	{
		if (month <= 6) {
			if (month == 2)
			{
				if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) // leap year
				{
					if (day <= 0 || day > 29) return 3;
				}
				else if (day <= 0 || day > 28) { //윤달이 아닐때

					return 2;
				}

			}
			if (day <= 0 || day > 30) return 1;
		}
		//else { // month > 6

			//if (day <= 0 || day > 31) return 0;
		//}
	}

	return 0; //성공
}

void Time::insertTime()//시간입력함수
{

	// 이전시간 기록
	cout << "\n\n******************************" << endl;
	cout << "마지막 날짜(";
	cout << bY << "-" << int2string(bM) << "-" << int2string(bD)
		<< "  " << int2string(bH) << ":" << int2string(bmin) << ")\n";
	int inputDate;

	// 1) input 길이 12
	// 2) input 이 다 숫자인지
	// 예외처리
	while (1) {
	label1:
		string strDate;
		cout << "\n현재 날짜는 몇 년 몇 월 며칠입니까?(ex:20221201): \n>> ";
		getline(cin, strDate);
		cin.clear();
		if (strDate.length() != 8) {
			cout << "8글자를 입력하셔야합니다." << endl;
			goto label1;
		}
		for (int i = 0; i < 8; i++) {
			if (strDate[i] < '0' || strDate[i]>'9') {
				cout << "숫자만 입력하세요" << endl;
				goto label1;
			}
		}
		inputDate = stoi(strDate);
		Y = inputDate / 10000;
		M = (inputDate % 10000) / 100;
		D = (inputDate % 10000) % 100;

		if (inputDate < (bY * 10000 + bM * 100 + bD)) {
			cout << "** 마지막 날짜 이후의 날짜를 입력하세요. \n" << endl;
			continue;
		}if (1900 > Y || Y > 2999) {
			cout << "** '년'은 1900~2999 내에서 입력해주세요\n" << endl; continue;
		}if (M < 1 || M>12) {
			cout << "**'월'은 1~12 내에서 입력해주세요\n"; continue;
		}if (D < 1 || D>31) {
			cout << "**'일'은 1~31 내에서 입력해주세요\n"; continue;
		}if (checkDate(Y, M, D) != 0) {
			cout << "** 없는 날짜입니다. 다시 입력해주세요\n"; continue;
		}
		break;
	}

	Date = inputDate;
	//Y = Date / 10000;

	
	cin.clear();

	while (1) {
	label2:
		string strTime;
		cout << "현재 시간은 몇 시 몇 분 입니까?(ex1:0959 ex2:1701): \n>> ";
		getline(cin, strTime);
		cin.clear();
		if (strTime.length() != 4) {
			cout << "4글자를 입력하셔야합니다." << endl;
			goto label2;
		}
		for (int i = 0; i < 4; i++) {
			if (strTime[i] < '0' || strTime[i]>'9') {
				cout << "숫자만 입력하세요" << endl;
				goto label2;
			}
		}

		Time = stoi(strTime);
		H = Time / 100;
		min = Time % 100;
		cin.clear();

		if (Date == (bY * 10000 + bM * 100 + bD)) {

			if (Time < (bH * 100 + bmin)) {
				cout << "마지막 시간 이후의 시간을 입력하세요.\n" << endl;
				continue;
			}if (inputDate == (bY * 10000 + bM * 100 + bD) && Time == (bH * 100 + bmin)) {
				cout << "마지막 시간 이후의 시간을 입력하세요.\n" << endl;
				continue;
			}
		}
		if (H < 0 || H>23) {
			cout << "'시간'은 0~23 안에서 입력해주세요.\n" << endl;
			continue;
		}if (min < 0 || min>59) {
			cout << "'분'은 0~59 안에서 입력해주세요.\n" << endl;
			continue;
		}

		break;
	}


	bY = Y;
	bM = M;
	bD = D;
	bH = H;
	bmin = min;


}



string Time::int2string(int I)
{

	if (I < 10) return to_string(0) + to_string(I);
	else return to_string(I);


}

string Time::leftTime(string num, string start, string finish)
{
	int sY, sM, sD, sH, smin;
	int lY, lM, lD, lH, lmin;  //끝난시간

	//cout << "본무시작인자" << start << "끝" << finish << "\n";

	int n;
	stringstream ssInt(num);
	ssInt >> n;

	//start int로변경
	string sDate, sTime;
	sDate.assign(start, 0, 8);
	sTime.assign(start, 8, 11);

	int dDate = stoi(sDate);
	int dTime = stoi(sTime);
	//cout << Date << "날짜" << Time << "시간\n";
	sY = dDate / 10000;
	sM = (dDate % 10000) / 100;
	sD = (dDate % 10000) % 100;
	//cout << Time << "타임입니다";
	sH = dTime / 100;
	smin = dTime % 100;

	//finish int로변경
	string lDate, lTime;
	lDate.assign(finish, 0, 8);
	lTime.assign(finish, 8, 11);

	dDate = stoi(lDate);
	dTime = stoi(lTime);
	//cout << Date << "날짜" << Time << "시간\n";
	lY = dDate / 10000;
	lM = (dDate % 10000) / 100;
	lD = (dDate % 10000) % 100;
	//cout << Time << "타임입니다";
	lH = dTime / 100;
	lmin = dTime % 100;


	if (n == 3) { //
		int a = sH * 60 + smin;
		int b = lH * 60 + lmin;
		int c = b - a;
		lH = c / 60;
		lmin = c % 60;

		return to_string(lH) + "시간" + to_string(lmin) + "분";
	}
	else { //정기권
		if (lM != sM) {
			return to_string((30 - sD) + lD) + "일";
		}
		else {
			return to_string(lD - sD) + "일";
		}
	}

}

void Time::showTime()
{
	cout << "\n(" << bY << "-" << int2string(bM) << "-" << int2string(bD)
		<< "  " << int2string(bH) << ":" << int2string(bmin) << ")\n";

}

string Time::returnTime()
{
	return int2string(Y) + int2string(M) + int2string(D) + int2string(H) + int2string(min);
}