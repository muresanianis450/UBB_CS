#pragma once
#include <vector>
#include "Programmer.h"
#include "SourceFile.h"

class Repository {
private:
    std::vector<Programmer> programmers;
    std::vector<SourceFile> sourceFiles;

public:
    Repository(const std::string& pFile,const std::string& sFile);
    const std::vector<Programmer>& getProgrammers() const;
    const std::vector<SourceFile>& getSourceFiles() const;

    void addFile(const SourceFile& file);
    void reviseFile(const std::string& fileName, const std::string& reviewerName);
};