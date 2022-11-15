#include "header.h"

int main()
{
	cin.clear();
	SeasonDB season;
	OnedayDB oneday;
	SeatDB seat;
	Account account;
	Time time;
	PersonDB personDB(season, oneday, seat, account); //person ������ �ʱ�ȭ�� �̹� ������ class �����ؾ� ��
	personDB.initLinkedList();
	// �����б�
	account.readDB();
	time.readData();
	season.readFile();
	oneday.readFile();
	personDB.readFile();
	string menu;
	do {
		// �ð��Է��ϱ��Լ�
		time.insertTime();
		//���� �ð�
		string currentTime = time.returnTime();
		//��ü �� �ð� ������Ʈ
		account.whatTime(currentTime);
		//����� ȸ���� DB���� ����
		//personDB.deleteOneday(currentTime);

		//personDB.deleteEndPerson(currentTime);

		time.showTime();
		cout << "����� ���� ȸ���� �ִٸ� �����մϴ�..." << endl;


		// ���
		 Person* person;
		 while((person=personDB.deleteEndPerson(currentTime))!=NULL){
		 	seat.delSeat(season.searchSeasonDB_time(currentTime,person));
		 }


		time.showTime();
		cout << "���ϱ� ���� ȸ���� �ִٸ� �����մϴ�..." << endl;
		 //���
		 while((person=personDB.deleteEndPerson(currentTime))!=NULL){
		 	seat.delSeat(oneday.searchOnedayDB_time(currentTime,person));
		 }
		
		cin.clear();
		cout << endl;
		cout << "�������������������������������� �������������������������������� �������������������������������� �������������������������������� �������������������������������� �������������������������������� �������������������������������� ��������������������" << endl;
		cout << "�� [1] ȸ������ �� �� [2] ȸ������ �� �� [3] ȸ����� �� �� [4] ȸ��Ȯ�� �� �� [5] �¼�Ȯ�� �� �� [6] �¼��̵� �� �� [7] ȸ    �� �� �� ����: Q��" << endl;
		cout << "�������������������������������� �������������������������������� �������������������������������� �������������������������������� �������������������������������� �������������������������������� �������������������������������� ��������������������" << endl;
		cout << ">> ";
		cin >> menu;
		cin.clear();
		if (menu.compare("1") == 0) {											// [1] ȸ������
			personDB.signup(currentTime, &account);
			//ȸ�� ���� �Ϸ� / Ȥ�� ����
			continue;
			//�ٽ� ���� �޴���

		}
		else if (menu.compare("2") == 0) {									// [2] ȸ������
			string PhoneNum = personDB.inputPhoneNum();
			Person* targetPerson = personDB.searchPerson(PhoneNum);
			if (targetPerson == NULL) {	// ��ȭ��ȣX, ȸ������
				personDB.signup(PhoneNum, currentTime, &account);
				//ȸ�� ���� �Ϸ� / Ȥ�� ����
				continue;
				//�ٽ� ���� �޴���
			}
			cout << "targetperson seat ���" << targetPerson->Seat << endl;
			if (targetPerson->Seat.compare("1") == 0) {	// ��ȭ��ȣO, ����
				cout << "����� (������)" << endl;				//�ּ�
				season.ReEntrance(PhoneNum, currentTime);
				cout << "�����Դϴ� ^^ (�����)" << endl;
			}
			else if (targetPerson->Seat.compare("2") == 0) {
				cout << "����� (������)" << endl;				//�ּ�
				//�¼� ����
				if ((season.searchSeasonDB_retseatIdx(PhoneNum) > 0)) {
					season.ReEntrance(PhoneNum, currentTime);
				}
				else {
					//�¼� x  - �¼� ����
					int seatnum = seat.chooseSeat(2);
					season.ReEntranceNseat(PhoneNum, seatnum, currentTime);
				}
				//����
				cout << "�����Դϴ� ^^ (�����)" << endl;
			}
			else if (targetPerson->Seat.compare("3") == 0) {
				cout << "���ϱ�" << endl;
				//�¼� ����
				if (oneday.searchOnedayDB_retseatIdx(PhoneNum) > 0) {
					oneday.ReEntrance(PhoneNum, currentTime);
				}
				else {
					//�¼� ����
					//�¼� ����
					int seatnum = seat.chooseSeat(3);
					oneday.ReEntranceNseat(PhoneNum, seatnum, currentTime);
				}
				cout << "�����Դϴ� ^^ (���ϱ�)" << endl;
			}
			else {
				cout << "�߸��� �Է�(�ڸ��� 1 2 3 �� �ƴմϴ�.)" << endl;
			}
			continue;
		}

		else if (menu.compare("3") == 0) {									// [3] ȸ�����
			bool ft;
			string PhoneNum = personDB.inputPhoneNum();
			if (season.searchSeasonDB(PhoneNum)) {
				season.deleteSeason(PhoneNum);
				cout << "��� ó�� �Ǿ����ϴ�." << endl;
			}
			else {
				cout << "�������� �ʴ� ȸ���Դϴ�." << endl;
			}
			//season.writeFile();
			continue;
		}

		else if (menu.compare("4") == 0) {									// [4] ȸ��Ȯ��
			string PhoneNum = personDB.inputPhoneNum();
			//[ 2022-09-28 16:15:54 ] ������ ������ / ���ϱ� 2�ð� 34�� ���ҽ��ϴ�.
			personDB.showPersonInfo(PhoneNum, currentTime);
			continue;
		}



		else if (menu.compare("5") == 0) {									// [5] �¼�Ȯ��
			seat.showSeat();
			continue;
		}
		else if (menu.compare("6") == 0) {									// [6] �¼��̵�

			string PhoneNum = personDB.inputPhoneNum();
			Person* targetPerson = personDB.searchPerson(PhoneNum);
			while (targetPerson == NULL) {
				cout << "��ȭ��ȣ �Է��� �߸��Ǿ����ϴ�. �ٽ� �Է����ּ���.\n";
				personDB.inputPhoneNum();
				targetPerson = personDB.searchPerson(PhoneNum);
			}

			if (targetPerson->Seat.compare("1") == 0) {	//����� (������) ȸ��
				season.ChangeSeat_1(PhoneNum, targetPerson);
			}
			else if (targetPerson->Seat.compare("2") == 0) {	//����� (������) ȸ��
				season.ChangeSeat_2(PhoneNum, targetPerson);
			}
			else if (targetPerson->Seat.compare("3") == 0) {
				oneday.ChangeSeat_3(PhoneNum, targetPerson);
			}

		}
		else if (menu.compare("7") == 0) {									// [7] ȸ    ��
		
			time.showTime();
		
			account.showAccount();
			continue;
		}
		else if (menu.compare("Q") != 0) {
			cout << "�߸��� �Է��Դϴ�." << endl;
		}
	} while (menu != "Q");													// [Q] ��    ��


	// ���Ͼ���
	cout << "Account" << endl;
	account.writeDB();
	cout << "time" << endl;
	time.writeData();
	cout << "time" << endl;
	personDB.writeFile();
	cout << "personDB" << endl;
	season.writeFile();
	cout << "seasonDB" << endl;
	oneday.writeFile();
	cout << "���� ���� �Ϸ�" << endl;

	return 0;

}