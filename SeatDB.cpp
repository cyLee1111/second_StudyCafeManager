#include "header.h"

bool SeatDB::readFile()
{
	string filename = "seat.txt";
	ifstream fin(filename);
	if (!fin.is_open()) {
		cout << "DB파일이 없습니다. seat.txt 파일을 생성합니다...\n";
		ofstream fout;
		fout.open(filename);
		for (int i = 0; i < SEAT_MAX; i++) {
			fout << "0" << endl;
			seat[i] = "0";
		}
		return true;
	}

	for (int i = 0; i < SEAT_MAX; i++) {
		getline(fin, seat[i]);
	}

	return true;
}

bool SeatDB::writeFile()
{
	string filename = "seat.txt";
	try {
		ofstream fout(filename);
		if (!fout.is_open()) {
			cerr << "파일 쓰기 실패" << endl;
			return false;
		}

		for (int i = 0; i < SEAT_MAX; i++) {
			fout << seat[i] << endl;
		}
		cout << "SeatDB 저장이 완료되었습니다." << endl;
	}
	catch (exception& e) {
		return false;
	}
	return false;
}

// 현재좌석상태 보여주는 함수
void SeatDB::showSeat()
{
	readFile();
	cout << "\n[           좌석현황          ]" << endl;
	cout << "(□:빈좌석,▦:자유석,■:지정석)" << endl;
	cout << "   1  2  3  4  5  6  7  8  9 10" << endl;
	for (int i = 0; i < SEAT_MAX; i++) {
		if (i % 10 == 0) {
			cout << char('A' + i / 10) << " ";
		}
		string c = toChar(seat[i]);
		cout << c << " ";
		if (i % 10 == 9) {
			cout << endl;
		}
	}
	cout << endl;
}

// 좌석선택 함수
int SeatDB::chooseSeat(int memType)
{
	readFile();

	if(ifFull()){ // 좌석DB 빈자리 탐색
		cout << "\n좌석이 모두 사용중으로 메인화면으로 이동합니다." << endl;
		return -1;
	}

	string chooseS;	// 사용자입력(ex: A3, C10)
	do {
		cout << "\n[           좌석선택          ]" << endl;
		showSeat();
		cout << "\n좌석을 선택하세요(ex: A3, C10)(□: 빈 좌석, ▦: 자유석, ■: 지정석) : ";
		cin >> chooseS;
	} while (!checkInput(chooseS));

	int chooseIdx = checkInput(chooseS) - 1;
	fixSeat(memType, chooseIdx);

	return chooseIdx;

}

// 좌석DB 안이 빈자리(0) 없이 꽉 차있는지
bool SeatDB::ifFull()
{
	for (int i = 0; i < SEAT_MAX; i++) {
		if(seat[i].compare("0")==0){
			return false;
		}
	}	
	return true;
}

// 좌석선택 input검사 함수
int SeatDB::checkInput(string s)
{
	string s1, s2;	// ex: 입력받은 A3에서 A부분과 3부분
	s1 = s.substr(0, 1);
	s2 = s.substr(1);

	if (s1.compare("A") < 0 || s1.compare("C") > 0) {
		return 0;
	}
	if (stoi(s2) < 1 || stoi(s2) > 10) {
		return 0;
	}

	int ss = 0;
	if (s1.compare("A") == 0) {
		ss = 0 + stoi(s2);
	}
	else if (s1.compare("B") == 0) {
		ss = 10 + stoi(s2);
	}
	else if (s1.compare("C") == 0) {
		ss = 20 + stoi(s2);
	}

	if (seat[ss - 1].compare("0") == 0) {
		return ss;
	}
	else {
		return 0;
	}
}

// 선택받은 좌석수정
bool SeatDB::fixSeat(int memType, int idx)
{
	string fixStr;
	if (memType == 1) {			// 정기권지정석
		fixStr = "2";
	}
	else if (memType == 2 || memType == 3) {	// 정기권자유석, 단기권자유석
		fixStr = "1";
	}
	else {
		return false;
	}

	seat[idx] = fixStr;
	writeFile();
	return true;
}

// 선택받은 좌석삭제
bool SeatDB::delSeat(int idx)
{
	if (idx < 0) {
		//cout << "좌석삭제할거없음" << endl;
		return false;
	}
	readFile();
	seat[idx] = "0";
	writeFile();
	return true;
}

// 0,1,2 숫자를 '□','▦','■'로 바꿔줌
string SeatDB::toChar(string seat)
{
	if (seat.compare("0") == 0) {
		return "□";
	}
	else if (seat.compare("1") == 0) {
		return "▦";
	}
	else if (seat.compare("2") == 0) {
		return "■";
	}
	else {
		return "??";
	}
}

// 0~29 인덱스를 A1~C10 으로 변경
string SeatDB::idxToString(int idx)
{
	char c1 = char('A' + (idx / 10));
	string c2 = to_string((idx % 10) + 1);
	return c1 + c2;
}