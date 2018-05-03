#include "stdafx.h"
#include "massive.h"

#include <iostream>		// For printing
#include <string>		// For printing
#include <cmath>		// For powers etc

/// ctors and dtor
massive::massive() { this->size = 0; }
massive::massive(long long int num) { this->setNumber(num); }
massive::~massive() {}

/// Input the number (base 10) as long long int, and store.
void massive::setNumber(long long int num)
{
	if (num < 0)
	{
		this->sign = 1;
		num *= -1;
	}
	else
		this->sign = 0;
	unsigned int exponent = 0;
	while (std::pow(2, exponent) <= num)
	{
		exponent++;
	}

	/// Fill vector with needed amonuts of 0's
	this->size = exponent;
	this->number.assign(exponent, 0);

	/// Loop through number
	long long int pwr;
	for(int i = exponent - 1; i >= 0; i--)
	{
		pwr = (long long int)(std::pow(2, i));
		if (num >= pwr)
		{
			this->number.at(i) = 1;
			num -= pwr;
			//std::cout << num << std::endl;
		}
	}
}

/// Clears the number and sets a new size.
void massive::setSize(unsigned int size)
{
	this->number.clear();
	this->number.assign(size, 0);
	this->size = size;
}

/// Returns the binary representation of the number.
std::vector<bool> massive::getBinary()
{
	return this->number;
}

bool massive::getBit(unsigned int index)
{
	if (index > this->size - 1)
		return 0;
	return this->number.at(index);
}

void massive::setBit(unsigned int index, bool bit)
{
	/// This if should generally not be triggered.
	if (index > this->size - 1)
	{
		for (unsigned int i = this->size; i <= index; i++)
			this->number.push_back(0);
		this->size = index + 1;
	}
	
	this->number.at(index) = bit;
}

/// Returns a long long int version of the number.
long long int massive::getDecimal()
{
	/// Does not check if long long int has sufficient capacity to store the number.
	long long int num = 0;
	for (int i = this->size - 1; i >= 0; i--)
	{
		if(this->number.at(i))
			num += (long long int)std::pow(2, i);
	}
	return num;
}

unsigned int massive::getSize()
{
	return this->size;
}

/// Prints the binary representation of the number.
void massive::binaryPrint()
{
	std::string numAsText = "";
	if (this->sign == 0)
		numAsText += "+";
	else
		numAsText += "-";
	
	for (int index = this->size - 1; index >= 0; index--)
	{
		if (this->number.at(index))
			numAsText += "1";
		else
			numAsText += "0";
	}
	std::cout << numAsText << std::endl;
}

/// Prints the decimal representation of the number.
void massive::decimalPrint()
{
	std::cout << this->getDecimal() << std::endl;
}

massive massive::add(massive &A, massive &B)
{
	/// Create new number
	massive C;
	
	/// Get and set biggest size
	if (A.getSize() > B.getSize())
		C.setSize(A.getSize());
	else
		C.setSize(B.getSize());
	
	/// Addition loop
	bool carry = false;
	//for (unsigned int i = 0; i < C.getSize(); i++)
	unsigned int i = 0;
	while(carry || (i < C.getSize()))
	{
		// 1+1
		if (A.getBit(i) && B.getBit(i))
		{
			if(carry)
				C.setBit(i, 1);
			else
			{
				C.setBit(i, 0);
				carry = true;
			}
		}
		// 1+0 || 0+1
		else if (A.getBit(i) || B.getBit(i))
		{
			if (carry)
				C.setBit(i, 0);
			else
			{
				C.setBit(i, 1);
				carry = false;
			}
		}
		// 0+0
		else
		{
			if (carry)
				C.setBit(i, 1);
			else
				C.setBit(i, 0);
			carry = false;
		}
		i++;
	}

	return C;
}

massive massive::sub(massive A, massive B)
{
	return massive();
}

massive massive::mul(massive A, massive B)
{
	return massive();
}

massive massive::div(massive A, massive B)
{
	return massive();
}
