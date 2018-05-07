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
	void setNumber(long long int num);
	void setSize(unsigned int size);
	void setBit(unsigned int index, bool bit);
	void append_back(bool bit);
	void append_front(bool bit);
	void trim(unsigned int index);
	void trimLeadingZeros();

	std::deque<bool> getBinary();
	long long int getDecimal();
	unsigned int getSize();
	bool getBit(unsigned int index);
	
	void binaryPrint();
	void decimalPrint();

	void complement();

	massive add(massive &A, massive &B);
	massive sub(massive &A, massive &B);
	massive mul(massive &A, massive &B);
	massive div(massive &A, massive &B);
	massive pow(massive &A);
	massive increment();

};
