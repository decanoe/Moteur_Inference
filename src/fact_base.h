#pragma once
#include <iostream>
#include <fstream>

#include "exception/syntax_exception.h"

#include "utils/fact_factory.h"
#include "fact/fact.h"

class FactBase {
private:
    std::vector<std::shared_ptr<Fact>> facts;

    std::ostream& cout(std::ostream& os) const {
        os << "[\n";
        for (auto fact : facts)
        {
            os << "\t" << fact << "\n";
        }
        os << "]";
        
        return os;
    }
public:
    FactBase():
        facts() {}
    FactBase(const std::vector<std::shared_ptr<Fact>>& facts):
        facts(facts) {}
    FactBase(const FactBase& fact) = delete;
    
    FactBase& add_fact(std::shared_ptr<Fact> fact) {
        this->facts.push_back(fact);
        return *this;
    }
    FactBase& add_file(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::invalid_argument("cannot open file at path \"" + path + "\"");
        }

        int line_count = 0;
        std::string line;
        while (std::getline(file, line))
        {
            line_count++;
            std::shared_ptr<Fact> fact = FactFactory::read_file_fact(line, line_count, path);
            if (fact != nullptr) add_fact(fact);
        }
        file.close();

        return *this;
    }
    const std::vector<std::shared_ptr<Fact>>& get_facts() const { return facts; }
    
    friend std::ostream& operator<<(std::ostream &os, const FactBase& fact_base);
};

std::ostream& operator<<(std::ostream& os, const FactBase& fact_base) {
    return fact_base.cout(os);
}