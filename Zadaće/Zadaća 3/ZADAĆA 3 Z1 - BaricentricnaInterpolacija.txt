//TP 2021/2022: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>
#include <functional>
#include <cmath>
#include <iomanip>
#include <algorithm>

double fja(double x){
    return x*x+std::sin(x);
}

double w(int n, int d, int index, double xi, const std::vector<std::pair<double, double>> &x){

    double suma = 0;
    index++;

    for(int i=std::max(1,index-d); i<=std::min(index,n-d); i++){
        double proizvod = 1;
        for(int j=i-1; j<i+d; j++){
            if(index-1 == j) continue;
            proizvod*=(1/(xi-x[j].first));
        }
        proizvod*=pow(-1,i-1);
        suma+=proizvod;
    }
    
    return suma;

}

std::function<double(double)> BaricentricnaInterpolacija(std::vector<std::pair<double,double>> parovi, int d){
    
    if(d<0 || d>=parovi.size()) throw std::domain_error("Nedozvoljen red");

    for(int i=0; i<parovi.size(); i++){
        for(int j=0; j<parovi.size(); j++){
            if((parovi[j].first==parovi[i].first) && i!=j) throw std::domain_error("Neispravni cvorovi");
        }
    }

    int paroviSize = parovi.size();
    
    std::vector<double> omega;
    for(int i=0; i<parovi.size(); i++){
        omega.push_back(w(paroviSize,d,i,parovi[i].first,parovi));
    }

    return[parovi, omega, paroviSize](double x){
        
        for(int i=0; i<paroviSize; i++){
            if(x==parovi[i].first) return parovi[i].second;
        }

        int i=0;
        auto f1 = double((omega[i]*(parovi[i].second))/(x-parovi[i].first));
        auto f2 = omega[i]/(x-parovi[i].first);

        for(int i=1; i<paroviSize; i++){
            f1+=(omega[i]*(parovi[i].second))/(x-parovi[i].first);
            f2+=omega[i]/(x-parovi[i].first);
        }

        return f1/f2;

    };
}

std::function<double(double)> BaricentricnaInterpolacija(std::function<double(double)> f, double xmin, double xmax, double dx, double d){

    if(xmin>xmax || dx<=0) throw std::domain_error("Nekorektni parametri");
    std::vector<std::pair<double,double>> v;

    while(true){
        if(xmin>xmax) break;
        v.push_back(std::make_pair(xmin,f(xmin)));
        xmin+=dx;
    }
    return BaricentricnaInterpolacija(v,d);
}

int main ()
{
    try{
        while(true){
            
            std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
            int n;
            std::cin>>n;
            std::vector<std::pair<double,double>> vektor;
            
            if(n==1){

                std::cout<<"Unesite broj cvorova: ";
                int brCvorova;
                std::cin>>brCvorova;
                
                std::cout<<"Unesite cvorove kao parove x y: ";
                for(int i=0; i<brCvorova; i++){
                    double prvi, drugi;
                    std::cin>>prvi>>drugi;
                    vektor.push_back(std::make_pair(prvi, drugi));
                }

                std::cout<<"Unesite red interpolacije: ";
                int redInterpolacije;
                std::cin>>redInterpolacije;
                if(redInterpolacije<0 || redInterpolacije>=vektor.size()) throw std::domain_error("Nedozvoljen red");
                
                while(true){

                    double x;
                    std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                    std::cin>>x;

                    if(!std::cin) return 0;
                    std::cout<<"f("<<x<<") = "<<BaricentricnaInterpolacija(vektor,redInterpolacije)(x)<<std::endl;

                }

            }else if(n==2){

                double xmin,xmax,dx;
                std::cout<<"Unesite krajeve intervala i korak: ";
                std::cin>>xmin>>xmax>>dx;

                int d;
                std::cout<<"Unesite red interpolacije: ";
                std::cin>>d;

                if(xmin>xmax || dx<=0) throw std::domain_error("Nekorektni parametri");

                double xmin2 = xmin;

                while(true){

                    if(xmin2>xmax) break;

                    vektor.push_back(std::make_pair(xmin2,fja(xmin2)));
                    xmin2+=dx;

                }

                while(true){

                    double x;
                    std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                    std::cin>>x;

                    if(!std::cin) return 0;
                    std::cout<<"f("<<x<<") = "<<fja(x)<<" ";
                    std::cout<<"fapprox("<<x<<") = "<<BaricentricnaInterpolacija(fja,xmin,xmax,dx,d)(x)<<std::endl;

                }


            }
        }
    }catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }

	return 0;
}
