#pragma once
#include "ReportRepository.h"
#include "DriverRepo.h"
#include "Observable.h"

class ReportService : public Observable {
private:
    ReportRepository& reportRepo;
    DriverRepo& driverRepo;
    std::vector<std::string> chatMessage;

public:
    ReportService(ReportRepository& rr, DriverRepo& dr):
    reportRepo(rr), driverRepo(dr){}

    const std::vector<Report> & getReports() const {
        return reportRepo.getAll();
    }
    void addReport(const std::string& description, const std::string& reporter,
        double lat, double lon);
    std::vector<std::string> getChatMessages() const {
        return chatMessage;
    };
    void validateReport(const std::string &reportString, const std::string &validator);

    void notifyObservers (){
        Observable::notifyObservers();
    };
    void sendMessage(const std::string& message);
};