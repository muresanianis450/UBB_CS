#pragma once
#include "Report.h"
#include <string>
#include <vector>

class ReportRepository {
private:
    std::vector<Report> reports;

public:
    ReportRepository();
    void loadFile(const std::string& filename= "reports.txt");
    void saveToFile(const std::string& filename="reports.txt");
    const std::vector<Report>& getAll() const;

    Report* findReport(const std::string& description);
    void addReport(const Report& report);
};


