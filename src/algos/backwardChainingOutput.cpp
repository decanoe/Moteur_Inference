#include "./backwardChainingOutput.h"

BackwardChainingOutput::BackwardChainingOutput(): lines(), indent_level(), proof(false) {}
BackwardChainingOutput::BackwardChainingOutput(const BackwardChainingOutput& other):
    lines(other.lines), indent_level(other.indent_level), proof(other.proof) {}

void BackwardChainingOutput::add(const std::string& text) {
    lines.push_back((BackwardChainingOutput::Line) {text, indent_level});
}
void BackwardChainingOutput::indent() {
    indent_level++;
}
void BackwardChainingOutput::unindent() {
    if (indent_level != 0) indent_level--;
}
void BackwardChainingOutput::set_result(bool proof_result) {
    this->proof = proof_result;
}
BackwardChainingOutput::operator bool() const {
    return proof;
}



std::ostream& operator<<(std::ostream& os, const BackwardChainingOutput& output) {
    for (int i = 0; i < output.lines.size(); i++)
    {
        int current_level = output.lines[i].indent_level;

        
        for (int j = 1; j < current_level; j++)
        {
            os << " │ ";
        }
        if (current_level != 0) {
            os << " ├─";
            // else os << " └─";
        }
        
        os << " " << output.lines[i].text << "\n";
    }
    return os;
}