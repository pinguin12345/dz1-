#include "kernel/equation.h"
#include "include/High/High_float.h"
#include <cmath>
#include <iostream>
#include <cctype>
#include <cstdint> // <- for int types
int main() { 
    std::cout << "-------------" << std::endl;
    
    // Тест дроби
    Fraction<sint64> f1(3, 4);
    Fraction<sint64> f2(2, 3);
    std::cout << "3/4 + 2/3 = " << (f1 + f2).Out() << std::endl;
    
    // Тест одночлена
    Monomial m("3*x^2*y");
    std::cout << "Monominal: " << m.Out() << std::endl;
    
    // Тест многочлена
    Polynomial p("3*x^2+2*x+1");
    std::cout << "Polynominal: " << p.Out() << std::endl;
    
    // Тест уравнения
    Equation eq;
    eq.Input("2*x + 3 = 7");
    std::cout << "equation: " << eq.Out() << std::endl;
    
    // Тест суммы экспонент
    Polynomial_Exponential_Sum pes;
    pes.Out();
    
    std::cout << "\n Успешно!" << std::endl;
    
    return 0;
}
// g++ -std=c++17 -g -o main.exe main.cpp src/kernel/arithmetic_expression.cpp src/kernel/equation.cpp src/kernel/mathematical_expression.cpp src/kernel/monomial.cpp src/kernel/polynomial.cpp src/kernel/polynomial_exponential.cpp src/kernel/polynomial_exponential_sum.cpp src/High/High_float.cpp src/High/High_int.cpp src/High/High_io.cpp src/High/High_math.cpp -Iinclude -Iinclude/kernel -Iinclude/High -Iinclude/misinttypes 