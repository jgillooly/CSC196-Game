#include <iostream>

int main() {
#ifdef _DEBUG
	std::cout << "DEBUG!" << std::endl;
#endif
	std::cout << "Hello World!" << std::endl;
}