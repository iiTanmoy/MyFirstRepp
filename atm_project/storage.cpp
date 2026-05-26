#include "storage.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>

namespace atm {

namespace {

bool directoryExists(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

void createDefaultUsersFile() {
    std::ofstream out(DEFAULT_DATA_PATH);
    if (!out) {
        return;
    }

    out << "admin|admin123|admin|100000\n";
    out << "john|john123|common|5000\n";
    out << "sara|sara123|common|7000\n";
}

}  // namespace

bool ensureDataFile() {
    const std::string dataDir = "data";

    if (!directoryExists(dataDir)) {
        std::filesystem::create_directories(dataDir);
    }

    std::ifstream existing(DEFAULT_DATA_PATH);
    if (!existing.good()) {
        createDefaultUsersFile();
    }
    return true;
}

bool loadUsers(std::vector<User>& users, const std::string& filePath) {
    users.clear();

    std::ifstream in(filePath);
    if (!in.good()) {
        return false;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string username, password, role, balanceText;

        std::getline(ss, username, '|');
        std::getline(ss, password, '|');
        std::getline(ss, role, '|');
        std::getline(ss, balanceText, '|');

        if (username.empty() || password.empty() || role.empty() || balanceText.empty()) {
            continue;
        }

        User user;
        user.username = username;
        user.password = password;
        user.role = role;
        user.balance = std::stoll(balanceText);
        users.push_back(user);
    }

    return true;
}

bool saveUsers(const std::vector<User>& users, const std::string& filePath) {
    std::ofstream out(filePath);
    if (!out) {
        return false;
    }

    for (const User& user : users) {
        out << user.username << "|" << user.password << "|" << user.role << "|" << user.balance << "\n";
    }

    return true;
}

}  // namespace atm
