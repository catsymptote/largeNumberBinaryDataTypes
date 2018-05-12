/*	Author:	Catsymptote
 *	Email:	catsymptote@gmail.com
 */


/// Imports
#include "stdafx.h"
#include "massive.h"

#include <iostream>		// For printing
#include <string>		// For printing
//#include <cmath>		// For powers etc


/// ctors and dtor
massive::massive() { this->size = 0; }
massive::massive(long long int num) { this->setNumber(num); }
massive::~massive() {}



/* Set methods */

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

/// Set sign (+/-).
void massive::setSign(bool sign)
{
	this->sign = sign;
}



/* Get methods */

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
	if (this->sign)
		num *= -1;
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

/// Get the sign (+/-).
bool massive::getSign()
{
	return this->sign;
}



/* Prints */

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



/* Other functions */

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

/// Trims/removes every bits after (bigger than) index.
void massive::trim(unsigned int index)
{
	if (index < this->size - 1)
	{
		this->number.erase(this->number.begin() + index + 1, this->number.end());
		this->size = index + 1;
	}
}

/// Removes all leading zeros (00001110 will remove the first 0's).
void massive::trimLeadingZeros()
{
	//unsigned int leadingZeros = 0;
	unsigned int index = this->size - 1;
	while (index > 0)
	{
		if (this->getBit(index))
		{
			this->trim(index + 0);
			return;
		}
		index--;
	}
	/*
	for (int i = 0; i < this->size; i++)
	{
	if (this->getBit(i))
	break;
	else
	leadingZeros++;
	}
	*/
	//this->trim(this->size - leadingZeros);
}

/// Complement of the binary number.
void massive::complement()
{
	for (unsigned int i = 0; i < this->getSize(); i++)
	{
		this->setBit(i, !this->getBit(i));
	}
}



/* Mathematics */

/// A + B
massive massive::add(massive & A, massive & B)
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

/// A - B
massive massive::sub(massive & A, massive & B)
{
	massive cB;		// Complement of B
	cB = B;
	massive result;	// Return value
	
	// Add necessary 0's or 1's
	if (cB.getSize() < A.getSize())
		for (unsigned int i = 0; i < (A.getSize() - cB.getSize()); i++)
			cB.append_back(0);
	else if(cB.getSize() > A.getSize())
		for (unsigned int i = 0; i < (cB.getSize() - A.getSize()); i++)
			A.append_back(0);
		
	// Complement -> add -> complement
	
	// Print A and cB
	std::cout << "AOrig:\t";
	A.binaryPrint();

	// cB complement
	std::cout << "cBOrig:\t";
	cB.binaryPrint();
	cB.complement();
	std::cout << "cBCom:\t";
	cB.binaryPrint();

	// Increment cB by 1
	massive one;
	one.setNumber(1);
	cB = cB.add(cB, one);
	std::cout << "cB++:\t";
	cB.binaryPrint();

	

	// Result = add + trim 0 complement
	result = result.add(A, cB);
	std::cout << "resAdd:\t";
	result.binaryPrint();
	result.trim(A.getSize() -1);
	std::cout << "resTrm:\t";
	result.binaryPrint();
	result.trimLeadingZeros();
	std::cout << "rsTrm0:\t";
	result.binaryPrint();
	//result.complement();
	//std::cout << "resCom:\t";
	//result.binaryPrint();

	return result;
}

/// A * B
massive massive::mul(massive & A, massive & B)
{
	// Trim leading zeros
	A.trimLeadingZeros();
	B.trimLeadingZeros();
	A.binaryPrint();
	B.binaryPrint();

	// Multiply
	std::vector<massive> multElem;
	for (unsigned int i = 0; i < A.getSize(); i++)
	{
		multElem.push_back(massive(0));
		unsigned int j = 0, k = 0;
		while (j < B.getSize())
		{
			if (k < i)
			{
				multElem.at(i).append_back(0);
			}
			else if (A.getBit(i) && B.getBit(j))
			{
				multElem.at(i).append_back(1);
				j++;
			}
			else
			{
				multElem.at(i).append_back(0);
				j++;
			}
			k++;
		}
	}

	// Print multElem
	for (unsigned int i = 0; i < multElem.size(); i++)
	{
		for (int j = multElem.at(i).getSize() - 1; j > 0; j--)
		{
			std::cout << multElem.at(i).getBit(j);
		}
		std::cout << std::endl;
	}

	// Add together
	massive C;
	C = multElem.at(0);
	for (unsigned int i = 1; i < multElem.size(); i++)
	{
		C = C.add(C, multElem.at(i));
	}
	
	// Sign (+/-)
	if ((A.getSign() || B.getSign()) && !(A.getSign() && B.getSign()))
		C.setSign(1);
	else
		C.setSign(0);

	return C;
}

/// A / B
massive massive::div(massive & A, massive & B)
{
	return massive();
}

/// A^2
massive massive::pow(massive & A)
{
	return this->mul(A, A);
}

/// A++
void massive::increment()
{
	unsigned int first0Bit = this->getSize();
	unsigned int index = 0;
	while(index < this->getSize())
	{
		// If bit is 0 (otherwise pass this bit)
		if (!this->getBit(index))
		{
			first0Bit = index;
			break;
		}
		index++;
	}
	// Set first 0-bit to 1
	this->setBit(first0Bit, 1);
	// Set all lower bits to 0
	for (int i = first0Bit - 1; i >= 0; i--)
		this->setBit(i, 0);
}

/// A--
void massive::decrement()
{
	unsigned int first1Bit = this->getSize();
	unsigned int index = 0;
	while (index < this->getSize())
	{
		// If bit is 1 (otherwise pass this bit)
		if (this->getBit(index))
		{
			first1Bit = index;
			break;
		}
		index++;
	}
	// Set first 0-bit to 1
	this->setBit(first1Bit, 0);
	// Set all lower bits to 0
	for (int i = first1Bit - 1; i >= 0; i--)
		this->setBit(i, 1);
}



/* Comparisons */

/// A == B
bool massive::equals(massive & A, massive & B)
{
	// Sign comparison
	if (A.getSign() != B.getSign())
		return false;

	// Size comparison
	if (A.getSize() != B.getSize())
		return false;

	// Bit comparison, from lsd to msd
	for (unsigned int i = 0; i < A.getSize(); i++)
		if (A.getBit(i) != B.getBit(i))
			return false;

	// Otherwise
	return true;
}

/// A != B
bool massive::notEquals(massive & A, massive & B)
{
	return !(this->equals(A, B));
}

/// A > B
bool massive::isBigger(massive & A, massive & B)
{
	// size: A > B
	if (A.getSize() > B.getSize())
		return true;
	// size: A < B
	else if (A.getSize() < B.getSize())
		return false;
	// size: A == B?
	else
	{
		// Bitwise comparison, from msd to lsd
		for (int i = A.getSize() - 1; i >= 0; i--)
		{
			// A > B
			if (A.getBit(i) > B.getBit(i))
				return true;
			// A < B
			else if (A.getBit(i) < B.getBit(i))
				return false;
		}
	}

	// Otherwise (A == B)
	return false;
}

/// A < B
bool massive::isSmaller(massive & A, massive & B)
{
	return this->isBigger(B, A);
}

/// A >= B
bool massive::biggerOrEqual(massive & A, massive & B)
{
	if (this->isBigger(A, B) || this->equals(A, B))
		return true;

	return false;
}

/// A <= B
bool massive::smallerOrEqual(massive & A, massive & B)
{
	if (this->isSmaller(A, B) || this->equals(A, B))
		return true;

	return false;
}
