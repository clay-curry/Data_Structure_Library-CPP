// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


#include "ArrayClass.h"

int main()
{
	ArrayClass<int> ai(8, 4); //-V112
	ArrayClass<int> ai2 = ai;
	ArrayClass<int> ai3(10);
	std::cout << ai << std::endl;
	std::cout << ai2 << std::endl;
	std::cout << ai3 << std::endl;
	std::cout << std::endl;
	for (size_t i = 0; i < ai.size(); i++)
	{
		ai[i] = i * 2;
	}
	try
	{
		ai[5] = 10;
	}
	catch (std::exception& e)
	{
		e;
		std::cout << "Index out of bounds" << std::endl;
	}
	std::cout << std::endl;
	ai3 = ai;
	std::cout << ai << std::endl;
	std::cout << ai2 << std::endl;
	std::cout << ai3 << std::endl;

	return 0;
}
