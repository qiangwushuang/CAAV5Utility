#include <iostream>
#include "SimpleLicense.h"

int main()
{
	SimpleLicense lic;
	if (!lic.Init() )
	{
		std::cout<<"许可无效"<<std::endl;
	}
	if (!lic.CheckDateLic(CATTime(2024,3,27,0,0,0)))
	{
		std::cout<<"许可无效"<<std::endl;
	}
	return 1;
}