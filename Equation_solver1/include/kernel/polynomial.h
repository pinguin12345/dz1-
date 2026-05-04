#pragma once
#include <vector>
#include <map>
#include <set>
#include "monomial.h" 


class Polynomial // описанние полинома
{
public:
	std::vector<Monomial> list;
private:
	bool error;

public:
	Polynomial(std::string std_value);
	Polynomial(Monomial val);
	Polynomial();
public:
	void SetValue(Polynomial value);
	void SetValue(std::string std_value);

public:
	void Input(std::string value);

public:
	std::string GetValue();
public:
	std::string Out();

public:
	void Unite_like_terms();
public:
	void DeleteZero();
public:
	void Push(Monomial val);
public:
	Monomial GetDegree();
	Fraction<sint64> GetTheDegree();
	suint64 GetLocationOfDegree();
	Fraction<sint64> GetDegreeOfMixOfchar(sint8 a);
public:
	Monomial CommonFactor(Polynomial val);
	Fraction<sint64> LeastCommonMultiple_of_coe(Polynomial val);
public:
	void Move();
public:
	void Clear();
public:
	bool Substitute(sint8 character, Polynomial val); // sint8 = char
public:
	bool operator==(Polynomial val);
	bool operator!=(Polynomial val);
public:
	Polynomial operator=(Monomial val);
	Polynomial operator=(Polynomial val); // !
public: // операторы для мономинала
	Polynomial operator+(Monomial val);
	Polynomial operator-(Monomial val);
	Polynomial operator*(Monomial val);
	Polynomial operator/(Monomial val);
public: // операторы для полинома
	Polynomial operator+(Polynomial val);
	Polynomial operator-(Polynomial val);
	Polynomial operator*(Polynomial val);
	Polynomial operator/(Polynomial val);
	Polynomial operator%(Polynomial val);
public:
	Polynomial operator+=(Polynomial val);
	Polynomial operator-=(Polynomial val);
	Polynomial operator*=(Polynomial val);
	Polynomial operator/=(Polynomial val);
	Polynomial operator%=(Polynomial val);
public:
	operator Monomial();
public:
	bool IsMonomial();
	bool IsNumber();
	static bool IsValid(std::string val); 
public:
	bool IsError();
};

bool IsParentPolynomial(Polynomial a, Polynomial b); // папа полином?

bool IsLetterSetEquality(Polynomial a, Polynomial b);
