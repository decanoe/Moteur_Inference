#pragma once
#include <iostream>
#include <memory>

class Fact
{
protected:
    std::string variable;

    virtual std::ostream& cout(std::ostream& os) const;
public:
    Fact(const std::string& variable);
    Fact(const Fact& fact) = delete;
    virtual ~Fact();
    
    const std::string& get_name() const;
    enum Type { Boolean, Numeric, Text };
    virtual Type get_type() const;

    virtual bool validate(const std::shared_ptr<Fact> fact) const;
    virtual bool contradict(const std::shared_ptr<Fact> fact) const;

    friend std::ostream& operator<<(std::ostream &os, const Fact& fact);
    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Fact> fact);
};

std::ostream& operator<<(std::ostream& os, const Fact& fact);
std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Fact> fact);