#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include "exception/syntax_exception.h"

#include "utils/fact_factory.h"
#include "fact/fact.h"
#include "rule.h"

class RuleBase {
private:
    std::vector<std::shared_ptr<Rule>> rules;

    std::ostream& cout(std::ostream& os) const {
        os << "[\n";
        for (auto rule : rules)
        {
            os << "\t" << rule << "\n";
        }
        os << "]";
        
        return os;
    }
public:
    RuleBase():
        rules() {}
    RuleBase(const std::vector<std::shared_ptr<Rule>>& rules):
        rules(rules) {}
    RuleBase(const RuleBase& fact) = delete;
    
    RuleBase& add_rule(std::shared_ptr<Rule> rule) {
        this->rules.push_back(rule);
        return *this;
    }
    RuleBase& add_file(const std::string& path) {
        std::regex label_regex("[a-zA-Z_0-9]+");

        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::invalid_argument("cannot open file at path \"" + path + "\"");
        }

        int line_count = 0;
        std::string line;
        while (std::getline(file, line))
        {
            line_count++;

            std::size_t dots_pos = line.find(':');
            if (dots_pos == std::string::npos) {
                throw SyntaxException("Syntax error at line " + std::to_string(line_count) + " of \"" + path + "\": rules need to be labeled (absence of symbol ':')");
            }
            std::string label = FactFactory::trim(line.substr(0, dots_pos));
            std::string rule = FactFactory::trim(line.substr(dots_pos + 1));

            if (!std::regex_match(label, label_regex)) throw SyntaxException("Syntax error at line " + std::to_string(line_count) + " of \"" + path + "\": rule labels can only be letters and digits with underscore (and no spaces)");
            if (label.size() == 0) throw SyntaxException("Syntax error at line " + std::to_string(line_count) + " of \"" + path + "\": rules need to be labeled (absence of symbol ':')");
            
            if (rule.find(':') != std::string::npos) throw SyntaxException("Syntax error at line " + std::to_string(line_count) + " of \"" + path + "\": symbol ':' must be present only once");
            
            std::smatch match;
            if (std::regex_search(rule, match, std::regex("=>")))
            {
                std::string antecedents = FactFactory::trim(match.prefix());
                std::string consequents = FactFactory::trim(match.suffix());

                if (std::regex_search(antecedents, std::regex("=>")) || std::regex_search(consequents, std::regex("=>"))) throw SyntaxException("Syntax error at line " + std::to_string(line_count) + " of \"" + path + "\": symbol '=>' is present more than once in the rule");

                std::vector<std::string> a_facts = FactFactory::split(antecedents, ',');
                std::vector<std::string> c_facts = FactFactory::split(consequents, ',');

                auto rule = std::make_shared<Rule>(label);
                for (const std::string& antecedent : a_facts)
                {
                    std::shared_ptr<Fact> fact = FactFactory::read_file_fact(antecedent, line_count, path);
                    if (fact != nullptr) rule->add_antecedent(fact);
                    else throw SyntaxException("Syntax error at line " + std::to_string(line_count) + " of \"" + path + "\": rules cannot contain an empty antecedent");
                }
                for (const std::string& consequents : c_facts)
                {
                    std::shared_ptr<Fact> fact = FactFactory::read_file_fact(consequents, line_count, path);
                    if (fact != nullptr) rule->add_consequent(fact);
                    else throw SyntaxException("Syntax error at line " + std::to_string(line_count) + " of \"" + path + "\": rules cannot contain an empty consequent");
                }
                add_rule(rule);
            }
            else throw SyntaxException("Syntax error at line " + std::to_string(line_count) + " of \"" + path + "\": symbol '=>' is not present in the rule");
        }
        file.close();

        return *this;
    }
    const std::vector<std::shared_ptr<Rule>>& get_rules() const { return rules; }
    
    friend std::ostream& operator<<(std::ostream &os, const RuleBase& fact_base);
};

std::ostream& operator<<(std::ostream& os, const RuleBase& rule_base) {
    return rule_base.cout(os);
}