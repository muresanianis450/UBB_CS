#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
	testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;

    std::cout<<"TEST TRIM VALUES"<<std::endl;
    testTrimValues();
    std::cout<<"Finished SMM TRIM VALUES Tests!"<<std::endl;
	system("pause");
}
