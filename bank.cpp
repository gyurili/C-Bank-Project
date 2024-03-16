#include <iostream>
#include <string>
using namespace std;

//계좌 클래스
class Account {

    int accountNum; 
    int balance; 

public:
    Account(int accountNum, int money): accountNum(accountNum), balance(money) {} 

    int GetAccNum() { 
        return accountNum;
    }

    virtual void Deposit(int money) { 
        cout << money << "원이 입금되었습니다." << endl;
        balance += money;
    }

    int Withdraw(int money) { 

        if (balance - money < 0) {
            return 0;
        }
        else {
            balance -= money;
            return balance;
        }
    }

    void ShowAccount() { 
        cout << "계좌번호: " << accountNum << endl;
        cout << "잔액: " << balance << endl;
    }
};

//기본 계좌 클래스
class NormalAccount: public Account { 
private:
    int Rate; 
public:
    NormalAccount(int accountNum, int money): Account(accountNum, money), Rate(5) {}

    void Deposit(int money) { 
        Account::Deposit(money); 
        Account::Deposit(money * (Rate / 100.0)); //% → 소수로 변환
    }
};

//고급 계좌 클래스
class HighAccount : public NormalAccount { 
private:
    char grade; 
    int gradeRate; 

public:
    HighAccount(int accountNum, int money, char grade): NormalAccount(accountNum, money), grade(grade) {}

    void Deposit(int money) { 
        if (grade == 'A') {
            gradeRate = 5; //추가 이자율 5%
        }
        else if (grade == 'B') {
             gradeRate = 3; //추가 이자율 3%
        }
        else if (grade == 'C') {
            gradeRate = 1; //추가 이자율 1%
        }

        NormalAccount::Deposit(money); 
        Account::Deposit(money * (gradeRate / 100.0)); //% → 소수로 변환

    }
};

//계좌 삭제 클래스
class AccountDelete {
private:
    Account** accArr; 
    int* accNum; 

public:
    AccountDelete(Account** accounts, int* num): accArr(accounts), accNum(num) {}

    void DeleteAccount() {
        cout << "삭제할 계좌번호: ";
        int accID;
        cin >> accID;

        for (int i = 0; i < *accNum; i++) { //입력받은 계좌번호와 일치하는 계좌를 찾기
            if (accArr[i]->GetAccNum() == accID) {
                delete accArr[i];  
                accArr[i] = accArr[*accNum - 1];
                accArr[*accNum - 1] = nullptr; 
                (*accNum)--; 
                cout << "선택하신 계좌가 삭제되었습니다." << endl;
                return;
            }
        }
        cout << "유효하지 않은 계좌번호입니다." << endl;
    }
};

//계좌 관리 클래스
class AccountManager {

private:
    Account* accArr[50]; 
public:
    int accNum = 0; 
    void ShowMenu(); 
    void MakeAccount();
    void DepositAccount(); 
    void WithdrawAccount();
    void DeleteAccount();
    void ShowAccount();
};


int main(void) {

    cout << "***** 은행 계좌 관리 프로그램 *****" << endl;
    AccountManager manager;

    while (true) {

        manager.ShowMenu();
        int num;
        cin >> num;

        switch (num) {
        case 1:
            manager.MakeAccount();
            break;
        case 2:
            manager.DepositAccount();
            break;
        case 3:
            manager.WithdrawAccount();
            break;
        case 4:
            manager.DeleteAccount();
            break;
        case 5:
            manager.ShowAccount();
            break;
        case 6:
            return 0;
        }

    }
}

//은행 메뉴 출력
void AccountManager::ShowMenu() {

    cout << "----- Bank Menu -----" << endl;
    cout << "1. 계좌 개설" << endl;
    cout << "2. 입금" << endl;
    cout << "3. 출금" << endl;
    cout << "4. 계좌 삭제" << endl;
    cout << "5. 계좌 정보 전체 출력" << endl;
    cout << "6. 프로그램 종료" << endl;
    cout << "선택: ";

}

//계좌 만들기
void AccountManager::MakeAccount() {
    int num;
    int accountNum;
    int balance;
    char grade;

    cout << "[계좌 종류 선택]" << endl;
    cout << "1.기본 계좌 2.고급 계좌" << endl;
    cout << "선택: "; cin >> num;
    cout << "계좌번호: "; cin >> accountNum;

    //계좌번호 중복 검사
    for (int i = 0; i < accNum; i++) {
        if (accArr[i]->GetAccNum() == accountNum) {
            cout << "이미 존재하는 계좌번호입니다. 다시 시도하세요." << endl;
            return;  
        }
    }

    cout << "입금할 금액: ";
    cin >> balance;

    if (num == 1) {
        accArr[accNum] = new NormalAccount(accountNum, balance); //일반 계좌 생성
    }
    else if (num == 2) {
        cout << "신용 등급(A,B,C): "; cin >> grade;
        accArr[accNum] = new HighAccount(accountNum, balance, grade); //고급 계좌 생성
    }
    accNum++;
}

//입금
void AccountManager::DepositAccount() {

    int accID;
    int money;
    
    cout << "[입금]" << endl;
    cout << "계좌번호: "; cin >> accID;
    cout << "입금할 금액: "; cin >> money;

    for (int i = 0; i < accNum; i++) {

        if (accID == accArr[i]->GetAccNum()) {
            accArr[i]->Deposit(money);
            return;
        }
    }
    cout << "유효하지 않은 계좌번호입니다." << endl;
}

//출금
void AccountManager::WithdrawAccount() {
    
    int accID;
    int money;

    cout << "[출금]" << endl;
    cout << "계좌번호: "; cin >> accID;
    cout << "출금할 금액: "; cin >> money;

    for (int i = 0; i < accNum; i++) {

        if (accID == accArr[i]->GetAccNum()) {
            if (accArr[i]->Withdraw(money) == 0) {
                cout << "잔액이 부족합니다." << endl;
            }
            else {
                cout << money << "원이 출금되었습니다." << endl;
            }
            return;
        }
    }
    cout << "유효하지 않은 계좌번호입니다." << endl;

}

//계좌 삭제
void AccountManager::DeleteAccount()
{
    cout << "[계좌 삭제]" << endl;

    AccountDelete deleter(accArr, &accNum);
    deleter.DeleteAccount();
}


//계좌정보 전체 출력
void AccountManager::ShowAccount() {

    cout << "[계좌정보 전체 출력]" << endl;

    for (int i = 0; i < accNum; i++) {
        accArr[i]->ShowAccount();
        cout << endl;
    }
}