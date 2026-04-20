#pragma once
#include "..\misinttypes\saint.h"
#include "Equation_solver\High\High_int.h"
#include "mathematical_expression.h"
#include <iostream>

template <class T>
class Fraction // библеотека дробей
{
public:
	T a; 
	T b; 
public:
	Fraction<T> operator=(Fraction<T> b)
	{
		this->a = b.a;
		this->b = b.b;
		return *this;
	}
public: // операторы 
	Fraction<T> operator+(Fraction<T> b) 
	{
		Fraction<T> result();
		result.b = this->b * b.b;
		result.a = (this->a * b.b) + (b.a * this->b);
		return result;
	}
	Fraction<T> operator-(Fraction<T> b)
	{
		Fraction<T> result();
		result.b = this->b * b.b;
		result.a = (this->a * b.b) - (b.a * this->b);
		return result;
	}
	Fraction<T> operator*(Fraction<T> b)
	{
		Fraction<T> result();
		result.b = this->b * b.b;
		result.a = this->a * b.a;
		return result;
	}
	Fraction<T> operator/(Fraction<T> b)
	{
		Fraction<T> temp();
		temp.a = b.b;
		temp.b = b.a;
		return *this * temp;
	}
};

template <>
class Fraction <sint64>
{
public:
	sint64 a; // small int64?
	sint64 b;
public:
	Fraction(std::string value)
	{
		this->Input(value);
	}
	Fraction(sint64 a, sint64 b)
	{
		this->a = a;
		this->b = b;
		this->Simplification();
	}
	Fraction()
	{
		this->a = 0;
		this->b = 1;
	}
public:
	Fraction<sint64> operator=(sint64 value) // ниже операторы
	{
		this->a = value;
		this-> b = 1;
		return *this;
	}
public:
	bool operator==(Fraction<sint64> b)
	{
		
		this->Simplification();
		b.Simplification();
		if (this->a == b.a && this->b == b.b)
			return true;
		else
			return false;
	}
	bool operator!=(Fraction<sint64> b)
	{
		if (*this == b) return false;
		return true;
	}
public:
	bool operator>(Fraction<sint64> b)
	{
		if (this->a * b.b > b.a * this->b) return true;
		else return false;
	}
	bool operator>=(Fraction<sint64> b) 
	{
		if (this->a * b.b >= b.a * this->b) return true;
		else return false;
	}
	bool operator<(Fraction<sint64> b)
	{
		if (this->a * b.b < b.a * this->b) return true;
		else return false;
	}
	bool operator<=(Fraction<sint64> b)
	{
		if (this->a * b.b <= b.a * this->b) return true;
		else return false;
	}
public:
	Fraction<sint64> operator+(Fraction<sint64> b)
	{
		Fraction<sint64> result;
		result.b = this->b * b.b;
		result.a = (this->a * b.b) + (b.a * this->b);
		result.Simplification();
		return result;
	}
	Fraction<sint64> operator-(Fraction<sint64> b)
	{
		Fraction<sint64> result;
		result.b = this->b * b.b;
		result.a = (this->a * b.b) - (b.a * this->b);
		result.Simplification();
		return result;
	}
	Fraction<sint64> operator*(Fraction<sint64> b)
	{
		Fraction<sint64> result;
		result.b = this->b * b.b;
		result.a = this->a * b.a;
		result.Simplification();
		return result;
	}
	Fraction<sint64> operator/(Fraction<sint64> b)
	{
		Fraction<sint64> temp;
		temp.a = b.b;
		temp.b = b.a;
		return *this * temp;
	}
	Fraction<sint64> operator%(Fraction<sint64> b)
	{
		return *this - ((*this / b) * b);
	}
public:
	Fraction<sint64> operator+=(Fraction<sint64> b)
	{
		*this = *this + b;
		return *this;
	}
	Fraction<sint64> operator-=(Fraction<sint64> b)
	{
		*this = *this - b;
		return *this;
	}
	Fraction<sint64> operator*=(Fraction<sint64> b)
	{
		*this = *this * b;
		return *this;
	}
	Fraction<sint64> operator/=(Fraction<sint64> b)
	{
		*this = *this / b;
		return *this;
	}
	Fraction<sint64> operator%=(Fraction<sint64> b)
	{
		*this = *this % b;
		return *this;
	} // выше операторы
public:
	static sint64 gcd(sint64 a, sint64 b)
	{
		a = abs(a); b = abs(b);
		sint64 mod = a % b;
		while (mod != 0)
		{
			a = b;
			b = mod;
			mod = a % b;
		}
		return b;
	}
	static sint64 gcds(std::vector<sint64> a)
	{
		sint64 tem = a.at(0);
		for (suint64 i = 1; i < a.size(); i++) {
			tem = gcd(tem, a.at(i));
		}
		return tem;
	}
public:
	void Simplification() // упрощение?
	{
		if (this->a < 0 && this->b < 0)
		{
			this->a = 0 - this->a;
			this->b = 0 - this->b;
		}
		if (this->a * this->b < 0)
		{
			if (this->a > 0) this->a = 0 - this->a;
			this->b = abs(this->b);
		}

		sint64 a_sign = this->a > 0 ? 1 : -1;

		this->a = abs(this->a);

		sint64 temp = this->gcd(this->a, this->b);

		this->a /= temp;
		this->b /= temp;

		this->a *= a_sign;
	}
public:
	bool IsInteger() // проверка на интеграл?
	{
		this->Simplification();
		if (this->b == 1) return true;
		return false;
	}
	static bool IsValid(std::string val)
	{
		if (!ParenthesisSyntax(val)) return false;
		val = DeleteCircumjacentParentheses(val);
		val = DeleteTheBlank(val);

		if (val.size() == 0) return false;

		if (val.find('/') != std::string::npos)
		{
			for (suint64 i = 0; i < val.find('/'); i++)
			{
				if (val.at(i) == '-' && i != 0) return false;
				else if (val.at(i) == '-') continue;
				else if (!(val.at(i) >= '0' && val.at(i) <= '9'))
				{
					return false;
				}
			}

			for (suint64 i = val.find('/') + 1; i < val.size(); i++)
			{
				if (val.at(i) == '-' && i != val.find('/') + 1) return false;
				else if (val.at(i) == '-') continue;
				else if (!(val.at(i) >= '0' && val.at(i) <= '9'))
				{
					return false;
				}
			}
			return true;
		}
		
		for (suint64 i = 0; i < val.size(); i++)
		{
			if (val.at(i) == '-' && i != 0) return false;
			else if (val.at(i) == '-') continue;
			else if (!(val.at(i) >= '0' && val.at(i) <= '9'))
			{
				return false;
			}
		}
		return true;
	}

public:
	void SetValue(std::string std_value) // установка значения
	{
		std::string container; 
		suint64 i = 0;
		for (i; std_value.at(i) != '/'; i++)
		{
			container.push_back(std_value.at(i));
		}
		this->a = (sint64)(High_int)container;
		container.clear(), ++i;

		for (i; i < std_value.size(); i++)
		{
			container.push_back(std_value.at(i));
		}
		this->b = (sint64)(High_int)container;

		this->Simplification();
	}
	void Input(std::string value)
	{
		value = DeleteCircumjacentParentheses(value);

		std::string container; 
		suint64 i = 0; 

		for (i; i < value.size(); i++)
		{
			if (value.at(i) == '/') break;
			else container.push_back(value.at(i));
		}

		this->a = (sint64)(High_int)container;

		if (i == value.size())
		{
			this->b = 1;
			return;
		}

		container.clear(), ++i; 

		for (i; i < value.size(); i++)
		{
			container.push_back(value.at(i));
		}

		this->b = (sint64)(High_int)container;

		this->Simplification();
	}

public:
	std::string GetValue() // получить значение 
	{
		std::string value;
		value += (std::string)(High_int)this->a;
		value.push_back('/');
		value += (std::string)(High_int)this->b;
		return value;
	}
	std::string Out()
	{
		std::string value;
		value += (std::string)(High_int)this->a;

		if (this->a == 0) return value;

		if (this->b != 1)
		{
			value.push_back('/');
			value += (std::string)(High_int)this->b;
		}
		return value;
	}
};
