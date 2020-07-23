#include "Library.h"

int main()
{
	IHen* hen = CreateHen();

	hen->Cluck();
	hen->Roost();

	delete hen;
	return 0;
	
}