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

/// Set bit at specific index.
void massive::setBit(unsigned int index, bool bit)
{
	/// This if should generally not be triggered.
	if (index > this->size - 1)
	{
		for (unsigned int i = this->size; i <= index; i++)
			this->append_back(0);
		//this->size = index + 1;
	}

	this->number.at(index) = bit;
}

/// Append a value
void massive::append_back(bool bit)
{
	this->number.push_back(bit);
	this->size++;
}

void massive::append_front(bool bit)
{
	this->number.push_front(bit);
	this->size++;
}

void massive::trim(unsigned int index)
{
	if (index < this->size - 1)
	{
		this->number.erase(this->number.begin() + index, this->number.end());
		this->size = index;
	}
}

void massive::trimLeadingZero()
{
	unsigned int leadingZeros = 0;
	for (int i = 0; i < this->size; i++)
	{
		if (this->getBit(i))
			break;
		else
			leadingZeros++;
	}
	this->trim(leadingZeros);
}


/// Returns the binary representation of the number.
std::deque<bool> massive::getBinary()
{
	return this->number;
}

/// Returns a long long int version of the number.
long long int massive::getDecimal()
{
	/// Does not check if long long int has sufficient capacity to store the number.
	long long int num = 0;
	for (int i = this->size - 1; i >= 0; i--)
	{
		if (this->number.at(i))
			num += (long long int)std::pow(2, i);
	}
	return num;
}

/// Get the size (bit length) of the number.
unsigned int massive::getSize()
{
	return this->size;
}

/// Set bit at specific index.
bool massive::getBit(unsigned int index)
{
	if (index > this->size - 1)
		return 0;
	return this->number.at(index);
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



void massive::complement()
{
	for (int i = 0; i < this->getSize(); i++)
	{
		this->setBit(i, !this->getBit(i));
	}
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

massive massive::sub(massive &A, massive &B)
{
	massive cB;		// Complement of B
	cB = B;
	massive result;	// Return value
	
	// Add necessary 0's or 1's
	if (cB.getSize() < A.getSize())
		for (int i = 0; i < (A.getSize() - cB.getSize()); i++)
			cB.append_back(0);
	else if(cB.getSize() > A.getSize())
		for (int i = 0; i < (cB.getSize() - A.getSize()); i++)
			A.append_back(0);
		
	// Complement -> add -> complement
	
	std::cout << "cB:\t";
	cB.binaryPrint();
	cB.complement();
	std::cout << "cB:\t";
	cB.binaryPrint();

	// Increment cB by 1
	massive one;
	one.setNumber(1);
	std::cout << "one:\t";
	one.binaryPrint();
	cB = cB.add(cB, one);
	std::cout << "cB:\t";
	cB.binaryPrint();

	// Print A and cB
	std::cout << "A:\t";
	A.binaryPrint();
	std::cout << "cB:\t";
	cB.binaryPrint();

	// Result = add + trim 0 complement
	result = result.add(A, cB);
	std::cout << "resAdd:\t";
	result.binaryPrint();
	result.trim(A.getSize() -1);
	std::cout << "resTrm:\t";
	result.binaryPrint();
	result.trimLeadingZero();
	std::cout << "rsTrm0:\t";
	result.binaryPrint();
	result.complement();
	std::cout << "resCom:\t";
	result.binaryPrint();

	return result;
}

massive massive::mul(massive A, massive B)
{
	return massive();
}

massive massive::div(massive A, massive B)
{
	return massive();
}
