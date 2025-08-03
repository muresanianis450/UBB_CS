
#include "Service.h"
#include <algorithm>
#include <stdexcept>

Service::Service(Repository& repo)
    :repo(repo){}

const std::vector<Programmer>& Service::getProgrammers() const {
    return repo.getProgrammers();
}

std::vector<SourceFile> Service::getSortedFiles() const {
    auto files = repo.getSourceFiles();
    std::sort(files.begin(),files.end(),
        [](const SourceFile& f1, const SourceFile& f2) {
            return f1.getName() < f2.getName();
        });
    return files;
}

void Service::addFile(const std::string& fileName, const std::string& creatorName) {
    const auto& allFiles = repo.getSourceFiles();
    auto it = std::find_if(allFiles.begin(), allFiles.end(), [&](const SourceFile& f) {
        return f.getName() == fileName;
    });

    if (it != allFiles.end()) {
        throw std::runtime_error("File already exists");
    }
SourceFile newFile(fileName,false,creatorName,"");
    repo.addFile(newFile);
    notifyObservers();
}
void Service::reviseFile(const std::string& fileName, const std::string& reviewerName) {
    repo.reviseFile(fileName,reviewerName);
    notifyObservers();
}

