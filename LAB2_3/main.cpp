#include <iostream>
#include <math.h>
#include "Header.h"
#include <time.h>
#include "windows.h"
#include <iomanip>

using namespace OOP;


double genMtr(unsigned int i, unsigned int j) {
	return i + j;
}

double genVec(unsigned int i) {
	return i + i;
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "ru");
	matrix a(3);
	matrix b(3);
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	matrix c;
	c = a + b;
	std::cout << c << std::endl;
	c = a - b;
	std::cout << c << std::endl;
	c = a * b;
	std::cout << c << std::endl;

	return 0;
}