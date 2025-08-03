
#include "SourceFile.h"

SourceFile::SourceFile(const std::string& name, bool revised, const std::string& creator, const std::string& reviewer)
    : name(name), revised(revised), creator(creator), reviewer(reviewer){}

std::string SourceFile::getName() const {
    return name;
}
bool SourceFile::isRevised() const {
    return revised;
}
std::string SourceFile::getCreator() const {
    return creator;
}
std::string SourceFile::getReviewer() const {
    return reviewer;
}

void SourceFile::markRevised(const std::string& reviewerName) {
    revised = true;
    reviewer = reviewerName;
}

