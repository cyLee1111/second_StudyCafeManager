#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

#ifndef _HEADER_H
#define _HEADER_H
#define SEAT_MAX 30

using namespace std;

/*class 순서
    SeatDB
    Time
    Account
    Oneday
    OnedayDB
    Season
    SeasonDB
    Person
    PersonDB
*/

class SeatDB {
private:
    string seat[SEAT_MAX];
public:
    bool readFile();
    bool writeFile();
    void showSeat();						/* showSeat() : 현재좌석상태 보여주는 함수 */
    int chooseSeat(int memType);			/* chooSeat() : 좌석선택 함수 */
    bool isFull();                          /* isFull() : 좌석DB 안이 빈자리(0) 없이 꽉 차있는지 */
    int checkInput(string s);				/* checkInput() : 좌석선택 input검사 함수 */
    bool fixSeat(int memType, int idx);		/* fixSeat() : 선택받은 좌석수정 */
    bool delSeat(int idx);					/* delSeat() : 선택받은 좌석삭제 */
    string toChar(string seat);				/* toChar() : 0,1,2 숫자를 '□','▦','■'로 바꿔줌 */
    string idxToString(int idx);            /* idxToString() : 0~29 인덱스를 "A1"로 변경 */

};

class Time {
private:
    int Date, Time;
    int bY, bM, bD, bH, bmin;
    int Y, M, D, H, min;
public:
    void readData();
    void insertTime(); //시간입력함수
    string leftTime(string seatnum, string start, string finish); //남은시간 계산
    void showTime(); //시간출력 함수
    string int2string(int I);
    string returnTime();
    void writeData();
    int checkDate(int year, int month, int day);
};

class Account {
public:
    int Saccount, Oaccount;
    int Y, M, D, H, min;
    string T;

    void whatTime(string time);
    void readDB();
    void writeDB();
    void showAccount();
    string int2string(int I);
    string payTicket(string seat);
    string plusDate(int Y, int M, int D, int day);
    bool checkEnter();
};

class Person {
    //PersonDB 내의 각 객체 Person
public:
    string PhoneNum;
    string Name;
    string Seat;
    string startDate;
    string endDate;
    Person* next;
    Person(string num, string name, string seat, string startdate, string enddate) :PhoneNum(num), Name(name), Seat(seat), startDate(startdate), endDate(enddate) {
        next = NULL;
    };
    Person() {
        Seat = "0";
        next = NULL;
    };
};
class Oneday
{
public:
    Oneday* next = nullptr;
    string DB_phone_num;
    string DB_payment_date;
    string DB_expert_date;
    string DB_seat_num;
    string DB_arrival_time;
    string DB_departure_time;


    Oneday() {};
    Oneday(string num, string paydate, string expertdate, string seat, string arrivaltime, string departtime)
        :DB_phone_num(num), DB_payment_date(paydate), DB_expert_date(expertdate), DB_seat_num(seat), DB_arrival_time(arrivaltime), DB_departure_time(departtime) {};
};
class OnedayDB
{
public:
    Oneday* start = new Oneday();	//시작노드

    bool readFile();	//oneday.txt 읽는 함수
    bool writeFile();	//oneday.txt 쓰는 함수
    //회원가입
    void signup(string phone_num, string payment_date, string expert_date, string seat_num, string arrival_date, string depart_date);
    //노드를 연결리스트에 추가하는 함수
    void AddNode(Oneday _oneday);
    void printData();
    //DB 삭제할 때 몇번째 노드인지 확인용 함수 
    int searchOnedayDB(string phonenum);
    bool deleteOneday(string phonenum);
    int searchOnedayDB_time(string currentTime, Person* person);
    void ReEntrance(string phonenum, string current_time);  //재입장
    void ReEntranceNseat(string phonenum, int seatnum, string current_time);
    int searchOnedayDB_retseatIdx(string PhoneNum); //좌석이 없는경우 찬양한테 자리넘버넘겨줘
    void ChangeSeat_3(string phone_num, Person* person);
private:
    int cntSize = 0;
};

class Season
{
public:
    Season* next = nullptr;
    string DB_phone_num;
    string DB_payment_date;
    string DB_expert_date;
    string DB_seat_num;
    string DB_arrival_time;
    string DB_departure_time;
    Season() {};
    Season(string num, string paydate, string expertdate, string seat, string arrivaltime, string departtime)
        :DB_phone_num(num), DB_payment_date(paydate), DB_expert_date(expertdate), DB_seat_num(seat), DB_arrival_time(arrivaltime), DB_departure_time(departtime) {};
};
class SeasonDB
{
public:
    Season* start = new Season();
    //Season* current = new Season();

    bool readFile();
    bool writeFile();

    //회원가입
    void signup(string phone_num, string payment_date, string expert_date, string seat_num, string arrival_date, string depart_date);
    void AddNode(Season _Season);	//노드를 연결리스트에 추가하는 함수
    bool deleteSeason(string phonenum);

    void ReEntrance(string phonenum, string current_time);  //재입장
    void ReEntranceNseat(string phonenum, int seatnum, string current_time);  //재입장 자리선택 필요한경우
    int searchSeasonDB(string phonenum);	//전번 있으면 true
    int new_searchSeasonDB(string phonenum);    //퇴실이나 만료인경우 자리 없는 회원일 때 좌석 선택하면 안되니까 따로처리
    int searchSeasonDB_time(string current_time, Person* person);   //시간보고 회원 삭제
    int searchSeasonDB_retseatIdx(string PhoneNum); //좌석이 없는경우 찬양한테 자리넘버넘겨줘
    int searchSeasonDBforExit(string phonenum); //회원 퇴실을 위한 회원 탐색(회원 자리가 없을 경우 예외처리를 따로 해줘야해서)
    void ChangeSeat_1(string phone_num, Person* person); //정기권(지정석) 자리 이동
    void ChangeSeat_2(string phone_num, Person* person); //정기권(자유석) 자리 이동
    bool exitSeason(string phonenum, string current_time);   // 회원 퇴실 함수
private:
    int cntSize=0;
};


class PersonDB {
    //Person 을 저장하는 PersonDB
public:
    //startpoint는 공백!
    Person* startPoint = new Person();
    string T;
    void whatTime(string time);
    int size;
    SeasonDB seasonDB;
    OnedayDB onedayDB;
    SeatDB seatDB;
    Account account;
    //  PersonDB() {};
    PersonDB(SeasonDB Season, OnedayDB Oneday, SeatDB Seat, Account account);
    //LinkedList 관리
    void initLinkedList();
    bool addPerson(Person target);
    bool deletePerson(string PhoneNum);
    Person* searchPerson(string PhoneNum);
    void showPersonInfo(string PhoneNum, string currentTime);
    void getTime(string currentTime);
    //만료고객 삭제
    Person* deleteEndPerson(string time);
    //File I/O
    bool readFile();
    bool writeFile();

    //회원가입
    bool signup(string currentTime, Account* account);
    bool signup(string PhoneNum, string currentTime, Account* account);

    //검증
    bool checkPhoneNum(string PhoneNum);
    bool checkName(string Name);
    bool checkSeat(string Seat);
    //bool checkDate(string Date);

    //입력
    string inputPhoneNum();
    string inputName();
    string inputSeat();
    //string inputDate();
};


#endif