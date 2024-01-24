#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<string>

using namespace std;

class Account {
    int acno;
    string name;
    int deposit;
    char type;

public:
    void createAccount();
    void showAccount() const;
    void modify();
    void depositAmount(int);
    void withdrawAmount(int);
    void report() const;

    int getAccountNumber() const;
    int getDepositAmount() const;
    char getAccountType() const;
};

void Account::createAccount() {
    cout << "\nEnter The account No. : ";
    cin >> acno;
    cout << "\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    getline(cin, name);
    cout << "\nEnter Type of The account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter The Initial amount (>=500 for Saving and >=1000 for current): ";
    cin >> deposit;
    cout << "\n\n\nAccount Created..";
}

void Account::showAccount() const {
    cout << "\nAccount No. : " << acno;
    cout << "\nAccount Holder Name : " << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit;
}

void Account::modify() {
    cout << "\nAccount No. : " << acno;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    getline(cin, name);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : ";
    cin >> deposit;
}

void Account::depositAmount(int x) {
    deposit += x;
}

void Account::withdrawAmount(int x) {
    deposit -= x;
}

void Account::report() const {
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int Account::getAccountNumber() const {
    return acno;
}

int Account::getDepositAmount() const {
    return deposit;
}

char Account::getAccountType() const {
    return type;
}

// Function Declarations
void writeAccount();
void displayAccount(int);
void modifyAccount(int);
void deleteAccount(int);
void displayAllAccounts();
void depositOrWithdraw(int, int);
void introduction();

int main() {
    char choice;
    int accountNumber;
    introduction();

    do {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8): ";
        cin >> choice;

        system("cls");

        switch (choice) {
            case '1':
                writeAccount();
                break;
            case '2':
                cout << "\n\n\tEnter The account No. : ";
                cin >> accountNumber;
                depositOrWithdraw(accountNumber, 1);
                break;
            case '3':
                cout << "\n\n\tEnter The account No. : ";
                cin >> accountNumber;
                depositOrWithdraw(accountNumber, 2);
                break;
            case '4':
                cout << "\n\n\tEnter The account No. : ";
                cin >> accountNumber;
                displayAccount(accountNumber);
                break;
            case '5':
                displayAllAccounts();
                break;
            case '6':
                cout << "\n\n\tEnter The account No. : ";
                cin >> accountNumber;
                deleteAccount(accountNumber);
                break;
            case '7':
                cout << "\n\n\tEnter The account No. : ";
                cin >> accountNumber;
                modifyAccount(accountNumber);
                break;
            case '8':
                cout << "\n\n\tThanks for using the bank management system";
                break;
            default:
                cout << "\a";
        }

        cin.ignore();
        cin.get();
    } while (choice != '8');

    return 0;
}

void writeAccount() {
    Account ac;
    ofstream outFile("database.csv", ios::app);
    ac.createAccount();
    outFile << ac.getAccountNumber() << "," << ac.getAccountType() << "," << ac.getDepositAmount() << "," << ac.getDepositAmount() << "," << ac.getAccountType() << endl;
    outFile.close();
}

void displayAccount(int n) {
    Account ac;
    bool found = false;
    ifstream inFile("database.csv");

    if (!inFile) {
        cout << "File could not be opened! Press any key...";
        return;
    }

    cout << "\nBALANCE DETAILS\n";

    while (inFile >> ac.acno >> ac.type >> ac.deposit) {
        if (ac.getAccountNumber() == n) {
            ac.showAccount();
            found = true;
        }
    }

    inFile.close();

    if (!found)
        cout << "\n\nAccount number does not exist";
}

void modifyAccount(int n) {
    bool found = false;
    Account ac;
    fstream File("database.csv", ios::in | ios::out);

    if (!File) {
        cout << "File could not be opened! Press any key...";
        return;
    }

    while (File >> ac.acno >> ac.type >> ac.deposit) {
        if (ac.getAccountNumber() == n) {
            ac.showAccount();
            cout << "\n\nEnter The New Details of the account" << endl;
            ac.modify();

            int position = static_cast<int>(File.tellg()) - static_cast<int>(sizeof(ac));
            File.seekp(position, ios::beg);

            File << ac.getAccountNumber() << "," << ac.getAccountType() << "," << ac.getDepositAmount() << "," << ac.getDepositAmount() << "," << ac.getAccountType() << endl;

            cout << "\n\n\t Record Updated";
            found = true;
            break;
        }
    }

    File.close();

    if (!found)
        cout << "\n\n Record Not Found ";
}

void deleteAccount(int n) {
    Account ac;
    ifstream inFile("database.csv");
    ofstream outFile("Temp.csv");

    if (!inFile) {
        cout << "File could not be opened! Press any key...";
        return;
    }

    while (inFile >> ac.acno >> ac.type >> ac.deposit) {
        if (ac.getAccountNumber() != n)
            outFile << ac.getAccountNumber() << "," << ac.getAccountType() << "," << ac.getDepositAmount() << "," << ac.getDepositAmount() << "," << ac.getAccountType() << endl;
    }

    inFile.close();
    outFile.close();

    remove("database.csv");
    rename("Temp.csv", "database.csv");

    cout << "\n\n\tRecord Deleted ..";
}

void displayAllAccounts() {
    Account ac;
    ifstream inFile("database.csv");

    if (!inFile) {
        cout << "File could not be opened! Press any key...";
        return;
    }

    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";

    while (inFile >> ac.acno >> ac.type >> ac.deposit) {
        ac.report();
    }

    inFile.close();
}

void depositOrWithdraw(int n, int option) {
    int amount;
    bool found = false;
    Account ac;
    fstream File("database.csv", ios::in | ios::out);

    if (!File) {
        cout << "File could not be opened! Press any key...";
        return;
    }

    while (File >> ac.acno >> ac.type >> ac.deposit) {
        if (ac.getAccountNumber() == n) {
            ac.showAccount();

            if (option == 1) {
                cout << "\n\n\tTO DEPOSIT AMOUNT ";
                cout << "\n\nEnter The amount to be deposited: ";
                cin >> amount;
                ac.depositAmount(amount);
            }

            if (option == 2) {
                cout << "\n\n\tTO WITHDRAW AMOUNT ";
                cout << "\n\nEnter The amount to be withdrawn: ";
                cin >> amount;

                int balance = ac.getDepositAmount() - amount;

                if ((balance < 500 && ac.getAccountType() == 'S') || (balance < 1000 && ac.getAccountType() == 'C'))
                    cout << "Insufficient balance";
                else
                    ac.withdrawAmount(amount);
            }

            int position = static_cast<int>(File.tellg()) - static_cast<int>(sizeof(ac));
            File.seekp(position, ios::beg);

            File << ac.getAccountNumber() << "," << ac.getAccountType() << "," << ac.getDepositAmount() << "," << ac.getDepositAmount() << "," << ac.getAccountType() << endl;

            cout << "\n\n\t Record Updated";
            found = true;
            break;
        }
    }

    File.close();

    if (!found)
        cout << "\n\n Record Not Found ";
}

void introduction() {
    cout << "\n\n\n\t  BANK";
    cout << "\n\n\tMANAGEMENT";
    cout << "\n\n\t  SYSTEM";
    cin.get();
}
