#include <iostream>
#include <vector>

#include "menu.h"
#include "storage.h"

int main() {
    using namespace atm;

    std::vector<User> users;

    if (!ensureDataFile()) {
        std::cout << "Failed to initialize storage.\n";
        return 1;
    }

    if (!loadUsers(users)) {
        std::cout << "Failed to load user data.\n";
        return 1;
    }

    showWelcome();

    while (true) {
        User currentUser;

        if (!loginMenu(users, currentUser)) {
            continue;
        }

        if (currentUser.role == "admin") {
            if (!adminWorkflow(users)) {
                std::cout << "Admin session ended unexpectedly.\n";
            }
        } else {
            if (!commonWorkflow(users, currentUser)) {
                std::cout << "Common session ended unexpectedly.\n";
            }
        }

        std::cout << "\nReturning to login screen...\n";
    }

    return 0;
}
