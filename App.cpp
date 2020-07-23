#include "Library.h"

int main()
{
	IHen* hen = CreateHen();

	hen->Cluck();
	hen->Roost();
	hen->Release();

	return 0;
	
}