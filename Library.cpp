
#include <iostream>
#include "Library.h"

struct Hen : IHen
{
	Hen()
	{
		std::cout << "Cheep!\n" << std::endl;
	}
	~Hen() 
	{
		std::cout << "Chicken soup!\n" << std::endl;
	}
	void __stdcall Cluck()
	{
		std::cout << "Cluck!" << std::endl;
	}
	void __stdcall Roost()
	{
		std::cout << "ZZzz.." << std::endl;
	}
};

IHen * __stdcall CreateHen()
{
	return new Hen();
}