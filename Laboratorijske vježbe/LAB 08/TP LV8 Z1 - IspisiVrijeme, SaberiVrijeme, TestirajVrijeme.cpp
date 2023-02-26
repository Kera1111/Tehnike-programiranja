//TP 2021/2022: LV 8, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>

struct Vrijeme{
    int sati, minute, sekunde;
};

void TestirajVrijeme(struct Vrijeme v){
    if(v.sati>24 || v.sati<0) throw std::domain_error("Neispravno vrijeme");
    else if(v.sati==24 && (v.minute!=0 || v.sekunde!=0)) throw std::domain_error("Neispravno vrijeme");
    else if(v.minute>59 || v.minute<0) throw std::domain_error("Neispravno vrijeme");
    else if(v.sekunde>59 || v.sekunde<0) throw std::domain_error("Neispravno vrijeme");
}

void IspisiVrijeme(struct Vrijeme v){
    TestirajVrijeme(v);
    if(v.sati<10) std::cout<<"0";
    std::cout<<v.sati<<":";
    if(v.minute<10) std::cout<<"0";
    std::cout<<v.minute<<":";
    if(v.sekunde<10) std::cout<<"0";
    std::cout<<v.sekunde;
}

Vrijeme SaberiVrijeme(struct Vrijeme v1, struct Vrijeme v2){
    TestirajVrijeme(v1), TestirajVrijeme(v2);
    Vrijeme v3;
    v3.sekunde = v1.sekunde+v2.sekunde;
    v3.minute = v1.minute + v2.minute + v3.sekunde / 60;
    v3.sekunde %= 60;
    v3.sati = (v1.sati + v2.sati + v3.minute / 60) % 24;
    v3.minute %= 60;
    return v3;
}

int main ()
{
    try{
        
    std::cout<<"Unesite prvo vrijeme (h m s): ";
    Vrijeme v1, v2;
    std::cin>>v1.sati>>v1.minute>>v1.sekunde;
    TestirajVrijeme(v1);
    std::cout<<"Unesite drugo vrijeme (h m s): ";
    std::cin>>v2.sati>>v2.minute>>v2.sekunde;
    TestirajVrijeme(v2);
    std::cout<<"Prvo vrijeme: ";
    IspisiVrijeme(v1);
    std::cout<<std::endl<<"Drugo vrijeme: ";
    IspisiVrijeme(v2);
    std::cout<<std::endl<<"Zbir vremena: ";
    IspisiVrijeme(SaberiVrijeme(v1,v2));
	
    }catch(std::domain_error izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
    
    return 0;
}
