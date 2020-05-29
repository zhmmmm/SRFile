#include <iostream>
#include "Tools/Tools.h"
#define COLOR system("color 2");


int main()
{
	COLOR;

	Tools tools;
	auto local = tools.getLocalHostName();
	auto ret = tools.getHostIP("www.github.com");

	std::cout << ret.c_str() << std::endl;



	return 0;
}