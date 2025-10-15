#include <iostream>
#include <vector>

#include "fact_base.h"
#include "utils/cout.h"

void show_help() {
    std::ostream& c = Cout::out(Cout::Cyan);
    c << "Usage: ./moteur_inference <rule_base_path> <fact_base_path> [options]\n";
    c << "Options are:\n";

    c << "\t-help or -h\tto access this text\n";
    Cout::end(c);
}

int main(int argc, char *argv[]) {
    std::vector<std::string> arguments(argv, argv+argc);
    arguments.erase(arguments.begin());
    
    if (arguments.size() < 2 || (arguments[0] == "-help" || arguments[0] == "-h")) {
        bool help = (arguments.size() >= 1) && (arguments[0] == "-help" || arguments[0] == "-h");
        if (!help) Cout::end(Cout::err() << "Some arguments are missing !\n");
        show_help();
        return !help;
    }

    try
    {
        FactBase fact_base = FactBase();
        fact_base.add_file(arguments[1]);

        std::cout << fact_base << "\n";
    }
    catch(const std::exception& e)
    {
        Cout::endl(Cout::err(Cout::Red) << e.what());
        return 1;
    }
    
    return 0;
}