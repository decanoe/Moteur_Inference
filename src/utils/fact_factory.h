#pragma once

#include "../exception/syntax_exception.h"
#include "../fact/fact.h"

namespace FactFactory
{
    enum Operator { Equal, Greater, Lower, GreaterEqual, LowerEqual, NotEqual };

    std::string trim(const std::string& str, const std::string& whitespace = "\r\n\t\f\v ");
    std::shared_ptr<Fact> read_file_fact(const std::string& variable, const std::string& value, Operator op, int debug_line_count, const std::string& debug_path);
    std::shared_ptr<Fact> read_file_fact(const std::string& variable, bool value, int debug_line_count, const std::string& debug_path);
};
