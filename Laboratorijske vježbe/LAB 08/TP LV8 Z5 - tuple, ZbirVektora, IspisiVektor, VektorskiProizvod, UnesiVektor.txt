// TP 2021/2022: LV 8, Zadatak 5
#include <cmath>
#include <iostream>
#include <tuple>

typedef std::tuple<double, double, double> Vektor3d;

void UnesiVektor(Vektor3d &v) {
  double x, y, z;
  std::cout << "X = ";
  std::cin >> x;
  std::cout << "Y = ";
  std::cin >> y;
  std::cout << "Z = ";
  std::cin >> z;
  v = std::tie(x, y, z);
}

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) { 
    // return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return {std::get<0>(v1) + std::get<0>(v2), std::get<1>(v1) + std::get<1>(v2), std::get<2>(v1) + std::get<2>(v2)};
}

Vektor3d VektorskiProizvod(const Vektor3d &v1, const Vektor3d &v2){
    // return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
    // v1.x * v2.y - v1.y * v2.x};
    return {std::get<1>(v1) * std::get<2>(v2) - std::get<2>(v1) * std::get<1>(v2), std::get<2>(v1) * std::get<0>(v2) - std::get<0>(v1) * std::get<2>(v2), std::get<0>(v1) * std::get<1>(v2) - std::get<1>(v1) * std::get<0>(v2)};
}

void IspisiVektor(const Vektor3d &v) {
    // std::cout << "{" << v.x << "," << v.y << "," << v.z << "}";
    std::cout << "{" << std::get<0>(v) << "," << std::get<1>(v) << ","
            << std::get<2>(v) << "}";
}

int main() {
  Vektor3d a, b;
  std::cout << "Unesi prvi vektor:\n";
  UnesiVektor(a);
  std::cout << "Unesi drugi vektor:\n";
  UnesiVektor(b);
  std::cout << "Suma ova dva vektora je: ";
  IspisiVektor(ZbirVektora(a, b));
  std::cout << std::endl << "Njihov vektorski prozivod je: ";
  IspisiVektor(VektorskiProizvod(a, b));
  return 0;
}
