#include <iostream>
#include "fact.h"

class NumericFact: public Fact
{
public:
    enum Operator { Equal, Greater, Lower, GreaterEqual, LowerEqual, NotEqual };
protected:
    double value;
    Operator op;
public:
    enum Operator { Equal, Greater, Lower, GreaterEqual, LowerEqual, NotEqual };
    NumericFact(const std::string& variable, double value, Operator op = Operator::Equal):
        Fact(variable), value(value), op(op) {}
    
    double get_value() const { return value; }
    Operator get_operator() const { return op; }
    Type get_type() const override { return Type::Numeric; }

    virtual bool validate(const std::shared_ptr<Fact> fact) const override {
        if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
        
        const std::shared_ptr<NumericFact> casted = std::dynamic_pointer_cast<NumericFact>(fact);

        switch (casted->get_operator())
        {
        case Operator::Equal:
            return get_operator() == Operator::Equal && get_value() == casted->get_value();
        case Operator::NotEqual:
            return (get_operator() == Operator::Equal && get_value() != casted->get_value())
                || (get_operator() == Operator::NotEqual && get_value() == casted->get_value())
                || (get_operator() == Operator::Greater && get_value() >= casted->get_value())
                || (get_operator() == Operator::Lower && get_value() <= casted->get_value())
                || (get_operator() == Operator::GreaterEqual && get_value() > casted->get_value())
                || (get_operator() == Operator::LowerEqual && get_value() < casted->get_value());
        case Operator::Greater:
            return (get_operator() == Operator::Equal && get_value() > casted->get_value())
                || (get_operator() == Operator::Greater && get_value() >= casted->get_value())
                || (get_operator() == Operator::GreaterEqual && get_value() > casted->get_value());
        case Operator::Lower:
            return (get_operator() == Operator::Equal && get_value() < casted->get_value())
                || (get_operator() == Operator::Lower && get_value() <= casted->get_value())
                || (get_operator() == Operator::LowerEqual && get_value() < casted->get_value());
        case Operator::GreaterEqual:
            return (get_operator() == Operator::Equal && get_value() >= casted->get_value())
                || (get_operator() == Operator::Greater && get_value() > casted->get_value())
                || (get_operator() == Operator::GreaterEqual && get_value() >= casted->get_value());
        case Operator::LowerEqual:
            return (get_operator() == Operator::Equal && get_value() <= casted->get_value())
                || (get_operator() == Operator::Lower && get_value() < casted->get_value())
                || (get_operator() == Operator::LowerEqual && get_value() <= casted->get_value());
        default:
            return false;
        }
    }
    virtual bool contradict(const std::shared_ptr<Fact> fact) const override {
        if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
        
        const std::shared_ptr<NumericFact> casted = std::dynamic_pointer_cast<NumericFact>(fact);

        switch (casted->get_operator())
        {
        case Operator::Equal:
            return (get_operator() == Operator::Equal && get_value() != casted->get_value())
                || (get_operator() == Operator::NotEqual && get_value() == casted->get_value())
                || (get_operator() == Operator::Greater && get_value() >= casted->get_value())
                || (get_operator() == Operator::Lower && get_value() <= casted->get_value())
                || (get_operator() == Operator::GreaterEqual && get_value() > casted->get_value())
                || (get_operator() == Operator::LowerEqual && get_value() < casted->get_value());
        case Operator::NotEqual:
            return (get_operator() == Operator::Equal && get_value() != casted->get_value());
        case Operator::LowerEqual:
            return (get_operator() == Operator::Equal && get_value() > casted->get_value())
                || (get_operator() == Operator::Greater && get_value() >= casted->get_value())
                || (get_operator() == Operator::GreaterEqual && get_value() > casted->get_value());
        case Operator::GreaterEqual:
            return (get_operator() == Operator::Equal && get_value() < casted->get_value())
                || (get_operator() == Operator::Lower && get_value() <= casted->get_value())
                || (get_operator() == Operator::LowerEqual && get_value() < casted->get_value());
        case Operator::Lower:
            return (get_operator() == Operator::Equal && get_value() >= casted->get_value())
                || (get_operator() == Operator::Greater && get_value() > casted->get_value())
                || (get_operator() == Operator::GreaterEqual && get_value() >= casted->get_value());
        case Operator::Greater:
            return (get_operator() == Operator::Equal && get_value() <= casted->get_value())
                || (get_operator() == Operator::Lower && get_value() < casted->get_value())
                || (get_operator() == Operator::LowerEqual && get_value() <= casted->get_value());
        default:
            return false;
        }
    }
};
