#pragma once
#include <iostream>
#include <vector>
#include "fact/fact.h"
#include "fact_base.h"

class Rule
{
private:
    std::string name;
    std::vector<std::shared_ptr<Fact>> antecedents;
    std::vector<std::shared_ptr<Fact>> consequents;

    std::ostream &cout(std::ostream &os) const
    {
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
    Rule(const std::string &name, const std::vector<std::shared_ptr<Fact>> &antecedents, const std::vector<std::shared_ptr<Fact>> &consequents) : name(name), antecedents(antecedents), consequents(consequents) {}
    Rule(const std::string &name) : name(name), antecedents(), consequents() {}
    Rule(const Rule &fact) = delete;

    Rule &add_antecedent(std::shared_ptr<Fact> fact)
    {
        this->antecedents.push_back(fact);
        return *this;
    }
    Rule &add_consequent(std::shared_ptr<Fact> fact)
    {
        this->consequents.push_back(fact);
        return *this;
    }

    /**
     * @brief Tries to apply the rule to the given fact base, adding new facts if the antecedents are validated
     * @param fact_base the fact base to update
     * @return true if new facts were added, false else
     */
    bool update_fact_base(FactBase &fact_base) const
    {
        const auto& facts = fact_base.get_facts();
        for (auto antecedent : antecedents)
        {
            bool validated = false;
            for (auto fact : facts)
            {
                if (antecedent->contradict(fact))
                    return false;
                if (!validated && fact->validate(antecedent))
                    validated = true;
            }
            if (!validated)
                return false;
        }
        for (auto consequent_ptr : consequents)
        {
            Fact& consequent = *consequent_ptr;
            if (!(consequent.findFact(facts))) {
                fact_base.add_fact(consequent_ptr);
            }
        }
        return true;
    }

    friend std::ostream &operator<<(std::ostream &os, const Rule &rule);
    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Rule> rule);
};

std::ostream &operator<<(std::ostream &os, const Rule &rule)
{
    return rule.cout(os);
}
std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Rule> rule)
{
    return rule->cout(os);
}

