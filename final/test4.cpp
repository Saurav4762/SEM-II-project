#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

struct detail {
    string name, accountType, password;
    int accountNumber, pin;
    double balance, amount;
} D;

vector<detail> accounts;

class Bank {
private:
public:
    void createAccount();
    void deposit();
    void withdraw();
    void checkBalance();
    void displayAllAccounts();
    void deleteAccount();
    void transaction();
    void validation();
    void Register();
    void Login();
    void exit();
};

void Bank::createAccount() {
    system("cls");
    string accNam;
    int accNum, choice;
    detail newaccount;

    fstream filess("accounts.txt", ios::in);
    if (!filess) {
        ofstream createFile("accounts.txt");
        createFile.close();
        filess.open("accounts.txt", ios::in);
    }

    while (true) {
        cout << "Enter name: ";
        cin >> newaccount.name;

        bool validName = true;
        for (char c : newaccount.name) {
            if (!isalpha(c)) {
                validName = false;
                break;
            }
        }

        if (validName) {
            break;
        } else {
            cout << "Name should contain only alphabets! Please try again." << endl;
        }
    }
    while (true) {
        cout << "Set your 4-digit PIN: ";
        cin >> newaccount.pin;

        if (newaccount.pin >= 1000 && newaccount.pin <= 9999) {
            break;
        } else {
            cout << "PIN must be exactly 4 digits! Please try again." << endl;
        }
    }

    cout << "Set your account number: ";
    cin >> newaccount.accountNumber;

    bool accountExists = false;
    while (filess >> accNam >> accNum) {
        if (accNum == newaccount.accountNumber) {
            accountExists = true;
            break;
        }
    }
    if (accountExists) {
        cout << "Account Number Already Exists!" << endl;
        return;
    }
    filess.close();

    cout << "Enter account type: " << endl;
    cout << "1. Saving" << endl
         << "2. Current" << endl
         << "3. Fixed" << endl;
    cin >> choice;
    switch (choice) {
        case 1: newaccount.accountType = "Saving"; break;
        case 2: newaccount.accountType = "Current"; break;
        case 3: newaccount.accountType = "Fixed"; break;
        default: 
            cout << "Invalid choice!" << endl;
            return;
    }
    cout << "Enter balance: ";
    cin >> newaccount.balance;
    while (newaccount.balance < 1) {
        cout << "Enter a valid amount!" << endl;
        cout << "Enter balance: ";
        cin >> newaccount.balance;
    }

    cout << "Account created successfully!" << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();

    accounts.push_back(newaccount);

    fstream file;
    file.open("accounts.txt", ios::out | ios::app);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    file << newaccount.name << " " << newaccount.accountNumber << " " << newaccount.accountType << " " << newaccount.pin << " " << newaccount.balance << endl;
    file.close();
}

void Bank::deposit() {
    system("cls");
    detail temp2;
    int tempac;
    bool ismatch = false;
    cout << "Enter Account Number: ";
    cin >> tempac;

    fstream file("accounts.txt", ios::in | ios::out);
    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }

    fstream temp_file("temp_account.txt", ios::out);
    if (!temp_file) {
        cout << "Error opening temp file." << endl;
        return;
    }

    while (file >> temp2.name >> temp2.accountNumber >> temp2.accountType >> temp2.pin >> temp2.balance) {
        if (temp2.accountNumber == tempac) {
            ismatch = true;
            int pin;
            cout << "Enter PIN: ";
            cin >> pin;

            if (temp2.pin != pin) {
                cout << "Invalid PIN!" << endl;
                return;
            }

            cout << "Account found!" << endl;
            cout << "Name: " << temp2.name << endl;
            cout << "Current Balance: " << temp2.balance << endl;
            cout << "Enter amount to deposit: ";
            cin >> D.amount;

            temp2.balance += D.amount;
            cout << "New Balance: " << temp2.balance << endl;
        }
        temp_file << temp2.name << " " << temp2.accountNumber << " "
                  << temp2.accountType << " " << temp2.pin << " " << temp2.balance << endl;
    }

    file.close();
    temp_file.close();

    if (!ismatch) {
        cout << "Account number not found!" << endl;
    }

    remove("accounts.txt");
    rename("temp_account.txt", "accounts.txt");
}

void Bank::withdraw() {
    system("cls");
    detail temp3;
    int tempac;
    bool ismatch = false;
    cout << "Enter Account Number: ";
    cin >> tempac;

    fstream file("accounts.txt", ios::in | ios::out);
    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }

    fstream temp_file("temp_account.txt", ios::out);
    if (!temp_file) {
        cout << "Error opening temp file." << endl;
        return;
    }

    while (file >> temp3.name >> temp3.accountNumber >> temp3.accountType >> temp3.pin >> temp3.balance) {
        if (temp3.accountNumber == tempac) {
            ismatch = true;
            int pin;
            cout << "Enter PIN: ";
            cin >> pin;

            if (temp3.pin != pin) {
                cout << "Invalid PIN!" << endl;
                return;
            }

            cout << "Account found!" << endl;
            cout << "Name: " << temp3.name << endl;
            cout << "Current Balance: " << temp3.balance << endl;
            cout << "Enter amount to withdraw: ";
            cin >> temp3.amount;

            while (temp3.balance < temp3.amount) {
                cout << "Enter an amount less than your current balance." << endl;
                cout << "Enter amount to withdraw: ";
                cin >> temp3.amount;
            }
            temp3.balance -= temp3.amount;
            cout << "New Balance: " << temp3.balance << endl;
        }
        temp_file << temp3.name << " " << temp3.accountNumber << " "
                  << temp3.accountType << " " << temp3.pin << " " << temp3.balance << endl;
    }

    file.close();
    temp_file.close();

    if (!ismatch) {
        cout << "Account number not found!" << endl;
    }

    remove("accounts.txt");
    rename("temp_account.txt", "accounts.txt");
}

void Bank::checkBalance() {
    system("cls");
    detail temp;
    int tempNum;
    bool isfound = false;
    cout << "Enter the Bank Account Number: ";
    cin >> tempNum;

    fstream file("accounts.txt");
    if (!file) {
        cout << "Error opening file" << endl;
        return;
    }

    while (file >> temp.name >> temp.accountNumber >> temp.accountType >> temp.pin >> temp.balance) {
        if (tempNum == temp.accountNumber) {
            cout << "Name: " << temp.name << endl;
            cout << "Account Balance: " << temp.balance << endl;
            isfound = true;
            break;
        }
    }

    if (!isfound) {
        cout << "Account Not Found.." << endl;
    }
    file.close();
}

void Bank::displayAllAccounts() {
    system("cls");
    detail temp;
    int acnum;
    bool ismatch = false;
    cout << "Enter Bank Account Number: ";
    cin >> acnum;

    fstream file("accounts.txt", ios::in);
    if (!file) {
        cout << "File not open.." << endl;
        return;
    }

    while (file >> temp.name >> temp.accountNumber >> temp.accountType >> temp.pin >> temp.balance) {
        if (temp.accountNumber == acnum) {
            ismatch = true;
            cout<<"---------------------------------------------"<<endl;
            cout << "Name: " << temp.name << endl;
            cout << "Account Number: " << temp.accountNumber << endl;
            cout << "Account Type: " << temp.accountType << endl; 
            cout << "Account Balance: " << temp.balance << endl;
            cout<< "----------------------------------------------"<<endl;
            return;
        }
    }

    file.close();

    if (!ismatch) {
        cout << "Account number not found!" << endl;
        return;
    }
}

void Bank::deleteAccount() {
    system("cls");
    detail temp;
    int acnum;
    bool ismatch = false;
    cout << "Enter Bank Account Number: ";
    cin >> acnum;

    fstream file("accounts.txt", ios::in);
    if (!file) {
        cout << "File not open.." << endl;
        return;
    }

    fstream temp_file("temp_accounts.txt", ios::out);
    if (!temp_file) {
        cout << "Error creating temp file!" << endl;
        file.close();
        return;
    }

    while (file >> temp.name >> temp.accountNumber >> temp.accountType >> temp.pin >> temp.balance) {
        if (temp.accountNumber == acnum) {
            ismatch = true;
            cout << "Account found and deleted!" << endl;
            continue;
        }
        temp_file << temp.name << " " << temp.accountNumber << " "
                  << temp.accountType << " " << temp.pin << " " << temp.balance << endl;
    }

    file.close();
    temp_file.close();

    if (!ismatch) {
        cout << "Account number not found!" << endl;
        remove("temp_accounts.txt");
        return;
    }

    remove("accounts.txt");
    rename("temp_accounts.txt", "accounts.txt");
}

void Bank::transaction() {
    system("cls");
    detail temp;
    int acNum, acNumb, tbalance;
    bool senderFound = false, receiverFound = false;

    cout << "Enter Your Account Number: ";
    cin >> acNum;

    fstream file("accounts.txt", ios::in);
    if (!file) {
        cout << "File not open!" << endl;
        return;
    }

    detail accounts[100];
    int count = 0;

    while (file >> accounts[count].name >> accounts[count].accountNumber >> accounts[count].accountType >> accounts[count].pin >> accounts[count].balance) {
        count++;
    }
    file.close();

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == acNum) {
            senderFound = true;
            int pin;
            cout << "Enter PIN: ";
            cin >> pin;

            if (accounts[i].pin != pin) {
                cout << "Invalid PIN!" << endl;
                return;
            }
            cout << "Your Name: " << accounts[i].name << endl;
            cout << "Your Balance: " << accounts[i].balance << endl;
            cout << "======= Send Money =======" << endl;
            cout << "Enter Amount: ";
            cin >> tbalance;

            if (accounts[i].balance < tbalance) {
                cout << "Insufficient balance!" << endl;
                return;
            }

            cout << "Enter Receiver Account Number: ";
            cin >> acNumb;

            for (int j = 0; j < count; j++) {
                if (accounts[j].accountNumber == acNumb) {
                    if (acNumb == acNum) {
                        cout << "You cannot send money to your own account!" << endl;
                        return;
                    }

                    receiverFound = true;

                    accounts[i].balance -= tbalance;
                    accounts[j].balance += tbalance;

                    cout << "Transaction successful!" << endl;
                    cout << "Your new balance: " << accounts[i].balance << endl;

                    ofstream outFile("accounts.txt", ios::trunc);
                    for (int k = 0; k < count; k++) {
                        outFile << accounts[k].name << " " << accounts[k].accountNumber << " "
                                << accounts[k].accountType << " " << accounts[k].pin << " " << accounts[k].balance << endl;
                    }
                    outFile.close();
                    return;
                }
            }

            if (!receiverFound) {
                cout << "Receiver account not found!" << endl;
                return;
            }
        }
    }

   
    if (!senderFound) {
        cout << "Sender account not found!" << endl;
    }
}
void Bank:: exit()
{
    Bank b;
    b.validation();
}


void menu() {
    Bank b;
    int choice;
    while (true) {
        system("cls");
        cout << "====================================" << endl;
        cout << "       BANK MANAGEMENT SYSTEM       " << endl;
        cout << "====================================" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. Display Accounts Detail" << endl;
        cout << "6. Delete Account" << endl;
        cout << "7. Transaction Management " << endl;
        cout << "8. Exit" << endl;
        cout << "====================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
        }

        switch (choice) {
        case 1:
            b.createAccount();
            break;
        case 2:
            b.deposit();
            break;
        case 3:
            b.withdraw();
            break;
        case 4:
            b.checkBalance();
            break;
        case 5:
            b.displayAllAccounts();
            break;
        case 6:
            b.deleteAccount();
            break;
        case 7:
            b.transaction();
            break;
        case 8:
            b.validation();
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void Bank::Login() {
    system("cls");
    detail loginData;
    string tempName, tempPassword;
    bool ismatch = false;

    ifstream file("UserLoginData.txt", ios::in);
    if (!file) {
        cout << "File Not Found!" << endl;
        return;
    }

    while (!ismatch) {
        cout << "Enter Your Username: ";
        cin >> tempName;

        bool validUsername = true;
        for (char c : tempName) {
            if (!isalpha(c)) {
                validUsername = false;
                break;
            }
        }

        if (!validUsername) {
            cout << "Username should contain only alphabets! Please try again." << endl;
            continue;
        }

        cout << "Enter Your Password: ";
        cin >> tempPassword;

        file.clear();  
        file.seekg(0); 

        while (file >> loginData.name >> loginData.password) {
            if (tempName == loginData.name && tempPassword == loginData.password) {
                ismatch = true;
                cout << "Login Successful! Welcome, " << tempName << "!" << endl;
                return;
            }
        }

        if (!ismatch) {
            cout << "Invalid username or password! Try again." << endl;
        }
    }
    file.close();
}

void Bank::Register() {
    system("cls");
    detail registerData;
    ofstream file("UserLoginData.txt", ios::app);
    
    if (!file) {
        cout << "File Not Found!" << endl;
        return;
    }

    while (true) {
        cout << "Enter Username: ";
        cin >> registerData.name;

        bool validUsername = true;
        for (char c : registerData.name) {
            if (!isalpha(c)) {
                validUsername = false;
                break;
            }
        }

        if (!validUsername) {
            cout << "Username should contain only alphabets! Please try again." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter Password (alphabets and numbers only): ";
        cin >> registerData.password;

        bool hasLetter = false, hasDigit = false;
        for (char c : registerData.password) {
            if (isalpha(c)) hasLetter = true;
            if (isdigit(c)) hasDigit = true;
        }

        if (!(hasLetter || hasDigit)) {
            cout << "Password must contain at least one letter or number! Please try again." << endl;
            continue;
        }
        break;
    }

    file << registerData.name << " " << registerData.password << endl;
    file.close();
    
    cout << "Registration Successful!" << endl;
    validation();
}


void Bank::validation()
{
    system("cls");
    Bank b;
    int choice;
    
    while (true) {
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;

        if (cin.fail()) { 
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            cout << "Invalid choice! Please enter 1 or 2." << endl;
            continue;
        }

        if (choice == 1) {
            b.Login();
            break;
        } else if (choice == 2) {
            b.Register();
            break;
        } else {
            cout << "Invalid choice! Please enter 1 or 2." << endl;
        }
    }
}


int main() {
    Bank b;
    b.validation();
    menu();
    return 0;
}