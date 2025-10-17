#include "text_fact.h"

TextFact::TextFact(const std::string& variable, const std::string& value, bool equal):
    Fact(variable), value(value), equal(equal) {}

const std::string& TextFact::get_value() const { return value; }
Fact::Type TextFact::get_type() const { return Type::Text; }
std::ostream& TextFact::cout(std::ostream& os) const {
    os << variable;
    if (equal) os << " = ";
    else       os << " != ";
    return os << value;
}

bool TextFact::validate(const std::shared_ptr<Fact> fact) const {
    if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
    
    const std::shared_ptr<TextFact> casted = std::dynamic_pointer_cast<TextFact>(fact);
    if (casted->equal) return equal && casted->get_value() == get_value();
    if (equal) return casted->get_value() != get_value();
    return casted->get_value() == get_value();
}
bool TextFact::contradict(const std::shared_ptr<Fact> fact) const {
    if (fact->get_type() != get_type() || fact->get_name() != get_name()) return false;
    
    const std::shared_ptr<TextFact> casted = std::dynamic_pointer_cast<TextFact>(fact);
    if (casted->equal) return equal && casted->get_value() != get_value();
    if (equal) return casted->get_value() == get_value();
    return false;
}

bool TextFact::operator==(const Fact& fact) const {
    return (this->get_type() == fact.get_type() &&
            this->get_name() == fact.get_name() &&
            this->value == dynamic_cast<const TextFact &>(fact).value &&
            this->equal == dynamic_cast<const TextFact &>(fact).equal);
}
