#pragma once
#include <iostream>
#include <exception>

/// @brief Error to signal a syntax error in given files
class SyntaxException: public std::exception
{
private:
    std::string message;
public:
    SyntaxException(const std::string& message): message(message) {}
    const char * what() const noexcept override { return message.c_str(); }
};
