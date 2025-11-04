#pragma once
#include <iostream>
#include <vector>

class BackwardChainingOutput
{
    struct Line
    {
        std::string text;
        int indent_level;
        bool last;
    };
    
    std::vector<Line> lines;
    int indent_level;
    bool proof;
public:
    BackwardChainingOutput();
    BackwardChainingOutput(const BackwardChainingOutput&);

    void add(const std::string& text);
    void indent();
    void unindent();

    void set_result(bool proof_result);
    operator bool() const;

    friend std::ostream& operator<<(std::ostream& os, const BackwardChainingOutput& output);
};

std::ostream& operator<<(std::ostream& os, const BackwardChainingOutput& output);