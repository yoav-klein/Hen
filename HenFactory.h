#include <windows.h>


class HenFactory : public IClassFactory
{
public:
    HenFactory();
    ~HenFactory();

    HRESULT __stdcall QueryInterface(const IID& iid, void** piid);
    ULONG __stdcall AddRef();
    UNLONG __stdcall Release();

    virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid,
                                             void** piid);
    virtual HRESULT __stdcall LockServer(bool bLock);

private:
    unsigned int m_counter;
}