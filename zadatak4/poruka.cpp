#include <iostream>

#include "poruka.h"

///ispis svih poruka jedne kategorije
/*void Kategorija::ispis()
{       std::cout << mporuke.size()<<std::endl;
        for(auto iter = mporuke.begin(); iter != mporuke.end();iter++){
            std::cout << (*iter)->sadrzaj()<<std::endl;
        }

    }*/



Kategorija::~Kategorija(){
    for(auto poruka : mporuke){
        poruka->ukloni(*this);
    }
    mporuke.clear();
}

// dodaj poruku u kategoriju
void Kategorija::dodaj_poruku(Poruka * poruka){
    poruka->mkategorije.insert(this);
    mporuke.insert(poruka);
}
// ukloni poruku iz kategorije
void Kategorija::ukloni_poruku(Poruka * poruka){
    for(auto it = mporuke.begin(); it != mporuke.end(); ++it){
        if(poruka == *it){
            mporuke.erase(it);
            break;
        }
    }
    for(auto it = poruka->mkategorije.begin(); it != poruka->mkategorije.end(); ++it){
        if(this == *it){
            poruka->mkategorije.erase(it);
        }
    }
}



Poruka::Poruka(Poruka const & obj){
    msadrzaj = obj.msadrzaj;
    mkategorije.clear();

    for(auto kategorija : obj.mkategorije){
        kategorija->dodaj_poruku(this);
    }
}

Poruka::Poruka(Poruka && obj) : msadrzaj(std::move(obj.msadrzaj)), mkategorije(std::move(obj.mkategorije)){
    for(auto kategorija : mkategorije){
        kategorija->ukloni_poruku(&obj);
        kategorija->dodaj_poruku(this); //dvaput se dodaju kategorije, ali mkategorije je set
    }
}

Poruka& Poruka::operator=(Poruka const& obj){
    if(this == &obj){
        return *this;
    }
    msadrzaj = obj.msadrzaj;
    for(auto kategorija : mkategorije){
        kategorija->ukloni_poruku(this);
    }
    mkategorije.clear();
    for(auto kategorija : obj.mkategorije){
        kategorija->dodaj_poruku(this);
    }

    return *this;
}

Poruka& Poruka::operator=(Poruka&& obj){
    if(this == &obj) return *this;
    msadrzaj = std::move(obj.msadrzaj);
    for(auto kategorija : mkategorije){
        kategorija->ukloni_poruku(this);
    }
    //mkategorije.clear();
    mkategorije = std::move(obj.mkategorije);
    for(auto kategorija : mkategorije){
        kategorija->ukloni_poruku(&obj);
        kategorija->dodaj_poruku(this);
    }
    //obj.mkategorije.clear();

    return *this;
}

Poruka::~Poruka(){
    for(auto kategorija : mkategorije){
        kategorija->ukloni_poruku(this);
    }
    mkategorije.clear();
}

// dodaj poruku u kategoriju
void Poruka::dodaj(Kategorija& kategorija){
    kategorija.dodaj_poruku(this);
}

// ukloni poruku iz kategorije
void Poruka::ukloni(Kategorija& kategorija){
    kategorija.ukloni_poruku(this);
}

// vrati sve kategorije u kojima je poruka (odvojene bjelinom, kao jedan string)
std::string Poruka::kategorije() const{
    std::string svekategorije = "";
    for(auto it = mkategorije.begin(); it != mkategorije.end(); ++it){
        svekategorije += (*it)->opis();
        svekategorije += ' ';
    }
    return svekategorije;
}
