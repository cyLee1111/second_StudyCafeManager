#include "header.h"



PersonDB::PersonDB(SeasonDB Season, OnedayDB Oneday, SeatDB Seat, Account account) {
    initLinkedList();
    seasonDB = Season;
    onedayDB = Oneday;
    seatDB = Seat;
    account = account;

}


void PersonDB::initLinkedList() {
    //초기화
    size = 0;
};
void getTime(string currentTime) {
};

bool PersonDB::addPerson(Person target) {
    if (size == 0)
    {
        startPoint->PhoneNum = target.PhoneNum;
        startPoint->Name = target.Name;
        startPoint->Seat = target.Seat;
        startPoint->startDate = target.startDate;
        startPoint->endDate = target.endDate;
        startPoint->next = NULL;
        size++;
        return true;
    }
    else
    {
        Person* currentPoint = new Person();
        currentPoint->PhoneNum = target.PhoneNum;
        currentPoint->Name = target.Name;
        currentPoint->Seat = target.Seat;
        currentPoint->startDate = target.startDate;
        currentPoint->endDate = target.endDate;
        currentPoint->next = NULL;
        Person* temp = startPoint;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = currentPoint;
        size++;
        return true;
    }
    return false;
};
Person* PersonDB::searchPerson(string phonenum) {
    cout << "searchstart" << endl;
    Person* current = startPoint;
    // while(currentIndex!=size){
    while (current != NULL) {
        if (strncmp(current->PhoneNum.c_str(), phonenum.c_str(), 11) == 0 || strncmp(current->PhoneNum.c_str(), phonenum.c_str(), 10) == 0) {

            return current;
        }
        else {
            current = current->next;
        }
    }
    cout << "없는 회원입니다." << endl;
    return NULL;
};
// void PersonDB::deleteOneday(string time){
//     //자정이 지난 단일권 고객 삭제
//     Person* current=startPoint;
//     // while(currentIndex!=size){
//     while(current!=nullptr){
//         if(strncmp(current->Seat.c_str(),"3",1)==0){
//             deletePerson(current->PhoneNum);
//             current=current->next;
//         }
//         else {
//             current=current->next;
//         }
//     }
// };
Person* PersonDB::deleteEndPerson(string curtime) {
    //  cout<<"PersonDB삭제 시작"<<endl;
    Person* current = startPoint;
    if (current == NULL || current->PhoneNum == "") {
        return NULL;
    }
    // while(currentIndex!=size){    
    while (current != NULL && current->PhoneNum != "") {
        if (stod(current->endDate) < stod(curtime)) {

             Person* temp=current;
            deletePerson(current->PhoneNum);
            return temp;
            current = current->next;
        }
        else {
            current = current->next;
        }
    }
    cout << "PersonDB삭제끝" << endl;
    return current;
};

void PersonDB::showPersonInfo(string phonenum, string currentTime) {
    Person* rtn = searchPerson(phonenum);
    if (rtn == NULL) {
        cout << "존재하지 않는 회원입니다.";
    }
    else {
        string output;
        string leftTime;
        string seatNum = rtn->Seat;
        if (strncmp(seatNum.c_str(), "1", 1) == 0) {
            output = "정기권(지정석)";
        }
        else if (strncmp(seatNum.c_str(), "2", 1) == 0) {
            output = "정기권(자유석)";
        }
        else {
            output = "단일권";
        }
        Time time;
        leftTime = time.leftTime(seatNum, currentTime, rtn->endDate);
        //2022-09-28 16:15:54 ] 구본무 고객님 / 단일권 2시간 34분 남았습니다.
       // time.showTime();

        //이쁘게 출력
        int Y, M, D, H, min, T, Dat;
        string Date, Time;
        Date.assign(currentTime, 0, 8);
        Time.assign(currentTime, 8, 11);

        Dat = stoi(Date);
        T = stoi(Time);
        //cout << Date << "날짜" << Time << "시간\n";
        Y = Dat / 10000;
        M = (Dat % 10000) / 100;
        D = (Dat % 10000) % 100;
        //cout << Time << "타임입니다";
        H = T / 100;
        min = T % 100;
        cout << "[";
        cout << Y << "-" << M << "-" << D << "  " << H << ":" << min;
        cout << "] " << rtn->Name << "고객님 / " << output << " " << leftTime << " 남았습니다." << endl;
    }
};

bool PersonDB::deletePerson(string Phonenum) {
    Person* nextptr = startPoint->next;
    Person* target = startPoint;
    int currentPoint = 1;
    if (size == 0)
    {
        cout << "회원이 없습니다." << endl;
        return false;
    }
    //startpoint
    if (strncmp(target->PhoneNum.c_str(), Phonenum.c_str(), 11) == 0 || strncmp(target->PhoneNum.c_str(), Phonenum.c_str(), 10) == 0) {
        cout << "1.personDB삭제:" << target->PhoneNum << endl;
        startPoint = target->next;
        size--;
        //free(target);
        cout << "회원이 삭제되었습니다." << endl;
        return true;
    }
    // target=target->next;
    // nextptr=nextptr->next;
    while (nextptr != NULL) {
        // cout<<"삭제:"<<nextptr->PhoneNum<<endl;
        // cout<<"삭제:"<<Phonenum<<endl;

        if (strncmp(nextptr->PhoneNum.c_str(), Phonenum.c_str(), 11) == 0 || strncmp(nextptr->PhoneNum.c_str(), Phonenum.c_str(), 10) == 0) {
            cout << "2. personDB삭제:" << nextptr->Name << endl;
            target->next = nextptr->next;
            size--;
            // cout<<"회원이 삭제되었습니다."<<endl;
            //free(nextptr);
            return true;
        }
        else {
            target = target->next;
            nextptr = nextptr->next;
        }
    }

    cout << "delete:입력한 회원정보가 존재하지 않습니다." << endl;
    return false;
};
bool PersonDB::readFile() {
    string path = "ticket.txt";
    ifstream file(path);
    size = 0;
    string inputPhoneNum;
    string inputName;
    string inputSeat;
    string inputStarttime;
    string inputendtime;
    string line;
    if (!file.is_open()) {
        cout << "DB파일이 없습니다. Person.txt 파일을 생성합니다...\n";
        writeFile();
    }
    while (file.is_open()) {
        getline(file, inputPhoneNum, '\n');
        if (inputPhoneNum == "") {
            break;
        }
        getline(file, inputName, '\n');
        getline(file, inputSeat, '\n');
        getline(file, inputStarttime, '\n');
        getline(file, inputendtime, '\n');
        // Person newperson(inputPhoneNum,inputName,inputSeat,inputStarttime,inputendtime);
        addPerson(Person(inputPhoneNum, inputName, inputSeat, inputStarttime, inputendtime));

        if (!getline(file, line)) {
            file.close();
        }
    }
    file.close();
    return true;
};

bool PersonDB::writeFile() {
    string path = "ticket.txt";
    const char* enter = "\n";
    try {
        ofstream file;
        file.open(path, ios::out);
        //WRITE
        Person* target = startPoint;
        if (target == NULL || target->PhoneNum == "") {
            file.close();
            return true;
        }
        while (target != NULL) {
            file << target->PhoneNum << enter;
            file << target->Name << enter;
            file << target->Seat << enter;
            file << target->startDate << enter;
            file << target->endDate << enter;
            file << enter;
            target = target->next;
        }
        file.close();
        return true;
    }
    catch (exception& e) {
        return false;
    }
};

bool PersonDB::signup(string currentTime, Account inaccount) {
    string PhoneNum = inputPhoneNum();
    if (searchPerson(PhoneNum) != NULL) {
        cout << "이미 존재하는 회원입니다." << endl;
        return false;
    }
    string Name = inputName();
    string inseat = inputSeat();
    int seatInt;
    string seatNum;
    if (strncmp(inseat.c_str(), "1", 1) == 0) {
        SeatDB seat;
        seatInt = seat.chooseSeat(stoi("1"));
        seatNum = to_string(seatInt);
    }
    cout << "결제로 이동합니다." << endl;
    string endTime = inaccount.payTicket(inseat);
    cout << "저장중...." << endl;
    bool addrnt;
    do {
        addrnt = this->addPerson(Person(PhoneNum, Name, inseat, currentTime, endTime));
    } while (addrnt == false);
    if (strncmp(inseat.c_str(), "1", 1) == 0) {
        //정기권
        seasonDB.signup(PhoneNum, currentTime, endTime, seatNum, "0", "0");
    }
    else if (strncmp(inseat.c_str(), "2", 1) == 0) {
        //지금 자리없고 이따 필요할때

        seasonDB.signup(PhoneNum, currentTime, endTime, "-1", "0", "0");
    }
    else {
        onedayDB.signup(PhoneNum, currentTime, endTime, "-1", "0", "0");

    }
    cout << "회원가입이 완료되었습니다." << endl;
    return true;
};
bool PersonDB::signup(string PhoneNum, string currentTime, Account inaccount) {
    string Name = inputName();
    string inseat = inputSeat();
    int seatInt;
    string seatNum;
    if (strncmp(inseat.c_str(), "1", 1) == 0) {
        SeatDB seat;
        seatInt = seat.chooseSeat(stoi("1"));
        seatNum = to_string(seatInt);
    }
    cout << "\n결제로 이동합니다.\n" << endl;
    string endTime = inaccount.payTicket(inseat);
    cout << "현재시간:" << currentTime << endl;
    cout << "만료시간:" << endTime << endl;
    cout << "\n저장중...." << endl;
    bool addrnt;
    do {
        addrnt = this->addPerson(Person(PhoneNum, Name, inseat, currentTime, endTime));
    } while (addrnt == false);
    if (strncmp(inseat.c_str(), "1", 1) == 0) {
        //정기권
        seasonDB.signup(PhoneNum, currentTime, endTime, seatNum, "0", "0");
    }
    else if (strncmp(inseat.c_str(), "2", 1) == 0) {
        //지금 자리없고 이따 필요할때

        seasonDB.signup(PhoneNum, currentTime, endTime, "-1", "0", "0");
    }
    else {
        onedayDB.signup(PhoneNum, currentTime, endTime, "-1", "0", "0");

    }
    cout << "회원가입이 완료되었습니다." << endl;
    return true;
};
bool PersonDB::checkPhoneNum(string PhoneNum) {
    //올바른 입력 : 01012341234
    // 010 011 지원 이외는 안지원!
    // 7자 or 8자
    // 
    if (PhoneNum.length() > 11) {
        cout << "전화번호는 11자 이하여야 합니다." << endl;
        return false;
    }
    else if (PhoneNum.length() < 10) {
        cout << "전화번호는 10자 이상이여야 합니다." << endl;
        return false;
    }

    const char* varify = PhoneNum.c_str();
    string start = PhoneNum.substr(0, 3);
    string cmp1 = "010";
    string cmp2 = "011";
    if (strncmp(start.c_str(), cmp1.c_str(), 3) != 0 && strncmp(start.c_str(), cmp2.c_str(), 3) != 0) {
        cout << "전화번호는 010 또는 011로 시작하여야 합니다." << endl;
        return false;
    }
    if (PhoneNum.length() == 11 || PhoneNum.length() == 10) {
        for (int j = 3; j < 11; j++) {
            if (varify[j] < '0' || varify[j]>'9') {
                cout << "전화번호는 숫자를 입력하여야합니다." << endl;
                return false;
            }
        }
        return true;
    }
    else return false;
};
bool PersonDB::checkName(string Name) {
    // 올바른 입력 : 구본무 구본 구 ㄱ ㅡ 다 ok
    // 5글자 이하면 다 ok. 
    int strlen = Name.length();
    if (Name.length() > 15) {
        cout << "이름은 5자 이하여야 합니다." << endl;
        return false;
    }
    for (int i = 0; i < strlen; i++) {
        //한글 아님
        if ((Name[i] & (0x80)) != 0x80) {
            cout << "이름은 한글이여야 합니다." << endl;
            return false;
        }
    }
    return true;
};
bool PersonDB::checkSeat(string Seat) {
    if (strncmp(Seat.c_str(), "3", 1) == 0 || strncmp(Seat.c_str(), "2", 1) == 0 || strncmp(Seat.c_str(), "1", 1) == 0) {
        return true;
    }
    cout << "좌석을 다시 입력하세요" << endl;
    return false;
};

string PersonDB::inputPhoneNum() {
    string PhoneNum;
    do {
        cout << "\n회원의 전화번호를 입력하세요(-없이):" << endl;
        cout << ">> ";
        cin >> PhoneNum;
    } while (!checkPhoneNum(PhoneNum));
    cin.clear();
    return PhoneNum;
};
string PersonDB::inputName() {
    string Name;
    do {
        cout << "\n회원의 이름을 입력하세요(최대5자):" << endl;
        cout << ">> ";
        cin >> Name;
    } while (!checkName(Name));
    cin.clear();
    return Name;
};
string PersonDB::inputSeat() {
    string Seat;
    do {
        cout << "\n스터디카페 회원권 종류를 입력하세요 :" << endl;
        cout << "1. 정기권 - 지정석" << endl;
        cout << "2. 정기권 - 자유석" << endl;
        cout << "3. 단일권 - 자유석" << endl;
        cout << ">> ";
        cin >> Seat;
    } while (!checkSeat(Seat));
    cin.clear();
    return Seat;
};
// bool PersonDB::checkDate(string Date){
//     double date;

//     return true;
// };

// string PersonDB::inputDate(){
// string Date;
//     do{
//         cout<<"회원의 전화번호를 입력하세요(-없이):"<<endl;
//         cin>>Date;
//     }while(!checkDate(Date));    
//     cin.clear();
//     return Date;
// };