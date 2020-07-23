
#include <iostream>
#include "Library.h"

struct Hen : IHen
{
public:

	Hen()
		: m_counter(0)
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

	void __stdcall AddRef()
	{
		++m_counter;
	}

	void __stdcall Release()
	{
		if(--m_counter == 0)
		{
			delete this;
		}
	}
private:

	unsigned int m_counter;

};

IHen * __stdcall CreateHen()
{
	IHen* hen = new Hen();
	hen->AddRef();

	return hen;
}