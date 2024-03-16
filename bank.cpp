#include <iostream>
#include <string>
using namespace std;

//���� Ŭ����
class Account {

    int accountNum; 
    int balance; 

public:
    Account(int accountNum, int money): accountNum(accountNum), balance(money) {} 

    int GetAccNum() { 
        return accountNum;
    }

    virtual void Deposit(int money) { 
        cout << money << "���� �ԱݵǾ����ϴ�." << endl;
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
        cout << "���¹�ȣ: " << accountNum << endl;
        cout << "�ܾ�: " << balance << endl;
    }
};

//�⺻ ���� Ŭ����
class NormalAccount: public Account { 
private:
    int Rate; 
public:
    NormalAccount(int accountNum, int money): Account(accountNum, money), Rate(5) {}

    void Deposit(int money) { 
        Account::Deposit(money); 
        Account::Deposit(money * (Rate / 100.0)); //% �� �Ҽ��� ��ȯ
    }
};

//��� ���� Ŭ����
class HighAccount : public NormalAccount { 
private:
    char grade; 
    int gradeRate; 

public:
    HighAccount(int accountNum, int money, char grade): NormalAccount(accountNum, money), grade(grade) {}

    void Deposit(int money) { 
        if (grade == 'A') {
            gradeRate = 5; //�߰� ������ 5%
        }
        else if (grade == 'B') {
             gradeRate = 3; //�߰� ������ 3%
        }
        else if (grade == 'C') {
            gradeRate = 1; //�߰� ������ 1%
        }

        NormalAccount::Deposit(money); 
        Account::Deposit(money * (gradeRate / 100.0)); //% �� �Ҽ��� ��ȯ

    }
};

//���� ���� Ŭ����
class AccountDelete {
private:
    Account** accArr; 
    int* accNum; 

public:
    AccountDelete(Account** accounts, int* num): accArr(accounts), accNum(num) {}

    void DeleteAccount() {
        cout << "������ ���¹�ȣ: ";
        int accID;
        cin >> accID;

        for (int i = 0; i < *accNum; i++) { //�Է¹��� ���¹�ȣ�� ��ġ�ϴ� ���¸� ã��
            if (accArr[i]->GetAccNum() == accID) {
                delete accArr[i];  
                accArr[i] = accArr[*accNum - 1];
                accArr[*accNum - 1] = nullptr; 
                (*accNum)--; 
                cout << "�����Ͻ� ���°� �����Ǿ����ϴ�." << endl;
                return;
            }
        }
        cout << "��ȿ���� ���� ���¹�ȣ�Դϴ�." << endl;
    }
};

//���� ���� Ŭ����
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

    cout << "***** ���� ���� ���� ���α׷� *****" << endl;
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

//���� �޴� ���
void AccountManager::ShowMenu() {

    cout << "----- Bank Menu -----" << endl;
    cout << "1. ���� ����" << endl;
    cout << "2. �Ա�" << endl;
    cout << "3. ���" << endl;
    cout << "4. ���� ����" << endl;
    cout << "5. ���� ���� ��ü ���" << endl;
    cout << "6. ���α׷� ����" << endl;
    cout << "����: ";

}

//���� �����
void AccountManager::MakeAccount() {
    int num;
    int accountNum;
    int balance;
    char grade;

    cout << "[���� ���� ����]" << endl;
    cout << "1.�⺻ ���� 2.��� ����" << endl;
    cout << "����: "; cin >> num;
    cout << "���¹�ȣ: "; cin >> accountNum;

    //���¹�ȣ �ߺ� �˻�
    for (int i = 0; i < accNum; i++) {
        if (accArr[i]->GetAccNum() == accountNum) {
            cout << "�̹� �����ϴ� ���¹�ȣ�Դϴ�. �ٽ� �õ��ϼ���." << endl;
            return;  
        }
    }

    cout << "�Ա��� �ݾ�: ";
    cin >> balance;

    if (num == 1) {
        accArr[accNum] = new NormalAccount(accountNum, balance); //�Ϲ� ���� ����
    }
    else if (num == 2) {
        cout << "�ſ� ���(A,B,C): "; cin >> grade;
        accArr[accNum] = new HighAccount(accountNum, balance, grade); //��� ���� ����
    }
    accNum++;
}

//�Ա�
void AccountManager::DepositAccount() {

    int accID;
    int money;
    
    cout << "[�Ա�]" << endl;
    cout << "���¹�ȣ: "; cin >> accID;
    cout << "�Ա��� �ݾ�: "; cin >> money;

    for (int i = 0; i < accNum; i++) {

        if (accID == accArr[i]->GetAccNum()) {
            accArr[i]->Deposit(money);
            return;
        }
    }
    cout << "��ȿ���� ���� ���¹�ȣ�Դϴ�." << endl;
}

//���
void AccountManager::WithdrawAccount() {
    
    int accID;
    int money;

    cout << "[���]" << endl;
    cout << "���¹�ȣ: "; cin >> accID;
    cout << "����� �ݾ�: "; cin >> money;

    for (int i = 0; i < accNum; i++) {

        if (accID == accArr[i]->GetAccNum()) {
            if (accArr[i]->Withdraw(money) == 0) {
                cout << "�ܾ��� �����մϴ�." << endl;
            }
            else {
                cout << money << "���� ��ݵǾ����ϴ�." << endl;
            }
            return;
        }
    }
    cout << "��ȿ���� ���� ���¹�ȣ�Դϴ�." << endl;

}

//���� ����
void AccountManager::DeleteAccount()
{
    cout << "[���� ����]" << endl;

    AccountDelete deleter(accArr, &accNum);
    deleter.DeleteAccount();
}


//�������� ��ü ���
void AccountManager::ShowAccount() {

    cout << "[�������� ��ü ���]" << endl;

    for (int i = 0; i < accNum; i++) {
        accArr[i]->ShowAccount();
        cout << endl;
    }
}