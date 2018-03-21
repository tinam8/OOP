#include <iostream>
#include <cstdlib>
#include <fstream>

#include "visitor.h"

int main() {
    Document document;
    std::ifstream in("text.tex");
    document.readLatex(in);

    HtmlVisitor hv;
    for(Document::iterator it = document.begin(); it != document.end(); ++it)
           (*it)->accept(&hv);
    std::cout << std::endl;

    LatexVisitor lv;
    for(Document::iterator it = document.begin(); it != document.end(); ++it)
           (*it)->accept(&lv);
    std::cout << std::endl;

    return 0;
}
