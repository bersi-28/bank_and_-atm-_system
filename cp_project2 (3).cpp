//*************************************************************************************************
//                                      HEADER FILE USED IN THE PROJECT
//*************************************************************************************************

#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include <cstdlib>

using namespace std;

//*************************************************************************************************
//                                      USER DEFINED DATA TYPE USED IN THE PROJECT
//*************************************************************************************************

struct AccountInfo
{
    char account_holder[50];
    int pin;
    long account_number;
    double balance;
    char phone_number[50];
    char address[50];
    char nationality[50];
    char occupation[50];
};
enum SYSTEM {BRANCH_SYSTEM =1 , ATM_SYSTEM , PRINT , EXIT1};
enum BRANCH { NEW =1, DEPOSIT , WITHDRAW_BRANCH , TRANSFER , CHECK_BALANCE , DISPLAY , DELETE_ACCOUNT,EXIT2 };
enum ATM { WITHDRAW_ATM =1, CHECKBALANCE, CHANGE_PIN , EXIT3 };


//*************************************************************************************************
//                                      FUNCTION DECLARATION
//*************************************************************************************************

void introduction();

void Branch_system();
void createAccount();
void delete_account();
void deposit();
void withdraw();
void transfer();
void displayAccountInfo();
void displayAccountInfo(AccountInfo &);

void ATM_system(AccountInfo &);
void withdraw(int&); //function overloding
void changePin();
void checkBalance();

void displayAllAccounts();


/***/

void updateAccountData(AccountInfo &);
bool verification(AccountInfo &, int);
void writeToFile(AccountInfo &);


const string TEMP_FILE_PATH = "temp_account.txt";
const string ACCOUNTS_FILE_PATH = "BANK_ACCOUNTS.dat";

int main()
{
    introduction();
    int con;
    do{
    srand(time(0)); // generate random number every time we want

    int choice;
    cout << "\t=========WELCOME TO OUR BANK===========\n";
    cout << "\t\t1. Branch system.\n";
    cout << "\t\t2. ATM system.\n";
    cout << "\t\t3. Display All Account Info.\n";
    cout << "\t\t4. Exit.\n";
    cout << "\n Please enter your choice.\n";
    cin >> choice;
    AccountInfo account;
    switch (choice)
    {
    case BRANCH_SYSTEM:
        Branch_system();
        break;
    case ATM_SYSTEM:
        ATM_system(account);
        break;
    case PRINT:
        displayAllAccounts();
        break;
    case EXIT1:
         cout <<"\nTHANK YOU FOR USING OUR SERVICE. WISH TO SEE YOU AGAIN.\n";
        exit(1);
    default:
        cout << "Invalid choice. please try again\n";
        break;
    }
    cout<<"If you want to get other services press 1: ";
    cin>>con;
    }while(con == 1);
    return 0;
}


//*************************************************************************************************
//                                      FUNCTIONS USED IN BRANCH SYSTEM
//*************************************************************************************************
void Branch_system()
{
    int con = 0;

        do{
        int choice =0;
        system("cls");
        cout << "------Welcome to Branch system------\n ";
        cout << "\t1. Create new account.\n";
        cout << "\t2. Deposit.\n";
        cout << "\t3. Withdraw.\n";
        cout << "\t4. Transfer.\n";
        cout << "\t5. Check balance.\n";
        cout << "\t6. Display account information.\n";
        cout << "\t7. Delete account.\n";
        cout << "\t8. Exit.\n";

        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case NEW:
            createAccount();
            break;
        case DEPOSIT:
            deposit();
            break;
        case WITHDRAW_BRANCH:
            withdraw();
            break;
        case TRANSFER:
            transfer();
            break;
        case CHECK_BALANCE:
            checkBalance();
            break;
        case DISPLAY:
            displayAccountInfo();
            break;
        case DELETE_ACCOUNT:
            delete_account();
        case EXIT2:
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }

            cout<<"If you want to continue press 1: ";
             cin >> con;
        }while(con == 1);

}
void createAccount()
{
    AccountInfo account;
    string line;
    cout << "Please enter the following informations.\n";
    cout << "\t Account Holder Name: ";
    cin.ignore();
    getline(cin, line);
    strcpy(account.account_holder, line.c_str());
    cout << "\t Initial Balance: ";
    cin >> account.balance;
    cout << "\t Phone number: ";
    cin >> account.phone_number;
    cout << "\t Address: ";
    cin.ignore();
    getline(cin, line);
    strcpy(account.address, line.c_str());
    cout << "\t Nationality: ";
    cin.ignore();
    getline(cin, line);
    strcpy(account.nationality, line.c_str());
    cout << "\t Occupation: ";
    cin.ignore();
    getline(cin, line);
    strcpy(account.occupation, line.c_str());
    long maximum = 999999;

    account.account_number = (rand() % maximum) + 100000; // Generate random account number


    {
        int max_num = 9999;
        account.pin = (rand() % max_num) + 1000;
        cout << "Account created successfully!\n";
        cout << "You have got ATM card!\n";
        displayAccountInfo(account);
        cout << "\n========================================\n";
        writeToFile(account);

    }

}

void deposit()
{
    long accountNumber;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accountNumber;

    AccountInfo account;
    if (verification(account,accountNumber))
    {
        cout << "Enter Deposit Amount: ";
        cin >> amount;

        account.balance += amount;
        updateAccountData(account);

        cout << "Deposit successful. New balance: " << account.balance << "\n";
    }
    else
    {
        cout << "Account not found.\n";
    }
}
void withdraw()
{
    long accountNumber;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    AccountInfo account;

    if (verification(account, accountNumber))
    {
        cout << "Enter Withdrawal Amount: ";
        cin >> amount;

        if (amount < account.balance)
        {
            account.balance -= amount;
            updateAccountData(account);
            cout << "\nWithdrawal successful. New balance: " << account.balance << "\n";
        }
        else
        {
            cout << "Insufficient funds.\n";
        }
    }
    else
    {
        cout << "Account not found.\n";
    }
}

void transfer()
{
    AccountInfo sender;
    AccountInfo reciever;

    long S_accountNumber,R_accountNumber;
    double amount;
    cout << "Enter your account number.\n";
    cin >> S_accountNumber;
    if(verification(sender, S_accountNumber))
    {
        cout << "Enter the recievers account number.\n";
        cin >> R_accountNumber;
        if(verification(reciever,R_accountNumber))
        {
            cout<<"Enter amount: ";
            cin >> amount;
            if (amount < sender.balance)
        {
            sender.balance -= amount;
            updateAccountData(sender);
            cout << "\nTransfered successful. New balance: " << sender.balance << "\n";
            reciever.balance += amount;
            updateAccountData(reciever);
        }
        else
        {
            cout << "Insufficient fund.\n";
            return;
        }
        }
        else
            cout<<"Recievers account number not found.\n";
    }
    else
        cout<< "Your account number not found.\n";


}

void displayAccountInfo()
{
    int accountNumber;
    cout << "Enter Account Number: ";
    cin >> accountNumber;
    AccountInfo account;

    if (verification(account, accountNumber))
    {
        displayAccountInfo(account);
    }
    else
    {
        cout << "Account not found.\n";
    }
}

void displayAccountInfo(AccountInfo &account)
{
    cout << "====== Account Information ======\n";
    cout << "Account Number: " << account.account_number << "\n";
    cout << "Account Holder: " << account.account_holder << "\n";
    cout << "Account Balance: " << account.balance << "\n";
    cout << "ATM PIN: " << account.pin << "\n";
}


//*************************************************************************************************
//                                      FUNCTIONS USED IN ATM SYSTEM
//*************************************************************************************************
void ATM_system(AccountInfo &account)
{
    int con = 0;
    do{
        int choice, pin;
        system("cls");
        cout << "---------Welcome to ATM system--------\n";
        cout << "\t1. Withdraw.\n";
        cout << "\t2. Check balance.\n";
        cout << "\t3. Change pin.\n";
        cout << "\t4. Exit.\n";
        cout << "\n\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case WITHDRAW_ATM:
            withdraw(pin);
            break;
        case CHECKBALANCE:
            checkBalance();
            break;
        case CHANGE_PIN:
            changePin();
            break;
        case EXIT3:
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }

            cout<<"If you want to continue press 1: ";
            cin >> con;

    }while(con == 1);

}

void withdraw(int &pin)
{
    long accountNumber;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accountNumber;


    AccountInfo account;


    if (verification(account,accountNumber))
    {
        cout << "Enter pin number: ";
        cin >> pin;
        if (account.pin == pin)
        {
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            if (amount < account.balance)
            {
                account.balance -= amount;
                updateAccountData(account);
                cout << "\nWithdrawal successful. New balance: " << account.balance << "\n";
            }
            else
            {
                cout << "Insufficient funds.\n";
            }
        }
        else
        {
            cout << "Incorrect pin number.\n";
        }
    }
    else
    {
        cout << "Account not found.\n";
    }
}
void changePin()
{
    int con = 0;
    long accountNumber;
    do {
    cout << "Enter your account number: ";
    cin >> accountNumber;
    AccountInfo account;
    int pin1;
    if(verification(account, accountNumber))
    {

    cout << "Enter your previous PIN: ";
    cin >> pin1;

    if (account.pin == pin1)
    {

        int newPin, newPin1;
        cout << "Enter new PIN: ";
        cin >> newPin;
        cout << "Confirm your PIN: ";
        cin >> newPin1;

        if (newPin1 == newPin)
        {
            // Update the PIN in memory
            account.pin = newPin;
            updateAccountData(account);
            cout << "PIN successfully changed." << endl;
        }
        else
        {
            cout << "Not confirmed correctly\n";
        }

    }
    else
    {
        cout << "Incorrect pin!" << endl;
    }
    }
    else
    {
        cout<<"Account not found!"<<endl;
    }
    cout<<"If you want to try again press 1: ";
    cin>>con;
    }while(con == 1);
}



//*************************************************************************************************
//                                      FUNCTIONS USED IN BOTH SYSTEMS
//*************************************************************************************************

void checkBalance()
{
    int accountNumber;
    cout << "Enter Account Number: ";
    cin >> accountNumber;
    AccountInfo account;

    if (verification(account, accountNumber))
    {
        cout << "Account Balance: " << account.balance << "\n";
    }
    else
    {
        cout << "Account not found.\n";
    }
}
void writeToFile(AccountInfo &account)
{
    ofstream outfile;
    outfile.open(ACCOUNTS_FILE_PATH, ios::binary | ios::app);

    if (outfile.is_open())
    {
        outfile.write(reinterpret_cast<char *>(&account), sizeof(AccountInfo));
        outfile.close();
    }
    else
    {
        cout << "Error opening file\n";
    }
}

bool verification(AccountInfo &account, int accountNumber)
// reads and verify the account number//
{
    ifstream infile;
    bool found =false;
    infile.open(ACCOUNTS_FILE_PATH, ios::binary | ios::in);

    if (!infile.is_open())
    {
        cout << "Error opening file for reading.\n";
        return found;
    }

    while (infile.read(reinterpret_cast<char *>(&account), sizeof(AccountInfo)))
    {
        if (account.account_number == accountNumber)
        {
            infile.close();
            found = true;
            return found;
        }
    }
    infile.close();
    return found;
}

void updateAccountData(AccountInfo &account)
{
    fstream file;
    file.open(ACCOUNTS_FILE_PATH, ios::binary | ios::in | ios::out);

    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    AccountInfo modify_Account;

    while (file.read(reinterpret_cast<char *>(&modify_Account), sizeof(AccountInfo)))
    {
        if (modify_Account.account_number == account.account_number)
        {
            break;
        }
    }

    file.seekp(file.tellg() - sizeof(AccountInfo)); // Move the put pointer to the position of the record
    file.write(reinterpret_cast<char *>(&account), sizeof(AccountInfo)); // Write the updated record

    file.close();
}
void delete_account()
{
    ifstream infile;
    ofstream outfile;
    outfile.open(TEMP_FILE_PATH, ios::binary | ios::out);
    infile.open(ACCOUNTS_FILE_PATH, ios::binary | ios::in);
    if (!outfile.is_open() || !infile.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    long accountNumber;
    AccountInfo account;
    cout << "Enter Account Number: ";
    cin >> accountNumber;

    if (verification(account, accountNumber))
    {
      AccountInfo tempAccount;

    while (infile.read(reinterpret_cast<char *>(&tempAccount), sizeof(AccountInfo)))
    {
        if (!(tempAccount.account_number == account.account_number))
        {
            outfile.write(reinterpret_cast<char *>(&tempAccount), sizeof(AccountInfo));
        }

    }
    infile.close();
    outfile.close();
    remove(ACCOUNTS_FILE_PATH.c_str());
    rename(TEMP_FILE_PATH.c_str(), ACCOUNTS_FILE_PATH.c_str());

    }
    else
    {
        cout<<"Account not found.\n";
    }

}
//*************************************************************************************************
//                       FUNCTIONS USED TO DISPLAY ALL ACCOUNT INFORMATION IN THE SYSTEMS
//*************************************************************************************************
void displayAllAccounts()
{
    system("cls");
    ifstream infile;
    infile.open(ACCOUNTS_FILE_PATH, ios::binary | ios::in);

    if (!infile.is_open())
    {
        cout << "Error opening file for reading.\n";
        return;
    }

    AccountInfo account;

    while (infile.read(reinterpret_cast<char *>(&account), sizeof(AccountInfo)))
    {
        displayAccountInfo(account);
    }
    infile.close();
}







//*************************************************************************************************
//                                      INTRODUCTION TO THE PROJECT
//*************************************************************************************************

void introduction()
{
    system("cls");
    cout << endl;
    cout<<"\n\t\t\t\t\tBANK MANAGEMENT AND ATM TRANSACTION SYSTEM\n";

    cout<<"\n\t\tMADE BY: \n";
    cout << "\t\t\t1. Bersabeh Degfu "
         << "\t"
         << "UGR/2049/15" << endl;
    cout << "\t\t\t2. Eden Ephrem"
         << "\t\t"
         << "UGR/6388/15" << endl;
    cout << "\t\t\t3. Hana Hilekiros"
         << "\t"
         << "UGR/5655/15" << endl;
    cout << "\t\t\t4. Hanan Abdulshikur"
         << "\t"
         << "UGR/6257/15" << endl;
    cout << "\t\t\t5. Hanan Fatih"
         << "\t\t"
         << "UGR/6009/15" << endl;
    cout << "ADDIS ABABA UNIVERSITY FACULTY OF NATURAL SCIENCES \n DEPARTMENT OF COMPUTER SCIENCE STUDENTS!!\n\n";
    cout << "\t---------------------------------------------------------------------------------------------\n\n" << endl;


}



//*************************************************************************************************
//                                      END OF THE PROJECT
//*************************************************************************************************
