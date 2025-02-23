#include <iostream>
#include <cstring>
#include <string.h>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <ctime>
#include <string>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <limits>


using namespace std;
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE); //pentru a schimba culoarea textului


///Interfata pentru calcule / clasa abstracta ( are o functie virtuala pura)
class Calcule{
    virtual int suma(int* v) = 0;
};

///Interfata pentru cii si afisare
class IOInterface{
public:
    virtual istream &citire(istream &) = 0 ;
    virtual ostream &afisare(ostream &) const =0;
    virtual ~IOInterface() {}
};

class Jucator{
protected:
    double balanta;
    string nume;
    int* scorJM;
    int* scorJN;
    list<string> premiiObtinute;
    int nrRotiri;

public:

//Constructori:
    Jucator();
    Jucator(double balanta,string nume, int* scorJM, int* scorJN, int nrRotiri, list<string> premiiObtinute);

//Copy constructor
    Jucator(const Jucator& obj);

//Operator =
    Jucator& operator = (const Jucator& obj);

//Setteri si getteri
    double getBalanta();
    void setScorJN(int* v);
    int getRotiri();

//Supraincarcarea opearatorului --
    Jucator& operator --(int)
    {
        if(nrRotiri > 0)
            nrRotiri--;
        return *this;
    }
//Supraincarcarea opearatoruli -
    Jucator& operator -=(double valoare)
    {
        balanta -= valoare;
        return *this;
    }

//Supraincarcarea opearatorului += ca sa aduage o valoare la balanta
    Jucator& operator += (double valoare) {
        balanta += valoare;
        return *this;
    }

///Functii
//Functie care imi insereaza in lista obiectul catigat la pozitia corespunzatoare(lista crescatoare)
void inserarePremiu(map<string, double> premii,string premiu)
{
    auto it = premiiObtinute.begin();
    if(premiiObtinute.empty())
     while (it != premiiObtinute.end() && premii[*it] < premii[premiu]) 
        ++it;
    premiiObtinute.insert(it, premiu);
}

//Citire si afisare
friend ostream& operator <<(ostream& out,Jucator& obj);


    //Destructor
    ~Jucator()
    {
        if(scorJM != NULL)
            delete[] scorJM;
        if(scorJN != NULL)
            delete[] scorJN;
    }
};
ostream& operator <<(ostream& out, Jucator &obj)
{
    SetConsoleTextAttribute(h,13);
    cout<<"Obiecte achizitionate: ";
    for(auto it = obj.premiiObtinute.begin(); it != obj.premiiObtinute.end(); it++)
        out<< *it << " ";
    out << endl;
    SetConsoleTextAttribute(h,7);
    return out;
}
//=====
///CLASA JUCATOR:
//=====
Jucator::Jucator(){
    balanta = 0.00;
    nume = "TBA";
    scorJM = NULL;
    scorJN = NULL;
    nrRotiri = 3;
}
Jucator::Jucator(  double balanta,string nume, int* scorJM, int* scorJN, int nrRotiri, list<string> premiiObtinute): nume(nume), nrRotiri(nrRotiri),balanta(balanta),premiiObtinute(premiiObtinute)
{
    if(scorJM != NULL)
        delete[] scorJM;
    this->scorJM = new int[nrRotiri];
    for(int i = 0; i < nrRotiri; i++)
    {
        this->scorJM[i] = scorJM[i];
    }
    if(scorJN != NULL)
        delete[] scorJN;
    this->scorJN = new int[4];
    for(int i = 0; i < 4; i++)
    {
        this->scorJN[i] = scorJN[i];
    }
}
Jucator::Jucator(const Jucator& obj): nume(obj.nume), nrRotiri(obj.nrRotiri),balanta(obj.balanta),premiiObtinute(obj.premiiObtinute)
{
        if(scorJM != NULL)
            delete[] scorJM;
        this->scorJM = new int[nrRotiri];
        for(int i = 0; i < nrRotiri; i++)
        {
            this->scorJM[i] = obj.scorJM[i];
        }
        if(scorJN != NULL)
            delete[] scorJN;
        this->scorJN = new int[4];
        for(int i = 0; i < 4; i++)
        {
            this->scorJN[i] = obj.scorJN[i];
        }


}
Jucator& Jucator:: operator = (const Jucator& obj)
{
    if(this != &obj)
    {
        this->premiiObtinute = obj.premiiObtinute;
        this->balanta = obj.balanta;
        this->nume = obj.nume;
        this->nrRotiri = obj.nrRotiri;
        if(scorJM != NULL)
            delete[] scorJM;
        this->scorJM = new int[nrRotiri];
        for(int i = 0; i < nrRotiri; i++)
        {
            this->scorJM[i] = obj.scorJM[i];
        }
        if(scorJN != NULL)
            delete[] scorJN;
        this->scorJN = new int[nrRotiri];
        for(int i = 0; i < nrRotiri; i++)
        {
            this->scorJN[i] = obj.scorJN[i];
        }
    }
    return *this;
}

//Setteri si getteri
double Jucator :: getBalanta(){return balanta;}
void Jucator ::  setScorJN(int* v)
{
    if(scorJN != NULL)
        delete[] scorJN;
    scorJN = new int[4];
    for(int i = 0; i < 4; i++)
    {
        scorJN[i] = v[i];
    }
}
int Jucator ::  getRotiri(){return nrRotiri;}



class Joc:public  IOInterface,public Calcule{
protected:
    string numeZonaJoc;
    int numarLocuriTotal;
    int nrLocuriRezervate;

public:
    struct date{
        string numeZonaJoc;
        int nrLocuriRezervate;
        int numarLocuriTotal;
    };

//Constructori:
    Joc();
    Joc(string,int,int);

//Setters & getters:
    string getnumeJoc()const;
    int getNrLocuriRezervate()const;
    int getNumarLocuriTotal()const;

///Functii friend
 

//Supraincarcare operator =
    Joc& operator = (const Joc& obj);

//Copy constructor
    Joc(const Joc& obj);

///Supraincarcarea opearatorului []
///care im va return in functie de ce valoarea are indexul cate un tip de date diferit din clasa joc
    Joc::date operator[](int index) const ;

///Supraincarcare operator ++ ( ambele forme)
/*
    Joc& operator++();
    Joc operator++(int);
*/


///Citire si afisare
    friend istream& operator>>(istream& in, Joc& obj);
    friend ostream& operator<<(ostream& out, const Joc& obj);
    istream &citire(istream &);
    ostream &afisare(ostream &) const;

///Functii
    ///Functie care imi returneaza numarul de locuri disponibileie
    int suma(int *v)override;


///Destructorul
    virtual  ~Joc(){}

};


//==========
///CLASA JOC:
//==========

///Constructori:
Joc::Joc(){
    numeZonaJoc = "TBA";
    numarLocuriTotal = 0;
    nrLocuriRezervate = 0;
}
Joc::Joc( string numeZonaJoc,int numarLocuriTotal,int nrLocuriRezervate): numeZonaJoc(numeZonaJoc), nrLocuriRezervate(nrLocuriRezervate), numarLocuriTotal(numarLocuriTotal){}

///Getters & Setters:
string Joc:: getnumeJoc()const{return numeZonaJoc;}
int Joc:: getNrLocuriRezervate()const {return nrLocuriRezervate;}
int Joc:: getNumarLocuriTotal()const {return numarLocuriTotal;}


///Supraincarcare operator =
Joc& Joc:: operator = (const Joc& obj)
{
    if(this != &obj) {
        this->numeZonaJoc=obj.numeZonaJoc;
        this->nrLocuriRezervate = obj.nrLocuriRezervate;
        this->numarLocuriTotal = obj.numarLocuriTotal;
        return *this;
    }
}

///Copy constructor
Joc::Joc(const Joc& obj): numeZonaJoc(obj.numeZonaJoc),
                          nrLocuriRezervate(obj.nrLocuriRezervate), numarLocuriTotal(obj.numarLocuriTotal){}

///Supraincarcarea opearatorului []
///care imi va return in functie de ce valoarea are indexul cate un tip de date diferit din clasa joc
///Pentru a face asta m-am folosit de o structura date care contine toate datele din clasa joc
Joc::date Joc::operator[](int index) const {
    if (index == 0)
        return {numeZonaJoc, 0, 0};
    else if (index == 2)
        return {"",nrLocuriRezervate,0};
    else if (index == 3)
        return {"",numarLocuriTotal,0};
    throw out_of_range("Index out of range");

}


///Supraincarcarea operatorului ++, ambele forme:
/*Joc&  Joc::operator++(){
    this -> numarRunde++;
    int* vect = new int[this -> numarRunde];
    for (int i = 0; i < numarRunde - 1; i++)
        vect[i] = this -> scorPerRundeMaxim[i];
    vect[this -> numarRunde - 1] = 0;
    if (this -> scorPerRundeMaxim != NULL)
        delete[] this -> scorPerRundeMaxim;
    this -> scorPerRundeMaxim = vect;

    return *this;
}
Joc Joc:: operator++(int){    // post
    Joc copie = *this;
    this -> numarRunde++;
    int* vect = new int[this -> numarRunde];
    for (int i = 0; i < numarRunde - 1; i++)
        vect[i] = this -> scorPerRundeMaxim[i];
    vect[this -> numarRunde - 1] = 0;
    if (this -> scorPerRundeMaxim != NULL)
        delete[] this -> scorPerRundeMaxim;
    this -> scorPerRundeMaxim = vect;
    return copie;
}
*/
///Citire si afisare
istream& operator>>(istream& in, Joc& obj){  return obj.citire(in);}
ostream& operator<<(ostream& out, const Joc& obj){  return obj.afisare(out);}

ostream& Joc :: afisare(ostream &out) const{
    return out;
}
istream& Joc :: citire(istream &in){
    cout << "Nume zona (unde se afla sala): ";
    in >> numeZonaJoc;
    cout << "Numarul de locuri total: ";
    in >> numarLocuriTotal;
    system("cls");
    return in;
}

///Functii
    ///Functie care imi returneaza numarul de locuri disponibileie
    int Joc:: suma(int *v)
    {
        return numarLocuriTotal - nrLocuriRezervate;
    }



///Clasa template
template <class tip,class punctaj>
class TipJocDeMasa
{
       vector<tip> v;
       punctaj scor; 
       int dimensiune;
public:

 //Constructori  
   TipJocDeMasa();
   TipJocDeMasa(vector<tip> v, punctaj scor,int dimensiune);

//Setteri si getteri
    vector<tip> getV()const;
    void setV(vector<tip> v);
    punctaj getScor();
    void setScor(punctaj scor);
    int getDimensiune()const;
    void setDimensiune(int dimensiune);

    //Copy constructor
    TipJocDeMasa(const TipJocDeMasa& obj);

    //Operator =
    TipJocDeMasa& operator = (const TipJocDeMasa& obj);

//Functii(Metode template)
    void inserareElementPozitie(tip element, int pozitie); //inserarea unui element pe o pozitie data
    tip extrageElementRnadom(); //extragerea unui element random(de tipul precizat in template)
    void addToScor(punctaj valoare); //adunarea unui scor la scorul curent

//Destructor
   ~TipJocDeMasa(){}

};


//==========
///CLASA TIPJOCDEMASA:
//==========

//Constructori
    template <class tip,class punctaj>
        TipJocDeMasa<tip,punctaj> :: TipJocDeMasa(){
        v= {};
        scor = NULL;
        dimensiune = 0;
    }

    template <class tip,class punctaj>
        TipJocDeMasa<tip,punctaj> :: TipJocDeMasa (vector<tip> v, punctaj scor,int dimensiune):v(v),scor(scor),dimensiune(dimensiune){}

//Setteri si getteri
    template <class tip,class punctaj>
        vector<tip> TipJocDeMasa<tip,punctaj> :: getV()const{  return v;}

    template <class tip,class punctaj>
        void TipJocDeMasa<tip,punctaj> :: setV(vector<tip> v){this->v = v;}

    template <class tip,class punctaj>
        punctaj TipJocDeMasa<tip,punctaj> :: getScor(){return scor;}

    template <class tip,class punctaj>
        void TipJocDeMasa<tip,punctaj> :: setScor(punctaj scor){this->scor = scor;}

    template <class tip,class punctaj>
        int TipJocDeMasa<tip,punctaj> :: getDimensiune()const{return dimensiune;}

    template <class tip,class punctaj>
        void TipJocDeMasa<tip,punctaj> :: setDimensiune(int dimensiune){this->dimensiune = dimensiune;}

 //Copy constructor
    template <class tip,class punctaj>
        TipJocDeMasa<tip,punctaj> :: TipJocDeMasa(const TipJocDeMasa<tip,punctaj>& obj):v(obj.v),scor(obj.scor),dimensiune(obj.dimensiune){}

//Operator =
    template <class tip,class punctaj>
        TipJocDeMasa<tip,punctaj>& TipJocDeMasa<tip,punctaj> :: operator = (const TipJocDeMasa<tip,punctaj>& obj)
        {
            if(this != &obj)
            {
                this->v = obj.v;
                this->scor = obj.scor;
                this->dimensiune = obj.dimensiune;
            }
            return *this;
        }


//Functii
    template <class tip,class punctaj>
        void TipJocDeMasa<tip,punctaj> :: inserareElementPozitie(tip element, int pozitie){
        if (pozitie < 10000) 
            v[pozitie] = element;
        else
        throw(pozitie);     
            
        }
    template <class tip,class punctaj>
        tip TipJocDeMasa<tip,punctaj> :: extrageElementRnadom(){
            srand(time(0));
            return v[ rand() % dimensiune];
        }
    template <class tip,class punctaj>
        void TipJocDeMasa<tip,punctaj> :: addToScor(punctaj valoare){
            scor += valoare;
        }


class Spanzuratoarea
{
       TipJocDeMasa<string,double> cuvinte;
       //Variabile pentru jocul Spanzuratoarea
       int incercari;
       set<char> litere;
       string cuvantGhicit;

public:
//Constructori:
    Spanzuratoarea();
    Spanzuratoarea(vector<string> v,double scor,int dimensiune, int incercari);
//Copy constructor
    Spanzuratoarea(const Spanzuratoarea& obj);
//Operator =    
   Spanzuratoarea& operator = (const Spanzuratoarea& obj);

//Setter si getteri
void afisV();

///Functii
    void desen(int incercari);
    void spanzuratoarea();

//Citire si afisare:
friend istream& operator>>(istream& in, Spanzuratoarea& obj);
friend ostream& operator<<(ostream& out, const Spanzuratoarea& obj); 
istream& citire(istream& in);
ostream& afisare(ostream& out)const;

   ~Spanzuratoarea(){}

};



//==========
///CLASA SPANZURATOAREA:
//==========

//Constructori:
  Spanzuratoarea :: Spanzuratoarea  ():cuvinte() {
        incercari = 0;
        litere = {};
        cuvantGhicit = "";
    }
  Spanzuratoarea :: Spanzuratoarea  (vector<string> v,double scor,int dimensiune, int incercari):
  incercari(incercari), cuvinte(v,scor,dimensiune) {}

//Copy constructor
  Spanzuratoarea :: Spanzuratoarea  (const Spanzuratoarea& obj):incercari(obj.incercari),cuvinte(obj.cuvinte){}

//Operator =
  Spanzuratoarea& Spanzuratoarea ::  operator = (const Spanzuratoarea& obj)
    {
        if(this != &obj)
        {
            this->incercari = obj.incercari;
            this->cuvinte = obj.cuvinte;
        }
        return *this;
    }

//Setter si getteri
void Spanzuratoarea :: afisV()
{
    for(int i = 0; i < cuvinte.getDimensiune(); i++)
        cout << cuvinte.getV()[i] << " ";
    cout << endl;
}


///Functii
    void Spanzuratoarea ::  desen(int incercari)
    {
        switch(incercari)
        {
            case 0:
        
        cout << R"(
   +---+
   |   |
       |
       |
       |
       |
 =========

)";
                break;
            case 1:
                cout << R"(
   +---+
   |   |
   O   |
       |
       |
       |
 =========
 
 )";
                break;
            case 2:
                cout << R"(
   +---+
   |   |
   O   |
   |   |
       |
       |
 =========
 
 )";
                break;
            case 3:
                cout << R"(
   +---+
   |   |
   O   |
  /|   |
       |
       |
 =========)";
                break;
            case 4:
                cout << R"(
   +---+
   |   |
   O   |
  /|\  |
       |
       |
 =========
 
 )";
                break;
            case 5:
                cout << R"(
   +---+
   |   |
   O   |
  /|\  |
  /    |
       |
 =========
 
 )";
                break;
            case 6:
                cout << R"(
   +---+
   |   |
   O   |
  /|\  |
  / \  |
       |
 =========
 
 )";
                break;
        }
    }

    void Spanzuratoarea :: spanzuratoarea()
    {
        
        string cuvant = cuvinte.extrageElementRnadom(); // extrag un cuvant random din vectorul de cuvinte

        for(int i = 0; i < cuvant.size(); i++)
            cuvantGhicit += "_";

        for(int i = 0;i<3;i++) {
            int index = rand() % cuvant.size();
            if(cuvantGhicit[index] == '_')
                cuvantGhicit[index] = cuvant[index];
            else
                i--;
        }
       
        while (!(this->cuvantGhicit == cuvant || this->incercari == 0)) {
            system("cls");
            SetConsoleTextAttribute(h,13);
            cout<<"                              +================+\n";
            cout<<"                              | Spanzuratoarea |\n";  
            cout<<"                              +================+\n";
            SetConsoleTextAttribute(h,11);
           desen(6 - this->incercari);
            SetConsoleTextAttribute(h,7);
            cout << "Incercati sa ghiciti cuvantul.\n\n";
            cout << "Cuvant: " <<this->cuvantGhicit<< endl;
            cout << "Incercari ramase: " << this->incercari << endl;
            cout << "Ghiciri incorecte: ";
            for (char litera : this->litere) {
                cout << litera << " ";
            }
            cout << endl;
            string litera1;
            char litera;
            cout << "Introduceti o litera: ";                 
            try{
                cin>>litera1;
                litera = litera1[0];
                if(litera1.size() > 1)
                    throw litera1;
                if(!(litera>='a' && litera<='z'))
                    throw(invalid_argument("runtime_error"));  
            }
            catch(const invalid_argument& e) {
                cout<<"Caracterul introdus nu este o litera (7a - z): "<<e.what()<<endl;
                Sleep(1500);
                continue;
            }
            catch(string) {
                cout<<"Ati introdus mai mult de un caracter: "<<endl;
                Sleep(1500);
                continue;
            }

            bool ok =0;
            for(int i =0; i < cuvant.size(); i++)
                if (cuvant[i] == litera)
                    ok = 1;
            if (ok)
            {
                for (int i = 0; i < cuvant.size(); ++i) {
                    if (cuvant[i] == litera)
                        this->cuvantGhicit[i] = litera;
                }
            }
            else
            {
                incercari--;
                litere.insert(litera);
            }
        }
        if (cuvant == cuvantGhicit){
            system("cls");
            cout << "                              ~ Spanzuratoarea~\n";
            cout << "Felicitari! Ati ghicit cuvantul: " << cuvant << endl<<endl;
           
        }
          
        else{
            system("cls");
            cout << "                              ~ Spanzuratoarea~\n";
            cout << "Ati ramas fara incercari, cuvantul era: " << cuvant << endl<<endl;
           
        }

        }


//Supraincarcarea operatorilor de citire si afisare
 istream& operator>>(istream& in,  Spanzuratoarea& obj){
    
    return obj.citire(in);
    }   
 ostream& operator<<(ostream& out, const Spanzuratoarea& obj){
    
    return obj.afisare(out);
    }

 istream& Spanzuratoarea::citire(istream& in){
    cout << "Numarul de incercari: ";
    in >> incercari;
    cout<<"Numarul de cuvinte: ";
    int dimensiune;
    in >> dimensiune;
    if(!cin.good()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        throw runtime_error("Numarul introdus a fost prea mare");
      }
     if(incercari>6)
        throw incercari;
     if(incercari>10)
        throw dimensiune;   

    cuvinte.setDimensiune(dimensiune);
    string cuvant;
    vector<string> v;
    for(int i = 0; i < cuvinte.getDimensiune(); i++)
    {
        cout << "Cuvant "<<i+1<<" : ";
        in >> cuvant;
        if(cuvant.size() > 20)
            throw cuvant;
        v.push_back(cuvant);
    }
    cuvinte.setV(v);
    system("cls");
    return in;
 }
ostream& Spanzuratoarea::afisare(ostream& out)const{
    cout << "Numarul de incercari: " << incercari << endl;
    cout << "Cuvinte: ";
    for(int i = 0; i < cuvinte.getDimensiune(); i++)
        cout << cuvinte.getV()[i] << " ";
    cout << endl;
    return out;
 }

class XSi0{

    TipJocDeMasa<int,int> tabla;
public:

//Constructori:
    XSi0();
    XSi0(vector<int> v,int scor,int dimensiune);

 //copy constructor
    XSi0(const XSi0& obj);

//Operator =
    XSi0& operator = (const XSi0& obj);

//Functii:
    int castigator();
    void afisareTabla();
    bool verificareTabla();
    int verificareInput();
    void adaugare1();
    void play();

//Citire si afisare:
    friend istream& operator>>(istream& in, XSi0& obj);
    friend ostream& operator<<(ostream& out, const XSi0& obj);
    istream& citire(istream& in);
    ostream& afisare(ostream& out)const;

//Destructor
    ~XSi0(){}
};

//===========
///CLASA XSI0:
//===========

//Constructori:
    XSi0 :: XSi0 ():tabla(){}
    XSi0 :: XSi0  (vector<int> v,int scor,int dimensiune){
      for(int i = 0;i < dimensiune*dimensiune;i++)
          v.push_back(9);  
      tabla = TipJocDeMasa<int,int>(v,scor,dimensiune);  
    }

 //copy constructor
    XSi0 :: XSi0  (const XSi0& obj):tabla(obj.tabla){}

//Operator =
    XSi0& XSi0 ::  operator = (const XSi0& obj)
    {
        if(this != &obj)
        {
            this->tabla = obj.tabla;
        }
        return *this;
    }

/// Functii

int XSi0 :: castigator()
{
    bool x,y;
    
           
        
    for(int i = 0; i < tabla.getDimensiune(); i++)
    {
        bool ok1 = 0;
        bool ok2 = 0;
        
        x = tabla.getV()[i*tabla.getDimensiune()];
        y=tabla.getV()[i];

       
        for(int j = 1; j < tabla.getDimensiune(); j++)
        {
            if(x!=tabla.getV()[i*tabla.getDimensiune()+j] )
                ok1=1;
            if(tabla.getV()[j*tabla.getDimensiune()+i] )
                ok2 = 1;
        }  
        
        if(ok1== 0){
                if(x==1)
                   return 1;     
                
                else if(x ==0)
                   return 0; 
            }
         if(ok2 == 0){
                if(y==1)
                   return 1;     
                
                else if(y ==0)
                   return 0; 
            }
    }
    bool ok3 = 0;
    x = tabla.getV()[0];
    for(int i = 1; i < tabla.getDimensiune(); i++)
            if(x!=tabla.getV()[i*tabla.getDimensiune()+i] )
                ok3=1;
    if(ok3 == 0){
        if(x==1)
            return 1;     
        else if(x ==0)
            return 0; 
        
    }
    ok3 =0;
    x = tabla.getV()[tabla.getDimensiune()-1];
    for(int i = 1; i < tabla.getDimensiune(); i++)
            if(x!=tabla.getV()[i*tabla.getDimensiune()+tabla.getDimensiune()-1-i] )
                ok3=1;
     if(ok3 == 0) {
        if(x==1)
            return 1;     
        
        else if(x ==0)
            return 0; 
        
    }

    return 2;

}

void XSi0 ::  afisareTabla()
{
    cout<<"    ";
    for(int i = 1;i<tabla.getDimensiune()+1;i++)
      cout<<"  ("<<i<<") ";
    cout<<endl<<"     ";

    for(int i = 0; i < tabla.getDimensiune(); i++)
      cout<<"______";
     cout<<endl;

     for(int j = 0; j < tabla.getDimensiune(); j++)
    {
        cout<<"    |";
        for(int i = 0; i < tabla.getDimensiune(); i++)
        {
            if(j<1)
          cout<<"     |";
          else
             cout<<"_____|";
        }
        if(j>0)
        {
        cout<<endl<<"    |";
         for(int i = 0; i < tabla.getDimensiune(); i++)
             cout<<"     |";
           
        }
        
        cout<<endl;
        cout<<" ("<<j+1<<")|";
   for(int i = 0; i <tabla.getDimensiune(); i++)
    {
              if(tabla.getV()[i*tabla.getDimensiune()+j] == 0)
              {
                 cout << "  ";
                SetConsoleTextAttribute(h,13);
                cout<<tabla.getV()[i*tabla.getDimensiune()+j];
                SetConsoleTextAttribute(h,7);
                cout << "  |";
              }
                
            else if(tabla.getV()[i*tabla.getDimensiune()+j] == 1)
            {
                  cout << "  ";
                  SetConsoleTextAttribute(h,13);
                 cout<<tabla.getV()[i*tabla.getDimensiune()+j] ;
                  SetConsoleTextAttribute(h,7);
                 cout<< "  |";
            }
                
            else
            {
              SetConsoleTextAttribute(h,13);
                cout<<"  - ";
                 SetConsoleTextAttribute(h,7);
                 cout<<" |";
            }
    }
    cout << endl;
    }
    cout<<"    |";
    for(int i = 0;i<tabla.getDimensiune();i++)
        cout<<"_____|";
 
}

bool XSi0 ::  verificareTabla()
{
    vector<int> v = tabla.getV();
    for(int i = 0; i < tabla.getDimensiune()*tabla.getDimensiune(); i++)
    {
        if(v[i] == 9)
        {
            return 1;
        }
    }
    return 0;
}

int XSi0 ::  verificareInput(){
    int valoare;
    cin>>valoare;
 
    if(!cin.good()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        throw runtime_error("runtime_error");
      }
    else
        return valoare;

    return 0;
}

void XSi0 ::  adaugare1()
{
    int ok = 1;
      srand(time(0));
      int pozitie = rand() % tabla.getDimensiune()*tabla.getDimensiune();
     for(int i = 0; i < tabla.getDimensiune()*tabla.getDimensiune(); i++)
     {
       
         if(tabla.getV()[pozitie] == 9)
         {

             ok = 0;
             tabla.inserareElementPozitie(1,pozitie);
         }
     }
     if(ok == 1)
      for(int i = 0; i < tabla.getDimensiune()*tabla.getDimensiune(); i++)
            if(tabla.getV()[i] == 9)
            {
                tabla.inserareElementPozitie(1,i);
                break;
            }

    }
     


void XSi0 :: play()
{   
    int linie;
    int coloana;

    while(verificareTabla())
    {
        system("cls");
        afisareTabla();
        cout << "Introduceti linia si coloana: ";

        
    try {
        linie = verificareInput();
        coloana = verificareInput(); 
        if((coloana-1) * tabla.getDimensiune() + (linie-1) >10000)
             throw(bad_alloc());

        tabla.getV().at((coloana-1) * tabla.getDimensiune() + (linie-1));

    } 
    catch(const out_of_range& e) {
       cout << "Out of Range error: " << e.what() << endl;
       Sleep(1500);
       continue;
    }
    catch(const bad_alloc& e)
    {
        cout << "Pozitia introdusa este mult prea mare: " << e.what() << endl;
        Sleep(1500);
        continue;
    }
    catch(const runtime_error& e)
    {
        cout<<"Valorile introduse nu sunt numere intregi <= 10000 : "<<e.what()<<endl;
        Sleep(1500);
        continue;
    }

     int pozitie = (coloana-1) * tabla.getDimensiune() + (linie-1);
     tabla.inserareElementPozitie(0,pozitie);
     system("cls");
     afisareTabla();
     cout<<"(...)";  
     adaugare1(); 
     Sleep(1000);
     system("cls");
     afisareTabla(); 
        
    if(castigator() == 0)
    {
        cout<<"Felicitari! Ati castigat!"<<endl<<endl;
        vector<int> v;
        for(int i = 0; i < tabla.getDimensiune()*tabla.getDimensiune(); i++) //resetare tabla
           v.push_back(9);
        tabla.setV(v);
        cout<<endl<<"->APASATI ORICE TASTA PENTRU A VA INTOARCE<-";
        while (!_kbhit()) {}  
        break;
    }
    else if(castigator() == 1)
    {
        cout<<"Ati pierdut!"<<endl<<endl;
        vector<int> v;
        for(int i = 0; i < tabla.getDimensiune()*tabla.getDimensiune(); i++) //resetare tabla
           v.push_back(9);
        tabla.setV(v);
        cout<<endl<<"->APASATI ORICE TASTA PENTRU A VA INTOARCE<-";
        while (!_kbhit()) {}  
        break;
    }
    }
    
    
}

istream& operator>>(istream& in, XSi0& obj){
    return obj.citire(in);
}
ostream& operator<<(ostream& out, const XSi0& obj){
    return obj.afisare(out);
}
istream& XSi0::citire(istream &in){
    cout << "Dimensiunea tablei: ";
    int dimensiune;
    in >> dimensiune;
    if(dimensiune > 6)
        throw dimensiune;
    tabla.setDimensiune(dimensiune); 
    vector<int> v;
    for(int i = 0;i<(dimensiune*dimensiune);i++)
          v.push_back(9);
    tabla.setV(v);      
    return in;
}
ostream& XSi0::afisare(ostream &out) const{
    return out;
}



class JocDeMasa: public virtual Joc,public Spanzuratoarea,public XSi0{

protected:
    double pret;
    int numarRunde;
    int* scorMaximPerRunda;

public:

    ///Constructori:
    JocDeMasa();
    JocDeMasa(string , int , int , double , int , int* );

    //Copy constructor
    JocDeMasa(const JocDeMasa& obj);

    //Operator =
    JocDeMasa& operator = (const JocDeMasa& obj);

    //Functii citire si afisare
    ostream& afisare(ostream &out) const;
    istream& citire(istream &in);

    ///Functii
    int suma(int* v)override;

    //Destructor
    ~JocDeMasa(){
        if(scorMaximPerRunda != NULL)
            delete[] scorMaximPerRunda;
    }

};


//===========
///CLASA JOC DE NOROC:
//===========

///Constructori:
JocDeMasa :: JocDeMasa():Joc(){
    pret = 0.00;
    numarRunde = 0;
    scorMaximPerRunda = NULL;
   
    
}
JocDeMasa :: JocDeMasa(string numeZonaJoc, int numarLocuriTotal, int nrLocuriRezervate, double pret, int numarRunde, int* scorMaximPerRunda): 
    Joc(numeZonaJoc, numarLocuriTotal, nrLocuriRezervate),
        Spanzuratoarea({"banana","mere","pere","cirese"},0,4,6),
             XSi0({},0,3),
                pret(pret), numarRunde(numarRunde)
{
   
    this->scorMaximPerRunda = new int[numarRunde];
    for(int i = 0; i < numarRunde; i++)
    {
        this->scorMaximPerRunda[i] = scorMaximPerRunda[i];
    }
}

///Copy constructor
JocDeMasa :: JocDeMasa(const JocDeMasa& obj):Joc(obj),pret(obj.pret),numarRunde(obj.numarRunde)
{
    if(scorMaximPerRunda != NULL)
        delete[] scorMaximPerRunda;
    this->scorMaximPerRunda = new int[numarRunde];
    for(int i = 0; i < numarRunde; i++)
    {
        this->scorMaximPerRunda[i] = obj.scorMaximPerRunda[i];
    }
}

///Operator =
JocDeMasa& JocDeMasa :: operator = (const JocDeMasa& obj)
{
    if(this != &obj)
    {
        Joc::operator=(obj);
        this->pret = obj.pret;
        this->numarRunde = obj.numarRunde;
        if(scorMaximPerRunda != NULL)
            delete[] scorMaximPerRunda;
        this->scorMaximPerRunda = new int[numarRunde];
        for(int i = 0; i < numarRunde; i++)
        {
            this->scorMaximPerRunda[i] = obj.scorMaximPerRunda[i];
        }
    }
    return *this;
}

///Functii citire si afisare
ostream& JocDeMasa:: afisare(ostream &out) const{
    SetConsoleTextAttribute(h,11);
    out<< "Joc de masa: "<<endl;
    SetConsoleTextAttribute(h,7);
    out<<"Pret: "<<pret<<" RON\n";
    return out;
}
istream& JocDeMasa :: citire(istream &in){
   
    Joc :: citire(in);
    cout<< "~Pretul pentru joc de masa: ";
    in >> pret;
    cout<<"~Numarul de runde: ";
    in >> numarRunde;
    cout<<"~Scor maxim: \n";
    scorMaximPerRunda = new int[numarRunde];
    for(int i = 0; i < numarRunde; i++)
    {
        cout << "Runda " << i+1 << ": ";
        in >> scorMaximPerRunda[i];
    }
    system("cls");
    return in;
}

///Functii
//Functie CARE RETURNEAZA DACA JUCATORUL A OBTINUT SCORUL MAXIM PE TOATE RUNDURILE
int JocDeMasa:: suma(int *v)
{
    bool ok = 0;
    for(int i = 0;i<numarRunde;i++)
    {
        if ( v[i] != scorMaximPerRunda[i])
            ok=1;
    }
    if(ok == 0)
        return 0;
    else
        return 1;

}


class JocDeNoroc:public virtual Joc {
protected:
    double pret;
    int* scorMaximPerJoc;
    double valoarePunct;

public:

    ///Constructori:
    JocDeNoroc();
    JocDeNoroc(string numeZonaJoc, int numarLocuriTotal, int nrLocuriRezervate, double pret, int* scorMaximPerJoc, double valoarePunct);

    //Copy constructor
    JocDeNoroc(const JocDeNoroc& obj);

    //Operator =
    JocDeNoroc& operator = (const JocDeNoroc& obj);

    //Functii citire si afisare
    ostream& afisare(ostream &out) const;
    istream& citire(istream &in);

    ///Functii
    int suma(int * v) override;

    //Setteri si getteri
    double getValoarePunct();



    //Destructor
    ~JocDeNoroc(){
        if(scorMaximPerJoc != NULL)
            delete[] scorMaximPerJoc;
    }

};



//=======
///CLASA JOC DE NOROC:
//=======

///Constructori:
JocDeNoroc :: JocDeNoroc():Joc(){
    pret = 0.00;
    scorMaximPerJoc = NULL;
    valoarePunct = 0.00;
}
JocDeNoroc :: JocDeNoroc(string numeZonaJoc, int numarLocuriTotal, int nrLocuriRezervate, double pret, int* scorMaximPerJoc, double valoarePunct): Joc(numeZonaJoc, numarLocuriTotal, nrLocuriRezervate), pret(pret), valoarePunct(valoarePunct)
{

    this->scorMaximPerJoc = new int[4];
    for(int i = 0; i < 4; i++)
    {
        this->scorMaximPerJoc[i] = scorMaximPerJoc[i];
    }
}

///Copy constructor
JocDeNoroc :: JocDeNoroc(const JocDeNoroc& obj):Joc(obj),pret(obj.pret),valoarePunct(obj.valoarePunct)
{
    if(scorMaximPerJoc != NULL)
        delete[] scorMaximPerJoc;
    this->scorMaximPerJoc = new int[4];
    for(int i = 0; i < 4; i++)
    {
        this->scorMaximPerJoc[i] = obj.scorMaximPerJoc[i];
    }
}

///Operator =
JocDeNoroc& JocDeNoroc :: operator = (const JocDeNoroc& obj)
{
    if(this != &obj)
    {
        Joc::operator=(obj);
        this->pret = obj.pret;
        this->valoarePunct = obj.valoarePunct;
        if(scorMaximPerJoc != NULL)
            delete[] scorMaximPerJoc;
        this->scorMaximPerJoc = new int[4];
        for(int i = 0; i <4; i++)
        {
            this->scorMaximPerJoc[i] = obj.scorMaximPerJoc[i];
        }
    }
    return *this;
}

///Functii citire si afisare
ostream& JocDeNoroc:: afisare(ostream &out) const {
    SetConsoleTextAttribute(h,10);
    out << "Joc de noroc: " << endl;
    SetConsoleTextAttribute(h,7);
    out << "Pret: " << pret<<" RON\n"<<"--------------"<<endl;
    return out;
}
istream &JocDeNoroc::citire(istream &in) {
    cout<<"~Pretul pentru joc de noroc: ";
    in >> pret;
    cout<<"~Valoare punct: ";
    in >> valoarePunct;
    cout<<"~Valoarea fiecarei casute: \n";
    scorMaximPerJoc = new int[4];
    for(int i = 0; i < 4; i++)
    {
        cout << "Casuta " << i+1 << ": ";
        in >> scorMaximPerJoc[i];
    }
    system("cls");
    return in;
}
///Functii
//Aceasta functie imi returneaza suma de bani pe care un jucator o poate castiga in functie de scorul sau
//Cu cat este mai aproape de scorul maxim cu atat mai mult castiga
int JocDeNoroc:: suma(int *v)
{
    double bani = 100;
    for(int i = 0;i<4;i++)
    {
        bani +=1000.00 - ( abs( scorMaximPerJoc[i] - v[i]) * valoarePunct) ;
    }
    return bani;

}

//Setteri si getteri
double JocDeNoroc :: getValoarePunct(){return valoarePunct;}





class SalaDeJocuri:public  JocDeMasa,public  JocDeNoroc{
protected:
    int numarPremii;
    map<string,double> premii;
    vector<string> castigatori;
    double venituri;

public:
    //Constructori:
    SalaDeJocuri();
    SalaDeJocuri(string numeZonaJoc, int numarLocuriTotal, int nrLocuriRezervate,
                 double pret, int numarRunde, int* scorMaximPerRunda, double valoarePunct, int* scorMaximPerJoc, int numarPremii,  map<string,double> premii, vector<string> castigatori, double venituri);

    //Copy constructor
    SalaDeJocuri(const SalaDeJocuri& obj);

    //Operator =
    SalaDeJocuri& operator = (const SalaDeJocuri& obj);

    //Functii citire si afisare
    ostream& afisare(ostream &out) const override ;
    istream &citire(istream &in) override ;

    //Funcii
    int suma(int *v)override;

    //setteri si getteri
    double getValoarePunct()const;
    int getScorMaximPerJoc()const;
    double getVenituri()const;
    map<string,double> getPremii()const;

    ///Metoda constanta
    //Aceasta functie imi returneaza un string cu toate informatiile CONFIDENTIALE despre sala de jocuri (venituri, scoruri maxime, etc)
    string informatii() const;

    //Functii
    //Aceasta functie adauga un nou element in map-ul de premii
    void adaugaPremiu();

    //Destructor
    ~SalaDeJocuri(){
    }

};


//=======
///CLASA SALA DE JOCURI:
//=======

///Constructori:
SalaDeJocuri::SalaDeJocuri():JocDeMasa(),JocDeNoroc(){
    numarPremii = 0;
    map<string,double> premii = {};
    vector<string> castigatori = {};
    venituri = 0.00;
}
SalaDeJocuri :: SalaDeJocuri(string numeZonaJoc, int numarLocuriTotal, int nrLocuriRezervate, double pret, int numarRunde, int* scorMaximPerRunda, double valoarePunct, int* scorMaximPerJoc, int numarPremii, map<string,double> premii, vector<string> castigatori, double venituri):
        Joc(numeZonaJoc, numarLocuriTotal, nrLocuriRezervate),
        JocDeMasa(numeZonaJoc ,numarLocuriTotal, nrLocuriRezervate, pret, numarRunde, scorMaximPerRunda),
        JocDeNoroc(numeZonaJoc, numarLocuriTotal, nrLocuriRezervate, pret, scorMaximPerJoc, valoarePunct),
        numarPremii(numarPremii), premii(premii), castigatori(castigatori), venituri(venituri) {}


///Copy constructor
SalaDeJocuri::SalaDeJocuri(const SalaDeJocuri& obj):Joc(obj),JocDeMasa(obj),JocDeNoroc(obj),
                                                    numarPremii(obj.numarPremii),premii(obj.premii),castigatori(obj.castigatori),venituri(obj.venituri){}

///Operator =
SalaDeJocuri& SalaDeJocuri :: operator = (const SalaDeJocuri& obj)
{
    if(this != &obj)
    {
        Joc::operator=(obj);
        JocDeMasa::operator=(obj);
        JocDeNoroc::operator=(obj);
        this->numarPremii = obj.numarPremii;
        this->premii = obj.premii;
        this->castigatori = obj.castigatori;
        this->venituri = obj.venituri;
    }
    return *this;
}

///Functii citire si afisare
ostream& SalaDeJocuri::afisare(ostream &out) const {
    JocDeMasa::afisare(out);
    JocDeNoroc::afisare(out);
    for(auto it = premii.begin(); it != premii.end(); it++)
    {
        out << it->first << ": " << it->second << endl;
    }
    return out;
}

istream& SalaDeJocuri::citire(istream &in) {
    JocDeMasa::citire(in);
    JocDeNoroc::citire(in);
    cout<< "~Numar premii: ";
    in >> numarPremii;
    cout<<"~Premii: \n";
    for(int i = 0; i < numarPremii; i++)
    {
        cout<<"Premiul "<<i+1<<": ";
        string premiu;
        in >> premiu;
        cout<<"Pretul premiului "<<i+1<<": ";
        double pret;
        in >> pret;
        premii.insert(pair<string,double>(premiu,pret));
    }
    return in;
}

///Functii
//Aceasta functie imi returneaza cate premii poate castiga un jucator in functie de scorul sau obtinut la jocul de noroc
int SalaDeJocuri :: suma(int *v)
{
    double bani = 0.00;
    for(int i = 0;i<4;i++)
    {
        bani += 100 -( abs( scorMaximPerJoc[i] - v[i]) * valoarePunct) ;
    }
    this->venituri += bani;
    if(this->venituri <301)
        return 1;
    else if(this->venituri <601 && this->venituri> 300)
        return 2;
    else if( this->venituri >600 )
        return 3;

}
//setteri si getteri
double SalaDeJocuri :: getValoarePunct()const {return this->valoarePunct;}
int SalaDeJocuri :: getScorMaximPerJoc()const {return this->scorMaximPerJoc[0];}
double SalaDeJocuri :: getVenituri()const {return this->venituri;}
 map<string,double> SalaDeJocuri :: getPremii()const{return premii;}

//Metoda constanta
//Aceasta functie imi returneaza un string cu toate informatiile CONFIDENTIALE despre sala de jocuri (venituri, scoruri maxime, etc)
string SalaDeJocuri :: informatii() const
{
    string text;
    double puncteMaxim  = 0.00;
    string rotunjit = "";
    for(int i = 0 ;i< to_string(venituri).size();i++)         //
    {                                                         //
        rotunjit += to_string(venituri)[i];                   //Rotunjesc veniturile la 2 zecimale
        if(to_string(venituri)[i] == '.')                     //
            i = to_string(venituri).size()-3;                 //
    }                                                         //

    text = "Veniturile sali de joc din "+ numeZonaJoc +": " + rotunjit + " RON\n";
    for(int i = 0;i<4;i++)
    {
        puncteMaxim += scorMaximPerJoc[i] * valoarePunct;
        text += "Numarul de pe casuta " + to_string(i+1) + ": " + to_string(scorMaximPerJoc[i]) + "\n";
    }
    rotunjit = "";
    for(int i = 0 ;i< to_string(puncteMaxim).size();i++)    //
    {                                                       //
        rotunjit += to_string(puncteMaxim)[i];              //
        if(to_string(puncteMaxim)[i] == '.')                //Rotunjesc veniturile la 2 zecimale
            i = to_string(puncteMaxim).size()-3;            //
    }                                                       //
    text += "Punctaj maxim: " + rotunjit + "\n";
    return text;
}

    //Functii
    //Aceasta functie adauga un nou element in map-ul de premii
    void SalaDeJocuri :: adaugaPremiu()
    {
        string premiu;
        cout<<"Premiul: ";
        cin >> premiu;
        cout<<"Pretul premiului: ";
        double pret;
        cin >> pret;
        premii.insert(pair<string,double>(premiu,pret));
        cout<<premii.size();
    }




class MeniuInteractiv {
private:
    static MeniuInteractiv* instance;

    // Constructorul privat pentru a împiedica crearea de instanțe în afara clasei
    MeniuInteractiv() {}

public:
    // Metoda publică pentru a obține instanța Singleton
    static MeniuInteractiv* getInstance() {
        if (!instance) {
            instance = new MeniuInteractiv();
        }
        return instance;
    }

    string numeSala(vector<Joc*> salidejocuri);

    void info(vector<Joc*> salidejocuri) ;
    void creare(vector<Joc*> salidejocuri) ;
    void stergere(vector<Joc*> salidejocuri) ;

    void jocDeNoroc(vector<Joc*> salidejocuri,Jucator &eu);

    void spanzuratoarea(vector<Joc*> salidejocuri) ;
    void xsi0(vector<Joc*> salidejocuri);
    void editare(vector<Joc*> salidejocuri);
    void jocdemasa(vector<Joc*> salidejocuri);

    ~MeniuInteractiv() = default;
};

 string MeniuInteractiv :: numeSala(vector<Joc*> salidejocuri) {
        string nume = "";
        vector<string> numeJocuri;
        for (int i = 0; i < salidejocuri.size(); i++) {
            numeJocuri.push_back(salidejocuri[i]->getnumeJoc());
            cout << salidejocuri[i]->getnumeJoc() << " ";
        }
        cout << endl << "---> ";
        cin >> nume;
        try
        {
        if(find(numeJocuri.begin(), numeJocuri.end(), nume) == numeJocuri.end()) 
            throw runtime_error("Sala nu exista!");
        
        }
        catch(const runtime_error& e)
        {
            cout<<e.what()<<endl;
            Sleep(1500);
            system("cls");
        }   
        system("cls");
        return nume;
    }

    void MeniuInteractiv::info(vector<Joc*> salidejocuri) {
        cout << "Introduceti numele salii despre care doriti sa aflati informatii: \nSali disponibile: ";
            string nume = numeSala(salidejocuri);
            for (int i = 0; i < salidejocuri.size(); i++) {
            if (salidejocuri[i]->getnumeJoc() == nume) {
                SalaDeJocuri *sala = dynamic_cast<SalaDeJocuri *>(salidejocuri[i]);     //Downcast din Joc in SalaDeJocuri
                if (sala != NULL) {
                    cout << sala->informatii() << endl;
                }
            }
        } 
    }

    void MeniuInteractiv :: creare(vector<Joc*> salidejocuri) {
        salidejocuri.push_back(new SalaDeJocuri());
        cin >> *salidejocuri.back();
        cout << "Sala a fost adaugata cu succes!\n";
    }

    void MeniuInteractiv :: stergere(vector<Joc*> salidejocuri) {
        
        cout << "Introduceti numele salii pe care doriti sa o stergeti: \nSali disponibile: ";
        string nume = numeSala(salidejocuri);
        for (int i = 0; i < salidejocuri.size(); i++) {
            if (salidejocuri[i]->getnumeJoc() == nume) {
                salidejocuri.erase(salidejocuri.begin() + i);
                cout << "Sala a fost stearsa cu succes!\n\n";
            }
        }
    }
    void MeniuInteractiv :: jocDeNoroc(vector<Joc*> salidejocuri,Jucator &eu)
    {
        int nr=0;
       
        char stare;
        map<string,double> premii;
        cout << "Introduceti numele sali de unde doriti sa alegeti un premiu: \nSali disponibile: ";
        string nume = numeSala(salidejocuri);
        while (stare != 'e') {
            int i = 0;
            system("cls");
            cout << "Balanta: " << eu.getBalanta() <<" RON"<< endl;
            cout<<"Apasati tasta <r> pentru a vedea cum functioneaza jocul\n";
            cout<<"Apasati tasta <a> pentru a adauga un premiu\n";
            cout << "Apasati tasta <b> pentru a va incerca norocul si sa vedeti cati bani puteti castiga\n";
            cout << "Apasati tasta <p> pentru a alege un premiu\n";
            cout << "Apasati tasta <e> pentru a iesi\n";
            cout << "---> ";
            cin >> stare;
            switch (stare) {

                case 'a':
                system("cls");
                 for(int i = 0; i < salidejocuri.size(); i++)
                 {
                    if(salidejocuri[i]->getnumeJoc() == nume)
                    {
                        SalaDeJocuri *sala = dynamic_cast<SalaDeJocuri *>(salidejocuri[i]); //Downcast din Joc in SalaDeJocuri
                        if(sala != NULL)
                        {
                            sala->adaugaPremiu();
                        }
                    }
                 }
                continue;

                case 'r':
                 system("cls");
                    cout<<"Va trebui sa introduceti 4 numere intre 1 si 20\n";
                    cout<<"Pentru fiecare numar introdus corect veti primi 100 de RON\n";
                    cout<<"In caz contrar o suma mai mica raporatata la cat de departe sunteti de numarul corect\n";
                    continue;

                case 'e':
                 system("cls");
                    break;

                case 'b':
                 system("cls");
                    eu--; //Scad numarul de rotiri
                    if(eu.getRotiri() == 0)
                    {
                        cout<<"Nu mai aveti rotiri disponibile!\n";
                        continue;
                    }
                    for (int i = 0; i < salidejocuri.size(); i++) {
                        if (salidejocuri[i]->getnumeJoc() == nume) {
                            cout << "Balanta: " << eu.getBalanta() <<" RON"<< endl;
                            cout<<"Rotiri ramase: "<< eu.getRotiri()<<endl;
                            cout << "Incercativa norocul si alegeti un premiu: \n";
                            int v[4];
                            for (int j = 0; j < 4; ++j) {
                                cout << "Numarul pentru casuta " << j + 1 << ": ";
                                cin >> v[j];
                            }
                            eu.setScorJN(v);
                            SalaDeJocuri *sala = dynamic_cast<SalaDeJocuri *>(salidejocuri[i]); //Downcast din Joc in SalaDeJocuri
                            if (sala != NULL)
                            {
                                nr = sala->suma(v);
                                eu += sala->getVenituri();          //Adaug veniturile la balanta jucatorului(eu)
                                cout << "Balanta: " << eu.getBalanta() << " RON"<<endl;
                                cout<<"Rotiri ramase: "<< eu.getRotiri()<<endl;
                                premii = sala->getPremii();

                            }
                        }
                    }
                    continue;

                case 'p':
                    system("cls");
                    cout << "Balanta: " << eu.getBalanta() <<" RON"<< endl;
                    cout<<"Alegeti un premiu pentru jucator(suma obiectului se va duce in veniturile companiei)\n";
                    


                        cout << R"(
     ____((______
    |    _\\     |
    |   |_|_|    |                 Mouse
)";
cout<<"1)  |   |   |    |                 ----->"; if(premii["Mouse"]< eu.getBalanta()) cout<<premii["Mouse"]<<" RON\n"; else cout<<"Indisponibil\n"; 
cout<<"    |   |___|    |\n";
cout<<"    |____________|\n\n";


                        cout << R"(
    ,--------------.
)";    
cout<<"2)  |* ********* oo|~~~~~~.         Tastatura\n";
cout<<"    |E888888 888 88|      /         ----->"; if(premii["Tastatura"]< eu.getBalanta()) cout<<premii["Tastatura"]<<" RON\n"; else cout<<"Indisponibil\n"; 
cout<<"    `=-=-=====-=-=-      `-=\n\n";
 


                        cout << R"(
     _______________
    |,----------.  |\
    ||           |=| |
3)  ||          || | |              Televizor
)";
cout<<"    ||       . _o| | |  __          ----->"; if(premii["Televizor"]< eu.getBalanta()) cout<<premii["Televizor"]<<" RON\n"; else cout<<"Indisponibil\n";
cout<<"    |`-----------' |/  /~/\n";
cout<<"     ~~~~~~~~~~~~~~~  / /~\n";
cout<<"                      ~~\n\n";


//Pnetru a aduga posibile alte premii adaugate in dictionarul Premii
for(auto it = premii.begin();  it != premii.end(); it++){
    i++;                                                    //Sare peste primele 3 premii
    if(i>3)
    {
cout<<"                                     "<<it->first<<endl;
cout<<i<<")     FARA IMAGINE (X)              ----->";if(it->second < eu.getBalanta()) cout<<it->second<<" RON\n\n"; else cout<<"Indisponibil\n\n";
    }
}
                    int numar;
                    cout<<"Apasati tasta corespunzatoare premiului pentru a-l achizitiona:\n -->";
                    cin>>numar;
                    if (numar<=premii.size())
                    {       
                            i = i-3;
                            for(auto it = premii.begin();  it != premii.end(); it++){
                                i++;
                                if(i == numar)
                                {
                                    if(it->second < eu.getBalanta())
                                    {
                                       
                                    eu -= it->second;
                                    cout<<it->first<<" a fost achizitionat cu succes!\n";
                                    eu.inserarePremiu(premii,it->first); //Adaug premiul in vectorul de premii al jucatorului(eu
                                    cout<<eu;
                                    it--;
                                    i=0;
                                    }
                                    else
                                    {
                                        
                                       // cout<<it->second<<" RON\n";
                                       // cout<<eu.getBalanta()<<" RON\n";
                                    cout<<"Nu aveti suficienti bani pentru a achizitiona acest premiu!\n";
                                    i=0;
                                    
                                    }
                                        
                                    
                                    break;
                                }
                            }
                        }
                    else
                        cout<<"Premiul " <<numar<<" nu este disponibil!\n";
                    
                    cout<<endl<<"->APASATI ORICE TASTA PENTRU A VA INTOARCE<-";
                     while (!_kbhit()) {}       //Functie care asteapta apasarea unei taste
                     continue;

                default:
                    continue;
            }
        }
    }


    void MeniuInteractiv :: spanzuratoarea(vector<Joc*> salidejocuri) {  
        cout << "Introduceti numele salii unde vreti sa va jucati spanzuratoarea: \nSali disponibile: ";
        string nume = numeSala(salidejocuri);
        for (int i = 0; i < salidejocuri.size(); i++) {
            if (salidejocuri[i]->getnumeJoc() == nume) {
                SalaDeJocuri *sala = dynamic_cast<SalaDeJocuri *>(salidejocuri[i]);  //Downcast din Joc in SalaDeJocuri
                if (sala != NULL) {
                    sala->spanzuratoarea();
                }
            }
        }
    }
    void MeniuInteractiv :: xsi0(vector<Joc*> salidejocuri){
        cout << "Introduceti numele salii unde vreti sa va jucati xsi0: \nSali disponibile: ";
        string nume = numeSala(salidejocuri);
        for (int i = 0; i < salidejocuri.size(); i++) {
            if (salidejocuri[i]->getnumeJoc() == nume) {
                SalaDeJocuri *sala = dynamic_cast<SalaDeJocuri *>(salidejocuri[i]);  //Downcast din Joc in SalaDeJocuri
                if (sala != NULL) {
                    sala->play();
                }
            }
        }
    }

    void MeniuInteractiv :: editare(vector<Joc*> salidejocuri){
        cout << "Introduceti numele salii unde vreti sa editati atributele unui joc: \nSali disponibile: ";
        string nume = numeSala(salidejocuri);
        for (int i = 0; i < salidejocuri.size(); i++) {
            if (salidejocuri[i]->getnumeJoc() == nume) {
                SalaDeJocuri *sala = dynamic_cast<SalaDeJocuri *>(salidejocuri[i]);  //Downcast din Joc in SalaDeJocuri
                if (sala != NULL) {
                    cout<<"La ce joc doriti sa modificati atributele?\n";
                    cout<<"1) Spanzuratoarea\n";
                    cout<<"2) X si 0\n";
                    cout<<"--->";
                    int optiune;
                    cin>>optiune;
                    try{
                        if(!cin.good()){
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            throw(runtime_error("Optiune invalida!"));
                        }
                    }
                    catch(const runtime_error &e){
                        cout<<e.what();
                        Sleep(1500);
                    }

                    if(optiune == 1){
                        Spanzuratoarea *sp = dynamic_cast<Spanzuratoarea*>(sala); //upcast din SalaDeJocuri in Spanzuratoarea
                        try
                        {
                           cin>>*sp;      
                        }
                        catch(const exception &e)
                        {
                            cout<<e.what()<<endl;
                            cout<<endl<<"->APASATI ORICE TASTA PENTRU A VA INTOARCE<-";
                            while (!_kbhit()) {}  
                        }
                        catch(int x)
                        {
                            cout<<"(!) Pentru incercari <=6 | Nr. cuvinte <=10: "<<x<<endl;
                            cout<<endl<<"->APASATI ORICE TASTA PENTRU A VA INTOARCE<-";
                            while (!_kbhit()) {}  
                        }
                        catch(string x)
                        {
                            cout<<"Dimensiunea maxima a unui cuvant este <=20,\n Dvs. ati introdus un cuvant de lungime : "<<x.size()<<endl;
                            cout<<endl<<"->APASATI ORICE TASTA PENTRU A VA INTOARCE<-";
                           while (!_kbhit()) {}  
                        }
                       
                    }  
                    else if(optiune == 2) 
                    {
                        XSi0 *x = dynamic_cast<XSi0*>(sala);
                         try
                         {
                            cin>>*x;
                         }
                         catch(const exception &e)
                         {
                             cout<<e.what()<<endl;
                             cout<<endl<<"->APASATI ORICE TASTA PENTRU A VA INTOARCE<-";
                             while (!_kbhit()) {}
                         }
                         catch(int x)
                         {
                            cout<<"(!)Dimensiunea maxima a tablei de joc este <=6:\n";
                            cout<<endl<<"->APASATI ORICE TASTA PENTRU A VA INTOARCE<-";
                            while (!_kbhit()) {}
                         }
                    }
                }
            }
        }
    }

    void MeniuInteractiv :: jocdemasa(vector<Joc*> salidejocuri)
    {
        char stare;
        while(stare !='e')
        {
            system("cls");
            cout<<"Apasati <e> pentru a iesi\n";
            cout<<"Apasati <j> pentru a edita atributele unui joc\n";
            cout<<"Apasati <s> pentru a va juca SPANZURATOAREA\n";
            cout<<"Apasati <x> pentru a va juca X SI 0\n";
            cout<<"--->";
            cin>>stare;
            switch(stare)
            {
                case 'j':
                  system("cls");
                    editare(salidejocuri);
                    continue;

                case 's':
                system("cls");
                    spanzuratoarea(salidejocuri);
                    continue;

                case 'x':
                system("cls");
                   xsi0(salidejocuri);
                    continue;

                case 'e':
                    system("cls");
                    break;

                default:
                    continue;
            }

        }

    }
// Inițializare statică
MeniuInteractiv* MeniuInteractiv::instance = nullptr;

/////MENIU INTERACTIV/////

void meniuInteractiv() {
    MeniuInteractiv* meniu = MeniuInteractiv::getInstance();

    Jucator eu;

    SalaDeJocuri sala1("Dristor", 20, 5, 24.99, 4, new int[4]{1, 2, 3,4}, 1.6,    new int[4]{13,15,19,5}, 3,
                        map<string,double>{{"Mouse",329.99},{"Tastatura",409.99},{"Televizor",599.99}},
                       vector<string>{"Andrei-Mouse"}, 129.60);
    SalaDeJocuri sala2("Titan", 15, 5, 29.99, 3, new int[4]{23,15,3}, 1.9,    new int[4]{12,5,17,9}, 3,
                      map<string,double>{{"Mouse",329.99},{"Tastatura",409.99},{"Televizor",599.99}},
                       vector<string>{"Matei-Tastatura"}, 202.78);

    vector<Joc* > salidejocuri;
    salidejocuri.push_back(&sala1);
    salidejocuri.push_back(&sala2);

    string stare1;
    char stare;
    while (stare != '!') {
        system("cls");
        set<char> optiuni = {'i', 'c', 'd', 'j', 'p', '!'};

        cout << "                             Bine ati venit !\n\n\n\n";
        cout << "Apasati ~!~ pentru a iesi\n";
        cout << "Apasati <c> pentru a adauga o noua sala in sistem\n";
        cout << "Apasati <d> pentru a sterge o sala\n";
        cout<<"Apasati <i> pentru a afisa informatii confidentiale despre o sala\n";
        SetConsoleTextAttribute(h,10);
        cout<<"Apasati <p> pentru a alege un premiu(Joc de noroc)\n";
        SetConsoleTextAttribute(h,11);
        cout<<"Apasati <j> pentru a va juca un joc\n";
        SetConsoleTextAttribute(h,7);
        cout << "---> ";
        try
        {
            cin>>stare1;
            stare = stare1[0];
            if(optiuni.find(stare) == optiuni.end())
                throw runtime_error("Comanda invalida!Incercati alta optiune");

        }
        catch(exception &e)
        {
            cout<<e.what();
            Sleep(1000);
        }
     

        switch (stare)
        {
                case 'i':
                system("cls");
                    meniu->info(salidejocuri);
                    cout<<endl<<"->APASATI ORICE TASTA PENTRU A VA INTOARCE<-";
                    while (!_kbhit()) {}  
                    continue;

                case 'c':
                system("cls");
                    meniu->creare(salidejocuri);
                    continue;

                case '!':
                system("cls");
                    system("cls");
                    break;

                case 'd':
                system("cls");
                    meniu->stergere(salidejocuri);
                    continue;

                case 'j':
                system("cls");
                    meniu->jocdemasa(salidejocuri);
                    continue;

                case 'p':
                system("cls");
                    meniu->jocDeNoroc(salidejocuri,eu);
                    continue;

            default:
             continue;
        
        }
    }
}

int main() {
   meniuInteractiv();
    return 0;
}
