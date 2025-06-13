#include "UI.h"
#include <limits>
#include <memory>
#include "../adoption/AdoptionListFactory.h"
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
    std::cout << "1. Show dogs one by one\n";
    std::cout << "2. Show all dogs by breed\n";
    std::cout << "3. Print current adopted dogs\n";
    std::cout << "4. Print adoption list\n";
}

void UI::show_by_breed() {
    std::string breed;
    std::cout << "Enter the breed of the dog: ";
    std::getline(std::cin, breed);

    std::vector<Dog> v = this->service.getDogsByBreed(breed);

    if (v.size() == 0) {
        std::cout << "No dogs found for the breed: " << breed << "\n";
        return;
    }

    for (int i = 0; i < v.size(); i++) {
        Dog &d = v[i];
        std::cout << d.getName() << " " << d.getBreed() << " " << d.getAge() << " " << d.getPhotography() << "\n";
    }
}
void UI::adoptDog(const Dog& d) {
    if (this->service.invalidDog(d)) {
        std::cout << "No dog with this information exists\n";
        return;
    }

    this->service.adoptDog(d); // Add the dog to the service's adoptedDogs list
    if (this->removing_dog(d)) {
        std::cout << "Dog adopted ☹️\n";
        if (adoptionList) {
            adoptionList->addDog(d);  // Save the dog in the file list
            adoptionList->saveToFile(fileType == "CSV" ? "adoption_list.csv" : "adoption_list.html");
        }
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
    std::string photo = d.getPhotography().empty() ? "N/A" : d.getPhotography();
    std::cout << "Photography: " << photo << "\n";

    // Open the photography link in the default browser
    //std::string command = "start msedge \"" + d.getPhotography() + "\"";
    //system(command.c_str());
}
void UI::print_one_by_one() {
    bool exit = false;
    int i = 0;
    std::vector<Dog> allDogs = this->service.getAllDogs();

    while (!exit && !allDogs.empty()) {
        Dog& d = allDogs[i];
        this->print_one_dog(d);

        std::cout << "Press 'A' to adopt this dog, 'N' for next, or 'E' to exit: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "A") {
            adoptDog(d);
            allDogs = this->service.getAllDogs(); // Reload the updated list
            if (i >= allDogs.size()) i = 0; // Reset if index out of bounds
        } else if (choice == "N") {
            i = (i + 1) % allDogs.size(); // Loop circularly
        } else if (choice == "E") {
            exit = true;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    if (allDogs.empty()) {
        std::cout << "No more dogs available.\n";
    }
}
int UI::getValidatedIntegerInput(const std::string& prompt) {
    std::string input;
    int value;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        try {
            value = std::stoi(input);
            if (value <= 0) {
                throw std::invalid_argument("Input must be a positive integer.");
            }
            return value;
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid positive integer.\n";
        }
    }
}
void UI::addDog() {
    try {
        std::string name, breed, photography;
        int age = this->getValidatedIntegerInput("Enter the age of the dog: ");

        std::cout << "Enter the name of the dog: ";
        std::getline(std::cin, name);

        std::cout << "Enter the breed of the dog: ";
        std::getline(std::cin, breed);

        std::cout << "Enter the link to the photography: ";
        std::getline(std::cin, photography);

        Dog d{name, breed, age, photography};
        this->service.addDog(d);
        std::cout << "Dog added successfully.\n";
    } catch (const ValidationException& e) {
        std::cout << "Validation error: " << e.what() << "\n";
    } catch (const RepositoryException& e) {
        std::cout << "Repository error: " << e.what() << "\n";
    }
}
void UI::removeDog() {
    try {
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
    } catch (const ValidationException& e) {
        std::cout << "Validation error: " << e.what() << "\n";
    } catch (const RepositoryException& e) {
        std::cout << "Repository error: " << e.what() << "\n";
    }
}

void UI::updateDog() {
    try{
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
    } catch (const ValidationException& e) {
        std::cout << "Validation error: " << e.what() << "\n";
    } catch (const RepositoryException& e) {
        std::cout << "Repository error: " << e.what() << "\n";
    }
}

void UI::printAllDogs() {
    const auto& v = this->service.getAllDogs();
    for (int i = 0; i < v.size(); i++) {
        Dog d = v[i];
        this->print_one_dog(d);
    }
}

void UI::run() {
    std::cout << "Choose file type for adoption list (CSV/HTML): ";
    std::getline(std::cin, fileType); // Initialize fileType

    try {
    this->adoptionList = AdoptionListFactory::createAdoptionList(fileType);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return;
    }

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

    if (choice == 3) {
        std::cout << "Exiting...\n";
        exit(0);
    } else if (choice == 2) {
        std::cout << "Entering user mode...\n";
        user_interface();
    } else if (choice == 1) {
        std::cout << "Entering admin mode...\n";
        admin_interface();
    }
}
void UI::print_adoption_list() {
    std::vector<Dog> dogs;
    std::string filename = (fileType == "CSV") ? "adoption_list.csv" : "adoption_list.html";
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "Error: Could not open adoption list file.\n";
        return;
    }

    if (fileType == "CSV") {
        std::string line;
        while (std::getline(fin, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string name, breed, ageStr, photography;
            if (!std::getline(ss, name, ',')) continue;
            if (!std::getline(ss, breed, ',')) continue;
            if (!std::getline(ss, ageStr, ',')) continue;
            if (!std::getline(ss, photography, ',')) photography = "";
            try {
                int age = std::stoi(ageStr);
                dogs.emplace_back(name, breed, age, photography);
            } catch (const std::exception&) {
                continue;
            }
        }
    } else { // HTML Parsing
        std::string line;
        bool insideTable = false;
        while (std::getline(fin, line)) {
            // Check if we are inside the table
            if (line.find("<table") != std::string::npos) {
                insideTable = true;
                continue;
            }
            if (insideTable && line.find("</table>") != std::string::npos) {
                break; // End of table
            }
            if (insideTable && line.find("<tr>") != std::string::npos) {
                std::vector<std::string> tokens;
                size_t pos = 0;
                while ((pos = line.find("<td>")) != std::string::npos) {
                    size_t end = line.find("</td>", pos);
                    if (end == std::string::npos) break;
                    std::string token = line.substr(pos + 4, end - pos - 4);

                    // Check if the token contains an <a> tag
                    size_t linkStart = token.find("<a href=\"");
                    if (linkStart != std::string::npos) {
                        size_t linkEnd = token.find("\">", linkStart);
                        if (linkEnd != std::string::npos) {
                            token = token.substr(linkStart + 9, linkEnd - (linkStart + 9)); // Extract href value
                        }
                    }

                    tokens.push_back(token);
                    line = line.substr(end + 5);
                }
                if (tokens.size() >= 4) {
                    try {
                        int age = std::stoi(tokens[2]);
                        dogs.emplace_back(tokens[0], tokens[1], age, tokens[3]);
                    } catch (const std::exception&) {
                        continue;
                    }
                }
            }
        }
    }

    fin.close();

    if (dogs.empty()) {
        std::cout << "No dogs adopted.\n";
    } else {
        std::cout << "----- Adoption List -----\n";
        for (const auto& dog : dogs) {
            std::cout << "Name: " << dog.getName() << ", "
                      << "Breed: " << dog.getBreed() << ", "
                      << "Age: " << dog.getAge() << ", "
                      << "Photography: " << dog.getPhotography() << "\n";
        }
    }
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
        } else if (choice == 3) {
            this->printAdoptedDogs();
        } else if (choice == 4) {
            this->print_adoption_list();
        } else {
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