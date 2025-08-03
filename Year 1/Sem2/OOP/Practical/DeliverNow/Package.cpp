#include "Package.h"

std::istream& operator>>(std::istream& in, Package& p) {
    in >> std::ws;
    std::getline(in, p.recipient);
    std::getline(in, p.street);
    in >> p.number >> p.x >> p.y >> p.delivered;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Package& p) {
    out << p.recipient << '\n'
        << p.street << '\n'
        << p.number << ' ' << p.x << ' ' << p.y << ' ' << p.delivered << '\n';
    return out;
}
