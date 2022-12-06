#include "header.h"

int main()
{
	cin.clear();
	SeasonDB season;
	OnedayDB oneday;
	SeatDB seat;
	Account account;
	Time time;
	PersonDB personDB(season, oneday, seat, account); //person 생성자 초기화시 이미 생성된 class 전달해야 됨
	personDB.initLinkedList();
	// 파일읽기
	account.readDB();
	time.readData();
	personDB.seasonDB.readFile();
	personDB.onedayDB.readFile();
	personDB.readFile();
	string menu;
	do {
		
		cin.clear();
		// 시간입력하기함수
		time.insertTime();
		//현재 시간
		string currentTime = time.returnTime();
		//객체 별 시간 업데이트
		account.whatTime(currentTime);
		//만료된 회원을 DB에서 삭제
		//personDB.deleteOneday(currentTime);

		//personDB.deleteEndPerson(currentTime);

		time.showTime();
		//cout << "정기권 만료 회원이 있다면 삭제합니다..." << endl;


		// 출력
		 Person* person;
		 cout << "만료 안됨?" << endl;
		 while((person=personDB.deleteEndPerson(currentTime))!=NULL){
			 if (person->Seat == "1" || person->Seat == "2") {
				 seat.delSeat(personDB.seasonDB.searchSeasonDB_time(currentTime, person));
			 }
			 else {
				 seat.delSeat(personDB.onedayDB.searchOnedayDB_time(currentTime, person));
			 }
		 }


		//time.showTime();
		//cout << "단일권 만료 회원이 있다면 삭제합니다..." << endl;
		 //출력
		 
		 cin.clear();
		
		cout << endl;
		cout << "┌──────────────┐ ┌──────────────┐ ┌──────────────┐ ┌──────────────┐ ┌──────────────┐ ┌──────────────┐ ┌──────────────┐ ┌────────┐" << endl;
		cout << "│ [1] 회원가입 │ │ [2] 회원입장 │ │ [3] 회원퇴실 │ │ [4] 회원확인 │ │ [5] 좌석확인 │ │ [6] 좌석이동 │ │ [7] 회    계 │ │ 종료: Q│" << endl;
		cout << "└──────────────┘ └──────────────┘ └──────────────┘ └──────────────┘ └──────────────┘ └──────────────┘ └──────────────┘ └────────┘" << endl;
		cout << ">> ";
		cin >> menu;
		while (getchar() != '\n');
		cin.clear();
		
		if (menu.compare("1") == 0) {											// [1] 회원가입
			personDB.signup(currentTime, &account);
			//회원 가입 완료 / 혹은 실패
			continue;
			//다시 시작 메뉴로

		}
		else if (menu.compare("2") == 0) {									// [2] 회원입장
			string PhoneNum = personDB.inputPhoneNum();
			Person* targetPerson = personDB.searchPerson(PhoneNum);
			if (targetPerson == NULL) {	// 전화번호X, 회원가입
				personDB.signup(PhoneNum, currentTime, &account);
				//회원 가입 완료 / 혹은 실패
				continue;
				//다시 시작 메뉴로
			}
			cout << "targetperson seat 출력" << targetPerson->Seat << endl;
			if (targetPerson->Seat.compare("1") == 0) {	// 전화번호O, 입장
				cout << "정기권 (지정석)" << endl;				//주석
				personDB.seasonDB.ReEntrance(PhoneNum, currentTime);
				cout << "입장입니다 ^^ (정기권)" << endl;
			}
			else if (targetPerson->Seat.compare("2") == 0) {
				cout << "정기권 (자유석)" << endl;				//주석
				//좌석 있음
				if ((personDB.seasonDB.searchSeasonDB_retseatIdx(PhoneNum) > 0)) {
					personDB.seasonDB.ReEntrance(PhoneNum, currentTime);
				}
				else {
					//좌석 x  - 좌석 배정
					int seatnum = seat.chooseSeat(2);
					personDB.seasonDB.ReEntranceNseat(PhoneNum, seatnum, currentTime);
				}
				//입장
				cout << "입장입니다 ^^ (정기권)" << endl;
			}
			else if (targetPerson->Seat.compare("3") == 0) {
				cout << "단일권" << endl;
				//좌석 있음
				if (personDB.onedayDB.searchOnedayDB_retseatIdx(PhoneNum) > 0) {
					personDB.onedayDB.ReEntrance(PhoneNum, currentTime);
				}
				else {
					//좌석 없음
					//좌석 배정
					int seatnum = seat.chooseSeat(3);
					personDB.onedayDB.ReEntranceNseat(PhoneNum, seatnum, currentTime);
				}
				cout << "입장입니다 ^^ (단일권)" << endl;
			}
			else {
				cout << "잘못된 입력(자리가 1 2 3 이 아닙니다.)" << endl;
			}
			continue;
		}
		
		else if (menu.compare("3") == 0) {									// [3] 회원퇴실
			bool ft;
			cout << "회원퇴실" << endl;
			string PhoneNum = personDB.inputPhoneNum();
			if (personDB.seasonDB.searchSeasonDBforExit(PhoneNum)==1) {		//좌석 있는 정기권 회원이 퇴실을 원하는 경우 
				personDB.seasonDB.exitSeason(PhoneNum, currentTime);
				cout << "퇴실 처리 되었습니다." << endl;
				
			}
			else if (personDB.seasonDB.searchSeasonDBforExit(PhoneNum) == 0) {	//좌석 없는 정기권 회원이 퇴실을 원하는 경우
				cout << "이용중인 좌석이 없습니다." << endl;
			}
			else if (personDB.onedayDB.searchOnedayDB(PhoneNum)) {				//단일권 회원이 퇴실을 원하는 경우
				cout << "단일권 회원은 일정시간이 지난 후 자동 퇴실처리가 됩니다." << endl;
				
			}
			else {
				cout << "존재하지 않는 회원입니다." << endl;
				
			}
			//season.writeFile();
			continue;
		}

		else if (menu.compare("4") == 0) {									// [4] 회원확인
			string PhoneNum = personDB.inputPhoneNum();
			//[ 2022-09-28 16:15:54 ] 구본무 고객님 / 단일권 2시간 34분 남았습니다.
			personDB.showPersonInfo(PhoneNum, currentTime);
			continue;
		}



		else if (menu.compare("5") == 0) {									// [5] 좌석확인
			seat.showSeat();
			continue;
		}
		else if (menu.compare("6") == 0) {									// [6] 좌석이동

			string PhoneNum = personDB.inputPhoneNum();
			Person* targetPerson = personDB.searchPerson(PhoneNum);
			while (targetPerson == NULL) {
				cout << "전화번호 입력이 잘못되었습니다. 다시 입력해주세요.\n";
				personDB.inputPhoneNum();
				targetPerson = personDB.searchPerson(PhoneNum);
			}

			if (targetPerson->Seat.compare("1") == 0) {	//정기권 (지정석) 회원
				personDB.seasonDB.ChangeSeat_1(PhoneNum, targetPerson);
			}
			else if (targetPerson->Seat.compare("2") == 0) {	//정기권 (자유석) 회원
				personDB.seasonDB.ChangeSeat_2(PhoneNum, targetPerson);
			}
			else if (targetPerson->Seat.compare("3") == 0) {
				personDB.onedayDB.ChangeSeat_3(PhoneNum, targetPerson);
			}

		}
		else if (menu.compare("7") == 0) {									// [7] 회    계
		
			time.showTime();
		
			account.showAccount();
			continue;
		}
		else if (menu.compare("Q") != 0) {
			cout << "잘못된 입력입니다." << endl;
		}
	} while (menu != "Q");													// [Q] 종    료


	// 파일쓰기
	cout << "Account" << endl;
	account.writeDB();
	cout << "time" << endl;
	time.writeData();
	cout << "time" << endl;
	personDB.writeFile();
	cout << "personDB" << endl;
	personDB.seasonDB.writeFile();
	cout << "seasonDB" << endl;
	personDB.onedayDB.writeFile();
	cout << "파일 저장 완료" << endl;

	return 0;

}