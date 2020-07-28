
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
	//	IUnknown methods
	//
	
	ULONG __stdcall AddRef()
	{
		++m_counter;

		return m_counter;
	}

	ULONG __stdcall Release()
	{
		ULONG result = --m_counter;
		if(result == 0)
		{
			delete this;
		}

		return result;
	}

	HRESULT __stdcall QueryInterface(const IID& iid, void** piid)
	{
		if(iid == __uuidof(IHen) || iid == __uuidof(IHen2) || iid == __uuidof(IUnknown))
		{
			*piid = static_cast<IHen2*>(this);
		}
		else if(iid == __uuidof(IOfflineChicken))
		{
			*piid = static_cast<IOfflineChicken*>(this);
		}
		else
		{
			*piid = 0;
			return E_NOINTERFACE;
		}

		static_cast<IUnknown*>(*piid)->AddRef();
		
		return S_OK;
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

HRESULT __stdcall CreateHen(IHen** ptr)
{
	IHen* hen = new Hen();
	hen->AddRef();
	*ptr = hen;
	
	return S_OK;
}