#include <iostream>
#include "SimpleLicense.h"

int main()
{
	SimpleLicense lic;
	if (!lic.Init() )
	{
		std::cout<<"�����Ч"<<std::endl;
	}
	if (!lic.CheckDateLic(CATTime(2024,3,27,0,0,0)))
	{
		std::cout<<"�����Ч"<<std::endl;
	}
	return 1;
}