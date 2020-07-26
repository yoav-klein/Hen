
#include <iostream>
#include <cstring>

#include "Library.h"

struct Hen : IHen2, IOfflineChicken
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

	//
	//	IObject methods
	//
	
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

	void* __stdcall As(const char* type)
	{
		if(0 == strcmp(type, "IHen")  || 
		   0 == strcmp(type, "IHen2") ||
		   0 == strcmp(type, "IObject"))
		{
			AddRef();
			return static_cast<IHen2*>(this);
		}
		else if(0 == strcmp("IOfflineChicken", type))
		{
			AddRef();

			return static_cast<IOfflineChicken*>(this);	
		}
		else
		{
			return 0;
		}
	}

	//
	//	IHen
	//	

	void __stdcall Cluck()
	{
		std::cout << "Cluck!" << std::endl;
	}
	void __stdcall Roost()
	{
		std::cout << "ZZzz.." << std::endl;
	}

	//
	//	IHen2
	//

	void __stdcall Forage()
	{
		std::cout << "Forage!" << std::endl;
	}

	//
	//	IOfflineChicken
	//

	void __stdcall Load(const char* file)
	{
			std::cout << "Loading " << file << std::endl;
	}

	void __stdcall Save(const char* file)
	{
		std::cout << "Saving " << file << std::endl;
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