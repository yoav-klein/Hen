#include <iostream>

#include "Library.h"

int main()
{
	IHen* hen = CreateHen();
	
	IHen2* hen2 = static_cast<IHen2*>(hen->As("IHen2"));
	if(hen2)
	{
		hen2->Forage();
		hen2->Release();
	}
	std::cout << "IHen2 address is: " << (void*)hen2 << std::endl;

	IOfflineChicken* off = static_cast<IOfflineChicken*>(hen2->As("IOfflineChicken"));
	if(off)
	{
		off->Save("File");
		off->Load("File");

		off->Release();
	}

	std::cout << "IOfflneChicken address is: " << (void*)off << std::endl;
	hen->Release();

	return 0;
	
}