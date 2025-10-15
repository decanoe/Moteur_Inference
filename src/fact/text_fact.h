#pragma once
#include <iostream>
#include "fact.h"

/// @brief Class that represents a text fact (either known or in rule antecedents and consequents)
class TextFact: public Fact
{
protected:
    std::string value; /*!< the value of the variable concerned by the fact */
    bool equal; /*!< is the variable equal or not equal to the value */
    std::ostream& cout(std::ostream& os) const override;
public:
    /// @brief Creates a text fact describing a variable value
    /// @param variable the name of the concerned variable
    /// @param value the value used to describe the variable
    /// @param equal a boolean at true if the variable has this value (false else)
    TextFact(const std::string& variable, const std::string& value, bool equal);
    
    /// @brief Returns the value describing the variable
    /// @return the value describing the variable
    virtual const std::string& get_value() const;
    /// @brief Returns the type of the fact (Text)
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
};
