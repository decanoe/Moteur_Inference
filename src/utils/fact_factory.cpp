#include "./fact_factory.h"
#include <regex>

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
std::vector<std::string> FactFactory::split(const std::string& str, char separator)
{
    std::stringstream test(str);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(test, segment, separator))
    {
        seglist.push_back(segment);
    }
    return seglist;
}

std::shared_ptr<Fact> FactFactory::read_file_fact(const std::string& line, int debug_line_count, const std::string& debug_path) {
    if (line.find(':') != std::string::npos) {
        throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": facts are not supposed to have labels (presence of symbol ':')");
    }

    std::size_t equal_pos = line.find('=');
    if (equal_pos != std::string::npos) { // assignation
        FactFactory::Operator op = FactFactory::Equal;

        std::string value = FactFactory::trim(line.substr(equal_pos+1));
        
        if (equal_pos != 0) {
            if      (line[equal_pos - 1] == '<') { equal_pos--; op = FactFactory::LowerEqual; }
            else if (line[equal_pos - 1] == '>') { equal_pos--; op = FactFactory::GreaterEqual; }
            else if (line[equal_pos - 1] == '!') { equal_pos--; op = FactFactory::NotEqual; }
        }
        if (equal_pos != line.size() - 1) {
            if (line[equal_pos + 1] == '>') throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": facts can't contain antecedents or consequents (presence of symbol '=>')");
        }
        

        std::string variable = FactFactory::trim(line.substr(0, equal_pos));
        
        return FactFactory::read_file_fact(variable, value, op, debug_line_count, debug_path);
    }

    std::size_t sign_pos = line.find('<');
    if (sign_pos != std::string::npos) {
        return FactFactory::read_file_fact(FactFactory::trim(line.substr(0, sign_pos)), FactFactory::trim(line.substr(sign_pos+1)), FactFactory::Lower, debug_line_count, debug_path);
    }
    sign_pos = line.find('>');
    if (sign_pos != std::string::npos) {
        return FactFactory::read_file_fact(FactFactory::trim(line.substr(0, sign_pos)), FactFactory::trim(line.substr(sign_pos+1)), FactFactory::Greater, debug_line_count, debug_path);
    }

    // boolean fact
    std::string variable = FactFactory::trim(line);
    if (variable.size() == 0) return nullptr; // empty line
    if (variable[0] == '-')
        return FactFactory::read_file_fact(FactFactory::trim(variable.substr(1)), false, debug_line_count, debug_path);
    else
        return FactFactory::read_file_fact(variable, true, debug_line_count, debug_path);
}
std::shared_ptr<Fact> FactFactory::read_file_fact(const std::string& variable, const std::string& value, FactFactory::Operator op, int debug_line_count, const std::string& debug_path)
{
    if (variable.size() == 0) throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": variables name must be non empty");
    if (value.size() == 0) throw SyntaxException("Syntax error at line " + std::to_string(debug_line_count) + " of \"" + debug_path + "\": value must be non empty");

    std::regex variable_regex("[a-zA-Z_]+");
    std::regex string_regex("[a-zA-Z_0-9]+");

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
