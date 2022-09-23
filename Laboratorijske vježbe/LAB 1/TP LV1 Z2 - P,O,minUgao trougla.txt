//TP 2021/2022: Tutorijal 1, Zadatak 2
#include <iostream>
#include <cmath>
using namespace std;

int main ()
{

    double a,b,c;
    cout<<"Unesite tri broja: ";
    cin>>a>>b>>c;

    if(a>0 && b>0 && c>0 && a+b>c && b+c>a && a+c>b){
        
        double s,P,O,alfa,beta,gama,minUgao;

        s=(a+b+c)/2;
        P=sqrt(s*(s-a)*(s-b)*(s-c));
        O=a+b+c;
        alfa = acos((b*b + c*c - a*a) / (2 * b * c)) *(180.0/(4*atan(1)));
        beta = acos((a*a + c*c - b*b) / (2 * a * c)) *(180.0/(4*atan(1)));
        gama = acos((b*b + a*a - c*c) / (2 * b * a)) *(180.0/(4*atan(1)));

        if (alfa<=beta && alfa<=gama) minUgao=alfa;
        if (beta<=alfa && beta<=gama) minUgao=beta;
        if (gama<=alfa && gama<=beta) minUgao=gama;

        int h,m,sek;
        h=minUgao;
        m=((minUgao-h)*60);
        sek=((((minUgao-h)*60-m)*60));

        cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<O<<"."<<endl;
        cout<<"Njegova povrsina iznosi "<<P<<"."<<endl;
        cout<<"Njegov najmanji ugao ima "<<h<<" stepeni, "<<m<<" minuta i "<<sek<<" sekundi."<<endl;

    }else{
        cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!"<<endl;
    }

	return 0;
}