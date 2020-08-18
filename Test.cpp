
#include <iostream>
#include <windows.h>
#include <objbase.h>

#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "Ole32.lib")

const GUID CLSID_Hen = 
{ 0x3a0e7ea5, 0xbae2, 0x46cb, {0xaf, 0x75, 0xac, 0xed, 0x47, 0x55, 0xee, 0x7f}};

int main()
{
    wchar_t guid_string[39];
    int ret = StringFromGUID2(CLSID_Hen, guid_string, 39);
    if(!ret)
    {
        std::cout << "error" << std::endl;
        return 1;
    }

    // The GUID is 36 long characters. The StringFromGUID2 adds curly braces
    // and null terminator, so it's 39.
    for(int i = 0; i < 39; ++i)
    {
        printf("%c", guid_string[i]);
        
    }

    WCHAR *lpwszClsid;
    char szBuff[MAX_PATH]="";
    char szClsid[MAX_PATH]="", szInproc[MAX_PATH]="",szProgId[MAX_PATH];
    char szDescriptionVal[256]="";

    StringFromCLSID(
            CLSID_Hen,
            &lpwszClsid);
    
    for(int i = 0; i < 39; ++i)
    {
        printf("%c", lpwszClsid[i]);
        //std::cout << lpwszClsid[i] << "/";
    }
    CLSID   clsid;
    HRESULT hr;
    std::cout << "Here" << std::endl;

    hr = CLSIDFromProgID(L"WindowsInstaller.Installer", &clsid);
    if(S_OK == hr)
    {
        std::cout << "Success" << std::endl;
    }
    else
    {
        std::cout << "Error" << std::endl;
    }
    std::cout << "Here" << std::endl;
    StringFromCLSID(
            clsid,
            &lpwszClsid);
    

    std::cout << "Here" << std::endl;
    for(int i = 0; i < 39; ++i)
    {
        printf("%c", lpwszClsid[i]);
        //std::cout << lpwszClsid[i] << "/";
    }
    
    return 0;
}
