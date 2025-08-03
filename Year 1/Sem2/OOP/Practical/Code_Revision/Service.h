#pragma once
#include "Repository.h"
#include "Observable.h"
#include <string>
#include <vector>

class Service : public Observable {
private:
    Repository& repo;

public:
    explicit Service(Repository& repo);
    const std::vector<Programmer>& getProgrammers() const;
    std::vector<SourceFile> getSortedFiles() const;

    void addFile(const std::string& fileName,const std::string& creatorName);
    void reviseFile(const std::string& fileName, const std::string& reviewerName);



};