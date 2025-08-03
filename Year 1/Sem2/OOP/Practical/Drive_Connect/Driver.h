#pragma once
#include <string>
class Driver {
private:
std::string name;
    double latitude,longitude;
    int score;
public:
    Driver(const std::string& name, double lat,double lon,int score);

    std::string getName() const;
    double getLatitude() const;
    double getLongitude() const;
    int getScore() const;

    void setLatitude(double lat);
    void setLongitude(double lon);

    void incrementScore() {
        score++;
    }
    double distanceTo(double lat,double lon) const;
};


