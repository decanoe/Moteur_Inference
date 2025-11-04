#include <iostream>
#include <vector>

#include "utils/cout.h"
#include "utils/fact_factory.h"
#include "fact_base.h"
#include "rule_base.h"
#include "algos/forwardChaining.h"
#include "algos/backwardChaining.h"
#include "fact/boolean_fact.h"
#include "criteres/maxpremisses.h"

void show_help() {
    std::ostream& c = Cout::out(Cout::Cyan);
    c << "Usage: ./moteur_inference <rule_base_path> <fact_base_path> [options]\n";
    c << "Options are:\n";

    c << "\t-help or -h\tto access this text\n";
    c << "\t-f or -fc\tto use forward chaining\n";
    c << "\t-b or -bc\tto use backward chaining\n";
    c << "\t-max_premisses\tto use the max premisses criteria\n";
    c << "\t-g <fact> or -goal <fact>\tto specify a goal\n";
    Cout::end(c);
}

int main(int argc, char *argv[]) {
    std::vector<std::string> arguments(argv, argv+argc);
    arguments.erase(arguments.begin());
    
    if (arguments.size() < 2 || (arguments[0] == "-help" || arguments[0] == "-h")) {
        bool help = (arguments.size() >= 1) && (arguments[0] == "-help" || arguments[0] == "-h");
        if (!help) Cout::endl(Cout::err() << "Some arguments are missing !");
        show_help();
        return !help;
    }

    std::string algo_param = "None";
    std::string criteria_param = "None";
    std::shared_ptr<Fact> goal = nullptr;
    for (auto iter = arguments.begin(); iter != arguments.end(); iter++)
    {
        if ((*iter) == "-f" || (*iter) == "-fc") {
            if (algo_param == "None") algo_param = "fc";
            else { Cout::endl(Cout::err() << "Two algorithms are specified !"); return 1; }
        }
        else if ((*iter) == "-b" || (*iter) == "-bc") {
            if (algo_param == "None") algo_param = "bc";
            else { Cout::endl(Cout::err() << "Two algorithms are specified !"); return 1; }
        }

        else if ((*iter) == "-max_premisses") {
            if (criteria_param == "None") criteria_param = "max_premisses";
            else { Cout::endl(Cout::err() << "Two criterias are specified !"); return 1; }
        }

        else if ((*iter) == "-g" || (*iter) == "-goal") {
            std::string arg = (*iter);
            iter++;
            if (iter != arguments.end()) {
                try
                {
                    goal = FactFactory::read_file_fact(*iter, 0, "command line");
                }
                catch(const std::exception& e)
                {
                    Cout::endl(Cout::err(Cout::Red) << e.what());
                    Cout::endl(Cout::err() << arg << " must be followed by a valid fact (surrounded by \"\") !"); return 1;
                    return 1;
                }
            }
            else { Cout::endl(Cout::err() << arg << " must be followed by a fact (surrounded by \"\") !"); return 1; }
        }
    }

    if (algo_param == "None") { Cout::end(Cout::err() << "Please specify an algorithm to run (use -help for documentation)\n"); return 1; }

    try
    {
        RuleBase rule_base;
        rule_base.add_file(arguments[0]);
        FactBase fact_base;
        fact_base.add_file(arguments[1]);

        std::shared_ptr<Critere> criteria;
        if (criteria_param == "None") criteria = std::make_shared<MaxPremisses>();
        else if (criteria_param == "max_premisses") criteria = std::make_shared<MaxPremisses>();

        std::shared_ptr<InferenceSolver> solver;
        if (algo_param == "fc") solver = std::make_shared<ForwardChaining>(criteria);
        if (algo_param == "bc") solver = std::make_shared<BackwardChaining>(criteria);

        solver->run(rule_base, fact_base, goal);
    }
    catch(const std::exception& e)
    {
        Cout::endl(Cout::err(Cout::Red) << e.what());
        return 1;
    }
    
    return 0;
}