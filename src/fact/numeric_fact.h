#pragma once
#include <iostream>
#include "fact.h"
#include "../utils/fact_factory.h"

class NumericFact: public Fact
{
protected:
    double value;
    FactFactory::Operator op;
    std::ostream& cout(std::ostream& os) const override;
public:
    NumericFact(const std::string& variable, double value, FactFactory::Operator op = FactFactory::Operator::Equal);
    
    double get_value() const;
    FactFactory::Operator get_operator() const;
    Type get_type() const override;

    virtual bool validate(const std::shared_ptr<Fact> fact) const override;
    virtual bool contradict(const std::shared_ptr<Fact> fact) const override;
};
