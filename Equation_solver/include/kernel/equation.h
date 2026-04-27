#pragma once
#include <vector>
#include <cstdint> // for int types
#include "polynomial.h"
#include "polynomial_exponential.h"
#include "polynomial_exponential_sum.h"
#include "fraction.h"
#include "Fraction_PES.h"
#include "../misinttypes/saint.h"
class Equation // класс для представления, преобразования и решения уравнений
{
public:
	std::vector<Polynomial> coefficient_left;
	std::vector<Polynomial> coefficient_right;
	std::vector<Fraction<sint64>> exponent_left;
	std::vector<Fraction<sint64>> exponent_right;
public:
	Fraction<Polynomial> root1; //Roots of poly
	//Roots of exp
	std::vector<Fraction<Polynomial_Exponential_Sum>> root2;

public:
	void SetValue(std::string value); //Set value
	void Input(std::string value); //Parse string with expression
	std::string GetValue(); // получить значение 
	std::string Out();
public:
	void DeleteZero(); // удалить ноль?
public:
	Fraction<sint64> GetTheHighestDegreeTermOfTheUnknown();
	sint64 FindDegree(Fraction<sint64> degree);
public:
	void ShiftItem();
	void Unite_like_terms();
public:
	//Does unknown exist?
	bool IsPurelyNumericalEquation();
	//Theorem of Algebra
	sint64 NumberOfRoot();
public:
	
	void linear_equation_with_one_unknown(); // линейное выражение с одним неизвестным
	void quadratic_equation_in_one_unknown(); // квадратичное выражение? с одним неизвестным
public:
	bool IsValid(std::string val); // проверка на валидность
};

//Eratosphene's sieve
inline bool IsPrime(sint64 n) {
	if (n <= 3) {
		return n > 1;
	}
	if (n % 6 != 1 && n % 6 != 5) {
		return false;
	}
	sint64 sqrt_n = (sint64)sqrt_n;
	for (sint64 i = 5; i <= sqrt_n; i += 6) {
		if (n % i == 0 || n % (i + 2) == 0) {
			return false;
		}
	}
	return true;
}

class Prime // проверка на простату? 
{
public:
	static std::vector<sint64> nk;
	sint64 n;
	suint64 i;
public:
	Prime() 
	{ 
		i = 0;
		n = 2; 
	}
	void Next()
	{
		if (++i < nk.size())
		{
			n = nk.at(i);
			return;
		}

		do
		{
			n += 2;
		} while (!IsPrime(n));
		return;
	}
};


std::string Out(Fraction<Polynomial> val);

Polynomial_Exponential Simplest_radical_AnBo(Polynomial_Exponential val);

Polynomial_Exponential Simplest_radical(Polynomial_Exponential val);
