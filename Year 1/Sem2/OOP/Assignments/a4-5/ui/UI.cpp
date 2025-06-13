#include "UI.h"
#include <limits>

void UI::menu_choice() {
    std::cout << "1.Admin mode\n";
    std::cout << "2.User mode\n";
    std::cout << "3.Exit\n";
    std::cout << "Your choice: ";
}

void UI::admin_menu() {
    std::cout << "----------------------------------------\n";
    std::cout << "Admin mode\n";
    std::cout << "1.Add dog\n";
    std::cout << "2.Remove dog\n";
    std::cout << "3.Update dog\n";
    std::cout << "4.Print all dogs\n";
    std::cout << "Your choice: ";
}

void UI::user_menu() {
    std::cout <<"--------------------------------------------\n";
    std::cout << "User mode\n";
    std::cout << "1.Show dogs one by one\n";
    std::cout << "2.Show all dogs by breed\n";
    std::cout << "3.Print adopted dogs\n";
}

void UI::show_by_breed() {
    std::string breed;
    std::cout << "Enter the breed of the dog: ";
    std::getline(std::cin, breed);

    DynamicArray<Dog> v = this->service.getDogsByBreed(breed);

    if (v.getLength() == 0) {
        std::cout << "No dogs found for the breed: " << breed << "\n";
        return;
    }

    for (int i = 0; i < v.getLength(); i++) {
        Dog &d = v[i];
        std::cout << d.getName() << " " << d.getBreed() << " " << d.getAge() << " " << d.getPhotography() << "\n";
    }
}
void UI::adoptDog(const Dog& d) {
    if (this->service.invalidDog(d)) {
        std::cout << "No dog with this information exists\n";
        return;
    }

    this->service.adoptDog(d); // Add the dog to the adopted list
    if (this->removing_dog(d)) {
        std::cout << "Dog adopted ☹️\n";
    } else {
        std::cout << "Failed to remove the dog from the repository\n";
    }
}
void UI::printAdoptedDogs() {
    std::cout << "Adopted dogs:\n";

    for (const Dog& d : this->service.getAdoptedDogs()) {
    this->print_one_dog(d);
    }
}

bool UI::removing_dog(const Dog& d) {
    return this->service.removeDog(d);
}

void UI::print_one_dog(const Dog& d) {
    std::cout << "Name: " << d.getName() << "\n";
    std::cout << "Breed: " << d.getBreed() << "\n";
    std::cout << "Age: " << d.getAge() << "\n";
    std::cout << "Photography: " << d.getPhotography() << "\n";

    // Open the photography link in the default browser
    //std::string command = "start msedge \"" + d.getPhotography() + "\"";
    //system(command.c_str());
}
void UI::print_one_by_one() {
    bool exit = false;
    int i = 0;
    DynamicArray<Dog>& allDogs = this->service.getAllDogs();

    while (i < allDogs.getLength() && !exit) {
        Dog &d = allDogs[i];
        this->print_one_dog(d);
        std::cout << "Press 'A' to adopt this dog or 'N' to see the next one or 'E' to exit: ";

        bool validChoiceMade = false;
        while (!validChoiceMade) {
            std::string choice;
            std::getline(std::cin, choice);
            if (choice == "A") {
                // When adopting, we call adoptDog which will remove the dog.
                this->adoptDog(d);
                // Move to the next dog.
                // the next dog slides into position i.
                validChoiceMade = true;
                // Note: If the dog was the last element,
                // i will remain equal to getLength() so the loop exits.
            } else if (choice == "N") {
                i++; // Move to the next dog.
                validChoiceMade = true;
            } else if (choice == "E") {
                exit = true;
                validChoiceMade = true;
            } else {
                std::cout << "Invalid choice. Please try again: ";
            }
        }

        // When we reach the end, ask if the user wants to start over.
        if (!exit && i >= allDogs.getLength()) {
            std::cout << "No more dogs available.\nDo you want to continue? y/n: ";
            std::string continueChoice;
            std::getline(std::cin, continueChoice);
            if (continueChoice == "y") {
                i = 0; // Restart at the beginning.
            } else {
                exit = true;
            }
        }
    }
}

void UI::addDog() {
    std::string name, breed, photography, ageStr;
    int age;

    std::cout << "Enter the name of the dog: ";
    std::getline(std::cin, name);

    std::cout << "Enter the breed of the dog: ";
    std::getline(std::cin, breed);

    std::cout << "Enter the age of the dog: ";
    while (true) {
        std::getline(std::cin, ageStr);
        try {
            age = std::stoi(ageStr);
            break;
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid age: ";
        }
    }

    std::cout << "Enter the link to the photography: ";
    std::getline(std::cin, photography);

    Dog d{name, breed, age, photography};
    this->service.addDog(d);
}

void UI::removeDog() {
    std::string name, breed, photography, ageStr;
    int age;

    std::cout << "Enter the name of the dog: ";
    std::getline(std::cin, name);

    std::cout << "Enter the breed of the dog: ";
    std::getline(std::cin, breed);

    std::cout << "Enter the age of the dog: ";
    while (true) {
        std::getline(std::cin, ageStr);
        try {
            age = std::stoi(ageStr);
            break;
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid age: ";
        }
    }

    std::cout << "Enter the link to the photography: ";
    std::getline(std::cin, photography);

    Dog d{name, breed, age, photography};
    if (this->removing_dog(Dog(name, breed, age, photography)))
        std::cout << "Removing dog(adopted)... YIPPIE😃😃😃😃😃\n";
    else
        std::cout << "No dog with this information exists\n";
}

void UI::updateDog() {
    std::string name, breed, photography, ageStr;
    int age;

    std::cout << "-------OLD DOG INFO-------\n";
    std::cout << "Enter the name of the dog: ";
    std::getline(std::cin, name);

    std::cout << "Enter the breed of the dog: ";
    std::getline(std::cin, breed);

    std::cout << "Enter the age of the dog: ";
    while (true) {
        std::getline(std::cin, ageStr);
        try {
            age = std::stoi(ageStr);
            break;
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid age: ";
        }
    }

    std::cout << "Enter the link to the photography: ";
    std::getline(std::cin, photography);

    Dog d{name, breed, age, photography};

    std::cout << "-------NEW DOG INFO-------\n";
    std::string name2, breed2, photography2, ageStr2;
    int age2;

    std::cout << "Enter the name of the dog: ";
    std::getline(std::cin, name2);

    std::cout << "Enter the breed of the dog: ";
    std::getline(std::cin, breed2);

    std::cout << "Enter the age of the dog: ";
    while (true) {
        std::getline(std::cin, ageStr2);
        try {
            age2 = std::stoi(ageStr2);
            break;
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid age: ";
        }
    }

    std::cout << "Enter the link to the photography: ";
    std::getline(std::cin, photography2);

    Dog d2{name2, breed2, age2, photography2};

    if (this->service.updateDog(d, d2))
        std::cout << "Updating dog... \n";
    else
        std::cout << "No dog with this information exists\n";
}

void UI::printAllDogs() {
    DynamicArray<Dog> &v = this->service.getAllDogs();
    for (int i = 0; i < v.getLength(); i++) {
        Dog &d = v[i];
        this->print_one_dog(d);
    }
}

void UI::run() {
    std::string choiceStr;
    int choice;

    this->menu_choice();
    while (true) {
        std::getline(std::cin, choiceStr);
        try {
            choice = std::stoi(choiceStr);
            break;
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid number: ";
        }
    }

    if (choice == 3)
        std::cout << "Exiting...", exit(0);
    else if (choice == 2)
        std::cout << "Entering user mode...", user_interface();
    else if (choice == 1)
        std::cout << "Entering admin mode...", admin_interface();
}

void UI::user_interface() {
    std::string choiceStr;
    int choice;

    while (true) {
        this->user_menu();
        std::getline(std::cin, choiceStr);
        try {
            choice = std::stoi(choiceStr);
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (choice == 1) {
            this->print_one_by_one();
        } else if (choice == 2) {
            this->show_by_breed();
        } else if (choice == 3)
            this->printAdoptedDogs();

        else{
            std::cout << "Invalid choice. Please select a valid option.\n";
        }
    }
}

void UI::admin_interface() {
    std::string choiceStr;
    int choice;

    while (true) {
        this->admin_menu();
        std::getline(std::cin, choiceStr);
        try {
            choice = std::stoi(choiceStr);
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (choice == 1) {
            this->addDog();
        } else if (choice == 2) {
            this->removeDog();
        } else if (choice == 3) {
            this->updateDog();
        } else if (choice == 4) {
            this->printAllDogs();
        } else {
            std::cout << "Please enter a number between 1-4\n";
        }
    }
}