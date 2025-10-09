#include <iostream>
#include <vector>
#include "fact/fact.h"

class Rule {
private:
    std::string name;
    std::vector<Fact> antecedent;
    std::vector<Fact> consequent;
public:
    Rule(const std::string& name, const std::vector<Fact>& antecedent, const std::vector<Fact>& consequent):
        name(name), antecedent(antecedent), consequent(consequent) {}
};