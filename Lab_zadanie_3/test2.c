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
  zbior[0] = ciag_arytmetyczny(3, 3, 24);
  zbior[1] = ciag_arytmetyczny(91, 3, 94);
  zbior[2] = singleton(11);
  zbior[3] = roznica(zbior[2], zbior[2]);
  zbior[4] = suma(zbior[2], zbior[0]);
  zbior[5] = iloczyn(zbior[4], zbior[2]);
  printf("%d\n", nalezy(zbior[5], 62));
  printf("%d\n", nalezy(zbior[0], 97));
  printf("%u\n", ary(zbior[3]));
  printf("%u\n", moc(zbior[0]));
  zbior[6] = suma(zbior[0], zbior[4]);
  printf("%u\n", moc(zbior[2]));
  zbior[7] = ciag_arytmetyczny(68, 3, 74);
  zbior[8] = iloczyn(zbior[2], zbior[4]);
  printf("%u\n", ary(zbior[0]));
  printf("%d\n", nalezy(zbior[3], 96));
  printf("%u\n", ary(zbior[5]));
  zbior[9] = iloczyn(zbior[4], zbior[4]);
  zbior[10] = ciag_arytmetyczny(83, 3, 92);
  printf("%d\n", nalezy(zbior[8], 100));
  printf("%d\n", nalezy(zbior[1], 12));
  printf("%u\n", ary(zbior[7]));
  printf("%u\n", moc(zbior[4]));
  zbior[11] = singleton(87);
  zbior[12] = roznica(zbior[9], zbior[11]);
  printf("%u\n", ary(zbior[11]));
  zbior[13] = iloczyn(zbior[11], zbior[11]);
  zbior[14] = singleton(94);
  zbior[15] = suma(zbior[6], zbior[12]);
  printf("%d\n", nalezy(zbior[12], 78));
  printf("%u\n", moc(zbior[5]));
  zbior[16] = iloczyn(zbior[3], zbior[0]);
  zbior[17] = iloczyn(zbior[15], zbior[3]);
  zbior[18] = singleton(81);
  zbior[19] = iloczyn(zbior[2], zbior[14]);
  zbior[20] = roznica(zbior[14], zbior[8]);
  printf("%u\n", moc(zbior[9]));
  printf("%u\n", ary(zbior[15]));
  printf("%d\n", nalezy(zbior[4], 2));
  printf("%u\n", moc(zbior[0]));
  printf("%d\n", nalezy(zbior[12], 5));
  zbior[21] = suma(zbior[9], zbior[2]);
  zbior[22] = ciag_arytmetyczny(44, 3, 98);
  zbior[23] = roznica(zbior[19], zbior[13]);
  zbior[24] = roznica(zbior[12], zbior[17]);
  zbior[25] = roznica(zbior[4], zbior[14]);
  zbior[26] = ciag_arytmetyczny(38, 3, 95);
  zbior[27] = ciag_arytmetyczny(56, 3, 95);
  zbior[28] = ciag_arytmetyczny(83, 3, 86);
  printf("%u\n", moc(zbior[13]));
  return 0;
}
