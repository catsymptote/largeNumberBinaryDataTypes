// largeNumberTypes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "massive.h"


int main()
{
	massive cake;
	cake.setNumber(12851);
	cake.binaryPrint();
	cake.decimalPrint();
	
	while (true);
    return 0;
}
