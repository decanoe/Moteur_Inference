// #pragma once
// #include "inferenceSolver.h"

// class BackwardChaining : public InferenceSolver
// {
// public:
//     void run(RuleBase& rule_base, FactBase& fact_base, std::shared_ptr<Fact> goal) override
//     {
//         if (demonstrate(goal, rule_base, fact_base)) {
//             std::cout << "proof";
//         }
//         else {
//             std::cout << "no proof";
//         }
//     }
//     bool demonstrate(std::shared_ptr<Fact> to_demonstrate, RuleBase& rule_base, FactBase& fact_base, int indent = 0) const {
//         // fact already in fact_base
//         if (fact_base.contains_fact(to_demonstrate)) {
//             fact_base.add_fact(to_demonstrate);
//             return true;
//         }
        
//         // search a demo for b
//         bool can_ask = true;
//         for (auto it_rules = rule_base.begin(); it_rules != rule_base.end(); it_rules++)
//         {
//             if (!(*it_rules)->contains_consequent(to_demonstrate)) continue;
//             can_ask = false;

//             // RuleBase rule_base_copy = rule_base.copy();
//             // FactBase fact_base_copy = fact_base.copy();
            
//             for (size_t i = 0; i < indent; i++)
//             {
//                 std::cout << "\t";
//             }
//             std::cout << "trying rule " << (*it_rules) << "\n";

//             bool end = true;
//             for (auto fact : (*it_rules)->get_antecedents()) {
//                 if (!demonstrate(fact, rule_base_copy, fact_base_copy, indent + 1)) {
//                     end = false;
//                     break;
//                 }
//             }
//             if (end) {
//                 fact_base.add_fact(to_demonstrate);
//                 return true;
//             }
//         }
        
//         // ask b
//         if (can_ask) {
//             std::cout << "Is this true ? (y/n/?) " << to_demonstrate << "\n";
//             char c;
//             std::cin >> c;

//             if (c == 'y') {
//                 fact_base.add_fact(to_demonstrate);
//                 return true;
//             }
//         }

//         return false;
//     }
// };