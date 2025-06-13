#ifndef UI_H
#define UI_H
#include "../service/service.h"
#include "../exceptions/CustomExceptions.h"
#include <memory>
#include "../adoption/AdoptionListFactory.h"

class UI {
private:
    Service service;
    std::string fileType; // Added fileType as a member variable
    std::unique_ptr<AdoptionList> adoptionList;

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
    void printAdoptedDogs();
    void print_one_by_one();
    void print_adoption_list();

public:
    void run();
    UI(const Service& service) : service{service} {};
    int getValidatedIntegerInput(const std::string& prompt);
};

#endif // UI_H