#pragma once
#include <string>
#include <sstream>

class Package {
private:
    std::string recipient;
    std::string street;
    int number;
    double x, y;
    bool delivered;

public:
    // Constructors
    Package() : recipient(""), street(""), number(0), x(0), y(0), delivered(false) {}
    Package(const std::string& recipient, const std::string& street, int number, double x, double y, bool delivered)
        : recipient(recipient), street(street), number(number), x(x), y(y), delivered(delivered) {}

    // Getters
    std::string getRecipient() const { return recipient; }
    std::string getStreet() const { return street; }
    int getNumber() const { return number; }
    double getX() const { return x; }
    double getY() const { return y; }
    bool isDelivered() const { return delivered; }

    // Setters
    void setDelivered(bool status) { delivered = status; }

    // For displaying as string (useful in GUI)
    std::string toString() const {
        std::stringstream ss;
        ss << "Recipient: " << recipient << ", Street: " << street << " " << number
           << ", Location: (" << x << ", " << y << "), Delivered: " << (delivered ? "Yes" : "No");
        return ss.str();
    }

    // For file I/O
    friend std::istream& operator>>(std::istream& in, Package& p);
    friend std::ostream& operator<<(std::ostream& out, const Package& p);
};
