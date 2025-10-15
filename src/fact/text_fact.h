#pragma once
#include <iostream>
#include "fact.h"

class TextFact: public Fact
{
protected:
    std::string value;
    bool equal;
    std::ostream& cout(std::ostream& os) const override;
public:
    TextFact(const std::string& variable, const std::string& value, bool equal);
    
    virtual const std::string& get_value() const;
    Type get_type() const override;

    virtual bool validate(const std::shared_ptr<Fact> fact) const override;
    virtual bool contradict(const std::shared_ptr<Fact> fact) const override;
};
