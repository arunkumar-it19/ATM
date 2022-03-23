#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class ATM {
  //private variable for ATM Machine
  long long int balance;
  long long int two_thousand;
  long long int five_hundered;
  long long int hundered;
  int admin_pin;

  public:
    //constructor to initialize values to variables
    ATM() {
      balance = 0;
      two_thousand = 2000;
      five_hundered = 500;
      hundered = 100;
    }
  //welcome function declaration to navigate or welcome user
  void welcomeboard();
  //checkadmin function declaration to check whether admin or not(admin pass=1234)
  void checkadmin();
  //loaddash function declaration to load cash in ATM
  void loadcash();
  //display_customers function declaration to display customers in txt file;
  void display_customers();
  //userdisplay function declaration to display user options
  void userdislay();
  int useroption();
  //usertransfer function declaration to transfer to another account
  void usertransfer(string s,int trans);
};

// Member functions definitions
void ATM::welcomeboard() {
  cout << "Welcome to Arun's Banking System" << endl;
  cout << "1.Admin\n2.User\n3.Exit\n";
  int input_user;
  cin >> input_user;
  ATM atm;
  switch (input_user) {
  case 1:
    checkadmin();
    break;
  case 2:
      userdislay();
    break;
  case 3:
    break;

  }
}

void ATM::checkadmin() {
  cout << "Enter Admin Pin:";
  cin >> admin_pin;
  if (admin_pin == 1234) {
    cout << endl << "Welcome Admin!" << endl;
    cout << "1.FEED CASH\n2.GET CUSTOMER DETAILS\n3.EXIT\n";
    int num;
    cin >> num;
    switch (num) {
    case 1:
      loadcash();
      break;
    case 2:
      display_customers();
      break;
    case 3:
      welcomeboard();
    }
  } else {
    cout << endl << "Your Admin Pin is Wrong Buddy!" << endl << endl;
    welcomeboard();
  }
}

void ATM::loadcash() {
  cout << "Feed Cash is here" << endl;
  int twos = 0;
  int fives = 0;
  int hunes = 0;
  cout << "How Many 2000's note : ";
  cin >> twos;
  cout << "How Many 500's note : ";
  cin >> fives;
  cout << "How Many 100's note : ";
  cin >> hunes;
  ofstream totalmoney("ATM_CASH.txt", ios::app);
  totalmoney << "Denomination " << two_thousand << "\n" << "Numbers " << twos << "\n" << "Value " << two_thousand * twos << "\n";
  totalmoney << "Denomination " << five_hundered << "\n" << "Numbers " << fives << "\n" << "Value " << five_hundered * fives << "\n";
  totalmoney << "Denomination " << hundered << "\n" << "Numbers " << hunes << "\n" << "Value " << hundered * hunes << "\n\n\n";
  balance = two_thousand * twos + five_hundered * fives + hundered * hunes;
  totalmoney << "Total Amount in ATM " << balance;
  cout << balance << " IS FEEDED :-)"<<endl;
  totalmoney.close();
  welcomeboard();
}

void ATM::display_customers() {
  string display;
  ifstream readcustomers("Account_Details.txt");
  if(readcustomers.is_open())
  {
      while (getline(readcustomers, display)) {

    cout << display << endl;
  }
  }
  else{
    cout<<"Unable to open file"<<endl;
  }
  readcustomers.close();
  cout << endl << endl;
  cout << "1.FEED CASH\n2.GET CUSTOMER DETAILS\n3.EXIT\n";
  int num;
  cin >> num;
  switch (num) {
  case 1:
    loadcash();
    break;
  case 2:
    display_customers();
    break;
  case 3:
    welcomeboard();
  }
}

void ATM::userdislay()
{
    string username,uname;
    string pass,upass;
    cout<<"Enter username : ";
    cin>>username;
    cout<<"Enter Password : ";
    cin>>pass;
    ifstream readcustomers("Account_Details.txt");
    int check_user=1;
    int loop=0;
    string line;
    int total_user_amount;
    string arr[1000];
    int i;
    if(readcustomers.is_open())
    {
        while (!readcustomers.eof())
    {
            getline(readcustomers,line);
            arr[loop]=line;
            loop++;
    }
    for(i=0;i<1000;i++)
    {
        if(arr[i]==username && arr[i+1]==pass)
        {
            check_user=0;

            break;
        }

    }
    if(!check_user)
    {
    cout << "1.CHECK BALANCE\n2.WITHDRAW AMOUNT\n3.TRANSFER MONEY\n4.EXIT\n";
    int num;
    cin >> num;
    switch (num) {
    case 1:
    cout<<"Balance Amount: "<<arr[i+2]<<endl;;
    break;
    case 2:
    {
        int withdraw;
    total_user_amount=stoi(arr[i+2]);
    cout<<"Withdraw amount :";
    cin>>withdraw;

    if(withdraw<=total_user_amount && withdraw<=balance)
    {
       cout<<"Cash Withdraw Success!"<<endl;
       cout<<"Current Balance: "<<total_user_amount-withdraw<<endl;
       cout<<"Thank You!";

    }
    else if(withdraw<=balance)
    {
        cout<<"Insufficent Balance"<<endl;
    }
    else
    {
        cout<<"ATM does not have enough money to vend"<<endl;
    }

    }
    break;
    case 3:
        string username;
        cin>>username;
        cout<<"Transfer Amount :";
        int transfer;
        cin>>transfer;
        if(transfer<=total_user_amount)
        {
            cout<<total_user_amount;
        }
        usertransfer(username,transfer);
        break;

  }
    }
    if(check_user)
    {
    cout<<"Incorrect Credatils"<<endl;
    welcomeboard();
    }
    }
    else
    {
        cout<<"Unable to open file"<<endl;
    }

}

void ATM::usertransfer(string user,int amount)
{
    //string username;
    ifstream readcustomers("Account_Details.txt");
    int check_user=1;
    int loop=0;
    string line;
    string arr[1000];
    int i;
    if(readcustomers.is_open())
    {
        while (!readcustomers.eof())
    {
            getline(readcustomers,line);
            arr[loop]=line;
            cout<<arr[i];
            loop++;
    }
    for(i=0;i<1000;i++)
    {
        if(arr[i]==user)
        {
            check_user=0;
            break;
        }

    }
    arr[i+2]+=amount;
    cout<<"Transfered SuccesFull"<<endl;

}}

int main() {
  ATM atm;
  atm.welcomeboard();
  return 0;
}
