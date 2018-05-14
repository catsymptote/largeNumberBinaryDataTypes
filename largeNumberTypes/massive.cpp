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
massive::massive()
{
	this->setNumber(0);
	this->size = 1;
}
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
			this->append_front(0);
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
void massive::append_front(bool bit)
{
	this->number.push_back(bit);
	this->size++;
}

void massive::append_back(bool bit)
{
	this->number.push_front(bit);
	this->size++;
}

void massive::remove_front()
{
	this->number.pop_back();
	this->size--;
}

void massive::remove_back()
{
	this->number.pop_front();
	this->size--;
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
	massive Ax = A, Bx = B, C, tmp;
	
	// Make sure the first is smaller than the second
	bool CSign = 0;
	if (Ax < Bx)
	{
		tmp = Ax;
		Ax = Bx;
		Bx = tmp;
		CSign = 1;;
	}

	// Add necessary 0's or 1's
	if (Bx.getSize() < Ax.getSize())
	{
		for (unsigned int i = 0; i < (Ax.getSize() - Bx.getSize()); i++)
		{
			Bx.append_front(0);
		}
	}
	else if (Bx.getSize() > Ax.getSize())
	{
		for (unsigned int i = 0; i < (Bx.getSize() - Ax.getSize()); i++)
		{
			Ax.append_front(0);
		}
	}
	Ax.binaryPrint();
	Bx.binaryPrint();
		
	// Complement -> increment -> add numbers -> trim
	!Bx;
	Bx.binaryPrint();
	Bx.increment();
	std::cout << "--------" << std::endl;
	Ax.binaryPrint();
	Bx.binaryPrint();
	std::cout << "--------" << std::endl;
	C = Ax + Bx;
	C.binaryPrint();
	C.trim(Ax.getSize() - 1);
	C.binaryPrint();

	C.setSign(CSign);

	return C;
}

/// A * B
massive massive::mul(massive & A, massive & B)
{
	// Trim leading zeros
	A.trimLeadingZeros();
	B.trimLeadingZeros();

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
				multElem.at(i).append_front(0);
			}
			else if (A.getBit(i) && B.getBit(j))
			{
				multElem.at(i).append_front(1);
				j++;
			}
			else
			{
				multElem.at(i).append_front(0);
				j++;
			}
			k++;
		}
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
massive massive::div(massive & A, massive & B, bool mod)
{
	massive C, A1, A2;// , num2, BOver2;
	A1 = A;
	A2 = A;
	A2.mul2();
	//num2.setNumber(2);
	//BOver2 = BOver2.div(B, num2);
	long long holeDivs = 0;
	
	// Hole number division
	while (A1.isBigger(A1, B))
	{
		A1 = A1.sub(A1, B);
		C.increment();
		//holeDivs++;
	}

	if (mod)
		return A1;

	// Half-way check (if)
	
	if (A1.isBigger(A2, B))
		C.increment();
		//holeDivs++;

	//C.setNumber(holeDivs);
	return C;
}

/// A^2
massive massive::pow(massive & A)
{
	return this->mul(A, A);
}

/// this ++
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

/// this --
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

/// this / 2
void massive::div2()
{
	this->remove_back();
}

/// this * 2
void massive::mul2()
{
	this->append_back(0);
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



/* Overloading operators */
/* Comparators */

/// >
bool operator > (massive & A, massive & B)
{
	return A.isBigger(A, B);
}

/// <
bool operator < (massive & A, massive & B)
{
	return A.isSmaller(A, B);
}

/// ==
bool operator == (massive & A, massive & B)
{
	return A.equals(A, B);
}

/// !=
bool operator != (massive & A, massive & B)
{
	return A.notEquals(A, B);
}

/// >=
bool operator >= (massive & A, massive & B)
{
	return A.biggerOrEqual(A, B);
}

/// <=
bool operator <= (massive & A, massive & B)
{
	return A.smallerOrEqual(A, B);
}



/* Mathematical methods */

/// A + B
massive operator+(massive & A, massive & B)
{
	massive C;

	// ++ or --
	if (A.getSign() == B.getSign())
	{
		C = C.add(A, B);
		// --
		if (A.getSign())
			C.setSign(1);
	}
	// -+
	else if (A.getSign())
	{
		C = C.sub(B, A);
	}
	// +-
	else
	{
		C = C.sub(A, B);
	}

	return C;
}

/// A - B
massive operator-(massive & A, massive & B)
{
	return A.sub(A, B);
}

/// A * B
massive operator*(massive & A, massive & B)
{
	return A.mul(A, B);
}

/// A / B
massive operator/(massive & A, massive & B)
{
	return A.div(A, B);
}

/// A % B
massive operator%(massive & A, massive & B)
{
	return A.div(A, B, true);
}

/// A ^ n (A_1 * A_2 * ... * A_n)
massive operator^(massive & A, long long int n)
{
	massive C = A;
	for (int i = 0; i < n - 2; i++)
		C = C * C;

	return C;
}

/// A ++
void operator++(massive & A)
{
	A.increment();
}

/// A --
void operator--(massive & A)
{
	A.decrement();
}

/// !A (complement of A)
void operator!(massive & A)
{
	A.complement();
}



/* Compound assignment operators (not yet working) */

/// +=
massive massive::operator+=(massive & A)
{
	massive B, C;
	B = *this;
	C = this->add(B, A);
	return C;
	//return this->add(*this, A);
}

/// -=
massive massive::operator-=(massive & A)
{
	return massive();
}

/// *=
massive massive::operator*=(massive & A)
{
	return massive();
}

/// /=
massive massive::operator/=(massive & A)
{
	return massive();
}

/// %=
massive massive::operator%=(massive & A)
{
	return massive();
}

/// ^=
massive massive::operator^=(massive & A)
{
	return massive();
}



/* Other overloaded operators */

/// <<
std::ostream & operator<<(std::ostream & out, massive A)
{
	if (A.getSign() == 0)
		out << "+";
	else
		out << "-";

	for (int index = A.getSize() - 1; index >= 0; index--)
	{
		//if (this->number.at(index))
		if (A.getBit(index))
			out << "1";
		else
			out << "0";
	}
	return out;
}

/// this[index]
bool massive::operator[](unsigned int index)
{
	return this->getBit(index);
}
