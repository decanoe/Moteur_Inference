#include "fact.h"
#include <vector>

Fact::Fact(const std::string& variable): variable(variable) {}
Fact::~Fact() {};

const std::string& Fact::get_name() const { return variable; }
Fact::Type Fact::get_type() const { return Boolean; };
std::ostream& Fact::cout(std::ostream& os) const { return os << variable; }

bool Fact::validate(const std::shared_ptr<Fact> fact) const { return false; }
bool Fact::contradict(const std::shared_ptr<Fact> fact) const { return false; }

bool Fact::findFact (const std::vector<std::shared_ptr<Fact>>& facts) const
    {
        for (const auto& fact : facts)
        {
            if (*fact == *this) {
                return true;
            }
        }
        return false;
    }

std::ostream& operator<<(std::ostream& os, const Fact& fact) {
    return fact.cout(os);
}
std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Fact> fact) {
    return fact->cout(os);
}