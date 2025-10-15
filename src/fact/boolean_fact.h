#pragma once
#include <iostream>
#include "fact.h"

class BooleanFact: public Fact
{
protected:
    bool value;
    std::ostream& cout(std::ostream& os) const override;
public:
    BooleanFact(const std::string& variable, bool value);
    
    virtual bool get_value() const;
    Type get_type() const override;

    virtual bool validate(const std::shared_ptr<Fact> fact) const override;
    virtual bool contradict(const std::shared_ptr<Fact> fact) const override;
};