
#include "ReportRepository.h"
#include <fstream>
#include <sstream>

ReportRepository::ReportRepository() {
loadFile("reports.txt");
}

void ReportRepository::loadFile(const std::string &filename) {
    std::ifstream fin(filename);
    std::string description,reporter;
    double lat,lon;
    int valid;

    while (fin >> reporter >> lat >> lon >> valid) {
        fin.ignore(); //ignore \n
        std::getline(fin,description);
        reports.emplace_back(description,reporter,lat,lon,valid == 1);
    }
    fin.close();
}
Report* ReportRepository::findReport(const std::string& description) {
    for (auto& report : reports) {
        if (report.getDescription() == description) {
            return &report;
        }
    }
    return nullptr;
}
const std::vector<Report>& ReportRepository::getAll() const {
    return reports;
}
void ReportRepository::addReport(const Report& report) {
    reports.push_back(report);
    std::ofstream fout("reports.txt", std::ios::app);
    if (fout.is_open()) {
        fout<<"\n\n";
        fout << report.getReporter() << " "
             << report.getLatitude() << " "
             << report.getLongitude() << " "
        << (report.getIsValid() ? 1 : 0) << "\n"
       << report.getDescription() ;
        fout.close();
    }
}