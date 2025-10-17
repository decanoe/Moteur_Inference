#pragma once
#include <iostream>
#include "fact.h"

/// @brief Class that represents a boolean fact (either known or in rule antecedents and consequents)
class BooleanFact: public Fact
{
protected:
    bool value; /*!< the value of the variable concerned by the fact */
    std::ostream& cout(std::ostream& os) const override;
public:
    /// @brief Creates a boolean fact giving a boolean value to a variable
    /// @param variable the name of the concerned variable
    /// @param value the value of the concerned variable
    BooleanFact(const std::string& variable, bool value);
    
    /// @brief Returns the value given by this fact to its variable
    /// @return the value of the fact variable
    virtual bool get_value() const;
    /// @brief Returns the type of the fact (Boolean)
    /// @return the type of the fact
    Type get_type() const override;

    /// @brief Can the given fact be deduced by this one
    /// @param fact a shared ptr to the given fact
    /// @return Returns true if the given fact can be deduced by this one, false else
    virtual bool validate(const std::shared_ptr<Fact> fact) const override;
    /// @brief Does this fact contradict the given one
    /// @param fact a shared ptr to the given fact
    /// @return Returns true if the given fact cannot be true at the same time as this one, false else
    virtual bool contradict(const std::shared_ptr<Fact> fact) const override;

    bool operator==(const Fact& fact) const override;
};