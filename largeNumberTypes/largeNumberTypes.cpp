// largeNumberTypes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "massive.h"

#include <iostream>


void testAB()
{
	massive A, B, C;
	//A.setNumber(9000000000000000000);
	//B.setNumber(-9000000000000000000);
	A.setNumber(66);
	B.setNumber(128);
	C = A - B;

	/// Decimal print
	std::cout << std::endl;
	A.decimalPrint();
	std::cout << "---" << std::endl;
	B.decimalPrint();
	std::cout << "===" << std::endl;
	C.decimalPrint();

	/// Binary print
	std::cout << std::endl;
	A.binaryPrint();
	std::cout << "---" << std::endl;
	B.binaryPrint();
	std::cout << "===" << std::endl;
	C.binaryPrint();
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
