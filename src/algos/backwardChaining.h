#pragma once
#include "backwardChainingOutput.h"
#include "inferenceSolver.h"

class BackwardChaining : public InferenceSolver
{
public:
    BackwardChaining(std::shared_ptr<Critere> critere) : InferenceSolver(critere) {}

    void run(RuleBase& rule_base, FactBase& fact_base, std::shared_ptr<Fact> goal) override
    {
        if (goal == nullptr) throw std::invalid_argument("BackwardChaining needs a goal, none was provided !");
        std::cout << demonstrate(goal, rule_base, fact_base);
    }
    BackwardChainingOutput demonstrate(std::shared_ptr<Fact> to_demonstrate, RuleBase& rule_base, FactBase& fact_base, BackwardChainingOutput output = BackwardChainingOutput()) const {
        // fact already in fact_base
        if (fact_base.contains_fact(to_demonstrate)) {
            fact_base.add_fact(to_demonstrate);

            std::stringstream ss;
            ss << (*to_demonstrate);
            output.add(ss.str());

            output.set_result(true);
            output.unindent();
            return output;
        }
        
        // search a demo for b
        bool can_ask = true;
        int index = -1;
        for (auto it_rules = rule_base.begin(); it_rules != rule_base.end(); it_rules++)
        {
            index++;
            if (!(*it_rules)->contains_consequent(to_demonstrate)) continue;
            can_ask = false;

            RuleBase rule_base_copy = rule_base.copy();
            rule_base_copy.remove_rule(std::next(rule_base_copy.begin(), index));

            FactBase fact_base_copy = fact_base.copy();
            
            BackwardChainingOutput output_copy = BackwardChainingOutput(output);
            std::stringstream ss;
            ss << (*it_rules);
            output_copy.add(ss.str());

            bool end = true;
            for (auto fact : (*it_rules)->get_antecedents()) {
                output_copy.indent();
                output_copy = demonstrate(fact, rule_base_copy, fact_base_copy, output_copy);
                if (!output_copy) {
                    end = false;
                    break;
                }
            }
            if (end) {
                fact_base.add_fact(to_demonstrate);
                output_copy.set_result(true);
                output_copy.unindent();
                return output_copy;
            }
        }
        
        // ask b
        if (can_ask) {
            std::cout << "Is this true ? (y/n/?) " << to_demonstrate << "\n";
            char c;
            std::cin >> c;

            if (c == 'y') {
                fact_base.add_fact(to_demonstrate);
                output.set_result(true);
                output.unindent();
                return output;
            }
        }

        output.set_result(false);
        output.unindent();
        return output;
    }
};