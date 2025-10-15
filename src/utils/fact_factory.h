#pragma once
#include <vector>

#include "../exception/syntax_exception.h"
#include "../fact/fact.h"

/// @brief collection of function used to create facts from files
namespace FactFactory
{
    /// @brief An enum descibing a 
    enum Operator { Equal, Greater, Lower, GreaterEqual, LowerEqual, NotEqual };

    /// @brief Removes all leading and tailing whitespace of a string
    /// @param str the string to trim
    /// @param whitespace a string containing all the characters to consider as whitespaces to trim
    /// @return the modified string
    std::string trim(const std::string& str, const std::string& whitespace = "\r\n\t\f\v ");
    /// @brief Splits a string into a vector of strings with a separator char
    /// @param str the string to split
    /// @param separator a char that delimits the splits
    /// @return a vector of strings
    std::vector<std::string> split(const std::string& str, char separator = ',');

    /// @brief Creates a fact from a string that comes from a file (with syntax verification)
    /// @param line the string to convert
    /// @param debug_line_count the line of the file this fact comes from (for error debugging)
    /// @param debug_path the path of the file this fact comes from (for error debugging)
    /// @return a shared ptr to the fact created (if no syntax error is found)
    std::shared_ptr<Fact> read_file_fact(const std::string& line, int debug_line_count, const std::string& debug_path);
    /// @brief Creates a fact from a variable, an operator sign, and a value comming from a file (with syntax verification)
    /// @param variable the name of the variable
    /// @param value the value of the variable as a string
    /// @param op the operator of the fact
    /// @param debug_line_count the line of the file this fact comes from (for error debugging)
    /// @param debug_path the path of the file this fact comes from (for error debugging)
    /// @return a shared ptr to the fact created (if no syntax error is found)
    std::shared_ptr<Fact> read_file_fact(const std::string& variable, const std::string& value, Operator op, int debug_line_count, const std::string& debug_path);
    /// @brief Creates a boolean fact from a variable and a value comming from a file (with syntax verification)
    /// @param variable the name of the variable
    /// @param value the value of the variable as a boolean
    /// @param debug_line_count the line of the file this fact comes from (for error debugging)
    /// @param debug_path the path of the file this fact comes from (for error debugging)
    /// @return a shared ptr to the fact created (if no syntax error is found)
    std::shared_ptr<Fact> read_file_fact(const std::string& variable, bool value, int debug_line_count, const std::string& debug_path);
};
