#include <iostream>
#include <fstream>
#include "../ui/UI.h"
#include "../service/service.h"
#include "../unittest/unittest.h"
using namespace std;

int main() {
    runUnitTest();
        Service service;
        UI ui(service);
        ui.run();
    return 0;
}