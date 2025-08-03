#include "WriterRepository.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

WriterRepository::WriterRepository(const std::string fileName) {
    writers.clear();
    std::ifstream fin(fileName);


    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string name, expertise;

        std::getline(iss, name, ',');
        std::getline(iss, expertise);

        if (!name.empty() && !expertise.empty()) {
            writers.emplace_back(name, expertise);
        }
    }

    fin.close();
}


const std::vector<Writer>& WriterRepository::getAll() const {
    return writers;
}
