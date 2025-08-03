#pragma once
#include <string>
#include <vector>
#include <sstream>

class Courier {
private:
    std::string name;
    std::vector<std::string> assignedStreets;
    double zoneX, zoneY, radius;

public:
    Courier(const std::string& name, const std::vector<std::string>& streets,
            double zoneX, double zoneY, double radius)
        : name(name), assignedStreets(streets), zoneX(zoneX), zoneY(zoneY), radius(radius) {}

    std::string getName() const { return name; }
    const std::vector<std::string>& getStreets() const { return assignedStreets; }
    double getZoneX() const { return zoneX; }
    double getZoneY() const { return zoneY; }
    double getRadius() const { return radius; }

    bool isInZone(double x, double y) const {
        double dx = x - zoneX, dy = y - zoneY;
        return dx * dx + dy * dy <= radius * radius;
    }
};
