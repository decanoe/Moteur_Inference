#pragma once
#include <vector>
#include "rule.h"

class Critere {
    private:
    public:
        virtual int choseRule(std::vector<std::shared_ptr<Rule>> rules) = 0;
}