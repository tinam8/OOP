#include "DataObserver.h"
#include <algorithm>
#include <fstream>

void Subject::attach(Observer* o){
	// Nemoj logirati više puta isti Promatrač
	iterator it = std::find(m_observers.begin(), m_observers.end(), o);
	if(it != m_observers.end())
		throw "Subject:: Observer already attached.";
	m_observers.push_back(o);
}

void Subject::dettach(Observer* o){
	// Eliminiraj promatrač ako je logiran.
	iterator it = std::find(m_observers.begin(), m_observers.end(), o);
	if(it == m_observers.end())
			throw "Subject:: Observer is not attached.";
	m_observers.erase(it);
}

std::string Concentrations::isOutOfBounds(){
        std::map< std::string, std::vector<int> >::iterator it;
        it = data.begin();
        for( ; it != data.end(); ++it){
            if(it->second[0] > it->second[2] || it->second[1] < it->second[2]){
                return it->first;
            }
        }
        return "";
}

void Subject::notify(){
	// Zovi update() na svim promatračima
    iterator it = m_observers.begin();
    for( ; it != m_observers.end(); ++it)
    	(*it)->update(this);
}

void Concentrations::notify(){
    std::string substance = isOutOfBounds();
	// Zovi update() na svim promatračima
    iterator it = m_observers.begin();
    for( ; it != m_observers.end(); ++it){
        if (DataAlert * p = dynamic_cast<DataAlert*>(*it)){
            if(substance.empty()){
                continue;
            } else {
                (*it)->update(this,substance);
                continue;
            }
        }
        (*it)->update(this);
    }
}

time_t IsFileModified::getLastModificationTime(){
	// C-kod za Unix platformu
	struct stat fileInfo;
	if(stat (m_fileName.c_str(),&fileInfo) != 0){
		throw "stat error!";
	}
	return fileInfo.st_mtime;
}
 void Concentrations::readData( std::string name ){
    std::ifstream myfile;
    std::string str;
    char *substant, *trash;
    trash = (char*)calloc(6,sizeof(char));
    substant = (char*)calloc(1000,sizeof(char));

    int a,b,c;
    std::vector<int> vec;
    vec.resize(3);
    myfile.open (name);
    if(myfile == 0) exit(-8);
    std::getline(myfile, str);
    std::getline(myfile, str);

    std::cout << "Ucitavam " << str  <<std::endl;

    while (myfile.is_open() && !str.empty()) {
        std::getline(myfile, str);
        std::sscanf (str.c_str(), "%s %s %d %d %d", substant, trash , &a, &b, &c);
        vec[0] = a;
        vec[1] = b;
        vec[2] = c;
        data[substant]=vec;
        //data.insert( std::pair<std::string,std::vector<int> >(substant,vec) );
        std::cout << "" << substant << " "<<data[substant][0]<< " "<<data[substant][1]<<  " " <<data[substant][2]<<std::endl;
    }

    myfile.close();
    lastReading = std::time(0);
    std::cout << "kraj" << std::endl;
}

Concentrations::Concentrations(std::string name):IsFileModified(name){
    std::cout << "Const" << std::endl;
    readData(name);
    this->name = name;

}

std::map< std::string, std::vector<int> > Concentrations::get() const{
    return data;
}

void Concentrations::setState(){
    time_t lastModification = getLastModificationTime();
    if( std::difftime( lastModification, lastReading ) > 0 ) {
        readData(name);
        notify();
    }
}

void DataAlert::update(Subject* ps){
    std::cout << "Data out of bounds!" << std::endl;
}

void DataAlert::update(Subject* ps, std::string substance){
    std::cout << "Data out of bounds: "<< substance << std::endl;
}

void DisplayData::update(Subject* ps){
    std::map< std::string, std::vector<int> > data;
    std::map< std::string, std::vector<int> >::iterator it;
    data = conc->get();
    for(it = data.begin() ; it != data.end(); ++it){
        std::cout << it->first << " "<<(it->second)[0] << " " <<it->second[1] <<  " " << it->second[2] << std::endl;
    }
}

void DisplayData::update(Subject* ps,  std::string substance){
    std::map< std::string, std::vector<int> > data;
    std::map< std::string, std::vector<int> >::iterator it;
    data = conc->get();
    for(it = data.begin() ; it != data.end(); ++it){
        std::cout << it->first << " "<<(it->second)[0] << " " <<it->second[1] <<  " " << it->second[2] << std::endl;
    }
}

