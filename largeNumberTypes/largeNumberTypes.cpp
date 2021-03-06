// largeNumberTypes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "massive.h"

#include <iostream>


void testAB()
{
	massive A(10), B, C;
	B.setFromString("1400000");
	C = A + B;
	//C += A;
	//C += A;

	/// Decimal print
	std::cout << std::endl;
	A.decimalPrint();
	std::cout << "---" << std::endl;
	B.decimalPrint();
	std::cout << "===" << std::endl;
	C.decimalPrint();

	/// Binary print
	std::cout << "\n" << A << "\n---\n" << B << "\n===\n" << C << std::endl;
}


void testA()
{
	massive A;
	massive B;
	A.setNumber(20);

	A.decimalPrint();
	A.binaryPrint();

	std::cout << "---" << std::endl;

	A = A ^ 4;

	A.decimalPrint();
	A.binaryPrint();
}


void testCompAB()
{
	massive A, B;
	A.setNumber(18);
	B.setNumber(17);
	A.decimalPrint();
	B.decimalPrint();
	std::cout << (A > B) << std::endl;
}


int main()
{
	testAB();
    return 0;
}
