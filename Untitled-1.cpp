
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct detail
{
    string name, accountType;
    int accountNumber, tempaccountNumber;
    double balance, amount;
} D;

vector<detail> accounts;

class Bank
{
private:
public:
    void createAccount();
    void deposit();
    void withdraw();
    void checkBalance();
    void displayAllAccounts();
    void deleteAccount();
    void transaction();
    void exit();
};

void Bank::createAccount()
{
    system("cls");
    string accNam;
    int accNum,choice;
    detail newaccount;

    fstream filess("accounts.txt", ios::in);
    if (!filess)
    {
        //if file dosen't exist, create one
       ofstream createFile ("account.txt");
       createFile.close();
       //Reopen for reading 
       filess.open("accounts.txt",ios::in);
    }
    cout << "Enter name: ";
    cin >> newaccount.name;
    cout << "Enter account number: ";
    cin >> newaccount.accountNumber;
    while (filess >> accNam >> accNum)
    {
        if (accNum == newaccount.accountNumber)
        {
            cout << "Account Number Already Exist !" << endl;
            cout << "Enter account number: ";
            cin >> newaccount.accountNumber;
            filess.clear();
            filess.seekg(0, ios::beg);
        }
    }
    filess.close();

    cout << "Enter account type: " << endl;
    cout << "1.Saving" << endl
         << "2.Current" << endl
         << "3.Fix" << endl;
    cin >> choice;
    switch (choice) {
        case 1: newaccount.accountType = "Saving"; break;
        case 2: newaccount.accountType = "Current"; break;
        case 3: newaccount.accountType = "Fix"; break;
        default: 
            cout << "Invalid choice!" << endl;
            return;
    }
    cout << "Enter balance: ";
    cin >> newaccount.balance;
    while (newaccount.balance < 1)
    {
        cout << "Enter Valid Number" << endl;
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
    if (!file)
    {
        cout << "Error in opening file..";
        return;
    }

    file << newaccount.name << " " << newaccount.accountNumber << " " << newaccount.accountType << " " << newaccount.balance << endl;

    file.close();
}

void Bank::deposit()
{
    system("cls");
    detail temp2;
    int tempac;
    bool ismatch = false;
    cout << "Enter Account Number:";
    cin >> tempac;

    fstream file;
    file.open("accounts.txt", ios::in | ios::out);
    if (!file)
    {
        cout << "Error in opening file.";
    };

    fstream temp_file;
    temp_file.open("temp_account.txt", ios::out);
    if (!file)
    {
        cout << "Error in opening file.";
    };

    while (file >> temp2.name >> temp2.accountNumber >> temp2.accountType >> temp2.balance)
    {
        if (temp2.accountNumber == tempac)
        {
            ismatch = true;
            cout << "Account found!" << endl;
            cout << "Name: " << temp2.name << endl;
            cout << "Current Balance: " << temp2.balance << endl;
            cout << "Enter amount to deposit:";
            cin >> D.amount;

            temp2.balance += D.amount;
            cout << "New Balance: " << temp2.balance << endl;
        }
        temp_file << temp2.name << " " << temp2.accountNumber << " "
                  << temp2.accountType << " " << temp2.balance << endl;
    }

    file.close();
    temp_file.close();

    if (!ismatch)
    {
        cout << "Account number not found!" << endl;
    }

    if (!ifstream("temp_account.txt"))
    {
        cout << "Error: temp file not created properly!" << endl;
        return;
    }

    remove("accounts.txt");
    rename("temp_account.txt", "accounts.txt");
}

void Bank::withdraw()
{
    system("cls");
    detail temp3;
    int tempac;
    bool ismatch = false;
    cout << "Enter Account Number:";
    cin >> tempac;

    fstream file;
    file.open("accounts.txt", ios::in | ios::out);
    if (!file)
    {
        cout << "Error in opening file.";
    };

    fstream temp_file;
    temp_file.open("temp_account.txt", ios::out);
    if (!file)
    {
        cout << "Error in opening file.";
    };

    while (file >> temp3.name >> temp3.accountNumber >> temp3.accountType >> temp3.balance)
    {
        if (temp3.accountNumber == tempac)
        {
            ismatch = true;
            cout << "Account found!" << endl;
            cout << "Name: " << temp3.name << endl;
            cout << "Current Balance: " << temp3.balance << endl;
            cout << "Enter amount to Withdraw:";
            cin >> temp3.amount;
            while (temp3.balance < temp3.amount)
            {
                cout << "Enter less then your current balance " << endl;
                cout << "Enter amount to Withdraw:";
                cin >> temp3.amount;
            }
            temp3.balance -= temp3.amount;
            cout << "New Balance: " << temp3.balance << endl;
        }
        temp_file << temp3.name << " " << temp3.accountNumber << " "
                  << temp3.accountType << " " << temp3.balance << endl;
    }

    file.close();
    temp_file.close();

    if (!ismatch)
    {
        cout << "Account number not found!" << endl;
    }

    if (!ifstream("temp_account.txt"))
    {
        cout << "Error: temp file not created properly!" << endl;
        return;
    }

    remove("accounts.txt");
    rename("temp_account.txt", "accounts.txt");
}

void Bank::checkBalance()
{
    system("cls");
    detail temp;
    int tempNum;
    bool isfound = false;
    cout << " Enter The Bank Account Number:";
    cin >> tempNum;

    fstream file;
    file.open("accounts.txt");
    if (!file)
    {
        cout << "Error in opening file" << endl;
        return;
    }

    while (file >> temp.name >> temp.accountNumber >> temp.accountType >> temp.balance)
    {
        if (tempNum == temp.accountNumber)
        {
            cout << "Name: " << temp.name << endl;
            cout << "Account Balancer: " << temp.balance << endl;
            isfound = true;
            break;
        }
    }
    if (!isfound)
    {
        cout << "Accoutn Not Found.." << endl;
    }
    file.close();
}

void Bank::displayAllAccounts()
{
    system("cls");
    detail temp;
    int acnum;
    bool ismatch = false;
    cout << "Enter Bank Account Number: ";
    cin >> acnum;

    // Open accounts file in read mode
    fstream file;
    file.open("accounts.txt", ios::in);
    if (!file)
    {
        cout << "File Not Open.." << endl;
        return;
    }

    // Read each account and copy to temp file except the one to delete
    while (file >> temp.name >> temp.accountNumber >> temp.accountType >> temp.balance)
    {
        if (temp.accountNumber == acnum)
        {
            ismatch = true;
            cout <<"Name: "<< temp.name << endl;
			cout<<"Accout Nummber: " << temp.accountNumber <<endl;
            cout<<"Account Type: "<< temp.accountType << endl; 
			cout<<"Account Balance: " << temp.balance << endl;
            return;
        }
    }

    file.close();

    // If account not found, delete temp file and return
    if (!ismatch)
    {
        cout << "Account number not found!" << endl;
        return;
    }
}

void Bank::deleteAccount()
{
    system("cls");
    detail temp;
    int acnum;
    bool ismatch = false;
    cout << "Enter Bank Account Number: ";
    cin >> acnum;

    fstream file;
    file.open("accounts.txt", ios::in);
    if (!file)
    {
        cout << "File Not Open.." << endl;
        return;
    }

    fstream temp_file;
    temp_file.open("temp_accounts.txt", ios::out);
    if (!temp_file)
    {
        cout << "Error creating temp file!" << endl;
        file.close();
        return;
    }

    while (file >> temp.name >> temp.accountNumber >> temp.accountType >> temp.balance)
    {
        if (temp.accountNumber == acnum)
        {
            ismatch = true;
            cout << "Account Found and Deleted..!" << endl;
            continue;
        }
        temp_file << temp.name << " " << temp.accountNumber << " "
                  << temp.accountType << " " << temp.balance << endl;
    }

    file.close();
    temp_file.close();

    if (!ismatch)
    {
        cout << "Account number not found!" << endl;
        remove("temp_accounts.txt");
        return;
    }

    remove("accounts.txt");
    rename("temp_accounts.txt", "accounts.txt");

}

void Bank::transaction()
{
    system("cls");
    detail temp;
    int acNum, acNumb, tbalance;
    bool senderFound = false, receiverFound = false;

    cout << "Enter Your Account Number: ";
    cin >> acNum;

    fstream file("accounts.txt", ios::in);
    if (!file)
    {
        cout << "File Not Open!" << endl;
        return;
    }

    // Read accounts into an array
    detail accounts[100]; // Assuming max 100 accounts
    int count = 0;

    while (file >> accounts[count].name >> accounts[count].accountNumber >> accounts[count].accountType >> accounts[count].balance)
    {
        count++;
    }
    file.close();

    // Find sender and take transaction details
    for (int i = 0; i < count; i++)
    {
        if (accounts[i].accountNumber == acNum)
        {
            senderFound = true;
            cout << "Your Name: " << accounts[i].name << endl;
            cout << "Your Amount: " << accounts[i].balance << endl;
            cout << "======= Send Money =======" << endl;
            cout << "Enter Amount: ";
            cin >> tbalance;

            // Check if sender has enough balance
            if (accounts[i].balance < tbalance)
            {
                cout << "Insufficient balance!" << endl;
                return;
            }

            cout << "Enter Receiver Account Number: ";
            cin >> acNumb;

            // Find receiver and update balances
            for (int j = 0; j < count; j++)
            {
                if (accounts[j].accountNumber == acNumb)
                {
                    if (acNumb == acNum)
                    {
                        cout << "You cannot send money to your own account!" << endl;
                        return;
                    }

                    receiverFound = true;

                    // Perform transaction (subtract from sender, add to receiver)
                    accounts[i].balance -= tbalance;
                    accounts[j].balance += tbalance;

                    cout << "Transaction successful!" << endl;
                    cout << "Your new balance: " << accounts[i].balance << endl;

                    // Update file with new balances
                    ofstream outFile("accounts.txt", ios::trunc);
                    for (int k = 0; k < count; k++)
                    {
                        outFile << accounts[k].name << " " << accounts[k].accountNumber << " "
                                << accounts[k].accountType << " " << accounts[k].balance << endl;
                    }
                    outFile.close();
                    return;
                }
            }

            if (!receiverFound)
            {
                cout << "Receiver account not found!" << endl;
                return;
            }
        }
    }

    if (!senderFound)
    {
        cout << "Sender account not found!" << endl;
    }
}

void Bank ::exit()
{
}

void menu()
{
    Bank b;
    int choice;
    while (true)
    {
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
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }

        switch (choice)
        {
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
        {
            b.displayAllAccounts();
            break;
        }
        case 6:
            b.deleteAccount();
            break;
        case 7:
            b.transaction();
            break;
        case 8:
            return;
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

int main()
{
    menu();
    return 0;
}