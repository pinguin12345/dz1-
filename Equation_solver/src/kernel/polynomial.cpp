#include "kernel/polynomial.h"
#include <iostream>
#include <math.h>

typedef std::map<sint8, Fraction<sint64>>::iterator FACTOR;

std::set<sint8> S_set_intersection(std::set<sint8> a, std::set<sint8> b)
{
	std::set<sint8> intersection;
	for (std::set<sint8>::iterator i = a.begin(); i != a.end(); i++)
	{
		if (b.find(*i) != b.end())
			intersection.insert(*i);
	}
	return intersection;
}

Polynomial::Polynomial(std::string std_value)
{
	this->SetValue(std_value);
}

Polynomial::Polynomial(Monomial val)
{
	*this = val;
}

Polynomial::Polynomial()
{
	this->list.push_back(Monomial());
	this->error = false;
}

void Polynomial::SetValue(Polynomial value)
{
	this->list.clear();

	*this = value;
}

void Polynomial::SetValue(std::string std_value)
{
	this->list.clear();

	std::string container; //����

	for (suint64 i = 0; i < std_value.size(); i++)
	{
		if (std_value.at(i) == '+')
		{
			this->Push(Monomial(container));
			container.clear();
		}
		else if(std_value.at(i) == 32){}
		else
		{
			container.push_back(std_value.at(i));
		}
	}
	this->Push(Monomial(container));

	this->DeleteZero();

	this->error = false;
}

void Polynomial::Input(std::string value)
{
	this->list.clear();

	value = DeleteCircumjacentParentheses(value);

	std::string container; 
	Monomial temp; 
	for (suint64 i = 0; i < value.size(); i++)
	{
		if (value.at(i) == '+')
		{
			temp.Input(container);
			this->Push(temp);
			container.clear();
		}
		else if (value.at(i) == 32) {}
		else
		{
			container.push_back(value.at(i));
		}
	}

	temp.Input(container);
	this->Push(temp);

	this->DeleteZero();
}

void Polynomial::Unite_like_terms()
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
			if (this->list.at(i).SimilarItems(this->list.at(j)))
			{
				this->list.at(i) = this->list.at(i) + this->list.at(j);
				this->list.erase(this->list.begin() + j);
			}
		}
	}
	this->DeleteZero();
	return;
}

void Polynomial::DeleteZero()
{
	if (this->list.size() <= 1
		&& this->list.at(0).GetCoefficient().a == 0)
	{
		this->list.at(0).Clear_factor();
		return;
	}

	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if (this->list.at(i).GetCoefficient().a == 0)
		{
			this->list.erase(this->list.begin() + i);
		}
	}

	if (this->list.size() == 0)
	{
		this->Push(Monomial());
	}
}

void Polynomial::Push(Monomial val)
{
	Monomial temp;
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if (this->list.at(i).SimilarItems(val))
		{
			temp = this->list.at(i);
			this->list.at(i) = temp + val;
			return;
		}
	}
	this->list.push_back(val);

	this->DeleteZero();
}

Monomial Polynomial::GetDegree()
{
	return this->list.at(GetLocationOfDegree());
}

Fraction<sint64> Polynomial::GetTheDegree()
{
	Fraction<sint64> degree;
	Monomial MAX_degree = this->GetDegree();
	for (FACTOR it = MAX_degree.GetFactor().begin(); it != MAX_degree.GetFactor().end(); it++)
	{
		degree += it->second;
	}
	return degree;
}

suint64 Polynomial::GetLocationOfDegree()
{
	Fraction<sint64> degree = this->list.at(0).GetDegree();

	sint64 element_quantity = GetLetterSize(this->list.at(0));

	suint64 location = 0;

	Fraction<sint64> temp_degree;
	for (suint64 i = 1, degree_temp = 0; i < this->list.size(); i++)
	{
		temp_degree = this->list.at(i).GetDegree();

		if (temp_degree > degree)
		{
			degree = temp_degree;
			element_quantity = GetLetterSize(this->list.at(i));
			location = i;
			continue;
		}
		else if (temp_degree == degree &&
			GetLetterSize(this->list.at(i)) < element_quantity)
		{
			degree = temp_degree;
			element_quantity = GetLetterSize(this->list.at(i));
			location = i;
		}
	}
	return location;
}

Fraction<sint64> Polynomial::GetDegreeOfMixOfchar(sint8 a)
{
	Fraction<sint64> degree = this->GetTheDegree();
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if ((this->list.at(i).GetFactor().find(a)) != (this->list.at(i).GetFactor().end()))
		{
			if ((this->list.at(i).GetFactor().find(a))->second < degree)
			{
				degree = (this->list.at(i).GetFactor().find(a))->second;
			}
		}
	}
	return degree;
}

Monomial Polynomial::CommonFactor(Polynomial val)
{
	Monomial common_factor;

	std::vector<sint64> facs;
	for (suint64 i = 0; i < val.list.size(); i++)
	{
		facs.push_back(val.list.at(i).GetCoefficient().a);
	}
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		facs.push_back(this->list.at(i).GetCoefficient().a);
	}
	sint64 common_number = Fraction<sint64>::gcds(facs);

	common_factor.SetCoefficient(common_number, 1);

	std::set<sint8> a_set_intersection;
	std::set<sint8> last_set; 
	std::set<sint8> set; 
	std::set<sint8> set_intersection; 

	for (FACTOR j = this->list.at(0).GetFactor().begin(); j != this->list.at(0).GetFactor().end(); j++)
	{	
		set.insert(j->first);
	}

	for (suint64 i = 0; i < this->list.size(); i++)
	{
		for (FACTOR j = this->list.at(i).GetFactor().begin(); j != this->list.at(i).GetFactor().end(); j++)
		{
			if (i % 2 == 0) last_set.insert(j->first);
			else
			{
				set.insert(j->first);
			}
		}

		if (i % 2 == 1)
		{
			set_intersection = S_set_intersection(
				S_set_intersection(last_set, set),
				set_intersection
			);

			last_set.clear();
		}
	}
	a_set_intersection = set_intersection;

	last_set.clear(); set.clear(); set_intersection.clear(); //��ʼ��

	for (FACTOR j = val.list.at(0).GetFactor().begin(); j != val.list.at(0).GetFactor().end(); j++)
	{
		set.insert(j->first);
	}

	for (suint64 i = 0; i < val.list.size(); i++)
	{
		for (FACTOR j = val.list.at(i).GetFactor().begin(); j != val.list.at(i).GetFactor().end(); j++)
		{
			if (i % 2 == 0) last_set.insert(j->first);
			else
			{
				set.insert(j->first);
			}
		}

		if (i % 2 == 1)
		{
			set_intersection = S_set_intersection(
				S_set_intersection(last_set, set),
				set_intersection
			);

			last_set.clear();
		}
	}
	set_intersection = S_set_intersection(a_set_intersection, set_intersection);

	for (std::set<sint8>::iterator it = set_intersection.begin(); it != set_intersection.end(); it++)
	{
		common_factor.Push(*it,
			(this->GetDegreeOfMixOfchar(*it) < val.GetDegreeOfMixOfchar(*it)
				? this->GetDegreeOfMixOfchar(*it) : val.GetDegreeOfMixOfchar(*it)));
	}

	return common_factor;
}

Fraction<sint64> Polynomial::LeastCommonMultiple_of_coe(Polynomial val)
{
	std::vector<sint64> a;
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		a.push_back(this->list.at(i).GetCoefficient().b);
	}
	for (suint64 i = 0; i < val.list.size(); i++)
	{
		a.push_back(val.list.at(i).GetCoefficient().b);
	}

	sint64 common_number = Fraction<sint64>::gcds(a);

	sint64 temp = 1;
	for (suint64 i = 0; i < a.size(); i++)
	{
		temp *= a.at(i);
	}
	return Fraction<sint64>(temp / common_number, 1);
}

void Polynomial::Clear()
{
	this->list.clear();
	this->Push(Monomial("(0/1)"));
}

bool Polynomial::Substitute(sint8 character, Polynomial val)
{
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if (this->list.at(i).GetFactor().find(character) != this->list.at(i).GetFactor().end())
		{
			if (this->list.at(i).GetFactor().find(character)->second.b != 1 ||
				this->list.at(i).GetFactor().find(character)->second.a < 0)
			{
				return false;
			}
		}
	}

	Polynomial temp; 
	sint64 exponent = 0;

	Fraction<sint64> coe_temp; 

	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if (this->list.at(i).GetFactor().find(character) 
			== this->list.at(i).GetFactor().end())
			continue;

		exponent = this->list.at(i).GetFactor().find(character)->second.a - 1;
		temp = val; 

		for (sint64 j = 0; j < exponent; j++)
		{
			temp *= val;
		}

		coe_temp = this->list.at(i).GetCoefficient();

		this->list.erase(this->list.begin() + i);

		*this += (Polynomial)(Monomial)coe_temp * temp;
	}
	return true;
}

Polynomial::operator Monomial()
{
	return this->list.at(0);
}

bool Polynomial::operator==(Polynomial val)
{
	this->Move();
	val.Move();
	if (this->list.size() != val.list.size())
	{
		return false;
	}
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if (this->list.at(i) != val.list.at(i))
		{
			return false;
		}
	}
	return true;
}

bool Polynomial::operator!=(Polynomial val)
{
	if (*this == val) return false;
	return true;
}

Polynomial Polynomial::operator=(Monomial val)
{
	this->list.clear();
	this->Push(val);
	this->error = val.IsError();
	return *this;
}

Polynomial Polynomial::operator=(Polynomial val)
{
	this->list = val.list;
	this->error = val.error;
	return *this;
}

Polynomial Polynomial::operator+(Monomial val)
{
	Polynomial result = *this;
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if (result.list.at(i).SimilarItems(val))
		{
			result.list.at(i) = result.list.at(i) + val;
			return result;
		}
	}
	result.list.push_back(Monomial(val));
	result.DeleteZero();
	result.Unite_like_terms();
	return result;
}

Polynomial Polynomial::operator-(Monomial val)
{
	Polynomial result = *this;
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if (result.list.at(i).SimilarItems(val))
		{
			result.list.at(i) = result.list.at(i) - val;
			return result;
		}
	}
	result.list.push_back(Monomial(
		Fraction<sint64>(0 - val.GetCoefficient().a, 
		val.GetCoefficient().b), 
		val.GetFactor())
	);
	result.DeleteZero();
	result.Unite_like_terms();
	return result;
}

Polynomial Polynomial::operator*(Monomial val)
{
	Polynomial result;

	for (suint64 i = 0; i < this->list.size(); i++)
	{
		result.list.push_back(this->list.at(i) * val);
	}
	result.DeleteZero();
	result.Unite_like_terms();
	return result;
}

Polynomial Polynomial::operator/(Monomial val)
{
	Polynomial result = *this;
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		result.list.at(i) = result.list.at(i) / val;
	}
	result.DeleteZero();
	result.Unite_like_terms();
	return result;
}

Polynomial Polynomial::operator+(Polynomial val)
{
	Polynomial result = *this;

	for (suint64 i = 0; i < val.list.size(); i++)
	{
		result = result + val.list.at(i);
	}
	result.DeleteZero();
	result.Unite_like_terms();
	return result;
}

Polynomial Polynomial::operator-(Polynomial val)
{
	Polynomial b = val;

	//0 - val
	for (suint64 i = 0; i < b.list.size(); i++)
	{
		b.list.at(i).SetCoefficientA(0 - b.list.at(i).GetCoefficient().a);
	}
	Polynomial result = *this + b;

	return result;
}

Polynomial Polynomial::operator*(Polynomial val)
{
	Polynomial result; 
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		for (suint64 j = 0; j < val.list.size(); j++)
		{
			result = result + (this->list.at(i) * val.list.at(j));
		}
	}
	result.DeleteZero();
	result.Unite_like_terms();
	return result;
}
//BAD PRACTICE!!! NEED TO REFACTOR
Polynomial Polynomial::operator/(Polynomial val)
{
	Polynomial result; 
	Polynomial remainder; 

	if (val.IsMonomial() && val.list.at(0).GetCoefficient().a == 0)
	{
		result.error = true;
		return result;
	}

	this->Move(); val.Move();

	if (*this == val)
	{
		Monomial temp;
		temp.SetCoefficient(1, 1);
		result = result + temp;
		return result;
	}

	if (IsParentPolynomial(*this, val) &&
		val.GetDegree().GetDegree() > Fraction<sint64>(0, 1) &&
		this->GetDegree().GetDegree() >= val.GetDegree().GetDegree())
	{
		remainder = *this;

		result.list.clear();

		if (!IsParentPolynomial(remainder, val) ||
			remainder.GetDegree().GetDegree() < val.GetDegree().GetDegree() ||
			(remainder.IsMonomial() && remainder.list.at(0) == Monomial("(0/1)")) ||
			(result.list.size() >= this->list.size())
			)
		{
			goto division_method;
		}

		while ( !( !IsParentPolynomial(remainder, val) ||
			remainder.GetDegree().GetDegree() < val.GetDegree().GetDegree() ||
			(remainder.IsMonomial() && remainder.list.at(0) == Monomial("(0/1)")) ||
			(result.list.size() >= this->list.size())
			) )
		{
			sint64 location_of_sonPolynomial = -1;

			for (suint64 i = 0; i < val.list.size(); i++)
			{
				if (IsParentPolynomial(remainder.list.at(0), val.list.at(i)))
				{
					location_of_sonPolynomial = i;
					break;
				}
			}

			if (location_of_sonPolynomial == -1)
			{
				goto division_method;
			}

			result.list.push_back(remainder.list.at(0) /
				val.list.at(location_of_sonPolynomial));

			remainder -= (val * result.list.at(result.list.size() - 1));

			remainder.Move();
		}
	}

	else
	{
	division_method:

		remainder = *this;

		result.list.clear();

		while (!((remainder.IsMonomial() && remainder.list.at(0) == Monomial("(0/1)")) ||
			result.list.size() >= this->list.size()))
		{
			result.list.push_back(remainder.list.at(0) / val.list.at(0));

			remainder -= (val * result.list.at(result.list.size() - 1));

			remainder.Move();
		}
	}

	if (result.list.size() == 0)
		result.Push(Monomial());

	result.DeleteZero();

	result.Unite_like_terms();

	if (result.list.size() == 0) result.SetValue("(0/1)");

	return result;
}

Polynomial Polynomial::operator%(Polynomial val)
{
	return *this - ((*this / val) * val);
}

Polynomial Polynomial::operator+=(Polynomial val)
{
	*this = *this + val;
	return *this;
}
Polynomial Polynomial::operator-=(Polynomial val)
{
	*this = *this - val;
	return *this;
}
Polynomial Polynomial::operator*=(Polynomial val)
{
	*this = *this * val;
	return *this;
}
Polynomial Polynomial::operator/=(Polynomial val)
{
	*this = *this / val;
	return *this;
}
Polynomial Polynomial::operator%=(Polynomial val)
{
	*this = *this % val;
	return *this;
}

bool Polynomial::IsMonomial()
{
	if (this->list.size() == 1)
	{
		return true;
	}
	return false;
}

bool Polynomial::IsNumber()
{
	if (!this->IsMonomial()) 
		return false;
	else if (this->list.at(0).IsNumber()) 
		return true;
	return false;
}

bool Polynomial::IsValid(std::string val)
{
	if (!ParenthesisSyntax(val)) return false;
	val = DeleteCircumjacentParentheses(val);

	if (val.size() == 0) return false;

	std::string container; 
	for (suint64 i = 0; i < val.size(); i++)
	{
		if (val.at(i) == '\40') continue;
		if (val.at(i) == '+')
		{
			if (!Monomial::IsValid(container))
				return false;
			container.clear();
			continue;
		}

		container.push_back(val.at(i));
	}

	if (!Monomial::IsValid(container))
		return false;
	return true;
}

bool Polynomial::IsError()
{
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		if (this->list.at(i).IsError())
		{
			this->error = true;
			return this->error;
		}
	}

	if (this->list.size() == 0)
	{
		this->error = true;
		return this->error;
	}

	return this->error;
}

std::string Polynomial::GetValue()
{
	std::string value;
	for (suint64 i = 0; i < this->list.size(); i++)
	{
		value += this->list.at(i).GetValue();
		if (i != this->list.size() - 1)
		{
			value.push_back('\40');
			value.push_back('+');
			value.push_back('\40');
		}
	}
	return value;
}

std::string Polynomial::Out()
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

void Polynomial::Move()
{
	if (this->list.size() <= 1)
	{
		return;
	}

	std::vector<Monomial> result;

	while (this->list.size() != 1)
	{
		result.push_back(this->list.at(this->GetLocationOfDegree()));
		this->list.erase(this->list.begin() + this->GetLocationOfDegree());
	}

	result.push_back(this->list.at(0));

	for (suint64 i = 0; i < result.size(); i++)
	{
		if (result.at(i).GetDegree().a == 0)
		{
			result.push_back(result.at(i));
			result.erase(result.begin() + i);
		}
	}

	this->list = result;
	return;
}

bool IsParentPolynomial(Polynomial a, Polynomial b)
{
	std::set<sint8> D; 
	std::set<sint8> E; 

	for (suint64 i = 0; i < a.list.size(); i++)
	{
		for (FACTOR j = a.list.at(i).GetFactor().begin(); j != a.list.at(i).GetFactor().end(); j++)
		{
			D.insert(j->first);
		}
	}

	for (suint64 i = 0; i < b.list.size(); i++)
	{
		for (FACTOR j = b.list.at(i).GetFactor().begin(); j != b.list.at(i).GetFactor().end(); j++)
		{
			E.insert(j->first);
		}
	}

	if (E.size() > D.size()) return false;

	for (std::set<sint8>::iterator it = E.begin(); it != E.end(); it++)
	{
		if (D.find(*it) == D.end()) return false;
	}

	return true;
}

bool IsLetterSetEquality(Polynomial a, Polynomial b)
{
	std::set<sint8> D;
	std::set<sint8> E;

	for (suint64 i = 0; i < a.list.size(); i++)
	{
		for (FACTOR j = a.list.at(i).GetFactor().begin(); j != a.list.at(i).GetFactor().end(); j++)
		{
			D.insert(j->first);
		}
	}

	for (suint64 i = 0; i < b.list.size(); i++)
	{
		for (FACTOR j = b.list.at(i).GetFactor().begin(); j != b.list.at(i).GetFactor().end(); j++)
		{
			E.insert(j->first);
		}
	}

	if (D == E) return true;

	return false;
}
