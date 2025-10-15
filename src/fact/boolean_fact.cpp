#include "boolean_fact.h"

BooleanFact::BooleanFact(const std::string& variable, bool value):
    Fact(variable), value(value) {}

bool BooleanFact::get_value() const { return value; }
Fact::Type BooleanFact::get_type() const { return Type::Boolean; }
std::ostream& BooleanFact::cout(std::ostream& os) const {
    if (!value) os << "-";
    return os << variable;
}

bool BooleanFact::validate(const std::shared_ptr<Fact> fact) const {
    if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
    
    const std::shared_ptr<BooleanFact> casted = std::dynamic_pointer_cast<BooleanFact>(fact);
    return casted->get_value() == get_value();
}
bool BooleanFact::contradict(const std::shared_ptr<Fact> fact) const {
    if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
    
    const std::shared_ptr<BooleanFact> casted = std::dynamic_pointer_cast<BooleanFact>(fact);
    return casted->get_value() != get_value();
}
