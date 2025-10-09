#include <iostream>
#include "fact.h"

class TextFact: public Fact
{
protected:
    std::string value;
public:
    TextFact(const std::string& variable, const std::string& value):
        Fact(variable), value(value) {}
    
    virtual const std::string& get_value() const { return value; }
    Type get_type() const override { return Type::Text; }

    virtual bool validate(const std::shared_ptr<Fact> fact) const override {
        if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
        
        const std::shared_ptr<TextFact> casted = std::dynamic_pointer_cast<TextFact>(fact);
        return casted->get_value() == get_value();
    }
    virtual bool contradict(const std::shared_ptr<Fact> fact) const override {
        if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
        
        const std::shared_ptr<TextFact> casted = std::dynamic_pointer_cast<TextFact>(fact);
        return casted->get_value() != get_value();
    }
};
