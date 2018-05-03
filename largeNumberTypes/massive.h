#pragma once

#include <vector>

class massive
{
public:
	massive();
	massive(long long int num);
	~massive();

private:
	std::vector<bool> number;
	unsigned int size;
	bool sign;	// 0=+, 1=-

public:
	void setNumber(long long int num);
	std::vector<bool> getBinary();
	long long int getDecimal();

	unsigned int getSize();

	void binaryPrint();
	void decimalPrint();

	
	void add();
	void sub();
	void mul();
	void div();
	void pow();
	void increment();

};
