#pragma once

#include <string>
#include <exception>

class bad_from_string : public std::exception {
public:
    explicit bad_from_string(char const *s);

    char const *what() const noexcept override;

private:
    std::string mMessage;
};
