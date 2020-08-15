
#include "HenFactory.h"

HenFactory::HenFactory()
    : m_counter(0)
{
}

HenFactory::~HenFactory() { }

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

HRESULT __stdcall HenFactory::LockServer(bool bLock)
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