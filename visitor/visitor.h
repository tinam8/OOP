#include <iostream>
#include <cstdlib>
#include <list>
#include <map>
#include <string>
#include  <ctime>
#include <vector>
#include <string>         // std::string
#include <cstddef>        // std::size_t
#include <memory>
#include <fstream>
#include <istream>

class PlainText;
class BoldText;
class Hyperlink;

struct Visitor{
	virtual void visitPlainText(PlainText *) = 0;
	virtual void visitBoldText(BoldText *) = 0;
	virtual void visitHyperlink(Hyperlink *) = 0;
};

struct Visitable{
	virtual void accept(Visitor *) = 0;
	virtual ~Visitable() {}
};

class DocumentPart{
public:
    std::string text();
    void setText(std::string);
    virtual void accept(Visitor *){}
   virtual void setHref(std::string){}
   virtual ~DocumentPart(){}
private:
    std::string _text;
};

class PlainText : public DocumentPart, public Visitable {
public:
    virtual void accept(Visitor *v){ v->visitPlainText(this); }
};

class BoldText : public DocumentPart, public Visitable {
public:
    virtual void accept(Visitor *v){ v->visitBoldText(this); }
};

class Hyperlink : public DocumentPart, public Visitable {
public:
    virtual void accept(Visitor *v){ v->visitHyperlink(this); }
    std::string href();
    void setHref(std::string);
private:
    std::string _href;
};


class HtmlVisitor : public Visitor {
    void visitPlainText(PlainText *);
    void visitBoldText(BoldText *);
	void visitHyperlink(Hyperlink *);
};

class LatexVisitor : public Visitor {
    void visitPlainText(PlainText *);
    void visitBoldText(BoldText *);
	void visitHyperlink(Hyperlink *);
};


class Document{
  public:
  typedef std::unique_ptr<DocumentPart> PTR;
  typedef std::list<PTR>::iterator  iterator;

  void readLatex(std::ifstream & in);

  iterator begin() {return m_text.begin();}
  iterator end() {return m_text.end(); }

  private:
  std::string createCorrectDocumentPart(std::string);
  std::list<PTR> m_text;
  friend std::string Read(std::ifstream &in);
};

std::string Read(std::ifstream &in);
