
#include <iostream>
#include <cstring>

#include "Library.h"

unsigned int g_ComObjsInUse = 0;

Hen::Hen()
	: m_counter(0)
{
	++g_ComObjsInUse;
	std::cout << "Cheep!\n" << std::endl;
}
Hen::~Hen() 
{
	--g_ComObjsInUse;
	std::cout << "Chicken soup!\n" << std::endl;
}

	//
	//	IUnknown methods
	//
	
ULONG __stdcall Hen::AddRef()
{
	++m_counter;

	return m_counter;
}

ULONG __stdcall Hen::Release()
{
	ULONG result = --m_counter;
	if(result == 0)
	{
		delete this;
	}

	return result;
}

HRESULT __stdcall Hen::QueryInterface(const IID& iid, void** piid)
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

void __stdcall Hen::Cluck()
{
	std::cout << "Cluck!" << std::endl;
}
void __stdcall Hen::Roost()
{
	std::cout << "ZZzz.." << std::endl;
}

//
//	IHen2
//

void __stdcall Hen::Forage()
{
	std::cout << "Forage!" << std::endl;
}

//
//	IOfflineChicken
//

void __stdcall Hen::Load(const char* file)
{
		std::cout << "Loading " << file << std::endl;
}

void __stdcall Hen::Save(const char* file)
{
	std::cout << "Saving " << file << std::endl;
}

HRESULT __stdcall CreateHen(IHen** ptr)
{
	IHen* hen = new Hen();
	hen->AddRef();
	*ptr = hen;
	
	return S_OK;
}


HenFactory::HenFactory()
    : m_counter(0)
{
	++g_ComObjsInUse;
}

HenFactory::~HenFactory() 
{ 
	--g_ComObjsInUse;
}

HRESULT __stdcall HenFactory::QueryInterface(const IID& iid, void** piid)
{
    if((iid == IID_IUnknown) || (iid == IID_IClassFactory))
    {
        *piid = static_cast<IClassFactory*>(this);
    }
    else
    {
        *piid = NULL;
        return E_NOINTERFACE;
    }

    reinterpret_cast<IUnknown*>(*piid)->AddRef();
    return S_OK;
}

ULONG __stdcall HenFactory::AddRef()
{
    ++m_counter;

    return m_counter;
}

ULONG __stdcall HenFactory::Release()
{
    --m_counter;
    if(0 == m_counter)
    {
        delete this;
    }
    return m_counter;
}

HRESULT __stdcall HenFactory::LockServer(BOOL bLock)
{
    return E_NOTIMPL;
}

HRESULT __stdcall HenFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, 
                                             void** piid)
{
    // cannot aggregate
    if(NULL != pUnknownOuter)
    {
        return CLASS_E_NOAGGREGATION;
    }

    Hen* hen = new Hen();
    if(NULL == hen)
    {
        return E_OUTOFMEMORY;
    }

    return hen->QueryInterface(iid, piid);
}

STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, void** piid)
{
	if(clsid == CLSID_Hen)
	{
		HenFactory *factory = new HenFactory();
		if(factory == NULL)
		{
			return E_OUTOFMEMORY;
		}

		return factory->QueryInterface(iid, piid);
	}

	return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow()
{
	if(!g_ComObjsInUse)
	{
		return S_OK;
	}
	return S_FALSE;
}