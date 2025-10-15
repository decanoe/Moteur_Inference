#include "cout.h"

std::ostream& Cout::err(Color col) {
    if (col == Default) return std::cerr << "\033[1m";
    return std::cerr << "\033[1;" + std::to_string(30 + col) + "m";
}
std::ostream& Cout::out(Color col) {
    if (col == Default) return std::cerr;
    return std::cerr << "\033[" + std::to_string(30 + col) + "m";
}
std::ostream& Cout::end(std::ostream& c) { return c << "\033[0m"; }
std::ostream& Cout::endl(std::ostream& c) { return c << "\033[0m\n"; }
