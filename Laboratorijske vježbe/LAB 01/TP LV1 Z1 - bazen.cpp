// TP 2021/2022: LV 1, Zadatak 1
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
int main() {

  int duzinaBazena, sirinaBazena, dubinaBazena;
  cout << "Unesite duzinu, sirinu i dubinu bazena u metrima: ";
  cin >> duzinaBazena >> sirinaBazena >> dubinaBazena;

    duzinaBazena*=100;
    dubinaBazena*=100;
    sirinaBazena*=100;

  int sirinaPlocice;
  cout << "Unesite sirinu plocice u centimetrima: ";
  cin >> sirinaPlocice;

  int ukupanBrPlocica;

  ukupanBrPlocica =
      2 * ((dubinaBazena * duzinaBazena) / (sirinaPlocice * sirinaPlocice)) +
      2 * ((dubinaBazena * sirinaBazena) / (sirinaPlocice * sirinaPlocice)) +
      ((sirinaBazena * duzinaBazena) / (sirinaPlocice * sirinaPlocice));

  if (duzinaBazena % sirinaPlocice == 0 && sirinaBazena % sirinaPlocice == 0 &&
      dubinaBazena % sirinaPlocice == 0) {
    
    cout<<endl<<"Za poplocavanje bazena dimenzija "<<duzinaBazena/100<<"x"    <<sirinaBazena/100<<"x"<<dubinaBazena/100<<"m sa plocicama dimenzija "     <<sirinaPlocice<<"x"<<sirinaPlocice<<"cm"<<endl<<"potrebno je "<<ukupanBrPlocica<<" plocica."<<endl; 
    
    }else{ 
        cout<<endl<<"Poplocavanje bazena dimenzija "<<duzinaBazena/100<<"x"<<sirinaBazena/100<<"x"<<dubinaBazena/100<<"m sa plocicama dimenzija "<<sirinaPlocice<<"x"<<sirinaPlocice<<"cm"<<endl<<"nije izvodljivo bez lomljenja plocica!";
  }

  return 0;
}