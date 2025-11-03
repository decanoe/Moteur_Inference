#pragma once
#include <vector>
#include "../rule.h"

class Critere {
    private:
    public:
        virtual bool betterThan(std::shared_ptr<Rule> r1, std::shared_ptr<Rule> r2) = 0;
};