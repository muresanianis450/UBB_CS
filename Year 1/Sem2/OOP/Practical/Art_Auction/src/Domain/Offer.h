#pragma once
#ifndef OFFER_H
#define OFFER_H
#include <string>


class Offer {
private:
    int userId;
    std::string date;//y-m-d
    int offeredSum;
public:
    Offer(int userId, const std::string& date, int offeredSum);

    int getUserId() const;
    const std::string& getDate() const;
    int getOfferedSum() const;

    bool operator<(const Offer& other) const;
    bool operator>(const Offer& other) const;
};



#endif //OFFER_H
