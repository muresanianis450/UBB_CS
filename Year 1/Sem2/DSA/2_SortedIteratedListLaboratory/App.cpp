#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main() {
	std::cout << "Starting testAll..." << std::endl;
	testAll();
	std::cout << "Finished testAll." << std::endl;

	std::cout << "Starting testAllExtended..." << std::endl;
	testAllExtended();
	std::cout << "Finished testAllExtended." << std::endl;

	std::cout << "Starting testJumpBackward..." << std::endl;
	testJumpBackward();
	std::cout << "Finished testJumpBackward." << std::endl;

	std::cout << "Finished IL Tests!" << std::endl;
	system("pause");
	return 0;
}