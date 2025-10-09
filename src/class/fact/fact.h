#include <iostream>
#include <memory>

class Fact
{
protected:
    std::string variable;
public:
    Fact(const std::string& variable):
        variable(variable) {}
    
    const std::string& get_name() const { return variable; }
    enum Type { Boolean, Numeric, Text };
    virtual Type get_type() const;

    virtual bool validate(const std::shared_ptr<Fact> fact) const {
        return false;
    }
    virtual bool contradict(const std::shared_ptr<Fact> fact) const {
        return false;
    }
};
