#include "Report.h"
#include <cmath>
#include <algorithm>

Report::Report(const std::string& description, const std::string& reporterName, double latitude, double longitude, bool isValid)
    :description(description), reporterName(reporterName), latitude(latitude), longitude(longitude), isValid(isValid)
{}

std::string Report::getDescription() const {
    return description;
}
std::string Report::getReporter() const {
    return reporterName;
}
double Report::getLatitude() const {
    return latitude;

}
double Report::getLongitude() const {
    return longitude;
}
bool Report::getIsValid() const {
    return isValid;
}
const std::vector<std::string>&Report::getValidators()const  {
    return validators;
}
void Report::addValidator(const std::string& validatorName) {
    if (std::find(validators.begin(), validators.end(), validatorName) == validators.end() &&
        validatorName != reporterName) {
        validators.push_back(validatorName);
        if (validators.size() >= 2) {
            isValid = true;
        }
        } else {
        }
}
void Report::setValid(bool status) {
    isValid = status;
}
bool Report::isWithinRange(double lat,double lon, double radius) const {
    double dist = std::sqrt((latitude - lat) * (latitude - lat) + (longitude - lon) * (longitude - lon));
    return dist <= radius;
}
