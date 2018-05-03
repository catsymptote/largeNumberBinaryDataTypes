#pragma once

#include <vector>

class massive
{
public:
	massive();
	massive(long long int num);
	~massive();

private:
	std::vector<bool> number;	// binary representation of the actual number
	unsigned int size;	// vector length / bit count
	bool sign;	// 0=+, 1=-

public:
	void setNumber(long long int num);
	void setSize(unsigned int size);
	std::vector<bool> getBinary();
	bool getBit(unsigned int index);
	void setBit(unsigned int index, bool bit);
	long long int getDecimal();
	unsigned int getSize();

	void binaryPrint();
	void decimalPrint();

	
	massive add(massive &A, massive &B);
	massive sub(massive A, massive B);
	massive mul(massive A, massive B);
	massive div(massive A, massive B);
	massive pow(massive A);
	massive increment();

};
