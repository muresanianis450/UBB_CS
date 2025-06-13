// repository/RepositoryException.h
#ifndef REPOSITORY_EXCEPTION_H
#define REPOSITORY_EXCEPTION_H

#include <stdexcept>
#include <string>

class RepositoryException : public std::runtime_error {
public:
    explicit RepositoryException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // REPOSITORY_EXCEPTION_H

// validator/ValidationException.h
#ifndef VALIDATION_EXCEPTION_H
#define VALIDATION_EXCEPTION_H

#include <stdexcept>
#include <string>

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // VALIDATION_EXCEPTION_H

// input/InputException.h
#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H

#include <stdexcept>
#include <string>

class InputException : public std::runtime_error {
public:
    explicit InputException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // INPUT_EXCEPTION_H