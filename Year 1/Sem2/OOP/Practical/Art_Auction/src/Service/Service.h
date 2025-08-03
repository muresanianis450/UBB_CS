#pragma once
#include <string>
#include <set>
#include "../Domain/Item.h"
#include "../Domain/User.h"
#include "../Domain/Offer.h"
#include "../Repository/Repository.h"
#include "../Observer/Observable.h"

class Service : public Observable {
private:
    Repository& repo;
public:
    explicit Service(Repository& repo) : repo(repo) {}

    const std::vector<User>& getUsers() const {
        return repo.getUsers();
    }
    const std::vector<Item>& getItems() const {
        return repo.getItems();
    }

    std::vector<Item> getSortedItems() const;
    std::vector<Item> getItemsByCategory(const std::string& category) const;
    std::vector<std::string> getCategories() const;

    bool addItem(const std::string& name, const std::string& category, int currentPrice);
    void bid(int userId, const std::string& itemName, int offeredSum, const std::string& date);
    void saveItems();

    void addObserver(Observer* obs) {
        Observable::addObserver(obs);
    }
    void notifyObservers() {
        Observable::notifyObservers();
    }
};