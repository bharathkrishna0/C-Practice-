#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class BankAccount {
public:    
    int balance;
    int accountNumber;
    std::string accountHolderName;
    
    // Constructor
    BankAccount(int accNum = 0, std::string name = "", int bal = 0) 
        : accountNumber(accNum), accountHolderName(name), balance(bal) {}
        
    void Deposit_money() {
        int depo = 0;
        std::cout << "Enter deposit: ";
        std::cin >> depo;
        if (depo > 0) {
            balance += depo;
            std::cout << "Deposited successfully! New b " << balance << std::endl;
        } else {
            std::cout << "Invalid " << std::endl;
        }
    }
    
    void withdraw() {  
        if (balance > 0) {
            int money;
            std::cout << "Enter money: ";
            std::cin >> money;
            if (money > 0 && money <= balance) {
                balance -= money;
                std::cout << "Withdrawal success! New balance: " << balance << std::endl;
            } else if (money > balance) {
                std::cout << "Insufficient bal" << std::endl;
            } else {
                std::cout << "Invalid withdrawal amount!" << std::endl;
            }
        } else {
            std::cout << "No balanc" << std::endl;
        }
    }
    
    void accdet() {
        std::cout << "Account Number " << accountNumber << std::endl;
        std::cout << "Account Holder " << accountHolderName << std::endl;
        std::cout << "Balance " << balance << std::endl;
    }
}; 

std::vector<BankAccount> accounts;

void addBankAccount(int accountNumber, std::string accountHolderName, int balance) {
    BankAccount account(accountNumber, accountHolderName, balance);  
    accounts.push_back(account);
}

void sortAccounts() {
    std::sort(accounts.begin(), accounts.end(), [](const BankAccount& a, const BankAccount& b) {
        return a.balance < b.balance;
    });
}

void displayDetails() {
    if (accounts.empty()) {
        std::cout << "No accounts" << std::endl;
        return;
    }
    
    for (const auto& account : accounts) {
        std::cout << "Account Numr: " << account.accountNumber 
                  << ", Name " << account.accountHolderName 
                  << ", Balance " << account.balance << std::endl;
    }
}

void searchAccount() {
    int searchAccountNumber;
    std::cout << "Enter account number  ";
    std::cin >> searchAccountNumber;
    
    auto it = std::find_if(accounts.begin(), accounts.end(), 
                          [searchAccountNumber](const BankAccount& account) {
                              return account.accountNumber == searchAccountNumber;
                          });
    
    if (it != accounts.end()) {
        std::cout << "Account foun" << std::endl;
        it->accdet();
    } else {
        std::cout << "Account not foun" << std::endl;
    }
}

int main() {
    int choice;
    
    while (true) {
        std::cout << "\n--- Bank Account Management System ---" << std::endl;
        std::cout << "1. Add Bank Account" << std::endl;
        std::cout << "2. Display All Accounts" << std::endl;
        std::cout << "3. Sort Accounts by Balance" << std::endl;
        std::cout << "4. Search Account" << std::endl;
        std::cout << "5. Deposit Money" << std::endl;
        std::cout << "6. Withdraw Money" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                // Add multiple accounts
                char addMore = 'y';
                while (addMore == 'y' || addMore == 'Y') {
                    int accNum, balance;
                    std::string name;
                    
                    std::cout << "\nEnter account number: ";
                    std::cin >> accNum;
                    
                    std::cout << "Enter account holder name: ";
                    std::cin.ignore(); // Clear the input buffer
                    std::getline(std::cin, name);
                    
                    std::cout << "Enter initial balance: ";
                    std::cin >> balance;
                    
                    addBankAccount(accNum, name, balance);
                    
                    std::cout << "Do you want to add another account? (y/n): ";
                    std::cin >> addMore;
                }
                break;
            }
            case 2:
                std::cout << "\n--- All Bank Accounts ---" << std::endl;
                displayDetails();
                break;
                
            case 3:
                sortAccounts();
                std::cout << "\n--- Accounts Sorted by Balance ---" << std::endl;
                displayDetails();
                break;
                
            case 4:
                searchAccount();
                break;
                
            case 5: {
                int accNum;
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                auto it = std::find_if(accounts.begin(), accounts.end(), [accNum](const BankAccount& account) {
                    return account.accountNumber == accNum;
                });
                if (it != accounts.end()) {
                    it->Deposit_money();
                } else {
                    std::cout << "Account not found" << std::endl;
                }
                break;
            }
            case 6: {
                int accNum;
                std::cout << "Enter account num for withdrawa: ";
                std::cin >> accNum;
                
                auto it = std::find_if(accounts.begin(), accounts.end(), 
                                      [accNum](const BankAccount& account) {
                                          return account.accountNumber == accNum;
                                      });
                
                if (it != accounts.end()) {
                    it->withdraw();
                } else {
                    std::cout << "Account not foun!" << std::endl;
                }
                break;
            }
            
            case 7:
                std::cout << "Thank you for using Bank Account Management System!" << std::endl;
                return 0;
                
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }
    
    return 0;
}
