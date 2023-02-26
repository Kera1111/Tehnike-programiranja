// TP 2021/2022: Zadaća 2, Zadatak 1
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

enum class Smjer {Nalijevo, Nadesno };
enum class Pravci {Sjever, Sjeveroistok, Istok, Jugoistok, Jug, Jugozapad, Zapad, Sjeverozapad};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar};
enum class Komande {Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj};

bool UnosKomande(Komande &, int &, KodoviGresaka &);

void AktivirajRobota();
void DeaktivirajRobota();
void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu);
void Idi(int &x, int &y, Pravci orijentacija, int korak);
void IspisiPoziciju(int x, int y, Pravci orijentacija);
void PrijaviGresku(KodoviGresaka kod_greske);
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y,
                   Pravci &orijentacija);

bool aktivan(true), kraj(false);

int main() {
  int x(0), y(0), parametar;
  Pravci orijentacija(Pravci::Sjever);
  Komande komanda;
  KodoviGresaka kod_greske;
  bool ispisi(true);
  while (!kraj) {
    if (ispisi){
       IspisiPoziciju(x, y, orijentacija); 
    }
      cout<<"Unesi komandu: "<<endl;
    if (UnosKomande(komanda, parametar, kod_greske)) {
      if (aktivan || komanda == Komande::Aktiviraj)
        IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
      ispisi = true;
    } else {
      PrijaviGresku(kod_greske);
      ispisi = false;
    }
    cin.clear();
    cin.ignore(10000, '\n');
  }
  cout << "Dovidjenja!" << endl;
  return 0;
}

void AktivirajRobota() { aktivan = true; }

void DeaktivirajRobota() { aktivan = false; }

void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu) {
  if (aktivan) {
    if (int(na_koju_stranu))
        if(orijentacija == Pravci::Sjeverozapad){
            orijentacija = Pravci::Sjever;
        }else orijentacija = Pravci(int(orijentacija) + 1);
    else{
        if(orijentacija == Pravci::Sjever){
            orijentacija = Pravci::Sjeverozapad;
        }else orijentacija = Pravci(int(orijentacija) - 1);
    }
     
  }
}

void Idi(int &x, int &y, Pravci orijentacija, int korak) {
  if (aktivan) {
    switch (orijentacija) {
    case Pravci::Sjever:
      y += korak;
      break;
    case Pravci::Sjeveroistok:
      y += korak;  x += korak; break;
    case Pravci::Istok:
      x += korak;
      break;
    case Pravci::Jugoistok:
      x += korak; y -= korak;  break;
    case Pravci::Jug:
      y -= korak;
      break;
    case Pravci::Jugozapad:
      y -= korak; x -= korak;  break;
    case Pravci::Zapad:
      x -= korak;
      break;
    case Pravci::Sjeverozapad:
      y += korak; x -= korak;  break;
    }
  }
}

void IspisiPoziciju(int x, int y, Pravci orijentacija) {
  cout << "Robot je " << (aktivan ? "" : "ne")
       << "aktivan, nalazi se na poziciji (" << x << "," << y
       << ") i gleda na ";
  switch (orijentacija) {
  case Pravci::Sjever:
    cout << "sjever"; break;
  case Pravci::Sjeveroistok:
    cout << "sjeveroistok"; break;
  case Pravci::Istok:
    cout << "istok"; break;
  case Pravci::Jugoistok:
    cout << "jugoistok"; break;
  case Pravci::Jug:
    cout << "jug"; break;
  case Pravci::Jugozapad:
    cout << "jugozapad"; break;
  case Pravci::Zapad:
    cout << "zapad"; break;
  case Pravci::Sjeverozapad:
    cout << "sjeverozapad"; break;
  }
  cout << "." << endl;
}

void PrijaviGresku(KodoviGresaka kod_greske) {
  switch (kod_greske) {
  case KodoviGresaka::PogresnaKomanda:
    cout << "Nerazumljiva komanda!" << endl; break;
  case KodoviGresaka::NedostajeParametar:
    cout << "Komanda trazi parametar koji nije naveden!" << endl; break;
  case KodoviGresaka::NeispravanParametar:
    cout << "Parametar komande nije ispravan!" << endl; break;
  case KodoviGresaka::SuvisanParametar:
    cout << "Zadan je suvisan parametar nakon komande!" << endl; break;
  }
}

void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y,
                   Pravci &orijentacija) {
  switch (komanda) {
  case Komande::Aktiviraj:
    AktivirajRobota(); break;
  case Komande::Deaktiviraj:
    DeaktivirajRobota(); break;
  case Komande::Idi:
    Idi(x, y, orijentacija, parametar); break;
  case Komande::Nalijevo:
    Rotiraj(orijentacija, Smjer::Nalijevo); break;
  case Komande::Nadesno:
    Rotiraj(orijentacija, Smjer::Nadesno); break;
  case Komande::Kraj:
    kraj = true; break;
  }
}

bool NemaNistaPoslije(KodoviGresaka &greska){
    cin.get();
    bool trenutni = true;
    while(cin.peek()!='\n') 
    if(cin.get()!=' ') trenutni=false, greska=KodoviGresaka::SuvisanParametar;
    return trenutni;
}

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {
cin>>ws;
switch(cin.peek()){
    case 'A':
        cin.get();
        if(cin.peek()=='+'){
            komanda=Komande::Aktiviraj;
            return NemaNistaPoslije(kod_greske);
        }else if(cin.peek()=='-'){
            komanda=Komande::Deaktiviraj;
            return NemaNistaPoslije(kod_greske);
        }else{
            kod_greske=KodoviGresaka::PogresnaKomanda;
            return false;
        }
    case 'I':
        cin.get();
        while(cin.peek()==' ') cin.get();
        if(cin.peek()=='\n'){
            kod_greske = KodoviGresaka::NedostajeParametar;
            return false;
        }
        int broj;
        cin>>broj;
        if(!cin){
            kod_greske = KodoviGresaka::NeispravanParametar;
            return false;
        }else if(cin.peek()!='\n' && cin.peek()!=' '){
            kod_greske = KodoviGresaka::NeispravanParametar;
            return false;
        }
        while(cin.peek()==' ') cin.get();
        if(cin.peek()!='\n'){
            kod_greske = KodoviGresaka::SuvisanParametar;
            return false;
        }else{
            komanda = Komande::Idi;
            parametar = broj;
            return true;
        }
    case 'L':
        komanda = Komande::Nalijevo;
        return NemaNistaPoslije(kod_greske);
    case 'D':
        komanda = Komande::Nadesno;
        return NemaNistaPoslije(kod_greske);    
    case 'K':
        komanda = Komande::Kraj;
        return NemaNistaPoslije(kod_greske);
    default: 
        kod_greske = KodoviGresaka::PogresnaKomanda;
        return false;
}

  return true;
}