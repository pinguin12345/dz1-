#pragma once
#include "polynomial.h"
#include <vector>
class Polynomial_Exponential // хранение и обработка полиноминальных экспонент
{
public:
	Fraction<sint64> coefficient;
	Polynomial number;
	Fraction<sint64> exponential;
public:
	bool error;

public:
	Polynomial_Exponential();
	Polynomial_Exponential(Polynomial value);
	Polynomial_Exponential(Fraction<sint64> coefficient, Polynomial number, Fraction<sint64> exponential);
public:
	void simplify();
	void merge();

public:
	static bool IsValid(std::string value);

public:
	void SetValue(std::string std_value);
	void SetValue(Polynomial value);
public:
	void Input(std::string value);

public:
	std::string GetValue();
public:
	std::string Out();

public:
	bool IsPolynomial();
	bool IsNumber();
public:
	operator Polynomial();
public: // операторы для полиномальных экспонент
	Polynomial_Exponential operator+(Polynomial_Exponential val);
	Polynomial_Exponential operator-(Polynomial_Exponential val);
	Polynomial_Exponential operator*(Polynomial_Exponential val);
	Polynomial_Exponential operator/(Polynomial_Exponential val);
	Polynomial_Exponential operator%(Polynomial_Exponential val);
public:
	bool operator==(Polynomial_Exponential val);
	bool operator!=(Polynomial_Exponential val);
public:
	bool Error(); // проверка на ошибку
};
