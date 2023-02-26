//TP 2021/2022: Zadaća 5, Zadatak 5
#include <iomanip>
#include <iostream>
#include <new>
#include <string>
#include <stdexcept>
#include <fstream>

template <typename TipEl> 
class Matrica {
  char ime_matrice;
  int br_redova, br_kolona;
  TipEl **elementi;
  static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
  static void DealocirajMemoriju(TipEl **elementi, int br_redova);
  void KopirajElemente(TipEl **elem);
    std::string PretvoriuString(double x){
        std::string novi;
        novi = std::to_string(x);
        int len = novi.length();
        for(; len>0 && novi[len-1]=='0'; len--) novi.resize(len);
        if(novi[len-1]=='.') novi.resize(len-1);
        return novi;
    }
public:
void SacuvajUTekstualnuDatoteku(const std::string& ime) const;
void SacuvajUBinarnuDatoteku(const std::string& ime) const;
void ObnoviIzTekstualneDatoteke(const std::string& ime);
void ObnoviIzBinarneDatoteke(const std::string& ime);
  Matrica(int brRedova, int brKolona, char ime = 0);
  Matrica(const Matrica &m);
  Matrica(Matrica &&m);
  ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
  Matrica &operator=(const Matrica &m);
  Matrica &operator=(Matrica &&m);

    template<typename nekiDrugiTip>
    friend std::ostream &operator <<(std::ostream& ispis, Matrica<nekiDrugiTip> m);
    template<typename nekiTreciTip>
    friend std::istream &operator >> (std::istream& ispis, Matrica<nekiTreciTip> &m);

    friend Matrica<TipEl> operator *(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
        if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
        Matrica<TipEl> m3(m1.br_redova, m2.br_kolona);
        try{
            for(int i=0; i<m1.br_redova; i++){
                for(int j=0; j<m2.br_kolona; j++){
                    TipEl suma = 0;
                    for(int k=0; k<m2.br_redova; k++){
                        suma+=m1.elementi[i][k] * m2.elementi[k][j];
                    }
                    m3.elementi[i][j]=suma;
                }
            }
        }catch(...){
            throw std::bad_alloc();
        }
        return m3;
    }

    Matrica<TipEl> operator *=(double x){
        for(int i=0; i<br_redova; i++){
            for(int j=0; j<br_redova; j++){
                elementi[i][j] *= x;
            }
        }
        return *this;
    }

    Matrica<TipEl> operator *=(const Matrica<TipEl> &m2){
        Matrica<TipEl> m1(*this);
        if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
        Matrica<TipEl> m3(m1.br_redova, m2.br_kolona);
        try{
            for(int i=0; i<m1.br_redova; i++){
                for(int j=0; j<m2.br_kolona; j++){
                    TipEl suma = 0;
                    for(int k=0; k<m2.br_redova; k++){
                        suma+=m1.elementi[i][k]*m2.elementi[k][j];
                    }
                    m3.elementi[i][j] = suma;
                }
            }
        }catch(...){
            throw std::bad_alloc();
        }
        DealocirajMemoriju(elementi, br_redova);
        br_kolona = m2.br_kolona;
        elementi = AlocirajMemoriju(br_redova, br_kolona);
        for(int i=0; i<br_redova; i++){
            for(int j=0; j<br_kolona; j++){
                elementi[i][j] = m3[i][j];
            }
        }
        return *this;
    }

    friend Matrica<TipEl> operator -(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
        if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
        Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
        for(int i=0; i<m1.br_redova; i++){
            for(int j=0; j<m2.br_kolona; j++){
                m3.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
            }
        }
        return m3;
    }

    friend Matrica<TipEl> operator +(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
        if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
        Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
        for(int i=0; i<m1.br_redova; i++){
            for(int j=0; j<m2.br_kolona; j++){
                m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
            }
        }
        return m3;
    }

    friend Matrica<TipEl> operator *(const Matrica<TipEl> &m1, double a){
        Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
        for(int i=0; i<m1.br_redova; i++){
            for(int j=0; j<m1.br_kolona; j++){
                m3.elementi[i][j] = m1.elementi[i][j]*a;
            }
        }
        return m3;
    }

    friend Matrica<TipEl> operator *(double a, const Matrica<TipEl> &m1){
        return m1*a;
    }

    Matrica<TipEl> &operator +=(const Matrica<TipEl> &m){
        if(br_redova!=m.br_redova || br_kolona!=m.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
        for(int i=0; i<m.br_redova; i++){
            for(int j=0; j<m.br_kolona; j++){
                elementi[i][j] += m.elementi[i][j];
            }
        }
        return *this;
    }
    Matrica<TipEl> &operator -=(const Matrica<TipEl> &m){
        if(br_redova!=m.br_redova || br_kolona!=m.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
        for(int i=0; i<m.br_redova; i++){
            for(int j=0; j<m.br_kolona; j++){
                elementi[i][j] -= m.elementi[i][j];
            }
        }
        return *this;
    }

    TipEl* operator [](int indeks) const{
        return elementi[indeks];
    }

    TipEl* operator [](int indeks){
        return elementi[indeks];
    }

    TipEl operator()(int indeks1, int indeks2) const{
        if(indeks1<1 || indeks1>br_redova) throw std::range_error("Neispravan indeks");
        if(indeks2<1 || indeks2>br_kolona) throw std::range_error("Neispravan indeks");
        return elementi[indeks1-1][indeks2-1];
    }

    TipEl &operator()(int indeks1, int indeks2){
        if(indeks1<1 || indeks1>br_redova) throw std::range_error("Neispravan indeks");
        if(indeks2<1 || indeks2>br_kolona) throw std::range_error("Neispravan indeks");
        return elementi[indeks1-1][indeks2-1];
    }

  void Unesi();
  void Ispisi(int sirina_ispisa) const;
  template <typename Tip2>
  friend Matrica<Tip2> ZbirMatrica(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2);
  explicit operator std::string();
  Matrica<TipEl> (const std::string& ime, bool logvrijednost);
};

template <typename nekiTip>
Matrica <nekiTip>::operator std::string()
{
    std::string novi;
    novi += '{';
    for(int i=0; i<br_redova; i++){
        novi += '{';
        for(int j=0; j<br_kolona; j++){
            novi+=PretvoriuString(elementi[i][j]);
            if(j != br_kolona-1) novi += ',';
        }
        novi += '}';
        if(i != br_redova-1) novi+=',';
    }
    novi+='}';    
    return novi;
}

template <typename TipEl>
std::ostream &operator <<(std::ostream &ispis, Matrica<TipEl> m)
{
    int duzina = ispis.width();
    for(int i=0; i<m.br_redova; i++){
        for(int j=0; j<m.br_kolona; j++){
            ispis.width(duzina);
            ispis<<m.elementi[i][j];
        }
        std::cout<<std::endl;
    }
    return ispis;
}

template <typename TipEl>
std::istream &operator >>(std::istream &ispis, Matrica<TipEl> &m)
{
    for(int i=0; i<m.br_redova; i++){
        for(int j=0; j<m.br_kolona; j++){
            std::cout<<m.ime_matrice<<'('<<i+1<<','<<j+1<<')'<<" = ";
            ispis>>m.elementi[i][j];
        }
    }
    return ispis;
}

template <typename TipEl>
TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) {
  auto **elementi = new TipEl *[br_redova+1] {};
  try {
    for (int i = 0; i < br_redova; i++)
      elementi[i] = new TipEl[br_kolona]{};
  } catch (...) {
    DealocirajMemoriju(elementi, br_redova);
    throw;
  }
  return elementi;
}

template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) {
    if(elementi==nullptr) return;
  for (int i = 0; i < br_redova; i++)
    delete[] elementi[i];
  delete[] elementi;
}

template <typename TipEl>
Matrica<TipEl>::Matrica(int brRedova, int brKolona, char ime) {
    br_redova=brRedova;
    br_kolona=brKolona;
    ime_matrice=ime;
    elementi=AlocirajMemoriju(brRedova, brKolona);
}

template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elem) {
  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++)
      Matrica::elementi[i][j] = elem[i][j];
}

template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) {
    br_redova=m.br_redova; br_kolona=m.br_kolona;
      ime_matrice=m.ime_matrice;
      elementi=AlocirajMemoriju(m.br_redova, m.br_kolona);
  KopirajElemente(m.elementi);
}

template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) {
    br_redova = m.br_redova; 
    br_kolona = m.br_kolona; 
    elementi = m.elementi;
    ime_matrice = m.ime_matrice;
  m.br_redova = 0;
  m.elementi = nullptr;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(const Matrica<TipEl> &m) {
  if (br_redova < m.br_redova || br_kolona < m.br_kolona) {
    TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
    DealocirajMemoriju(elementi, br_redova);
    elementi = novi_prostor;
  } else if (br_redova > m.br_redova)
    for (int i = m.br_redova; i < br_redova; i++)
      delete elementi[i];
  br_redova = m.br_redova;
  br_kolona = m.br_kolona;
  ime_matrice = m.ime_matrice;
  KopirajElemente(m.elementi);
  return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(Matrica<TipEl> &&m) {
  std::swap(br_redova, m.br_redova);
  std::swap(br_kolona, m.br_kolona);
  std::swap(ime_matrice, m.ime_matrice);
  std::swap(elementi, m.elementi);
  return *this;
}

template <typename TipEl> void Matrica<TipEl>::Unesi() {
  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++) {
      std::cout << ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
      std::cin >> elementi[i][j];
    }
}

template <typename TipEl> void Matrica<TipEl>::Ispisi(int sirina_ispisa) const {
  for (int i = 0; i < br_redova; i++) {
    for (int j = 0; j < br_kolona; j++)
      std::cout << std::setw(sirina_ispisa) << elementi[i][j];
    std::cout << std::endl;
  }
}

template <typename TipEl>
Matrica<TipEl> ZbirMatrica(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}

template <typename TipEl>
Matrica<TipEl>::Matrica(const std::string& ime, bool logvrijednost){
    if(logvrijednost)//za binarnu
    {
        std::ifstream tok(ime, std::ios::binary);
        if(!tok) throw std::logic_error("Trazena datoteka ne postoji");
        tok.read(reinterpret_cast<char*>(this), sizeof *this);
        elementi = new TipEl* [br_redova];
        for(int i=0; i<br_redova; i++) elementi[i] = nullptr;
        for(int j=0; j<br_redova; j++){
            elementi[j] = new TipEl[br_kolona];
            tok.read(reinterpret_cast<char*>(elementi[j]), br_kolona*sizeof(TipEl));
        }
        if(!tok){
            for(int i=0; i<br_redova; i++) delete []elementi[i];
            delete [] elementi;
            throw std::logic_error("Problemi pri citanju datoteke");
        }
    }
    else{//za tekstualnu
        std::ifstream tok(ime);
        if(!tok) throw std::logic_error("Trazena datoteka ne postoji");
        int redovi = 0, kolone = 0, brojka=0;
        bool prvi = true;
        TipEl vrijednost;
        for(;;){
            if(!tok) break;
            for(;;){
                if(!tok) break;
                tok>>vrijednost;
                if(tok.peek()==','){
                    tok.get();
                    kolone++;
                }else if(tok.peek()=='\n'){
                    kolone++; break;
                }
            }
            if(!tok) break;
            redovi++;
            if(prvi){
                brojka = kolone;
                kolone = 0;
                prvi = false;
            }else{
                if(kolone!=brojka) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                kolone = 0;
            }
        }
        if(!tok && tok.bad()) throw std::logic_error("Problem pri citanju datoteke");
        if(!tok && !tok.eof()) throw std::logic_error("Datoteka sadrzi besmislene podatke");
        else if(!tok && tok.eof()) tok.clear();
        tok.close();
        tok.open(ime);

        br_kolona = brojka;
        br_redova = redovi+1;

        elementi = new TipEl*[br_redova];
        for(int i=0; i<br_redova; i++) elementi[i] = new TipEl[br_kolona];
        for(int i=0; i<br_redova; i++){
            for(int j=0; j<br_kolona; j++){
                tok>>elementi[i][j];
                if(j<br_kolona-1) tok.get();
            }
        }
    }
}

template<typename TipEl>
void Matrica<TipEl>::SacuvajUTekstualnuDatoteku(const std::string& ime) const{
    std::ofstream tok(ime);
    if(!tok) throw std::logic_error("Problem sa upisom u datoteku");
    for(int i=0; i<br_redova; i++){
        for(int j=0; j<br_kolona; j++){
            if(j==br_kolona-1)//zadnji element
            tok<<elementi[i][j];
            else 
            tok<<elementi[i][j]<<",";
            if(!tok) throw std::logic_error("Problemi sa upisom u datoteku");
        }
        tok<<std::endl;
    }
}

template<typename TipEl>
void Matrica<TipEl>::SacuvajUBinarnuDatoteku(const std::string& ime) const{
    std::ofstream tok(ime, std::ios::binary);
    tok.write((char*)this, sizeof(*this));
    for(int i=0; i<br_redova; i++)  tok.write((char*) elementi[i], br_kolona*sizeof(TipEl));
    if(!tok) throw std::logic_error("Problemi sa upisom u datoteku");
}

template<typename TipEl>
void Matrica<TipEl>::ObnoviIzTekstualneDatoteke(const std::string &ime){
    std::ifstream tok(ime);
    if(!tok) throw std::logic_error("Trazena datoteka ne postoji");
/* for(int i=0;i<br_redova;i++){
      delete [] elementi[i];
 }
 delete [] elementi;*/
    int redovi = 0, kolone = 0, brojka = 0;
    bool prvi = true;
    TipEl vrijednost;
    for(;;){
        if(!tok) break;
        for(;;){
            tok>>vrijednost;
            if(!tok) break;
            if(tok.peek()==','){
                tok.get();
                kolone++;
            }
            else if(tok.peek()=='\n'){
                kolone++;
                break;
            }
        }
        if(!tok) break;
        redovi++;
        if(prvi){
            brojka = kolone;
            kolone = 0;
            prvi = false;
        }else{
            if(kolone!=brojka) throw std::logic_error("Datoteka sadrzi besmislene podatke");
            kolone = 0;
        }
    }
        if(!tok && tok.bad()) throw std::logic_error("Problem pri citanju datoteke");
        if(!tok && !tok.eof()) throw std::logic_error("Datoteka sadrzi besmislene podatke");
        else if(!tok && tok.eof()) tok.clear();
        tok.close();
        tok.open(ime);

        br_kolona = brojka;
        br_redova = redovi+1;

        elementi = new TipEl*[br_redova];
        for(int i=0; i<br_redova; i++) elementi[i] = new TipEl[br_kolona];
        for(int i=0; i<br_redova; i++){
            for(int j=0; j<br_kolona; j++){
                tok>>elementi[i][j];
            }
        }
}

template<typename TipEl>
void Matrica<TipEl>::ObnoviIzBinarneDatoteke(const std::string& ime){
    std::ifstream tok(ime, std::ios::binary);
    if(!tok) throw std::logic_error("Trazena datoteka ne postoji");
    //oslobadjanje
for(int i=0;i<br_redova;i++){
     delete [] elementi[i];
}
 delete [] elementi;
    tok.read(reinterpret_cast<char*>(this), sizeof *this);
    elementi = new TipEl* [br_redova];
    for(int i=0; i<br_redova; i++) elementi[i] = nullptr;
    for(int j=0; j<br_redova; j++){
        elementi[j] = new TipEl[br_kolona];
        tok.read(reinterpret_cast<char*>(elementi[j]), br_kolona*sizeof(TipEl));
    }
    if(!tok){
        for(int i=0; i<br_redova; i++)
        delete[] elementi[i];
        delete[] elementi;
        throw std::logic_error("Problemi pri citanju datoteke");
    }
}

int main() {
  int m, n;
  std::cout << "Unesi broj redova i kolona za matrice:\n";
  std::cin >> m >> n;
  try {
    Matrica<double> a(m, n, 'A'), b(m, n, 'B');
    std::cout << "Unesi matricu A:\n";
    a.Unesi();
    std::cout << "Unesi matricu B:\n";
    b.Unesi();
    std::cout << "Zbir ove dvije matrice je:\n";
    ZbirMatrica(a, b).Ispisi(7);
  } catch (std::bad_alloc) {
    std::cout << "Nema dovoljno memorije!\n";
  }
  return 0;
}