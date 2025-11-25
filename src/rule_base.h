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

    RuleBase copy() { return RuleBase(rules); }
    
    bool CheckConsistency(std::shared_ptr<Rule> rule) {
        if (!rule->CheckConsistency()) return false;

        for (std::shared_ptr<Rule> r : rules) {
            bool s1 = true, s2 = true;
            
            bool can_contradict = false;
            for (std::shared_ptr<Fact> consequent_1 : rule->get_consequents()) {
                for (std::shared_ptr<Fact> consequent_2 : r->get_consequents())
                {
                    if (can_contradict) break;
                    can_contradict |= consequent_1->contradict(consequent_2);
                }
                for (std::shared_ptr<Fact> antecedant_2 : r->get_antecedents())
                {
                    if (can_contradict) break;
                    can_contradict |= consequent_1->contradict(antecedant_2);
                }
            }
            for (std::shared_ptr<Fact> consequent_2 : r->get_consequents()) {
                for (std::shared_ptr<Fact> consequent_1 : rule->get_consequents())
                {
                    if (can_contradict) break;
                    can_contradict |= consequent_2->contradict(consequent_1);
                }
                for (std::shared_ptr<Fact> antecedant_1 : rule->get_antecedents())
                {
                    if (can_contradict) break;
                    can_contradict |= consequent_2->contradict(antecedant_1);
                }
            }
            if (!can_contradict) continue;
            
            if (rule->LeadsTo(r)) {
                std::ostream& c = Cout::out(Cout::Yellow);
                c << "Consistency Warning:\n\trule \t\"" << rule << "\"\n\tleads to\t\"" << r << "\"";
                Cout::endl(c);
                return false;
            }
            if (r->LeadsTo(rule)) {
                std::ostream& c = Cout::out(Cout::Yellow);
                c << "Consistency Warning:\n\trule \t\"" << r << "\"\n\tleads to\t\"" << rule << "\"";
                Cout::endl(c);
                return false;
            }
        }
        return true;
    }
    RuleBase& add_rule(std::shared_ptr<Rule> rule) {
        CheckConsistency(rule);
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
    std::vector<std::shared_ptr<Rule>>::iterator begin() { return rules.begin(); }
    std::vector<std::shared_ptr<Rule>>::iterator end() { return rules.end(); }
    std::vector<std::shared_ptr<Rule>>::iterator remove_rule(std::vector<std::shared_ptr<Rule>>::iterator iterator) { return rules.erase(iterator); }

    bool empty() { return rules.empty(); }
    
    friend std::ostream& operator<<(std::ostream &os, const RuleBase& fact_base);
};

std::ostream& operator<<(std::ostream& os, const RuleBase& rule_base) {
    return rule_base.cout(os);
}