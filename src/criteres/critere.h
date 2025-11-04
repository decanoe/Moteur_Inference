#pragma once
#include <vector>
#include "../rule.h"

class Critere {
    private:
    public:
    
        /**
         * @brief Compares two rules according to the criterion
         * @param r1 the first rule
         * @param r2 the second rule
         * @return true if r2 is better than r1 according to the criterion, false otherwise
         */
        virtual bool betterThan(std::shared_ptr<Rule> r1, std::shared_ptr<Rule> r2) = 0;
};