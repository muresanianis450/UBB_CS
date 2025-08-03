#pragma once
#include <vector>
#include "Courier.h"
class CourierRepository {
private:
    std::vector<Courier> couriers;
public:
    CourierRepository(const std::string& filename);
    const std::vector<Courier>& getCouriers() const;
};