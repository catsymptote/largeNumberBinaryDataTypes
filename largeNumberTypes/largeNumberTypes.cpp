// largeNumberTypes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "massive.h"


int main()
{
	massive A, B;
	A.setNumber(17);
	B.setNumber(15);
	A.binaryPrint();
	B.binaryPrint();
	A.decimalPrint();
	B.decimalPrint();
	
	massive C;
	C = C.add(A, B);
	C.binaryPrint();
	C.decimalPrint();

	while (true);
    return 0;
}
