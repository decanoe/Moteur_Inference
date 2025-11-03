#include "critere.h"

class MaxPremisses : public Critere
{
public:
    bool betterThan(std::shared_ptr<Rule> r1, std::shared_ptr<Rule> r2) override
    {
        if (r1 == nullptr) {
            return false;
        }
        if (r1->get_antecedents().size() >= r2->get_antecedents().size()) 
            return true;
        else
            return false;
    }
};