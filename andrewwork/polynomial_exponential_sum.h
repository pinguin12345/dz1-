#pragma once
#include <vector>
#include "polynomial_exponential.h"
class Polynomial_Exponential_Sum // сумма полиноминальных экспонент 
{
public:
	std::vector<Polynomial_Exponential> list;
public:
	Polynomial_Exponential_Sum();
	Polynomial_Exponential_Sum(Polynomial_Exponential val);
public:
	void Unite_like_terms();
public:
	void Split(); 
	void Merge(); 
public:
	void DeleteZero();
public:
	void Push(Polynomial_Exponential val);
р

public:
	std::string Out();

public: // проверки
	bool IsPolynomial();
	bool IsNumber();
	bool IsPolynomial_Exponential();
public:
	operator Polynomial();
	operator Polynomial_Exponential();

public:
	bool operator==(Polynomial_Exponential_Sum val); // val значение с чем сравниваем
	bool operator!=(Polynomial_Exponential_Sum val);
};
