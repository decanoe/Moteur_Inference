#include "./backwardChainingOutput.h"

BackwardChainingOutput::BackwardChainingOutput(): lines(), indent_level(), proof(false) {}
BackwardChainingOutput::BackwardChainingOutput(const BackwardChainingOutput& other):
    lines(other.lines), indent_level(other.indent_level), proof(other.proof) {}

void BackwardChainingOutput::add(const std::string& text) {
    lines.push_back((BackwardChainingOutput::Line) {text, indent_level, true});
    for (auto iter = std::next(lines.rbegin()); iter < lines.rend(); iter++)
    {
        if ((*iter).indent_level < indent_level) break;
        if ((*iter).indent_level == indent_level) (*iter).last = false;
    }
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
    std::vector<bool> has_next = std::vector<bool>();
    for (int i = 0; i < output.lines.size(); i++)
    {
        int current_level = output.lines[i].indent_level;
        while (current_level >= has_next.size()) has_next.push_back(false);

        has_next[current_level] = true;
        
        for (int j = 1; j < current_level; j++)
        {
            if (has_next[j]) os << " │ ";
            else os << "   ";
        }
        if (current_level != 0) {
            has_next[current_level] = !output.lines[i].last;

            if (has_next[current_level]) os << " ├─";
            else os << " └─";
        }
        
        os << " " << output.lines[i].text << "\n";
    }
    return os;
}