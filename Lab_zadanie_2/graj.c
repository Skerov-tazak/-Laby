#include"gra.h"
#include<stdio.h>

#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))

int graj(int a, int b)
{
	if(a % 2 == 0)
		return 1;
	else 
		return 2;

}	

