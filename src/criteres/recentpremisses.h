#include "critere.h"

class RecentPremisses : public Critere
{
public:
    bool betterThan(std::shared_ptr<Rule> r1, std::shared_ptr<Rule> r2, FactBase& factbase) override
    {
        if (r1 == nullptr) {
            return false;
        }
        if (getScore(r2, factbase) > getScore(r1, factbase)) 
            return true;
        else
            return false;
    }

    int getScore (std::shared_ptr<Rule> r, FactBase& factbase) {
        int score = 0;
        if (r->ruleValidated(factbase)) {
            for (auto antecedent : r->get_antecedents()) {
                for (int i = 0; i < factbase.get_facts().size(); i++) {
                    if (*factbase.get_facts()[i] == *antecedent) {
                        score += factbase.get_facts().size() - i;
                    }
                }
            }
        }
        std::cout << "Score pour la regle " << *r << " : " << score << std::endl;
        return score;
    }

    std::string toString() const override
    {
        return "RecentPremisses criterion";
    }
};