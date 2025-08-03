#pragma once

#include <string>
#include <vector>
#include "Offer.h"



class Item {
private:
    std::string name;
    std::string category;
    int currentPrice;
    std::vector<Offer> offers;
public:
    Item(const std::string& name, const std::string& category, int currentPrice);

    const std::string& getName() const;
    const std::string& getCategory() const;
    int getCurrentPrice() const;
    const std::vector<Offer>& getOffers() const;

    void setCurrentPrice(int currentPrice);
    void addOffer(const Offer& offer);
    void sortOffersBydateDesc();


};



