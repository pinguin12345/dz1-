#include "kernel/polynomial_exponential_sum.h"

Polynomial_Exponential_Sum::Polynomial_Exponential_Sum()
{
	this->Push(Polynomial_Exponential());
}

Polynomial_Exponential_Sum::Polynomial_Exponential_Sum(Polynomial_Exponential val)
{
	this->Push(val);
}

void Polynomial_Exponential_Sum::Unite_like_terms()
{
	if (this->list.size() <= 1)
	{
		return;
	}
	this->DeleteZero();
	for (suint64 i = 0; i < this->list.size() - 1; i++)
	{
		for (suint64 j = i + 1; j < this->list.size(); j++)
		{
			if ((this->list.at(i) + this->list.at(j)).coefficient.a != 0)
			{
				this->list.at(i) = this->list.at(i) + this->list.at(j);
				this->list.erase(this->list.begin() + j);
			}
		}
	}
	return;
}

void Polynomial_Exponential_Sum::Split()
{
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		this->list.at(i).simplify();
	}
}

void Polynomial_Exponential_Sum::Merge()
{
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		this->list.at(i).merge();
	}
}

void Polynomial_Exponential_Sum::DeleteZero()
{
	if (this->list.size() == 1)
	{
		return;
	}

	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if (this->list.at(i).coefficient.a == 0 || this->list.at(i).number == (Polynomial)Monomial("(0/1)"))
		{
			this->list.erase(this->list.begin() + i);
		}
	}
}

void Polynomial_Exponential_Sum::Push(Polynomial_Exponential val)
{
	this->list.push_back(val);
	this->DeleteZero();

	for (suint64 i = 0; i < this->list.size(); i++)
	{
		this->list.at(i).simplify();
	}

	this->Unite_like_terms();
}

std::string Polynomial_Exponential_Sum::Out()
{
	std::string value;
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		value += this->list.at(i).Out();
		if (i != this->list.size() - 1)
		{
			value.push_back('\40');
			value.push_back('+');
			value.push_back('\40');
		}
	}
	return value;
}

bool Polynomial_Exponential_Sum::IsPolynomial()
{
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if (!this->list.at(i).IsPolynomial())
		{
			return false;
		}
	}
	return true;
}

bool Polynomial_Exponential_Sum::IsNumber()
{
	if (this->IsPolynomial())
	{
		if (((Polynomial)*this).IsNumber())
		{
			return true;
		}
	}
	return false;
}

bool Polynomial_Exponential_Sum::IsPolynomial_Exponential()
{
	this->Unite_like_terms();
	if (this->list.size() == 1)
	{
		return true;
	}
	return false;
}

Polynomial_Exponential_Sum::operator Polynomial()
{
	Polynomial result;
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		result = result + (Polynomial)this->list.at(i);
	}
	return result;
}

Polynomial_Exponential_Sum::operator Polynomial_Exponential()
{
	if (this->list.size() == 0) return Polynomial_Exponential();

	return this->list.at(0);
}

bool Polynomial_Exponential_Sum::operator==(Polynomial_Exponential_Sum val)
{
	this->Unite_like_terms();
	this->DeleteZero();
	val.Unite_like_terms();
	val.DeleteZero();
	if (this->list.size() == val.list.size())
	{
		for (suint64 i = 0; i < this->list.size(); i++)
		{
			if (this->list.at(i) != val.list.at(i))
				return false;
		}
		return true;
	}

	return false;
}

bool Polynomial_Exponential_Sum::operator!=(Polynomial_Exponential_Sum val)
{
	return !(*this == val);
}
