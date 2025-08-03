#pragma once
#include <string>
#include <vector>

class Report {
private:
    std::string description, reporterName;
    double latitude, longitude;
    bool isValid;
    std::vector<std::string> validators;
public:
    Report(const std::string& description, const std::string& reporterName, double latitude, double longitude, bool isValid = false);

    std::string getDescription() const;
    std::string getReporter() const;
    double getLatitude() const;
    double getLongitude() const;
    bool getIsValid() const;
    const std::vector<std::string>& getValidators() const;

    std::string toString() const {
        return "Description: " + description
               + ", Reporter: " + reporterName
               + ", Location: (" + std::to_string(latitude) + ", " + std::to_string(longitude) + ")"
               + ", Valid: " + (isValid ? "Yes" : "No");
    }
    void addValidator(const std::string& validatorName);
    void setValid(bool status);
    bool isWithinRange(double lat, double lon, double radius) const;
};



