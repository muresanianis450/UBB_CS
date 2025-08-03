
#include "Offer.h"

Offer::Offer(int userId, const std::string& date, int offeredSum):
userId(userId), date(date),offeredSum(offeredSum){}

int Offer::getUserId()const {
    return userId;

}

const std::string& Offer::getDate() const {
    return date;
}
int Offer::getOfferedSum() const {
    return offeredSum;
}
bool Offer::operator<(const Offer& other) const {
    return date < other.date;
}
bool Offer::operator>(const Offer& other) const {
    return date > other.date;
}