#include "framework.h"
#include "DaFun.h"


DaFun::DaFun()
{

}

bool DaFun::cpstr(char* dest, char* src, int m, int n, int len)
{
	for (int i = 0; i < len; i++)
		dest[i] = '\0';

	if ((int)strlen(src) < n || m > n || m < 0)
		return 0;
	else
		memcpy(dest, src + m, n - m + 1);
	return 1;
}




DaFun::~DaFun()
{
}

