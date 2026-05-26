
#include <iostream>

int main() {
	long long n;
	if(!(std::cin >> n)) return 0;
	if (n % 2 == 0) std::cout << "Even\n";
	else std::cout << "Odd\n";
	return 0;
}
