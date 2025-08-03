
#include "Repository.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>


Repository::Repository(const std::string& pFile="programmers.txt", const std::string& sFile="source.txt") {
    std::ifstream progIn(pFile);

    std::string line;
    while (std::getline(progIn, line)) {
        std::istringstream iss(line);
        std::string name;
        int rev, total;
        if (iss >> name >> rev >> total) {
            programmers.emplace_back(name, rev, total);
        }
    }
    progIn.close();

    std::ifstream sorIn(sFile);
    while (std::getline(sorIn, line)) {
        std::istringstream iss(line);
        std::string name, statusStr, creator, reviewer;

        if (iss >> name >> statusStr >> creator) {
            bool revised = (statusStr == "revised");
            if (revised && iss >> reviewer) {
                sourceFiles.emplace_back(name, revised, creator, reviewer);
            } else {
                sourceFiles.emplace_back(name, revised, creator, "");
            }
        }
    }
    sorIn.close();
}

const std::vector<Programmer>& Repository::getProgrammers() const {
    return programmers;
}
const std::vector<SourceFile>& Repository::getSourceFiles() const {
    return sourceFiles;

}

void Repository::addFile(const SourceFile& file) {
    auto it = std::find_if(sourceFiles.begin(), sourceFiles.end(),
        [&file](const SourceFile& f) {return file.getName() == f.getName();});
    if (it != sourceFiles.end()) {
        throw std::runtime_error("File already exists");
    }
    sourceFiles.push_back(file);
}

void Repository::reviseFile(const std::string &fileName, const std::string &reviewerName) {
    for (auto& file : sourceFiles) {
        if (file.getName() == fileName) {
            if (file.isRevised())
                throw std::runtime_error("file already revised");
            if (file.getCreator() == reviewerName)
                throw std::runtime_error("file already revised by you");
            file.markRevised(reviewerName);

            for (auto& prog: programmers) {
                if (prog.getName()== reviewerName) {
                    prog.incrementRevised();
                    break;
                }
            }
            return;
        }

    }
    throw std::runtime_error("file not found");
}
