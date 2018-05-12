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
	void remove_back();
	void remove_front();
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
	massive div(massive &A, massive &B, bool mod=false);
	massive pow(massive &A);
	void increment();
	void decrement();
	void div2();
	void mul2();
	

	/// Comparisons
	bool equals(massive &A, massive &B);
	bool notEquals(massive &A, massive &B);
	bool isBigger(massive &A, massive &B);
	bool isSmaller(massive &A, massive &B);
	bool biggerOrEqual(massive &A, massive &B);
	bool smallerOrEqual(massive &A, massive &B);
	

	// Overloading operators
	/// Comparators
	friend bool operator > (massive &A, massive &B);
	friend bool operator < (massive &A, massive &B);
	friend bool operator == (massive &A, massive &B);
	friend bool operator != (massive &A, massive &B);
	friend bool operator >= (massive &A, massive &B);
	friend bool operator <= (massive &A, massive &B);

	/// Maths
	friend massive operator + (massive &A, massive &B);
	friend massive operator - (massive &A, massive &B);
	friend massive operator * (massive &A, massive &B);
	friend massive operator / (massive &A, massive &B);
	friend massive operator % (massive &A, massive &B);
	friend massive operator ^ (massive &A, long long int n);
	friend void operator ++ (massive &A);
	friend void operator -- (massive &A);
	//friend bool operator [ ] (unsigned int index);
	bool operator [ ] (unsigned int index);
	
};
