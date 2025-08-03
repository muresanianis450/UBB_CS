
#include "Repository.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

Repository::Repository(const std::string& userFile, const std::string& itemFile)
    :usersFile(userFile),itemsFile(itemFile){}

void Repository::loadUsers() {
    users.clear();
    std::ifstream fin(usersFile);


    std::string line;
    while (std::getline(fin,line)) {
        std::istringstream iss(line);

        int id;
        std::string name,type;
        iss >> id >> name >> type;
        users.emplace_back(id,name,type);
    }
    fin.close();
}

void Repository::loadItems() {
    items.clear();

    std::ifstream fin(itemsFile);
    if (!fin.is_open()) {
        std::cout << "Error opening file\n";
        return;
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);

        std::string name;
        std::string categ;
        std::string price;
        std::string offersStr;

        std::getline(iss, name, ';');
        std::getline(iss, categ, ';');
        std::getline(iss, price, ';');
        std::getline(iss, offersStr);

        int currentPrice = atoi(price.c_str());

        std::vector<Offer> offers_vector;

        if (offersStr.length() > 1 && offersStr[0] == '[' && offersStr[offersStr.length()-1] == ']') {
            std::string inner = offersStr.substr(1, offersStr.length() - 2);

            int pos = 0;
            while (pos < inner.length()) {
                int start = inner.find('(', pos);
                int end = inner.find(')', start);

                if (start == std::string::npos || end == std::string::npos)
                    break;

                std::string offerStr = inner.substr(start + 1, end - start - 1);

                int firstComma = offerStr.find(',');
                int secondComma = offerStr.find(',', firstComma + 1);

                std::string userIdStr = offerStr.substr(0, firstComma);
                std::string dateStr = offerStr.substr(firstComma + 1, secondComma - firstComma - 1);
                std::string offeredSumStr = offerStr.substr(secondComma + 1);

                int userId = atoi(userIdStr.c_str());
                int offeredSum = atoi(offeredSumStr.c_str());

                Offer offer(userId, dateStr, offeredSum);
                offers_vector.push_back(offer);

                pos = end + 1;
            }
        }
        Item item(name, categ, currentPrice);
        for (int i = 0; i < offers_vector.size(); i++) {
            item.addOffer(offers_vector[i]);
        }

        item.sortOffersBydateDesc();

        items.push_back(item);
    }
}
bool Repository::addItem(const Item& item) {
    for (const auto& current: items) {
        if (current.getName() == item.getName()) {
            return false;
        }
    }
    items.push_back(item);
    return true;
}
bool Repository::updateItem(const Item& item) {
    for (auto& i : items) {
        if (i.getName() == item.getName()) {
            i =item ;
            return true;
        }
    }
    return false;
}
void Repository::saveItems() {
    std::ofstream fout(itemsFile);
    for (const auto& item : items) {
        fout << item.getName() << ';'
             << item.getCategory() << ';'
             << item.getCurrentPrice() << ';'
             << '[';
        const auto& offers = item.getOffers();
        for (size_t i = 0; i < offers.size(); ++i) {
            const auto& offer = offers[i];
            fout << '(' << offer.getUserId() << ',' << offer.getDate() << ',' << offer.getOfferedSum() << ')';
            if (i != offers.size() - 1)
                fout << ',';
        }
        fout << ']' << '\n';
    }
    fout.close();
}