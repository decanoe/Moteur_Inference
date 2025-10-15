#pragma once
#include <iostream>
#include <vector>
#include "fact/fact.h"
#include "fact_base.h"

class Rule {
private:
    std::string name;
    std::vector<std::shared_ptr<Fact>> antecedents;
    std::vector<std::shared_ptr<Fact>> consequents;

    std::ostream& cout(std::ostream& os) const {
        os << name << ": ";
        for (auto fact : antecedents)
        {
            os << fact << ", ";
        }
        os << "\b\b => ";
        for (auto fact : consequents)
        {
            os << fact << ", ";
        }
        os << "\b\b \b";
        
        return os;
    }
public:
    Rule(const std::string& name, const std::vector<std::shared_ptr<Fact>>& antecedents, const std::vector<std::shared_ptr<Fact>>& consequents):
        name(name), antecedents(antecedents), consequents(consequents) {}
    Rule(const std::string& name):
        name(name), antecedents(), consequents() {}
    Rule(const Rule& fact) = delete;
    
    Rule& add_antecedent(std::shared_ptr<Fact> fact) {
        this->antecedents.push_back(fact);
        return *this;
    }
    Rule& add_consequent(std::shared_ptr<Fact> fact) {
        this->consequents.push_back(fact);
        return *this;
    }

    bool update_fact_base(FactBase& fact_base) const {
        for (auto antecedent : antecedents) {
            bool validated = false;
            for (auto fact : fact_base.get_facts())
            {
                if (antecedent->contradict(fact)) return false;
                if (!validated && fact->validate(antecedent)) validated = true;
            }
            if (!validated) return false;
        }
        
        for (auto consequent : consequents) fact_base.add_fact(consequent);
        return true;
    }

    friend std::ostream& operator<<(std::ostream &os, const Rule& rule);
    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Rule> rule);
};

std::ostream& operator<<(std::ostream& os, const Rule& rule) {
    return rule.cout(os);
}
std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Rule> rule) {
    return rule->cout(os);
}