#include "UI.h"
#include "../service/Service.h"
#include "../adoption/AdoptionListFactory.h"

using namespace std;

int main() {
        Service service;
        UI ui(service);
        ui.run();
    return 0;
}