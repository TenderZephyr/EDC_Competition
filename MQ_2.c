#include <MQ_2.h>
#include "delay.h"

sbit Fu = P3^4;
bit A;

bit Smoke1( )
{
	A = Fu;
	if(A == 0)
	{
		delay5ms();
		if(A == 0)
		{
			A = 0;
		}					
	}	
	return A;
}	
