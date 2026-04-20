#pragma once
#include <string>
#include "polynomial_exponential.h"
#include "Equation_solver\High\High_float.h"

//Class for arithmetic expressions, описанние выражений
class Arithmetic_Expression // класс для выражений, разбора и вычисления арифметических выражений
{
	/*member variable*/
public:
	Polynomial_Exponential a; // полиномиальные экспоненты
	Polynomial_Exponential b;
	sint8 _operator;

	/*member function*/
public:
	Arithmetic_Expression(); // класс арифметическое выражение
public:
	void Input(std::string value); // ввод
public:
	bool IsValid(std::string value); // проверка на корректность
public:
	bool IsNumber(); // проверка на число(тип это число или нет)
public:
	void Calculate(); // складывание вычитание и тд?
public:
	std::string Out(); // ?
	//Approx
	std::string Approximate_Out();
protected:
	long double Rooting(long double a, sint64 n);
};