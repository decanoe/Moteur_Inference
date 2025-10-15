#pragma once
#include <iostream>

namespace Cout
{
    enum Color { Default, Red, Green, Yellow, Blue, Magenta, Cyan, Gray };

    std::ostream& err(Color col = Color::Red);
    std::ostream& out(Color col = Color::Default);
    std::ostream& end(std::ostream& c);
    std::ostream& endl(std::ostream& c);
};
