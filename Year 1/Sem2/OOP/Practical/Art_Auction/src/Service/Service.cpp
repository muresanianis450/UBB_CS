#include <algorithm>
#include "Service.h"

#include <iostream>
#include <stdexcept>
#include <iostream>
std::vector<Item> Service::getSortedItems() const {
    std::vector<Item> sortedItems = repo.getItems();
    std::sort(sortedItems.begin(), sortedItems.end(), [](const Item& a, const Item& b) {
        return a.getCurrentPrice() < b.getCurrentPrice();
    });
    return sortedItems;
}

std::vector<Item> Service::getItemsByCategory(const std::string& category) const {
    std::vector<Item> filteredItems;
    for ( const auto& item: repo.getItems()) {
        if (item.getCategory() == category) {
            filteredItems.push_back(item);
        }
    }
    std::sort(filteredItems.begin(), filteredItems.end(), [](const Item& a, const Item& b) {
        return a.getCurrentPrice() < b.getCurrentPrice();
    });
    return filteredItems;
}

std::vector<std::string> Service::getCategories() const {
    // Example: assuming repo.getItems() returns a vector of Item objects with a getCategory() method
    std::set<std::string> categories;
    for (const auto& item : repo.getItems()) {
        categories.insert(item.getCategory());
    }
    return std::vector<std::string>(categories.begin(), categories.end());
}

bool Service::addItem(const std::string& name, const std::string& category, int currentPrice) {
    if (name=="")
        throw std::invalid_argument("empty name");
    if (currentPrice < 0)
        throw std::invalid_argument("negative price");

    auto items = repo.getItems();
    auto it = std::find_if(items.begin(),items.end(),[&](const Item& i) {
        return i.getName() == name;
    });

    if ( it != items.end()) {
        throw std::invalid_argument("item already exists");
    }
    repo.addItem(Item(name,category,currentPrice));
    notifyObservers();
    return true;
}

void Service::bid(int userId, const std::string& itemName, int offeredSum, const std::string& date) {
    auto items = repo.getItems();
    auto it = std::find_if(items.begin(), items.end(), [&](const Item& i) {
        return i.getName() == itemName;
    });

    if (it == items.end())
        throw std::invalid_argument("Item not found.");

    if (offeredSum <= it->getCurrentPrice())
        throw std::invalid_argument("Offer must be higher than current price.");

   //update the item from repo
    Item updatedItem = *it;
    updatedItem.setCurrentPrice(offeredSum);
    updatedItem.addOffer(Offer(userId, date, offeredSum));
    updatedItem.sortOffersBydateDesc();
    std::cout<<updatedItem.getOffers().size()<<std::endl;

    repo.updateItem(updatedItem);

    notifyObservers();
}
