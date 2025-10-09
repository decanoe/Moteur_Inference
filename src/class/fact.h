#include <iostream>

class Fact
{
private:
    std::string variable;
public:
    Fact(const std::string& variable):
        variable(variable) {}
    
    virtual bool validate(Fact fact) {
        return false;
    }
    virtual bool contradict(Fact fact) {
        return false;
    }
};
