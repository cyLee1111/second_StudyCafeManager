#include "header.h"
void OnedayDB::AddNode(Oneday _oneday)
{

	if (cntSize == 0)
	{
		start = new Oneday();
		start->DB_phone_num = _oneday.DB_phone_num;
		start->DB_arrival_time = _oneday.DB_arrival_time;
		start->DB_departure_time = _oneday.DB_departure_time;
		start->DB_expert_date = _oneday.DB_expert_date;
		start->DB_payment_date = _oneday.DB_payment_date;
		start->DB_seat_num = _oneday.DB_seat_num;
		start->next = nullptr;
		cntSize++;

		return;
	}
	else
	{
		Oneday* current = new Oneday();
		current->DB_phone_num = _oneday.DB_phone_num;
		current->DB_arrival_time = _oneday.DB_arrival_time;
		current->DB_departure_time = _oneday.DB_departure_time;
		current->DB_expert_date = _oneday.DB_expert_date;
		current->DB_payment_date = _oneday.DB_payment_date;
		current->DB_seat_num = _oneday.DB_seat_num;
		current->next = nullptr;
		Oneday* temp = start;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = current;
		cntSize++;

		return;
	}


}
void OnedayDB::printData()
{
	Oneday* temp = start;
	cout << "printData:\n";
	for (int i = 0; i < cntSize; i++)
	{
		cout << temp->DB_phone_num << endl;
		cout << temp->DB_seat_num << endl;
		cout << temp->DB_arrival_time << endl;
		cout << temp->DB_departure_time << endl;
		cout << temp->DB_expert_date << endl;
		cout << temp->DB_payment_date << endl;
		cout << temp->DB_seat_num << endl;
		temp = temp->next;
	}
}
//노드 삭제 함수
bool OnedayDB::deleteOneday(string phonenum)
{
	Oneday* temp = start;
	Oneday* del;
	Oneday* swap;
	int nodeIndex = 0;
	//searchOnedayDB에서 전화번호로 탐색하여 인덱스값을 반환 받음
	nodeIndex = searchOnedayDB(phonenum) -1;
	if (cntSize == 0)
	{
		cout << "회원이 없습니다." << endl;
		return false;
	}
	//startpoint
	if (start->DB_phone_num == phonenum) {
		temp = start->next;
		delete start;
		start = temp;
		cntSize--;
		return true;
	}
	if (nodeIndex != 0) {
		for (int i = 0; i < nodeIndex -1; i++)
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


void OnedayDB::ReEntrance(string phonenum, string current_time)
{
	Oneday* temp = start;
	int nodeIndex = searchOnedayDB(phonenum) - 1;

	for (int i = 0; i < nodeIndex - 1; i++)
	{
		temp = temp->next;
	}

	temp->DB_arrival_time = current_time;


}

void OnedayDB::ReEntranceNseat(string phonenum, int seatnum, string current_time)
{
	Oneday* temp = start;
	int nodeIndex = searchOnedayDB(phonenum) - 1;

	for (int i = 0; i < nodeIndex - 1; i++)
	{
		temp = temp->next;
	}

	temp->DB_arrival_time = current_time;
	temp->DB_seat_num = to_string(seatnum);
}

//자리번호 넘겨줄 함수
int OnedayDB::searchOnedayDB_retseatIdx(string phonenum)
{

	Oneday* current = start;
	int int_seatnum = 100;
	string string_seatnum;
	SeatDB seat;
	/*cout << "searchOnedayDB:: (onedayDB)" << endl;
	cout << "찾을 전화번호:" << phonenum << "(onedayDB)" << endl;*/
	while (current != NULL)
	{
		//cout << "노드속 전화번호:" << current->DB_phone_num << "(onedayDBDB)" << endl;
		if (current->DB_phone_num == phonenum) {
			//자리 -1이면 자유석임 -> 자리선택해줘 ->  db에 넣기
			if (current->DB_seat_num == "-1") {
				int_seatnum = seat.chooseSeat(3);
				current->DB_seat_num = to_string(int_seatnum);

			}
			return int_seatnum;
		}
		else {
			current = current->next;

		}
	}

	return int_seatnum;
}
int OnedayDB::searchOnedayDB(string phonenum)
{
	int nodeIndex = 1;
	Oneday* current = start;
	//cout << "searchOnedayDB:: (OnedayDB.cpp)" << endl;
	//cout << "찾을 전화번호:" << phonenum << "(OnedayDB.cpp)" << endl;
	while (current != NULL)
	{
		if (current->DB_phone_num == phonenum) {
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
int OnedayDB::searchOnedayDB_time(string current_time, Person* person)
{
	Oneday* current = start;
	SeatDB seat;
	int int_seatnum = 0;
	double double_current_time = stod(current_time);
	double double_expert_date;

	if (current == NULL || current->DB_phone_num == "") {
		return -1;
	}
	

	while (current != nullptr)
	{

		double_expert_date = stod(current->DB_expert_date);
		if (double_current_time >= double_expert_date) {
			
			int_seatnum = stoi(current->DB_seat_num);
			string seat_str = seat.idxToString(int_seatnum);
			if (seat_str == "A0") {
				cout << "단일권 회원 " << person->Name << "님 단일권 만료되었습니다.\n";
			}
			else
				cout << "단일권 회원 " << seat_str << "석 " << person->Name << "님 단일권 만료되었습니다." << endl;
			deleteOneday(current->DB_phone_num);
			current = start;
			return int_seatnum;
		}
		else {
			current = current->next;
		}
	}
	return -1;
}

void OnedayDB::ChangeSeat_3(string phone_num, Person* person) {
	Oneday* temp = start;
	SeatDB seat;
	int nodeIndex = searchOnedayDB(phone_num) - 1;

	for (int i = 0; i < nodeIndex - 1; i++)
	{
		temp = temp->next;
	}
	if (temp->DB_seat_num == "-1") {
		cout << "좌석을 선택해주세요.\n" << endl;
		int seat2 = seat.chooseSeat(2);
		if (seat2 == -1) {
			return;
		}
		temp->DB_seat_num = to_string(seat2);
		seat.showSeat();
		return;
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

bool OnedayDB::readFile()
{
	string path = "oneday.txt";
	ifstream file(path);
	Oneday oneday;   //Seaon 구조체에 담아갈 변수

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
		cout << "DB파일이 없습니다. OnedayDB.txt 파일을 생성합니다...\n";
		writeFile();
	}
	while (file.is_open())
	{
		getline(file, phone_num, '\n');
		if (phone_num == "") {
			break;
		}

		getline(file, payment_date, '\n');
		getline(file, expert_date, '\n');
		getline(file, seat_num, '\n');
		getline(file, arrival_time, '\n');
		getline(file, departure_time, '\n');
		getline(file, null_remove, '\n');
		//노드에 클래스 정보 저장
		AddNode(Oneday(phone_num, payment_date, expert_date, seat_num, arrival_time, departure_time));
		if (!getline(file, line)) {
			file.close();
		}

	}
	file.close();
	return true;
}
void OnedayDB::signup(string phone_num, string payment_date, string expert_date, string seat_num, string arrival_time, string departure_time)
{
	Oneday oneday;
	AddNode(Oneday(phone_num, payment_date, expert_date, seat_num, arrival_time, departure_time));
}

bool OnedayDB::writeFile()
{
	string path = "oneday.txt";
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
		Oneday* temp = start;

		if (temp == NULL || temp->DB_phone_num == "") {
			cout << "Oneday_person 0명" << endl;
			file.close();
			return true;
		}


		while (temp != NULL) {
			cout << "onedaydb temp값 null아님" << endl;
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
