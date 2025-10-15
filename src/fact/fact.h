#pragma once
#include <iostream>
#include <memory>

/// @brief Class that represents a fact (either known or in rule antecedents and consequents)
class Fact
{
protected:
    std::string variable; /*!< the name of the variable concerned by the fact */

    virtual std::ostream& cout(std::ostream& os) const;
public:
    /// @brief Creates a fact concerning a specific variable
    /// @param variable the name of the concerned variable
    Fact(const std::string& variable);
    Fact(const Fact& fact) = delete;
    virtual ~Fact();
    
    /// @brief Returns the name of the fact variable
    /// @return the name of the fact variable
    const std::string& get_name() const;
    /// @brief A type enum for the facts
    enum Type { Boolean, Numeric, Text };
    /// @brief Returns the type of the fact (Boolean, Numeric or Text)
    /// @return the type of the fact
    virtual Type get_type() const;

    /// @brief Can the given fact be deduced by this one
    /// @param fact a shared ptr to the given fact
    /// @return Returns true if the given fact can be deduced by this one, false else
    virtual bool validate(const std::shared_ptr<Fact> fact) const;

    /// @brief Does this fact contradict the given one
    /// @param fact a shared ptr to the given fact
    /// @return Returns true if the given fact cannot be true at the same time as this one, false else
    virtual bool contradict(const std::shared_ptr<Fact> fact) const;

    friend std::ostream& operator<<(std::ostream &os, const Fact& fact);
    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Fact> fact);
};

std::ostream& operator<<(std::ostream& os, const Fact& fact);
std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Fact> fact);