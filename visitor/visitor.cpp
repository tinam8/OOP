
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

std::string Document::createCorrectDocumentPart(std::string str){
    std::size_t found_pos;
    std::string pom;

    found_pos = str.find_first_of("textbf{");

    int textbfSize = 7;
    int hrefSize = 5;
    if(found_pos == 0){
        str = str.substr(textbfSize,str.size()-textbfSize);
        found_pos = str.find_first_of("}"); //uvijek ima kraj
        std::unique_ptr<BoldText> ptr;
        ptr.reset(new BoldText());
        ptr.get()->setText( str.substr(0,found_pos) );
        m_text.push_back(std::move(ptr));
    } else {
        str = str.substr(hrefSize,str.size()-hrefSize);
        found_pos = str.find_first_of("}{");
        PTR ptr;
        ptr.reset(new Hyperlink());
        ptr.get()->setHref(str.substr(0,found_pos));
        str = str.substr(found_pos+2, str.size()-found_pos-2);
        found_pos = str.find_first_of("}");
        ptr.get()->setText( str.substr(0,found_pos) );
        m_text.push_back(std::move(ptr));
    }
    return str.substr(found_pos+1, str.size()-found_pos-1);

}

std::string Read(std::ifstream &in){
    //std::cout << "funkcija" << std::endl;
    std::string temp = "hxjkdg", str = "";
    while(!temp.empty()) {
      std::getline(in,temp);
      str += temp + "\n";
    }
    //std::cout << "string: " << str << std::endl;
    return str;
}

void Document::readLatex(std::ifstream & in){
    std::string str = Read(in);
    std::cout << "string: " << str << std::endl;
    std::size_t found_pos;

    while (in.is_open() && !str.empty()) {
        found_pos = str.find_first_of("\\");
            if (found_pos == std::string::npos){
                PTR ptr;
                ptr.reset(new PlainText);
                ptr.get()->setText(str);
                m_text.push_back(std::move(ptr));
                str.clear();
            }
            else{
                PTR ptr;
                ptr.reset(new PlainText);
                ptr.get()->setText( str.substr(0,found_pos) );
                m_text.push_back(std::move(ptr));
                str = str.substr(found_pos+1, str.size()-found_pos-1);
                str = createCorrectDocumentPart(str);
            }

    }

    in.close();
}

