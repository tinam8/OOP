#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>

using namespace std;

void separator(string const & text,set<string> & skup){
	string tmp;
	for(string::const_iterator i = text.begin(); i < text.end();++i)
		{
		 	if(!ispunct(*i) and !isspace(*i)){
				tmp.push_back(*i);
				}
			else{
				///cout << tmp <<endl;
				skup.insert(tmp);
				tmp.clear();
				}

		}
	if(!text.empty())
		{///cout << tmp <<endl;
		 skup.insert(tmp);}
	return;
	}


void ucitavanje(string imeDatoteke, set<string> & skup)
{	try{
		string line;
		const char *dat = imeDatoteke.c_str();

		ifstream file;
		file.open(dat);
		if(file.is_open()){

			while(getline(file,line)){
				separator(line,skup);
				}

			}
		else {
			cout << "Ne mogu procitati file." << endl;
			file.close();
			return;}

		file.close();
	}catch(runtime_error e){
        throw e;
    }

	return;

}

double podudaranje(set<string> & skup1, set<string> & skup2)
{
	vector<string> inter(skup1.size());
    vector<string>::iterator it;
	it = set_intersection(skup1.begin(),skup1.end(),skup2.begin(),skup2.end(),inter.begin());
	inter.resize(it-inter.begin());
	int s1 = skup1.size();
	int s2 = skup2.size();

	//cout << "Prvi skup ima "<< s1<<" elemenata." <<endl;
	//cout << "Drugi skup ima "<< s2  <<" elemenata." <<endl;
	double x = (double)inter.size()/(double)sqrt(s1*s2);
	return x;

}

auto lambda = [](string s){
	cout << s <<endl;
		};

class Presijek{
	set<string> skup;

	void separator(std::string const & text,std::set<std::string> & skup)
	{
		string tmp;
		for(string::const_iterator i = text.begin(); i < text.end();++i)
		{
		 	if(!ispunct(*i) and !isspace(*i)){
				tmp.push_back(*i);
				}
			else{
				///cout << tmp <<endl;
				skup.insert(tmp);
				tmp.clear();
				}

			}
		if(!text.empty())
		{///cout << tmp <<endl;
			skup.insert(tmp);}
		return;}

	public:
	Presijek(set<string> skup){
		this->skup = skup;
		}

	~Presijek(){}

	void ucitavanje(std::string imeDatoteke,std::set<std::string> & skup){
			try{
			string line;
			const char *dat = imeDatoteke.c_str();

			ifstream file;
			file.open(dat);
			if(file.is_open()){

				while(getline(file,line)){
					separator(line,this->skup);
					}

				}
			else {
				cout << "Ne mogu procitati file." << endl;
				file.close();
				return;}

			file.close();
		}catch(runtime_error e){
			throw e;
		}
		return;}

	double podudaranje(std::set<std::string> & skup2,std::set<std::string> & skup){
		vector<string> inter(skup.size());
		vector<string>::iterator it;
	    it = set_intersection(skup.begin(),skup.end(),skup2.begin(),skup2.end(),inter.begin());
		inter.resize(it-inter.begin());
		int s1 = skup.size();
		int s2 = skup2.size();

		//cout << "Prvi skup ima "<< s1<<" elemenata." <<endl;
		//cout << "Drugi skup ima "<< s2  <<" elemenata." <<endl;
		double x = (double)inter.size()/(double)sqrt(s1*s2);
		return x;
		}

	void ispis(){
		for_each(skup.begin(),skup.end(),lambda);
		}

	set<string> get(){
		set<string> s = this->skup;
		return s;

		}

	};

int main(int argc,char** argv){
	if(argc < 2){
        std::cerr << " Ocekujem dva argumenta\n" << argv[0] << " ime1 ime2\n"
                  << " ime1 = ulazna datoteka s tekstom\n ime2 = datoteka s trazenim rijecima."
                  << std::endl;
        std::exit(1);
    }
    std::string in1(argv[1]);
    std::string in2(argv[2]);

    std::set<std::string> text, rijeci;
	ucitavanje(in1,text);
	cout << "1.SKUP:" <<endl;
	for_each(text.begin(),text.end(),lambda);
	cout << endl;

	ucitavanje(in2,rijeci);
	cout << "2.SKUP:" <<endl;
	for_each(rijeci.begin(),rijeci.end(),lambda);
	cout << endl;

	double x =podudaranje(text,rijeci);
	cout << "Vrijednost fje podudaranja je "<< x <<endl;
	cout << endl;
	cout << endl;

	Presijek skup1(text);
	Presijek skup2(rijeci);
	cout << endl;
	skup1.ispis();
	cout << endl;
	skup2.ispis();

	//Presijek skup3(skup1.get());
	//skup3.ispis();

	x =skup1.podudaranje(text = skup1.get(),rijeci = skup2.get());
	cout << "Vrijednost fje podudaranja je "<< x <<endl;

}
