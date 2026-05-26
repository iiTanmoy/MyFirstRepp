#include "menu.h"

#include <iostream>
#include <limits>
#include <string>

#include "storage.h"

namespace atm {

namespace {

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

long long readLongLong(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        try {
            long long value = std::stoll(input);
            return value;
        } catch (...) {
            std::cout << "Invalid number. Please try again.\n";
        }
    }
}

}  // namespace

void showWelcome() {
    std::cout << "==============================\n";
    std::cout << "   ATM WORKFLOW SIMULATOR     \n";
    std::cout << "==============================\n";
}

void showCommonMenu() {
    std::cout << "\nCommon User Menu\n";
    std::cout << "1. Check balance\n";
    std::cout << "2. Deposit\n";
    std::cout << "3. Withdraw\n";
    std::cout << "4. Transfer\n";
    std::cout << "5. Logout\n";
    std::cout << "Choose option: ";
}

void showAdminMenu() {
    std::cout << "\nAdmin Menu\n";
    std::cout << "1. View users\n";
    std::cout << "2. Create user\n";
    std::cout << "3. Logout\n";
    std::cout << "Choose option: ";
}

bool loginMenu(std::vector<User>& users, User& currentUser) {
    std::string username = readLine("Enter username: ");
    std::string password = readLine("Enter password: ");

    if (!authenticateUser(users, username, password, currentUser)) {
        std::cout << "Login failed. Invalid username or password.\n";
        return false;
    }

    std::cout << "Login successful. Welcome, " << currentUser.username << " (" << currentUser.role << ").\n";
    return true;
}

bool commonWorkflow(std::vector<User>& users, User& currentUser) {
    while (true) {
        showCommonMenu();

        int choice = 0;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::cout << "Current balance: " << currentUser.balance << "\n";
        } else if (choice == 2) {
            long long amount = readLongLong("Enter amount to deposit: ");
            if (depositMoney(users, currentUser.username, amount)) {
                currentUser.balance += amount;
                if (!saveUsers(users)) {
                    std::cout << "Warning: could not save transaction.\n";
                }
                std::cout << "Deposit successful.\n";
            } else {
                std::cout << "Deposit failed.\n";
            }
        } else if (choice == 3) {
            long long amount = readLongLong("Enter amount to withdraw: ");
            if (withdrawMoney(users, currentUser.username, amount)) {
                currentUser.balance -= amount;
                if (!saveUsers(users)) {
                    std::cout << "Warning: could not save transaction.\n";
                }
                std::cout << "Withdrawal successful.\n";
            } else {
                std::cout << "Withdrawal failed. Insufficient balance or invalid amount.\n";
            }
        } else if (choice == 4) {
            std::string receiver = readLine("Enter receiver username: ");
            long long amount = readLongLong("Enter amount to transfer: ");
            if (transferMoney(users, currentUser.username, receiver, amount)) {
                currentUser.balance -= amount;
                if (!saveUsers(users)) {
                    std::cout << "Warning: could not save transaction.\n";
                }
                std::cout << "Transfer successful.\n";
            } else {
                std::cout << "Transfer failed. Check recipient and balance.\n";
            }
        } else if (choice == 5) {
            return true;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}

bool adminWorkflow(std::vector<User>& users) {
    while (true) {
        showAdminMenu();

        int choice = 0;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::cout << "\nRegistered users:\n";
            for (const User& user : users) {
                std::cout << "- " << user.username << " | " << user.role << " | " << user.balance << "\n";
            }
        } else if (choice == 2) {
            std::string username = readLine("Enter username: ");
            std::string password = readLine("Enter password: ");
            std::string role = readLine("Enter role (common/admin): ");
            long long balance = readLongLong("Enter opening balance: ");

            if (createUser(users, username, password, role, balance)) {
                if (!saveUsers(users)) {
                    std::cout << "Warning: could not save new user.\n";
                }
                std::cout << "User created successfully.\n";
            } else {
                std::cout << "Unable to create user. Username exists or role invalid.\n";
            }
        } else if (choice == 3) {
            return true;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}

}  // namespace atm
