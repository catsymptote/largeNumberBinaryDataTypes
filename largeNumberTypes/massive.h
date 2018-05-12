#pragma once

#include <vector>
#include <deque>

class massive
{
public:
	massive();
	massive(long long int num);
	~massive();


private:
	std::deque<bool> number;	// binary representation of the actual number
	unsigned int size;	// vector length / bit count
	bool sign;	// 0=+, 1=-


public:
	/// Set methods
	void setNumber(long long int num);
	void setSize(unsigned int size);
	void setBit(unsigned int index, bool bit);
	void setSign(bool sign);
	

	/// Get methods
	std::deque<bool> getBinary();
	long long int getDecimal();
	unsigned int getSize();
	bool getBit(unsigned int index);
	bool getSign();
	

	/// Other methods
	void append_back(bool bit);
	void append_front(bool bit);
	void trim(unsigned int index);
	void trimLeadingZeros();
	void complement();


	/// Print
	void binaryPrint();
	void decimalPrint();


	/// Maths
	massive add(massive &A, massive &B);
	massive sub(massive &A, massive &B);
	massive mul(massive &A, massive &B);
	massive div(massive &A, massive &B);
	massive pow(massive &A);
	void increment();
	void decrement();
	

	/// Comparisons
	bool equals(massive &A, massive &B);
	bool notEquals(massive &A, massive &B);
	bool isBigger(massive &A, massive &B);
	bool isSmaller(massive &A, massive &B);
	bool biggerOrEqual(massive &A, massive &B);
	bool smallerOrEqual(massive &A, massive &B);
	
};
