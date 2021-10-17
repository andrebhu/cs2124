/*
  Andre Hu
  2/19/2021
  Code for managing bank accounts
*/

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account_s{
  string name;
  int balance;
};


// Task 2
// Define an Account class
class Account_c{
  friend ostream& operator<<(ostream&os, const Account_c& acc);

  public:
    Account_c(const string& n, int b) : name(n), balance(b) {};

    const string& getName() const {
      return name;
    }
    int getBalance() const {
      return balance;
    }

  private:
    string name;
    int balance;
};

ostream& operator<<(ostream& os, const Account_c& acc){
  //os << acc.getName() << " " << acc.getBalance() << endl;
  os << acc.name << " " << acc.balance;
  return os;
}


// Task 3
// Define an Account and Transaction classes
class Transaction{
  friend ostream& operator<<(ostream& os, const Transaction& t);

  public:
    Transaction(const string& a, int am) : action(a), amount(am) {};
  private:
    string action;
    int amount;
};

ostream& operator<<(ostream& os, const Transaction& t){
  os << t.action << " " << t.amount;
  return os;
}

class Account_t3{
  friend ostream& operator<<(ostream& os, const Account_t3& acc);

  public:
    Account_t3(const string& name, const int& id) : name(name), id(id), balance(0) {};

    int getID() const{
      return id;
    }

    void deposit(const int& amount){
      balance += amount;
      history.emplace_back(Transaction("deposit", amount));
    }
    void withdrawal(const int& amount){
      if (amount > balance){
        cout << "Account# " << id << " has only " << balance << ". ";
        cout << "Insufficient for withdrawal of " << amount << "." << endl;
      }
      else{
        balance -= amount;
        history.emplace_back(Transaction("withdrawal", amount));
      }      
    }
  private:
    string name;
    int id;
    int balance;
    vector<Transaction> history;
};

ostream& operator<<(ostream& os, const Account_t3& acc){
  cout << acc.name << "\t" << acc.id << ":" << endl;
  for(size_t i = 0; i < acc.history.size(); ++i){
    cout << "\t" << acc.history[i] << endl;
  }
  return os;
}



// Task 4
// Define an Account with a nested public Transaction class

class Account_t4{
  friend ostream& operator<<(ostream& os, const Account_t4& acc);

  public:
    class Transaction_t4{
      public:
        Transaction_t4(const string& a, int am) : action(a), amount(am) {};
        friend ostream& operator<<(ostream& os, const Transaction_t4& t);

      private:
        string action;
        int amount;
    };

    Account_t4(const string& name, const int& id) : name(name), id(id), balance(0) {};

    int getID() const{
        return id;
      }

    void deposit(const int& amount){
      balance += amount;
      history.emplace_back(Transaction_t4("deposit", amount));
    }
    void withdrawal(const int& amount){
      if (amount > balance){
        cout << "Account# " << id << " has only " << balance << ". ";
        cout << "Insufficient for withdrawal of " << amount << "." << endl;
      }
      else{
        balance -= amount;
        history.emplace_back(Transaction_t4("withdrawal", amount));
      }      
    }
  private:
    string name;
    int id;
    int balance;
    vector<Transaction_t4> history;
};

ostream& operator<<(ostream& os, const Account_t4::Transaction_t4& t){
  os << t.action << " " << t.amount;
  return os;
}

ostream& operator<<(ostream& os, const Account_t4& acc){
  cout << acc.name << "\t" << acc.id << ":" << endl;
  for(size_t i = 0; i < acc.history.size(); ++i){
    cout << "\t" << acc.history[i] << endl;
  }
  return os;
}


// Task 5
// Define an Account with a nested private Transaction class

class Account_t5{
  friend ostream& operator<<(ostream& os, const Account_t5& acc);

  public:
    Account_t5(const string& name, const int& id) : name(name), id(id), balance(0) {};

    int getID() const{
      return id;
    }

    void deposit(const int& amount){
      balance += amount;
      history.emplace_back(Transaction_t5("deposit", amount));
    }
    void withdrawal(const int& amount){
      if (amount > balance){
        cout << "Account# " << id << " has only " << balance << ". ";
        cout << "Insufficient for withdrawal of " << amount << "." << endl;
      }
      else{
        balance -= amount;
        history.emplace_back(Transaction_t5("withdrawal", amount));
      }      
    }
    

  private:
    class Transaction_t5{
      public:
        Transaction_t5(const string& a, int am) : action(a), amount(am) {};
        friend ostream& operator<<(ostream& os, const Transaction_t5& t){
          os << t.action << " " << t.amount;
          return os;
        };

      private:
        string action;
        int amount;
    };

  string name;
  int id;
  int balance;
  vector<Transaction_t5> history;
};

ostream& operator<<(ostream& os, const Account_t5& acc){
  cout << acc.name << "\t" << acc.id << ":" << endl;
  for(size_t i = 0; i < acc.history.size(); ++i){
    cout << "\t" << acc.history[i] << endl;
  }
  return os;
}














 int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream file("accounts.txt");
    vector<Account_s> accounts_s;
    string name;
    int bal;
    while(file >> name >> bal){
      Account_s acc;
      acc.name = name;
      acc.balance = bal;
      accounts_s.push_back(acc);
    }
    file.close();

    //Display accounts_s
    for(size_t i = 0; i < accounts_s.size(); ++i){
      cout << accounts_s[i].name << " " << accounts_s[i].balance << endl;
    }

    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    accounts_s.clear();

    file.open("accounts.txt");
    while(file >> name >> bal){
      Account_s acc{name, bal};
      accounts_s.push_back(acc);
    }
    file.close();

    //Display accounts_s
    for(size_t i = 0; i < accounts_s.size(); ++i){
      cout << accounts_s[i].name << " " << accounts_s[i].balance << endl;
    }

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";
    vector<Account_c> accounts_c;
    file.open("accounts.txt");
    while(file >> name >> bal){
      Account_c acc(name, bal);
      accounts_c.push_back(acc);
    }
    file.close();

    //Display accounts_c
    for(size_t i = 0; i < accounts_c.size(); ++i){
      cout << accounts_c[i].getName() << " " << accounts_c[i].getBalance() << endl;
    }


    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    for(size_t i = 0; i < accounts_c.size(); ++i){
      cout << accounts_c[i] << endl;
    }
    

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    for(size_t i = 0; i < accounts_c.size(); ++i){
      cout << accounts_c[i] << endl;
    }


    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";    
    accounts_c.clear();
    file.open("accounts.txt");
    while(file >> name >> bal){
      accounts_c.push_back(Account_c(name, bal));
    }
    file.close();
    for(size_t i = 0; i < accounts_c.size(); ++i){
      cout << accounts_c[i] << endl;
    }

    
    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    accounts_c.clear();
    file.open("accounts.txt");
    while(file >> name >> bal){
      accounts_c.emplace_back(Account_c(name, bal));
    }
    file.close();

    for(size_t i = 0; i < accounts_c.size(); ++i){
      cout << accounts_c[i] << endl;
    }
    
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";
    file.open("transactions.txt");
    vector<Account_t3> accounts_t3;

    int id;
    string action;
    int amount;

    while(file >> action){
      if (action == "Account"){
        file >> name >> id;
        accounts_t3.emplace_back(Account_t3(name, id));
      }
      else if (action == "Deposit"){
        file >> id >> amount;
        for(size_t i = 0; i < accounts_t3.size(); ++i){
          if (accounts_t3[i].getID() == id){
            accounts_t3[i].deposit(amount);
          }
        }
      }
      else if (action == "Withdraw"){
        file >> id >> amount;
        for(size_t i = 0; i < accounts_t3.size(); ++i){
          if (accounts_t3[i].getID() == id){
            accounts_t3[i].withdrawal(amount);
          }
        }
      }
    }
    file.close();

    for(size_t i = 0; i < accounts_t3.size(); ++i){
      cout << accounts_t3[i] << endl;
    }

    
    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";
    file.open("transactions.txt");
    vector<Account_t4> accounts_t4;

    while(file >> action){
      if (action == "Account"){
        file >> name >> id;
        accounts_t4.emplace_back(Account_t4(name, id));
      }
      else if (action == "Deposit"){
        file >> id >> amount;
        for(size_t i = 0; i < accounts_t4.size(); ++i){
          if (accounts_t4[i].getID() == id){
            accounts_t4[i].deposit(amount);
          }
        }
      }
      else if (action == "Withdraw"){
        file >> id >> amount;
        for(size_t i = 0; i < accounts_t4.size(); ++i){
          if (accounts_t4[i].getID() == id){
            accounts_t4[i].withdrawal(amount);
          }
        }
      }
    }
    file.close();

    for(size_t i = 0; i < accounts_t4.size(); ++i){
      cout << accounts_t4[i] << endl;
    }

    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";
    file.open("transactions.txt");
    vector<Account_t5> accounts_t5;

    while(file >> action){
      if (action == "Account"){
        file >> name >> id;
        accounts_t5.emplace_back(Account_t5(name, id));
      }
      else if (action == "Deposit"){
        file >> id >> amount;
        for(size_t i = 0; i < accounts_t5.size(); ++i){
          if (accounts_t5[i].getID() == id){
            accounts_t5[i].deposit(amount);
          }
        }
      }
      else if (action == "Withdraw"){
        file >> id >> amount;
        for(size_t i = 0; i < accounts_t5.size(); ++i){
          if (accounts_t5[i].getID() == id){
            accounts_t5[i].withdrawal(amount);
          }
        }
      }
    }
    file.close();

    for(size_t i = 0; i < accounts_t5.size(); ++i){
      cout << accounts_t5[i] << endl;
    }


    return 0;
}
