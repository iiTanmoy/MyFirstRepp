#ifndef ATM_STORAGE_H
#define ATM_STORAGE_H

#include <string>
#include <vector>

#include "account.h"

namespace atm {

const std::string DEFAULT_DATA_PATH = "data/users.txt";

bool ensureDataFile();
bool loadUsers(std::vector<User>& users, const std::string& filePath = DEFAULT_DATA_PATH);
bool saveUsers(const std::vector<User>& users, const std::string& filePath = DEFAULT_DATA_PATH);

}  // namespace atm

#endif
