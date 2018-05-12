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
	A.setNumber(200000000000000000);
	B.setNumber(-200000000000000000);
	//A.binaryPrint();
	//std::cout << "----------------" << std::endl;
	//B.binaryPrint();
	C = A * B;
	//std::cout << "================" << std::endl;
	//C.binaryPrint();
	//C.decimalPrint();

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


	/*
	B.setNumber(15);
	A.binaryPrint();
	B.binaryPrint();
	A.decimalPrint();
	B.decimalPrint();

	massive C;
	C = C.add(A, B);
	C.binaryPrint();
	C.decimalPrint();
	*/

	//while (true);
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
	testA();
    return 0;
}
