#pragma once
#include <iostream>
#include "fact.h"
#include "../utils/fact_factory.h"

/// @brief Class that represents a numeric fact (either known or in rule antecedents and consequents)
class NumericFact: public Fact
{
protected:
    double value; /*!< the value of the variable concerned by the fact */
    FactFactory::Operator op; /*!< the operator used by the fact */
    std::ostream& cout(std::ostream& os) const override;
public:
    /// @brief Creates a numeric fact describing a variable value with an operator
    /// @param variable the name of the concerned variable
    /// @param value the value used to describe the variable
    /// @param op the operator used to describe the variable
    NumericFact(const std::string& variable, double value, FactFactory::Operator op = FactFactory::Operator::Equal);
    
    /// @brief Returns the value describing the variable
    /// @return the value describing the variable
    double get_value() const;
    
    /// @brief Returns the operator describing the variable
    /// @return the operator describing the variable
    FactFactory::Operator get_operator() const;
    /// @brief Returns the type of the fact (Numeric)
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
