#pragma once
#include <iostream>

/// @brief collection of function used to modify the standard std::cout and std::cerr
namespace Cout
{
    /// @brief An enum containing colors for text output
    enum Color { Default, Red, Green, Yellow, Blue, Magenta, Cyan, Gray };
    
    /// @brief returns the standard error output with bold text and the text color set to the wanted one
    /// @return std::cerr
    std::ostream& err(Color col = Color::Red);
    /// @brief returns the standard output with the text color set to the wanted one
    /// @return std::cout
    std::ostream& out(Color col = Color::Default);
    /// @brief adds a text color and style reset to the wanted std::ostream
    std::ostream& end(std::ostream& c);
    /// @brief adds a text color and style reset to the wanted std::ostream as well as a line break
    std::ostream& endl(std::ostream& c);
};
