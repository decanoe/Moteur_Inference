#include "numeric_fact.h"

NumericFact::NumericFact(const std::string& variable, double value, FactFactory::Operator op):
    Fact(variable), value(value), op(op) {}

double NumericFact::get_value() const { return value; }
FactFactory::Operator NumericFact::get_operator() const { return op; }
Fact::Type NumericFact::get_type() const { return Type::Numeric; }
std::ostream& NumericFact::cout(std::ostream& os) const {
    os << variable;
    switch (op)
    {
        case FactFactory::Equal:        os << " = "; break;
        case FactFactory::NotEqual:     os << " != "; break;
        case FactFactory::Greater:      os << " > "; break;
        case FactFactory::Lower:        os << " < "; break;
        case FactFactory::GreaterEqual: os << " >= "; break;
        case FactFactory::LowerEqual:   os << " <= "; break;
    }
    return os << value;
}

bool NumericFact::validate(const std::shared_ptr<Fact> fact) const {
    if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
    
    const std::shared_ptr<NumericFact> casted = std::dynamic_pointer_cast<NumericFact>(fact);

    switch (casted->get_operator())
    {
    case FactFactory::Equal:
        return get_operator() == FactFactory::Equal && get_value() == casted->get_value();
    case FactFactory::NotEqual:
        return (get_operator() == FactFactory::Equal && get_value() != casted->get_value())
            || (get_operator() == FactFactory::NotEqual && get_value() == casted->get_value())
            || (get_operator() == FactFactory::Greater && get_value() >= casted->get_value())
            || (get_operator() == FactFactory::Lower && get_value() <= casted->get_value())
            || (get_operator() == FactFactory::GreaterEqual && get_value() > casted->get_value())
            || (get_operator() == FactFactory::LowerEqual && get_value() < casted->get_value());
    case FactFactory::Greater:
        return (get_operator() == FactFactory::Equal && get_value() > casted->get_value())
            || (get_operator() == FactFactory::Greater && get_value() >= casted->get_value())
            || (get_operator() == FactFactory::GreaterEqual && get_value() > casted->get_value());
    case FactFactory::Lower:
        return (get_operator() == FactFactory::Equal && get_value() < casted->get_value())
            || (get_operator() == FactFactory::Lower && get_value() <= casted->get_value())
            || (get_operator() == FactFactory::LowerEqual && get_value() < casted->get_value());
    case FactFactory::GreaterEqual:
        return (get_operator() == FactFactory::Equal && get_value() >= casted->get_value())
            || (get_operator() == FactFactory::Greater && get_value() > casted->get_value())
            || (get_operator() == FactFactory::GreaterEqual && get_value() >= casted->get_value());
    case FactFactory::LowerEqual:
        return (get_operator() == FactFactory::Equal && get_value() <= casted->get_value())
            || (get_operator() == FactFactory::Lower && get_value() < casted->get_value())
            || (get_operator() == FactFactory::LowerEqual && get_value() <= casted->get_value());
    default:
        return false;
    }
}
bool NumericFact::contradict(const std::shared_ptr<Fact> fact) const {
    if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
    
    const std::shared_ptr<NumericFact> casted = std::dynamic_pointer_cast<NumericFact>(fact);

    switch (casted->get_operator())
    {
    case FactFactory::Equal:
        return (get_operator() == FactFactory::Equal && get_value() != casted->get_value())
            || (get_operator() == FactFactory::NotEqual && get_value() == casted->get_value())
            || (get_operator() == FactFactory::Greater && get_value() >= casted->get_value())
            || (get_operator() == FactFactory::Lower && get_value() <= casted->get_value())
            || (get_operator() == FactFactory::GreaterEqual && get_value() > casted->get_value())
            || (get_operator() == FactFactory::LowerEqual && get_value() < casted->get_value());
    case FactFactory::NotEqual:
        return (get_operator() == FactFactory::Equal && get_value() != casted->get_value());
    case FactFactory::LowerEqual:
        return (get_operator() == FactFactory::Equal && get_value() > casted->get_value())
            || (get_operator() == FactFactory::Greater && get_value() >= casted->get_value())
            || (get_operator() == FactFactory::GreaterEqual && get_value() > casted->get_value());
    case FactFactory::GreaterEqual:
        return (get_operator() == FactFactory::Equal && get_value() < casted->get_value())
            || (get_operator() == FactFactory::Lower && get_value() <= casted->get_value())
            || (get_operator() == FactFactory::LowerEqual && get_value() < casted->get_value());
    case FactFactory::Lower:
        return (get_operator() == FactFactory::Equal && get_value() >= casted->get_value())
            || (get_operator() == FactFactory::Greater && get_value() > casted->get_value())
            || (get_operator() == FactFactory::GreaterEqual && get_value() >= casted->get_value());
    case FactFactory::Greater:
        return (get_operator() == FactFactory::Equal && get_value() <= casted->get_value())
            || (get_operator() == FactFactory::Lower && get_value() < casted->get_value())
            || (get_operator() == FactFactory::LowerEqual && get_value() <= casted->get_value());
    default:
        return false;
    }
}