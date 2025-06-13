#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
	testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;
    testJumpBackward();
    std::cout<<"\nFinished SMM Iterator Tests!"<<std::endl;
    std::cout<<"\nTesting trimValues..."<<std::endl;
    testTrimValues();
    std::cout<<"\nFinished trimValues Tests!"<<std::endl;
    system("pause");


}
