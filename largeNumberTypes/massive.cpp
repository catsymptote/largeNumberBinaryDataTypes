#include "stdafx.h"
#include "massive.h"

#include <iostream>		// For printing
#include <string>		// For printing
#include <cmath>		// For powers etc

/// ctors and dtor
massive::massive() {}
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
	unsigned int pwr;
	for(int i = exponent - 1; i >= 0; i--)
	{
		pwr = (unsigned int)(std::pow(2, i));
		if (num >= pwr)
		{
			this->number.at(i) = 1;
			num -= pwr;
			//std::cout << num << std::endl;
		}
	}
}

void massive::setSize(unsigned int size)
{
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
	return this->number.at(index);
}

void massive::setBit(unsigned int index, bool bit)
{
	/// This if should not be triggered.
	if (index > this->size - 1)
		for (unsigned int i = this->size; i <= index; i++)
			this->number.push_back(0);

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
	massive C;
	
	//unsigned int newSize;
	
	//C.setSize()
	for (unsigned int i = 0; i < this->size; i++)
	{
		if (A.getBit(i) && B.getBit(i))
		{
			C.setBit(i, 0);
			C.setBit(i + 1, 1);
		}
		else if (A.getBit(i) || B.getBit(i))
			C.setBit(i, 1);
		else
			C.setBit(i, 0);
	}

	//massive D(10);
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
