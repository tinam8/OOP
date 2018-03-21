#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <cmath>


using namespace std;
string odg = "Y";

#ifndef __GAME_OF_LIFE_H_INCLUDED__
#define __GAME_OF_LIFE_H_INCLUDED__

class GameOL{
    char* polje;
    int N,M;

  public:
    GameOL(){
		polje = NULL;
	};
    ~GameOL(){
        delete [] this->polje;
    };
    void init(std::string const & file_name);
    void print() const;
    void print(std::string const &  file_name) const;
    void update();
  private:
    // broj živih susjeda danog elementa (i,j)
    int  br_susjeda(int i, int j) const;
};
#endif
//ucitava dat
void GameOL::init(std::string const & file_name){

    const char *dat = file_name.c_str();
    ifstream f(dat);
    f >> N >> M ;
    ///cout << "velicina polja: ";
    ///cout << N << " x " << M <<endl;
	this->polje = new char[N*M]();
    string s;
    int i = 0;
    getline(f,s);
    while(getline(f,s)){
        //uzmi liniju i nadopuni ju do 20
        if(s.length()){

            for(string::const_iterator c = s.begin(); c < s.end();++c){
                this->polje[i++] = *c;

            }
            while(i%20){
                this->polje[i++] = ' ';
            }
        }else{
            for(int j = i;j < i+20;j++)
                this->polje[j] = ' ';
            i += 20;
        }
    }
}

void GameOL::print() const {

    for(int i = 0;i < N;++i){
        for(int j= 0;j < M;++j){
            cout<<polje[i*M+j];

        }
        cout << endl;

    }
}

void GameOL::print(std::string const &  file_name) const{
    const char *dat = file_name.c_str();
    ofstream f(dat);
    f << N << " " << M << endl;
    for(int i = 0;i < N;i++){
        for(int j = 0;j < M;++j){
            f << polje[i*N+j];
        }
        f << '\n';
    }
    f.close();
}

int GameOL::br_susjeda(int i, int j) const{
    int susjedi = 0;

    if((i!=0) && (j!=0) && (this->polje[(i-1)*N+(j-1)] == '*'))
        susjedi++;
    if((i!=0) && (this->polje[(i-1)*N+j] == '*'))
        susjedi++;
    if((i!=0) && (j!= M-1) && (this->polje[(i-1)*N+(j+1)] == '*'))
        susjedi++;
    if((j!=0) && (this->polje[(i)*N+(j-1)] == '*'))
        susjedi++;
    if((j!= M-1) && (this->polje[(i)*N+(j+1)] == '*'))
        susjedi++;
    if((i!=N-1) && (j!=0) && (this->polje[(i+1)*N+(j-1)] == '*'))
        susjedi++;
    if((i!=N-1) && (this->polje[(i+1)*N+j] == '*'))
        susjedi++;
    if((i!=N-1) && (j!=M-1) && (this->polje[(i+1)*N+(j+1)] == '*'))
        susjedi++;

    return susjedi;
}

void GameOL::update(){
    //update se odvija istovremeno
    char *tmp = new char[N*M]();
    for(int i = 0;i < N;i++){
        for(int j = 0;j < M;++j){
            int susjedi = br_susjeda(i,j);
            ///cout << susjedi << " ";
            switch(susjedi){
                case 0 :
                case 1 :
                    tmp[i*N+j]=' ';
                    break;
                case 2 :
                    tmp[i*N+j]=polje[i*N+j];
                    break;
                case 3 :
                    tmp[i*N+j]='*';
                    break;
    // you can have any number of case statements.
                default :
                    tmp[i*N+j]=' ';
                }
        }
        ///cout << endl;
    }
    polje = tmp;
}

bool user_continue(){

    return (odg == "y" || odg == "Y");
}


int main(int argc, char * argv[])
{
  // učitaj ulazno stanje iz datoteke. Datoteka je pocetno_stanje.txt
  // ili je zadana argumentom komandne linije
  std::string input_file("pocetno_stanje.txt");
  if(argc > 1)
    input_file = argv[1];

  GameOL gol;  // defaultni konstruktor

  // Inicijaliziraj Game Of Live objekt s početnim stanjem
  // koje je zadano u datoteci input_file
  gol.init(input_file);

  cout << endl;
  // iscrtaj početno stanje
  gol.print();
  while( user_continue())
  {
    gol.update();  // prijelaz automata u novo stanje
    gol.print();
    std::cout << "Next step (Y/N)? ";
    std::cin >> odg;

  }
  //ispiši završno stanje u datoteku
  gol.print("zavrsno_stanje.txt");

  /*gol.init("zavrsno_stanje.txt");
  cout << "Sljedece...\n"<<endl;
  gol.print();
  while( user_continue())
  {
    gol.update();  // prijelaz automata u novo stanje
    gol.print();
    std::cout << "Next step (Y/N)? ";
    std::cin >> odg;

  }
  //ispiši završno stanje u datoteku
  gol.print("zavrsno_stanje.txt");*/

  return 0;
}

