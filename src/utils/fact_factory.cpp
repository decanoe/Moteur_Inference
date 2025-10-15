#include "./fact_factory.h"
#include <regex>
#include <vector>

#include "../fact/numeric_fact.h"
#include "../fact/text_fact.h"
#include "../fact/boolean_fact.h"

std::string FactFactory::trim(const std::string& str, const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) return "";

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}
std::shared_ptr<Fact> FactFactory::read_file_fact(const std::string& variable, const std::string& value, FactFactory::Operator op, int debug_line_count, const std::string& debug_path)
{
    if (variable.size() == 0) throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": variables name must be non empty");
    if (value.size() == 0) throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": value must be non empty");

    std::regex variable_regex("[a-zA-Z_]+");
    std::regex string_regex("[a-zA-Z_]+");

    if (!std::regex_match(variable, variable_regex)) throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": variables name can only be letters with underscore (and no spaces)");
    try {
        double v = std::stod(value);
        return std::make_shared<NumericFact>(variable, v, op);
    } catch(...) {}
    if (std::regex_match(value, string_regex)) {
        if (op == FactFactory::Equal)  return std::make_shared<TextFact>(variable, value, true);
        else if (op == FactFactory::NotEqual) return std::make_shared<TextFact>(variable, value, false);
        else throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": text values cannot be compared");
    }
    throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": value cannot be interpreted (not numerical or text)");
}
std::shared_ptr<Fact> FactFactory::read_file_fact(const std::string& variable, bool value, int debug_line_count, const std::string& debug_path)
{
    if (variable.size() == 0) throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": variables name must be non empty");

    std::regex variable_regex("[a-zA-Z_]+");

    if (!std::regex_match(variable, variable_regex)) throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": variables name can only be letters with underscore (and no spaces)");
    return std::make_shared<BooleanFact>(variable, value);
}
