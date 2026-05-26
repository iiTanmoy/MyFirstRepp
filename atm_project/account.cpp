#include "account.h"

#include <algorithm>

namespace atm {

bool authenticateUser(const std::vector<User>& users, const std::string& username,
                      const std::string& password, User& currentUser) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            currentUser = user;
            return true;
        }
    }
    return false;
}

int findUserIndex(const std::vector<User>& users, const std::string& username) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].username == username) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool depositMoney(std::vector<User>& users, const std::string& username, long long amount) {
    if (amount <= 0) {
        return false;
    }

    int index = findUserIndex(users, username);
    if (index == -1) {
        return false;
    }

    users[index].balance += amount;
    return true;
}

bool withdrawMoney(std::vector<User>& users, const std::string& username, long long amount) {
    if (amount <= 0) {
        return false;
    }

    int index = findUserIndex(users, username);
    if (index == -1) {
        return false;
    }

    if (users[index].balance < amount) {
        return false;
    }

    users[index].balance -= amount;
    return true;
}

bool transferMoney(std::vector<User>& users, const std::string& fromUser,
                   const std::string& toUser, long long amount) {
    if (amount <= 0) {
        return false;
    }

    int fromIndex = findUserIndex(users, fromUser);
    int toIndex = findUserIndex(users, toUser);

    if (fromIndex == -1 || toIndex == -1 || fromIndex == toIndex) {
        return false;
    }

    if (users[fromIndex].balance < amount) {
        return false;
    }

    users[fromIndex].balance -= amount;
    users[toIndex].balance += amount;
    return true;
}

bool createUser(std::vector<User>& users, const std::string& username,
                const std::string& password, const std::string& role, long long balance) {
    if (username.empty() || password.empty()) {
        return false;
    }

    if (findUserIndex(users, username) != -1) {
        return false;
    }

    if (role != "common" && role != "admin") {
        return false;
    }

    User newUser;
    newUser.username = username;
    newUser.password = password;
    newUser.role = role;
    newUser.balance = balance;

    users.push_back(newUser);
    return true;
}

}  // namespace atm
