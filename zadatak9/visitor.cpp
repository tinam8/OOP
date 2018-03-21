#include "visitor.h"

std::string DocumentPart::text(){
    return _text;
}

void DocumentPart::setText(std::string text){
    _text = text;
}

std::string Hyperlink::href(){
    return _href;
}

void Hyperlink::setHref(std::string href){
    _href = href;
}

void HtmlVisitor::visitPlainText(PlainText *text){
    std::cout << text->text();
}

void HtmlVisitor::visitBoldText(BoldText *text){
    std::cout << "<b>" << text->text() << "</b>";
}

void HtmlVisitor::visitHyperlink(Hyperlink *text){
    std::cout << "<a href=\"" << text->href() << "\">" << text->text() << "</a>";
}

void LatexVisitor::visitPlainText(PlainText *text){
    std::cout << text->text();
}

void LatexVisitor::visitBoldText(BoldText *text){
    std::cout << "\\textbf{" << text->text() << "}";
}

void LatexVisitor::visitHyperlink(Hyperlink *text){
    std::cout << "\\href{" << text->href() << "}{" << text->text() << "}";
}



void Document::readLatex(std::istream & in){
    std::string str = " ";
    std::size_t found;

    while (in.is_open() && !str.empty()) {
        std::getline(in, str);
        while(!str.empty()){
            found = str.find_first_of("\\");
                if (found != std::string::npos){
                    PTR ptr;
                    ptr.reset(new PlainText);
                    ptr.get()->setText(str);
                    m_text.push_back(ptr);
                }
                else{
                    std::unique_ptr<PlainText> ptr;
                    ptr.reset(new PlainText);
                    ptr.get()->setText( str.substr(0,found) );
                    m_text.push_back(ptr);
                    str = str.substr(found+1, str.size()-found);
                    createCorrectDocumentPart(str,in);

                }
        }
    }

    in.close();
}

std::string Document::createCorrectDocumentPart(std::string str,std::istream & in){
    std::size_t found;
    std::string pom;

    found = str.find_first_of("textbf{");

    int textbfSize = 7;
    int hrefSize = 5;
    if(found == 0){
        str = str.substr(textbfSize,str.size()-textbfSize);
        found = str.find_first_of("}");
        while(found != std::string::npos){
           std::getline(in, pom);
           str += pom;
           found = str.find_first_of("}");
        }
        std::unique_ptr<BoldText> ptr;
        ptr.reset(new BoldText);
        ptr.get()->setText( str.substr(0,found) );
        m_text.push_back(ptr);
    } else {
        str = str.substr(hrefSize,str.size()-hrefSize);
        found = str.find_first_of("}{");
        while(found != std::string::npos){
           std::getline(in, pom);
           str += pom;
           found = str.find_first_of("}{");
        }
        std::unique_ptr<BoldText> ptr;
        ptr.reset(new BoldText);
        ptr.get()->setHref(str.substr(0,found));
        str = str.substr(found+2, str.size()-found-2);
        found = str.find_first_of("}");
        while(found != std::string::npos){
           std::getline(in, pom);
           str += pom;
           found = str.find_first_of("}");
        }
        ptr.get()->setText( str.substr(0,found) );
        m_text.push_back(ptr);
    }
    return str.substr(found+1, str.size()-found-1);



}
