#include "kernel/arithmetic_expression.h"

bool ParenthesisSyntax(std::string val)
{
	sint64 left = 0, right = 0;

	for (suint64 i = 0; i < val.size(); i++)
	{
		if (val.at(i) == '(')
		{
			++left;
		}
		else if (val.at(i) == ')')
		{
			++right;
		}
	}

	if (left != right)
		return false;

	for (suint64 i = 0; i < val.size();)
	{
		if (val.at(i) != '(' && val.at(i) != ')')
		{
			val.erase(val.begin() + i);
		}
		else
		{
			++i;
		}
	}

	if (val.size() == 0) return true;
	if (val.at(0) == ')') return false;

	std::vector<bool> nums;

	for (suint64 i = 0; i < val.size(); i++)
	{
		if (val.at(i) == '(')
		{
			nums.push_back(false);
		}
		else
		{
			bool up_to_standard = true;
			for (sint64 i = nums.size() - 1; i >= 0; i--)
			{
				if (!nums.at(i))
				{
					up_to_standard = false;
					nums.at(i) = true;
					break;
				}
			}
			if (up_to_standard) return false;
		}
	}

	return true;
}

std::string DeleteCircumjacentParentheses(std::string val)
{
	val = DeleteTheBlank(val);

	if (!ParenthesisSyntax(val))
		return val;

	if (val.size() == 0) return val;

	while (val.at(0) == '(' && val.at(val.size() - 1) == ')')
	{
		val.erase(val.begin());
		val.erase(val.begin() + val.size() - 1);

		if (!ParenthesisSyntax(val))
		{
			val.insert(val.begin(), '(');
			val.push_back(')');
			return val; 
		}
	}
	return val;
}

std::string DeleteTheBlank(std::string val)
{
	for (suint64 i = 0; i < val.size();)
	{
		if (val.at(i) == '\40')
		{
			val.erase(val.begin() + i);
		}
		else
		{
			++i;
		}
	}
	return val;
}

bool CharacterInParentheses(std::string val, suint64 i)
{
	sint8 temp_char = 0;

	if (val.size() == 0)
		return false;

	if (val.size() <= i)
		return false;

	while (val.rfind(val.at(i)) != i)
	{
		val.erase(val.begin() + val.rfind(val.at(i)));
	}

	temp_char = val.at(i);

	while (val.find(temp_char) != val.rfind(temp_char))
	{
		val.erase(val.begin() + val.find(temp_char));
	}

	for (suint64 j = 0; j < val.size();)
	{
		if (!(val.at(j) == '(' || val.at(j) == ')' || val.at(j) == temp_char))
		{
			val.erase(val.begin() + j);
		}
		else
		{
			++j;
		}
	}

	for (suint64 j = 0; j < val.size();)
	{
		if (j + 1 < val.size())
		{
			if (val.at(j) == '(' && val.at(j + 1) == ')')
			{
				val.erase(val.begin() + j);
				val.erase(val.begin() + j);
				j = 0;
			}
			else
				++j;
		}
		else
			break;
	}

	if (!ParenthesisSyntax(val))
		return false;

	if (val.size() == 1)
		return false;

	return true;
}
