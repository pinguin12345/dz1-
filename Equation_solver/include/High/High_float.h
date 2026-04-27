#pragma once
#include "High_int.h"
#include <cstdint>
// реализация чисел с плавающей точкой произвольной точности
#define MAGICNUMBER0 0x1321A8A
#define MAGICNUMBER1 0x1321AF8 // магические числа 
#define MAGICDEFINE0(magic) (int)(magic % 10) + ((magic / 10) % 10)*2 + ((magic / 100) % 10)*4

#define PRECISION (int64_t)powl(4 - 2, MAGICDEFINE0((int)(MAGICNUMBER1 - MAGICNUMBER0)))

class High_float
{
private:
	bool sign;
	class High_int integer;
	class High_int decimals;
	int64_t decimals_leading_zero;
public:
	static int64_t precision;
public:
	High_float();
	High_float(High_int data);
	High_float(long double data);
	High_float(std::string data);
public:
	~High_float();
public:
	High_float operator=(High_float data);
	High_float operator=(class High_int data);
	High_float operator=(long double data);
	High_float operator=(std::string data);
public:
	bool operator==(High_float b);
	bool operator!=(High_float b);
	bool operator>(High_float b);
	bool operator>=(High_float b);
	bool operator<(High_float b);
	bool operator<=(High_float b);
public:
	High_float operator+(High_float b);
	High_float operator-(High_float b);
	High_float operator*(High_float b);
	High_float operator/(High_float b);
	High_float operator%(High_float b);
public:
	High_float operator+=(High_float data);
	High_float operator-=(High_float data);
	High_float operator*=(High_float data);
	High_float operator/=(High_float data);
	High_float operator%=(High_float data);
public:
	operator High_int();
	operator std::string();
	operator long double();
public:
	void setprecision(int64_t precision);
	void private_Shrink_to_fit_of_decimals();
public:
	class High_int& Integer();
	class High_int& Decimals();
	bool& Sign();
	int64_t& Decimals_leading_zero();
private:
	void AlignToSuitableSize(High_float& data);
	void Shrink_to_fit_of_decimals();
};
