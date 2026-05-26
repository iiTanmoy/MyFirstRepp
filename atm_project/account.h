#ifndef ATM_ACCOUNT_H
#define ATM_ACCOUNT_H

#include <string>
#include <vector>

namespace atm {

struct User {
    std::string username;
    std::string password;
    std::string role;
    long long balance;
};

bool authenticateUser(const std::vector<User>& users, const std::string& username,
                      const std::string& password, User& currentUser);

int findUserIndex(const std::vector<User>& users, const std::string& username);

bool depositMoney(std::vector<User>& users, const std::string& username, long long amount);
bool withdrawMoney(std::vector<User>& users, const std::string& username, long long amount);
bool transferMoney(std::vector<User>& users, const std::string& fromUser,
                   const std::string& toUser, long long amount);
bool createUser(std::vector<User>& users, const std::string& username,
                const std::string& password, const std::string& role, long long balance);

}  // namespace atm

#endif
