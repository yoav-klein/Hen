#include "Library.h"

int main()
{
	IHen* hen = CreateHen();

	hen->Cluck();
	hen->Roost();
	hen->Delete();

	return 0;
	
}