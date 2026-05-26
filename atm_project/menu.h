#ifndef ATM_MENU_H
#define ATM_MENU_H

#include <vector>

#include "account.h"

namespace atm {

void showCommonMenu();
void showAdminMenu();
void showWelcome();

bool loginMenu(std::vector<User>& users, User& currentUser);
bool commonWorkflow(std::vector<User>& users, User& currentUser);
bool adminWorkflow(std::vector<User>& users);

}  // namespace atm

#endif
