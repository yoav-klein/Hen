#pragma once

#include <unknwn.h>

struct __declspec(uuid("3ee8b447-596a-424b-a290-6d3df875537d")) IHen : IUnknown
{
	virtual void __stdcall Cluck() = 0;
	virtual void __stdcall Roost() = 0;
	
};

struct __declspec(uuid("36216910-3076-4736-94d5-d7324ba009bb")) IHen2 : IHen
{
	virtual void __stdcall Forage() = 0;
};

struct __declspec(uuid("d2276cc3-624d-4983-840f-01d2bdb2dc64")) IOfflineChicken : IUnknown
{
	virtual void __stdcall Load(const char* file) = 0;
	virtual void __stdcall Save(const char* file) = 0;
};

HRESULT __stdcall CreateHen(IHen** ptr);
