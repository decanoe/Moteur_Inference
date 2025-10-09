#include <iostream>
#include "fact.h"

class BooleanFact: public Fact
{
protected:
    bool value;
public:
    BooleanFact(const std::string& variable, bool value):
        Fact(variable), value(value) {}
    
    virtual bool get_value() const { return value; }
    Type get_type() const override { return Type::Boolean; }

    virtual bool validate(const std::shared_ptr<Fact> fact) const override {
        if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
        
        const std::shared_ptr<BooleanFact> casted = std::dynamic_pointer_cast<BooleanFact>(fact);
        return casted->get_value() == get_value();
    }
    virtual bool contradict(const std::shared_ptr<Fact> fact) const override {
        if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
        
        const std::shared_ptr<BooleanFact> casted = std::dynamic_pointer_cast<BooleanFact>(fact);
        return casted->get_value() != get_value();
    }
};
