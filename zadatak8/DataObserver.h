#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <list>
#include <map>
#include <string>
#include  <ctime>
#include <vector>
#include  <sys/stat.h>

 class Subject;
// Design pattern: Observer
///Apstraktna bazna klasa za konkretne Promatrače.
class Observer{
public:
	/** Svaki konkretni Promatrač mora implementirati update().
	 *  Ovdje update() uzima pokazivač na Subjekt radi identifikacije Subjekta.
	 *  Tako jedan Promatrač može pratiti više Subjekata.
	 */
	virtual void update(Subject*,std::string) = 0;
	virtual void update(Subject*) = 0;
	virtual ~Observer() {}
};
// Design pattern: Observer.
///  Bazna klasa za konkretne Subjekte.
class Subject{
public:
	// Dodaj pokazivač na zainteresiranog Promatrača. */
	virtual void attach(Observer * o);
	// Ukloni pokazivač na Promatrača. */
	virtual void dettach(Observer * o);
	// Obavijesti sve Promatrače o promjeni Subjekta. */
	virtual void notify();
	virtual ~Subject() {}
protected:
    // Lista pokazivača na Promatrače zainteresirane za Subjekt.
	std::list<Observer*> m_observers;
protected:
	typedef std::list<Observer*>::iterator iterator;
};

class IsFileModified{
public:
    IsFileModified(std::string name){
        m_fileName = name;
    }
    time_t getLastModificationTime();
private:
    std::string m_fileName;

};

///konkretan subjekt
class Concentrations : public Subject, private IsFileModified{
public:
	Concentrations ( std::string name) ;
    std::map< std::string, std::vector<int> >get() const;
    // Obavijesti sve Promatrače o promjeni Subjekta. */
	void notify();

	void setState();
private:
    std::map< std::string, std::vector<int> > data;
    time_t lastReading;
    void readData( std::string name);
    std::string name;
    std::string isOutOfBounds();
};

///konkretan promatrač
class DisplayData : public Observer{
public:

	DisplayData(Concentrations * p) : conc(p) {conc->attach(this); }

    // Prerađeni update(). Identificira Subjekt i ignorira sve osimonog kod kojeg je logiran.
    virtual void update(Subject* ps);
    virtual void update(Subject* ps, std::string substance);

private:
    /** Pokazivač na konkretni Subjekt. */
	Concentrations * conc;
};

///konkretan promatrač
class DataAlert : public Observer{
public:

	DataAlert(Concentrations * p) : conc(p) {conc->attach(this); }
    // Prerađeni update(). Identificira Subjekt i ignorira sve osimonog kod kojeg je logiran.
    virtual void update(Subject* p);
    virtual void update(Subject* ps, std::string substance);

private:
    /** Pokazivač na konkretni Subjekt. */
	Concentrations * conc;
};



