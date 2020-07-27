
#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>

#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "Ole32.lib")

int main()
{
    HRESULT hr;
    
    GUID guid;
    
    if(!(S_OK == CoCreateGuid(&guid)))
    {
        std::cout << "Error" << std::endl;
        return 1;
    }

    wchar_t guid_string[39];
    int ret = StringFromGUID2(guid, guid_string, 39);
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
    std::cout << std::endl;
    std::cout << "Size of guid " << ret << std::endl;

    std::wstring str(guid_string + 1, 36);
    std::cout << str.c_str() << std::endl;

    printf("%s\n", guid_string);
    return 0;
}