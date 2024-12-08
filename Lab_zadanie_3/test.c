#include <stdio.h>
#include <stdlib.h>
#include "zbior_ary.h"

void print(zbior_ary A)
{
	if(A.size == 0)
		printf("{}\n");
	else 
	{
		printf("{");
		for(int i = 0; i < A.size - 2; i+=2)
			printf("%d %d,", A.sets[i], A.sets[i+1]);
		printf("%d %d}\n", A.sets[A.size - 2], A.sets[A.size - 1]);

	}

}


int main() {
  zbior_ary *zbior = (zbior_ary *)malloc(1000000U * sizeof(zbior_ary));
  zbior[0] = ciag_arytmetyczny(8, 3, 8);
  print(zbior[0]);
  zbior[1] = singleton(1);
  print(zbior[1]);
  printf("%u\n", moc(zbior[1]));
  zbior[2] = ciag_arytmetyczny(2, 3, 5);
  print(zbior[2]);
  zbior[3] = suma(zbior[1], zbior[2]);
  print(zbior[3]);
  zbior[4] = suma(zbior[2], zbior[3]);
  print(zbior[4]);
  zbior[5] = suma(zbior[0], zbior[1]);
  print(zbior[5]);
  zbior[6] = iloczyn(zbior[0], zbior[1]);
  print(zbior[6]);
  zbior[7] = iloczyn(zbior[3], zbior[0]);
  print(zbior[7]);
  printf("%u\n", ary(zbior[3]));
  return 0;
}
