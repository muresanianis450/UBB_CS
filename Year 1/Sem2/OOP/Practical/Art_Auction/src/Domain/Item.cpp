
#include "Item.h"
#include <algorithm>

Item::Item(const std::string& name, const std::string& category, int currentPrice) {
    this->name = name;
    this->category = category;
    this->currentPrice = currentPrice;

}
const std::string& Item::getName() const {
    return name;
}
const std::string& Item::getCategory() const {
    return category;
}
int Item::getCurrentPrice() const {
    return currentPrice;
}
const std::vector<Offer>& Item::getOffers() const {
    return offers;
}

void Item::setCurrentPrice(int currentPrice) {
    this->currentPrice = currentPrice;
}
void Item::addOffer(const Offer& offer) {
    offers.push_back(offer);
}
void Item::sortOffersBydateDesc() {
    std::sort(offers.begin(), offers.end(), [](const Offer& a, const Offer& b) {
       return a.getDate() > b.getDate();
   });
}



