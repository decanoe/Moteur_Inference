#include "critere.h"

class RecentPremisses : public Critere
{
private:
    FactBase& factbase;
public:
    RecentPremisses(FactBase& factbase) : factbase(factbase) {}
    bool betterThan(std::shared_ptr<Rule> r1, std::shared_ptr<Rule> r2) override
    {
        if (r1 == nullptr) {
            return false;
        }
        if (getScore(r2) > getScore(r1)) 
            return true;
        else
            return false;
    }

    int getScore (std::shared_ptr<Rule> r) {
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

};