#pragma once
#include <string>
#include <map>
#include <set>
#include "..\misinttypes\saint.h"
#include "fraction.h"

class Monomial // реализация мономинала(одночлен) для полинома? 
{
	/*member variable*/
private:
	Fraction<sint64> coefficient;
	std::map<sint8, Fraction<sint64>> factor;
private:
	bool error;

	/*member function*/
public: 
	Monomial();
	Monomial(std::string std_value);
	Monomial(Fraction<sint64> coefficient,
		std::map<sint8, Fraction<sint64>> factor = std::map<sint8, Fraction<sint64>>());
public:
	Fraction<sint64> GetDegree(); 
	Fraction<sint64> GetCoefficient(); // получение кэффа
	std::map<sint8, Fraction<sint64>>& GetFactor(); 
public:
	void SetCoefficient(sint64 a, sint64 b); 
	void SetCoefficientA(sint64 a); // установка кэфф а
	void SetCoefficientB(sint64 b); // установка кэфф б
	void Push(sint8 factor, Fraction<sint64> exponent); 
	bool Substitute(sint8 character, Monomial val); 
	void DelOne(); 
	void Clear_factor();
public:
	bool SimilarItems(Monomial b); 
	bool IsNumber(); // проверка на номер
	static bool IsValid(std::string val); 

public:
	void SetValue(Monomial value);
	void SetValue(std::string std_value);
public:
	void Input(std::string value);

public:
	std::string GetValue(); // получить значение
	std::string Out();
public:
	bool operator==(Monomial b);
	bool operator!=(Monomial b);
public:
	Monomial operator+(Monomial b);
	Monomial operator-(Monomial b);
	Monomial operator*(Monomial b);
	Monomial operator/(Monomial b);
public:
	operator Fraction<sint64>();
public:
	bool IsError(); // проверка на ошибку
};

sint64 GetLetterSize(Monomial& a); // получить размер букв??
