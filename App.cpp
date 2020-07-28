#include <iostream>

#include "Library.h"

int main()
{
	IHen* hen;
	HRESULT hr;
	
	hr = CreateHen(&hen);
	
	hen->Cluck();
	IHen2* hen2;
	if(S_OK == hen->QueryInterface(&hen2))
	{
		hen2->Forage();
		hen2->Release();
	}
	std::cout << "IHen2 address is: " << (void*)hen2 << std::endl;

	IOfflineChicken* off;
	if(S_OK == hen->QueryInterface(&off))
	{
		off->Save("File");
		off->Load("File");

		off->Release();
	}

	std::cout << "IOfflneChicken address is: " << (void*)off << std::endl;
	hen->Release();

	return 0;
	
}