#ifndef UI_H
#define UI_H
#include "../service/service.h"
#include "../repository/DynamicVector_01.h"

class UI {
private:
    Service service;

    void user_interface();
    void admin_interface();

protected:
    void menu_choice();
    void admin_menu();
    void user_menu();
    void printAllDogs();
    void addDog();
    void removeDog();
    void updateDog();
    void show_by_breed();
    void adoptDog(const Dog& d);
    void print_one_dog(const Dog& d);
    bool removing_dog(const Dog& d);
    //DynamicArray <Dog> getAdoptedDogs();

    void printAdoptedDogs();
    void print_one_by_one();
public:
    void run();
    UI(const Service& service) :service{service}{};
};

#endif //UI_H