
#include "ReportService.h"

void ReportService::addReport(const std::string& description, const std::string& reporterName,
    double lat, double lon) {
    Driver* reporter = driverRepo.findByName(reporterName);

    if (reporter->distanceTo(lat,lon)> 20.0) return;

    reportRepo.addReport(Report(description,reporterName,lat,lon));

    notifyObservers();
}
void ReportService::validateReport(const std::string& reportString, const std::string &validator) {
    Report* report = reportRepo.findReport(reportString);
    if (!report || report->getIsValid()) return;

    report->addValidator(validator);

    if (report->getIsValid()) {
        Driver* reporter = driverRepo.findByName(report->getReporter());
        if (reporter) reporter->incrementScore();
    }

    notifyObservers();
}

void ReportService::sendMessage(const std::string &message) {
    chatMessage.push_back(message);
    notifyObservers();
}

