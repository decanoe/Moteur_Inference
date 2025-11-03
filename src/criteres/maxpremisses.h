#include "criteres/critere.h"

class MaxPremisses : public Critere
{
    public:
        int choseRule(std::vector<std::shared_ptr<Rule>> rules) override
        {
            int index = -1;
            int max_premisses = 0;
            for (int i = 0; i < rules.size(); ++i)
            {
                int premisses_count = rules[i]->get_antecedents().size();
                if (premisses_count > max_premisses)
                {
                    max_premisses = premisses_count;
                    index = static_cast<int>(i);
                }
            }
            return index;
        }
}