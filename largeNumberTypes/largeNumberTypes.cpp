// largeNumberTypes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "massive.h"

#include <iostream>


int main()
{
	massive A, B, C;
	//A.setNumber(9000000000000000000);
	//B.setNumber(-9000000000000000000);
	A.setNumber(17);
	B.setNumber(12);
	A.binaryPrint();
	std::cout << "----------------" << std::endl;
	B.binaryPrint();
	C = C.sub(A, B);
	std::cout << "================" << std::endl;
	C.binaryPrint();
	C.decimalPrint();

	std::cout << std::endl;
	A.decimalPrint();
	std::cout << "---" << std::endl;
	B.decimalPrint();
	std::cout << "===" << std::endl;
	C.decimalPrint();


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
    return 0;
}
