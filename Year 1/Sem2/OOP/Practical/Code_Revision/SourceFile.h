#pragma once
#include <string>
class SourceFile {
private:
    std::string name;
    bool revised;
    std::string creator;
    std::string reviewer;

public:
    SourceFile(const std::string& name, bool revised, const std::string& creator, const std::string& reviewer);

    std::string getName() const;
    bool isRevised() const;
    std::string getCreator() const;
    std::string getReviewer() const;

    void markRevised(const std::string& reviewer);

};




