#pragma once
#include <vector>
#include <string>
#include "User.h"
#include "Item.h"
class Repository {
private:
    std::string usersFile;
    std::string itemsFile;

    std::vector<User> users;
    std::vector<Item> items;

public:
    Repository(const std::string& usersFile,const std::string& itemsFile);

    void loadUsers();
    void loadItems();
    void saveItems() const;

    const std::vector<User>& getUsers() const {
        return users;
    };
    const std::vector<Item>& getItems() const {
        return items;
    };

    const User* findUsersById(int id);
    bool updateItem(const Item& item);

    bool addItem(const Item& item);

    void saveItems();


};



