﻿#include "header.h"

//노드를 연결리스트에 추가하는 함수
void SeasonDB::AddNode(Season _season)
{

	if (cntSize == 0)
	{
		start->DB_phone_num = _season.DB_phone_num;
		start->DB_arrival_time = _season.DB_arrival_time;
		start->DB_departure_time = _season.DB_departure_time;
		start->DB_expert_date = _season.DB_expert_date;
		start->DB_payment_date = _season.DB_payment_date;
		start->DB_seat_num = _season.DB_seat_num;
		start->next = nullptr;
		cntSize++;

		return;
	}
	else
	{
		Season* current = new Season();
		current->DB_phone_num = _season.DB_phone_num;
		current->DB_arrival_time = _season.DB_arrival_time;
		current->DB_departure_time = _season.DB_departure_time;
		current->DB_expert_date = _season.DB_expert_date;
		current->DB_payment_date = _season.DB_payment_date;
		current->DB_seat_num = _season.DB_seat_num;
		current->next = nullptr;
		Season* temp = start;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = current;
		cntSize++;

		return;
	}

	cout << "addNode안되었어요(seasondb.cpp)" << endl;
}

//노드 삭제 함수
bool SeasonDB::deleteSeason(string phonenum)
{
	Season* temp = start;
	Season* del;
	Season* swap;
	int nodeIndex = 0;
	//searchSeasonDB에서 전화번호로 탐색하여 인덱스+1값을 반환 받음
	nodeIndex = searchSeasonDB(phonenum) - 1;
	cout << nodeIndex << "번째 노드 삭제됩니다. (시즌DB)" << endl;
	if (nodeIndex != 0) {
		for (int i = 0; i < nodeIndex - 1; i++)
		{
			temp = temp->next;
		}
		del = temp->next;
		swap = del->next;
		temp->next = swap;
	}
	else {
		start = temp->next;
		del = temp;
	}
	delete del;
	cntSize--;

	return true;

}

void SeasonDB::ReEntrance(string phonenum, string current_time)
{
	Season* temp = start;
	int nodeIndex = searchSeasonDB(phonenum) - 1;

	for (int i = 0; i < nodeIndex - 1; i++)
	{
		temp = temp->next;
	}

	temp->DB_arrival_time = current_time;

	//	cout << " 정기권 고객 재입장 입실시간 업데이트함(SeasonDB.cpp)\n";

}
void SeasonDB::ReEntranceNseat(string phonenum, int seatnum, string current_time)
{
	Season* temp = start;
	int nodeIndex = searchSeasonDB(phonenum) - 1;

	for (int i = 0; i < nodeIndex - 1; i++)
	{
		temp = temp->next;
	}

	temp->DB_arrival_time = current_time;
	temp->DB_seat_num = to_string(seatnum);

	cout << "정기권 고객 재입장 입실시간,자리번호 업데이트함(SeasonDB.cpp)\n";
	cout << "업데이트한 도착시간 : " << temp->DB_arrival_time << " 현재시간과 동일해야함(SeasonDB.cpp)\n";
	cout << "업데이트한 자리번호 : " << temp->DB_seat_num << "(시즌DB)" << endl;

}
//자리번호 넘겨줄 함수
int SeasonDB::searchSeasonDB_retseatIdx(string phonenum)
{

	Season* current = start;
	int int_seatnum = 100;
	string string_seatnum;
	SeatDB seat;
	cout << "searchSeasonDB:: (시즌DB)" << endl;
	cout << "찾을 전화번호:" << phonenum << "(시즌DB)" << endl;
	while (current != NULL)
	{
		cout << "노드속 전화번호:" << current->DB_phone_num << "(시즌DB)" << endl;
		if (current->DB_phone_num == phonenum) {
			//자리 -1이면 자유석임 -> 자리선택해줘 ->  db에 넣기
			if (current->DB_seat_num == "-1") {
				cout << "자리를 선택해주세요\n찬양 함수 호출해서 자리번호 배정받았다고 침(시즌DB)\n";
				int_seatnum = seat.chooseSeat(2);
				current->DB_seat_num = to_string(int_seatnum);
				cout << "정기권 자유석 자리 받아서 업데이트 했습니다(seasondb.cpp)" << endl;
			}
			return int_seatnum;
		}
		else {
			current = current->next;

		}
	}

	return int_seatnum;
}
int SeasonDB::searchSeasonDB(string phonenum)
{
	int nodeIndex = 1;
	Season* current = start;
	int int_seatnum = 100;
	string string_seatnum;
	SeatDB seat;
	cout << "searchSeasonDB:: (시즌DB)" << endl;
	cout << "찾을 전화번호:" << phonenum << "(시즌DB)" << endl;
	while (current != NULL)
	{
		cout << "노드속 전화번호:" << current->DB_phone_num << "(시즌DB)" << endl;
		if (current->DB_phone_num == phonenum) {
			//자리 -1이면 자유석임 -> 자리선택해줘 ->  db에 넣기
			if (current->DB_seat_num == "-1") {
				cout << "자리를 선택해주세요\n찬양 함수 호출해서 자리번호 배정받았다고 침(시즌DB)\n";
				int_seatnum = seat.chooseSeat(2);
				current->DB_seat_num = to_string(int_seatnum);
				cout << "정기권 자유석 자리 받아서 업데이트 했습니다(seasondb.cpp)" << endl;
			}
			return nodeIndex;
		}
		else {
			current = current->next;
			nodeIndex++;
		}
	}

	return 0;
}
//time 비교해서 만료된 노드 삭제하는 함수
int SeasonDB::searchSeasonDB_time(string current_time, Person* person)
{

	Season* current = start;
	SeatDB seat;
	double double_current_time = stod(current_time);

	int int_seatnum = 0;

	//	cout<<"현재시간 : "<< double_current_time <<" (SeasonDB.cpp)"<<endl;
	if (current == NULL || current->DB_phone_num == "") {
		return -1;
	}
	while (current != nullptr)
	{
		double double_expert_date = stod(current->DB_expert_date);
		//		cout <<"kkk"<< double_expert_date << " " << double_current_time << endl;
		if (double_current_time >= double_expert_date) {
			//cout<<current->DB_phone_num<<" 고객님 만료시간 : "<<current->DB_expert_date<<" SeasonDB에서 삭제합니다. (SeasonDB.cpp)\n";
			int_seatnum = stoi(current->DB_seat_num);
			string seat_str = seat.idxToString(int_seatnum);
			cout << "정기권 회원 " << seat_str << "석 " << person->Name << "님 정기권 만료되었습니다.\n";
			deleteSeason(current->DB_phone_num);
			current = start;
			return int_seatnum;
		}
		else {
			current = current->next;
		}
	}
	return -1;
}
//정기권 지정석 좌석 이동
void SeasonDB::ChangeSeat_1(string phone_num, Person* person) {
	Season* temp = start;
	SeatDB seat;
	int nodeIndex = searchSeasonDB(phone_num) - 1;

	for (int i = 0; i < nodeIndex - 1; i++)
	{
		temp = temp->next;
	}
	if (temp->DB_seat_num == "- 1") {
		int seat2 = seat.chooseSeat(1);
		if (seat2 == -1) {
			return;
		}
		temp->DB_seat_num = to_string(seat2);
	}
	string seat1 = seat.idxToString(stoi(temp->DB_seat_num));
	cout << person->Name << "님 현재 " << seat1 << " 좌석 이용중입니다." << endl;
	cout << "\n[           좌석이동          ]" << endl;
	int seat2 = seat.chooseSeat(1);
	//만석인 경우
	if (seat2 == -1) {
		return;
	}
	//원래자리 삭제
	seat.delSeat(stoi(temp->DB_seat_num));
	seat.showSeat();
	temp->DB_seat_num = to_string(seat2);
}

//정기권 자유석 좌석 이동
void SeasonDB::ChangeSeat_2(string phone_num, Person* person) {
	Season* temp = start;
	SeatDB seat;
	int nodeIndex = searchSeasonDB(phone_num) - 1;

	for (int i = 0; i < nodeIndex - 1; i++)
	{
		temp = temp->next;
	}
	if (temp->DB_seat_num == "- 1") {
		cout << "좌석을 선택해주세요.\n" << endl;
		int seat2 = seat.chooseSeat(1);
		if (seat2 == -1) {
			return;
		}
		temp->DB_seat_num = to_string(seat2);
	}
	string seat1 = seat.idxToString(stoi(temp->DB_seat_num));
	cout << person->Name << "님 현재 " << seat1 << " 좌석 이용중입니다." << endl;
	cout << "\n[           좌석이동          ]" << endl;
	int seat2 = seat.chooseSeat(2);
	if (seat2 == -1) {
		return;
	}
	//원래자리 삭제
	seat.delSeat(stoi(temp->DB_seat_num));
	seat.showSeat();
	temp->DB_seat_num = to_string(seat2);
}

bool SeasonDB::readFile()
{
	string path = "season.txt";
	ifstream file(path);
	Season season;   //Seaon 구조체에 담아갈 변수

	int person_num = 0;   //정기권 이용자수
	int data_num = 0;   //이용자당 입력할 데이터 수
	string phone_num;   //전화번호
	string payment_date;   //결제일시
	string expert_date;   //만료일시
	string seat_num;   //자리번호
	string arrival_time;   //입실시간
	string departure_time;   //퇴실시간
	string null_remove;   //공백제거
	string line;
	if (!file.is_open())
	{
		cout << "DB파일이 없습니다. SeasonDB.txt 파일을 생성합니다...\n";
		writeFile();
	}
	while (file.is_open()) {
		//cout << "파일 출력 확인\n";

		getline(file, phone_num, '\n');
		if (phone_num == "") {
			break;
		}


		getline(file, phone_num, '\n');
		getline(file, payment_date, '\n');
		getline(file, expert_date, '\n');
		getline(file, seat_num, '\n');
		getline(file, arrival_time, '\n');
		getline(file, departure_time, '\n');
		getline(file, null_remove, '\n');
		//노드에 클래스 정보 저장
		AddNode(Season(phone_num, payment_date, expert_date, seat_num, arrival_time, departure_time));
		if (!getline(file, line)) {
			file.close();
		}
	}
	file.close();
	return true;
}
void SeasonDB::signup(string phone_num, string payment_date, string expert_date, string seat_num, string arrival_time, string departure_time)
{
	AddNode(Season(phone_num, payment_date, expert_date, seat_num, arrival_time, departure_time));
}

bool SeasonDB::writeFile()
{
	string path = "season.txt";
	//int person_num = cntSize;   //정기권 이용자수
	int data_num = 5;   //이용자당 입력할 데이터 수
	string phone_num;   //전화번호
	string payment_date;   //결제일시
	string expert_date;   //만료일시
	string seat_num;   //자리번호
	string arrival_time;   //입실시간
	string departure_time;   //퇴실시간
	try {
		ofstream file;
		file.open(path, ios::out);
		Season* temp = start;

		if (temp == NULL || temp->DB_phone_num == "") {
			cout << "Season_person 0명" << endl;
			file.close();
			return true;
		}

		while (temp != NULL) {
			cout << "seasondb temp값 null아님" << endl;
			file << temp->DB_phone_num << "\n";
			file << temp->DB_payment_date << "\n";
			file << temp->DB_expert_date << "\n";
			file << temp->DB_seat_num << "\n";
			file << temp->DB_arrival_time << "\n";
			file << temp->DB_departure_time << "\n";
			file << "\n";
			temp = temp->next;

		}
		file.close();
		return true;
	}
	catch (exception& e)
	{
		return false;
	}

}

/*
int main()
{
	SeasonDB season;

	season.readFile();
	bool tf;

	season.signup("전화번호","결제일시","만료일시","-1","입실시간","퇴실시간");
	//재입장 관련
	tf=season.searchSeasonDB("전화번호");
	if (tf)

		cout << "재입장 가능\n";
	else
		cout << "입장 불가\n";
	//퇴실 관련
	tf = season.searchSeasonDB("01037937506");
	season.deleteSeason("01037937506");

	//season.deleteSeason("01012345888");
	season.writeFile();

}
*/