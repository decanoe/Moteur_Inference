#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include "exception/syntax_exception.h"

#include "utils/fact_factory.h"
#include "fact/fact.h"
#include "fact/numeric_fact.h"

class FactBase {
private:
    std::vector<std::shared_ptr<Fact>> facts;

    std::ostream& cout(std::ostream& os) const {
        os << "[\n";
        for (auto fact : facts)
        {
            os << "\t" << fact << "\n";
        }
        os << "]";
        
        return os;
    }
public:
    FactBase():
        facts() {}
    FactBase(const std::vector<std::shared_ptr<Fact>>& facts):
        facts(facts) {}
    FactBase(const FactBase& fact) = delete;
    
    FactBase& add_fact(std::shared_ptr<Fact> fact) {
        this->facts.push_back(fact);
        return *this;
    }
    FactBase& add_file(const std::string& path) {
        std::ifstream file(path);

        int line_count = 0;
        std::string line;
        while (std::getline(file, line))
        {
            line_count++;

            if (line.find(':') != std::string::npos) {
                throw SyntaxException("Syntax error at line " + std::to_string(line_count) + " of \"" + path + "\": facts are not supposed to have labels (presence of symbol ':')");
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
                    if (line[equal_pos + 1] == '>') throw SyntaxException("Syntax error at line " + std::to_string(line_count) + " of \"" + path + "\": facts can't contain antecedents or consequents (presence of symbol '=>')");
                }
                

                std::string variable = FactFactory::trim(line.substr(0, equal_pos));
                
                add_fact(FactFactory::read_file_fact(variable, value, op, line_count, path));
                continue;
            }

            std::size_t sign_pos = line.find('<');
            if (sign_pos != std::string::npos) {
                add_fact(FactFactory::read_file_fact(FactFactory::trim(line.substr(0, sign_pos)), FactFactory::trim(line.substr(sign_pos+1)), FactFactory::Lower, line_count, path));
                continue;
            }
            sign_pos = line.find('>');
            if (sign_pos != std::string::npos) {
                add_fact(FactFactory::read_file_fact(FactFactory::trim(line.substr(0, sign_pos)), FactFactory::trim(line.substr(sign_pos+1)), FactFactory::Greater, line_count, path));
                continue;
            }

            // boolean fact
            std::string variable = FactFactory::trim(line);
            if (variable.size() == 0) continue; // empty line
            if (variable[0] == '-')
                add_fact(FactFactory::read_file_fact(FactFactory::trim(variable.substr(1)), false, line_count, path));
            else
                add_fact(FactFactory::read_file_fact(variable, true, line_count, path));
        }

        return *this;
    }
    const std::vector<std::shared_ptr<Fact>>& get_facts() const { return facts; }
    
    friend std::ostream& operator<<(std::ostream &os, const FactBase& fact_base);
};

std::ostream& operator<<(std::ostream& os, const FactBase& fact_base) {
    return fact_base.cout(os);
}