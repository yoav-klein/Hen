//
//Registry.cpp
//
//Implementation for DllRegisterServer,DllUnregisterServer
//Contains code to write COM server data into the registry and 
//also removing the data that had been written into the registry 
//by this module.
//

#include    <windows.h>
#include    <objbase.h>


#define HenProgId "Yoav.Hen"
//extern HMODULE g_hModule;

const GUID CLSID_Hen = 
{ 0x3a0e7ea5, 0xbae2, 0x46cb, {0xaf, 0x75, 0xac, 0xed, 0x47, 0x55, 0xee, 0x7f}};

BOOL   HelperWriteKey(
                            HKEY roothk,
                            const char *lpSubKey,
                            LPCTSTR val_name, 
                            DWORD dwType,
                            void *lpvData, 
                            DWORD dwDataSize)
    {
    //
    //Helper function for doing the registry write operations
    //
    //roothk:either of HKCR, HKLM, etc

    //lpSubKey: the key relative to 'roothk'
    
    //val_name:the key value name where the data will be written
    
    //dwType:the type of data that will be written ,REG_SZ,REG_BINARY, etc.
    
    //lpvData:a pointer to the data buffer
    
    //dwDataSize:the size of the data pointed to by lpvData
    //
    //

    HKEY hk;
    if (ERROR_SUCCESS != RegCreateKey(roothk,lpSubKey,&hk) ) return FALSE;

    if (ERROR_SUCCESS != RegSetValueEx(hk,val_name,0,dwType,(CONST BYTE *)lpvData,dwDataSize)) return FALSE;
    
    if (ERROR_SUCCESS != RegCloseKey(hk))   return FALSE;
    return TRUE;
        
    }



///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

HRESULT  __stdcall DllRegisterServer(void)
    {
    //
    //As per COM guidelines, every self installable COM inprocess component
    //should export the function DllRegisterServer for printing the 
    //specified information to the registry
    //
    //

    WCHAR *lpwszClsid;
    char szBuff[MAX_PATH]="";
    char szClsid[MAX_PATH]="", szInproc[MAX_PATH]="",szProgId[MAX_PATH];
    char szDescriptionVal[256]="";

    StringFromCLSID(
            CLSID_Hen,
            &lpwszClsid);
    
    wsprintf(szClsid,"%S",lpwszClsid);
    wsprintf(szInproc,"%s\\%s\\%s","clsid",szClsid,"InprocServer32");
    wsprintf(szProgId,"%s\\%s\\%s","clsid",szClsid,"ProgId");


    //
    //write the default value 
    //
    wsprintf(szBuff,"%s","My Hen");
    wsprintf(szDescriptionVal,"%s\\%s","clsid",szClsid);

    HelperWriteKey (
                HKEY_CLASSES_ROOT,
                szDescriptionVal,
                NULL,//write to the "default" value
                REG_SZ,
                (void*)szBuff,
                lstrlen(szBuff)
                );


    //
    //write the "InprocServer32" key data
    //
    GetModuleFileName(
                NULL,
                szBuff,
                sizeof(szBuff));
    HelperWriteKey (
                HKEY_CLASSES_ROOT,
                szInproc,
                NULL,//write to the "default" value
                REG_SZ,
                (void*)szBuff,
                lstrlen(szBuff)
                );

    //
    //write the "ProgId" key data under HKCR\clsid\{---}\ProgId
    //
    lstrcpy(szBuff,HenProgId);
    HelperWriteKey (
                HKEY_CLASSES_ROOT,
                szProgId,
                NULL,
                REG_SZ,
                (void*)szBuff,
                lstrlen(szBuff)
                );


    //
    //write the "ProgId" data under HKCR\Yoav.Hen
    //
    wsprintf(szBuff,"%s","Hen Demo");
    HelperWriteKey (
                HKEY_CLASSES_ROOT,
                HenProgId,
                NULL,
                REG_SZ,
                (void*)szBuff,
                lstrlen(szBuff)
                );


    wsprintf(szProgId,"%s\\%s",HenProgId,"CLSID");
    HelperWriteKey (
                HKEY_CLASSES_ROOT,
                szProgId,
                NULL,
                REG_SZ,
                (void*)szClsid,
                lstrlen(szClsid)
                );

    return 1;

    }


///////////////////////////////////////////////////////////////////////////////

HRESULT  __stdcall DllUnregisterServer(void)
    {
    //
    //As per COM guidelines, every self removable COM inprocess component
    //should export the function DllUnregisterServer for erasing all the 
    //information that was printed into the registry
    //
    //

    char szKeyName[256]="",szClsid[256]="";
    WCHAR *lpwszClsid;

    

    //
    //delete the ProgId entry
    //
    wsprintf(szKeyName,"%s\\%s",HenProgId,"CLSID");
    RegDeleteKey(HKEY_CLASSES_ROOT,szKeyName);
    RegDeleteKey(HKEY_CLASSES_ROOT,HenProgId);


    //
    //delete the CLSID entry for this COM object
    //
    StringFromCLSID(
            CLSID_Hen,
            &lpwszClsid);
    wsprintf(szClsid,"%S",lpwszClsid);
    wsprintf(szKeyName,"%s\\%s\\%s","CLSID",szClsid,"InprocServer32");
    RegDeleteKey(HKEY_CLASSES_ROOT,szKeyName);

    wsprintf(szKeyName,"%s\\%s\\%s","CLSID",szClsid,"ProgId");
    RegDeleteKey(HKEY_CLASSES_ROOT,szKeyName);

    wsprintf(szKeyName,"%s\\%s","CLSID",szClsid);
    RegDeleteKey(HKEY_CLASSES_ROOT,szKeyName);

    return 1;

    }


