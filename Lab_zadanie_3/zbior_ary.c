#include"zbior_ary.h"
#include <stdio.h>

static int Q;
#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))

int mod(int a)
{
	return (a % Q + Q) % Q;
}

void printAry(zbior_ary);

void addNewIntervalwMem(zbior_ary* add_to, int start, int end)
{
	if(add_to->size == 0)
	{
		add_to->size += 2;
		add_to->sets = (int*)malloc(sizeof(int) * (unsigned long)(add_to->size));
		if(add_to->sets != NULL){	
			add_to->sets[add_to->size - 2] = start;
			add_to->sets[add_to->size - 1] = end;
		}
	}
	else
	{
		add_to->size += 2;
		int* temp = (int*)realloc(add_to->sets, sizeof(int) * (unsigned long)(add_to->size));
		if(temp != NULL){	
			temp[add_to->size - 2] = start;
			temp[add_to->size - 1] = end;
			add_to->sets = temp;
		}
	}
}

void removeLastEntry(zbior_ary* to_remove)
{
	if(to_remove->size == 0)
		return;
	if(to_remove->size == 2)
	{
		free(to_remove->sets);
		to_remove->size = 0;
	}
	else 
	{
		to_remove->size -= 2;
		to_remove->sets = (int*)realloc(to_remove->sets, (unsigned long)to_remove->size);
	}
}

void addNewInterval(int* add_to, int to_index, int* add_from, int from_index)
{
	add_to[to_index] = add_from[from_index];
	add_to[to_index + 1] = add_from[from_index + 1];
}

void mergeOverlapIntervals(int* merge_at, int at_index, int* merge_with, int with_index)
{
	merge_at[at_index + 1] = max(merge_at[at_index + 1], merge_with[with_index + 1]);
}

zbior_ary ciag_arytmetyczny(int a, int q, int b)
{
	zbior_ary new_set;
	new_set.sets = (int*)malloc(sizeof(int) * 2);
	new_set.sets[0] = a;
	new_set.sets[1] = b;
	new_set.size = 2;
	Q = q;
	return new_set;
}

zbior_ary singleton(int a)
{
	zbior_ary singleton;
	singleton.sets = (int*)malloc(sizeof(int) * 2);
	singleton.sets[0] = a;
	singleton.sets[1] = a;
	singleton.size = 2;
	return singleton;
}


zbior_ary suma(zbior_ary A, zbior_ary B)
{
	if(A.size == 0)
		return B;
	if(B.size == 0)
		return A;

	zbior_ary sum;
	sum.sets = (int*)calloc((unsigned long)(A.size + B.size), sizeof(int));
	sum.size = 0;
	int i = 0;
	int A_index = 0;
	int B_index = 0;
	
	if(mod(A.sets[0]) == mod(B.sets[0])) // Initialise the first interval
	{
		if(A.sets[0] < B.sets[0])
		{
			addNewInterval(sum.sets, 0, A.sets, 0);
			A_index += 2;
		}
		else
		{
			addNewInterval(sum.sets, 0, B.sets, 0);
			B_index += 2;
		}
	}
	else if(mod(A.sets[0]) < mod(B.sets[0]))
	{	
		addNewInterval(sum.sets, 0, A.sets, 0);
		A_index += 2;
	}
	else 
	{
		addNewInterval(sum.sets, 0, B.sets, 0);
		B_index += 2;
	}
	sum.size = 2;
	

	while(A_index < A.size || B_index < B.size) // zipper merge intervals if the same q
	{
		if(A_index < A.size && B_index < B.size && mod(A.sets[A_index]) == mod(B.sets[B_index]))
		{
			if(A.sets[A_index] < B.sets[B_index])
			{
				if(mod(A.sets[A_index]) == mod(sum.sets[i]) && A.sets[A_index] <= sum.sets[i + 1] + Q)
				{
					mergeOverlapIntervals(sum.sets, i, A.sets, A_index);
					A_index += 2;
				}
				else 
				{
					i += 2;
					addNewInterval(sum.sets, i, A.sets, A_index);
					sum.size += 2;
					A_index += 2;
				}
			}
			else if(B.sets[B_index] < A.sets[A_index])
			{	
				if(mod(B.sets[B_index]) == mod(sum.sets[i]) && B.sets[B_index] <= sum.sets[i + 1] + Q)
				{
					mergeOverlapIntervals(sum.sets, i, B.sets, B_index);
					B_index += 2;
				}
				else 
				{
					i += 2;
					addNewInterval(sum.sets, i, B.sets, B_index);
					sum.size += 2;
					B_index += 2;
				}

			}
		}
		else if(A_index < A.size && (B_index >= B.size || mod(A.sets[A_index]) < mod(B.sets[B_index])))
		{
			if(mod(A.sets[A_index]) == mod(sum.sets[i]))
			{
				if(A.sets[A_index] <= sum.sets[i + 1] + Q)
				{
					mergeOverlapIntervals(sum.sets, i, A.sets, A_index);
					A_index += 2;
				}
				else 
				{
					i += 2;
					addNewInterval(sum.sets, i, A.sets, A_index);
					sum.size += 2;
					A_index += 2;
				}

			}
			else 
			{	
				i += 2;
				addNewInterval(sum.sets, i, A.sets, A_index);
				sum.size += 2;
				A_index += 2;
			}
		}
		else if(A_index >= A.size || mod(B.sets[B_index]) < mod(A.sets[A_index]))
		{
			if(mod(B.sets[B_index]) == mod(sum.sets[i]))
			{
				if(B.sets[B_index] <= sum.sets[i + 1] + Q)
				{
					mergeOverlapIntervals(sum.sets, i, B.sets, B_index);
					B_index += 2;
				}
				else 
				{
					i += 2;
					addNewInterval(sum.sets, i, B.sets, B_index);
					sum.size += 2;
					B_index += 2;
				}

			}
			else 
			{	
				i += 2;
				addNewInterval(sum.sets, i, B.sets, B_index);
				sum.size += 2;
				B_index += 2;
			}
		}
	}

	int* new_array = (int*)realloc(sum.sets, (unsigned long)(sum.size) * sizeof(int));
	if(new_array != NULL)
		sum.sets = new_array;
	return sum;
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B)
{
	zbior_ary intersection;
	intersection.size = 0;
	intersection.sets = (int*)malloc(sizeof(int) * 2); // I dunno why but prevents segfault on realloc
	int A_index = 0;
	int B_index = 0;

	while(A_index < A.size && B_index < B.size)
	{
		if(mod(A.sets[A_index]) == mod(B.sets[B_index]))
		{
			int intersect_begin = max(A.sets[A_index], B.sets[B_index]);
			int intersect_end = min(A.sets[A_index + 1], B.sets[B_index + 1]);

			if(intersect_begin < intersect_end)
			{
				int* new_array = (int*)realloc(intersection.sets, sizeof(int) * (unsigned long)(intersection.size + 2));
				if(new_array != NULL)
					intersection.sets = new_array;

				intersection.sets[intersection.size] = intersect_begin;
				intersection.sets[intersection.size + 1] = intersect_end;
				intersection.size += 2;
			}

			if(A.sets[A_index + 1] < B.sets[B_index + 1])
				A_index += 2;
			else
				B_index += 2;
		}
		else if(mod(A.sets[A_index]) > mod(B.sets[B_index]))
		{
			B_index += 2;
		}
		else
		{
			A_index += 2;
		}
	}
	return intersection;
}


zbior_ary roznica(zbior_ary A, zbior_ary B)
{
	zbior_ary difference; 
	difference.size = 0;
	if(A.size == 0)
		return difference; 

	addNewIntervalwMem(&difference, A.sets[0], A.sets[1]);
	
	int A_index = 0;
	int B_index = 0; 
	
	while(B_index < B.size)
	{	
		printAry(difference);

		if(mod(difference.sets[difference.size - 2]) == mod(B.sets[B_index]))
		{
			int intersect_begin = max(B.sets[B_index], difference.sets[difference.size - 2]);
			int intersect_end = min(B.sets[B_index + 1], difference.sets[difference.size - 1]);

			if(intersect_begin <= intersect_end)
			{
				if(difference.sets[difference.size - 2] == intersect_begin && difference.sets[difference.size - 1] == intersect_end)
				{
					A_index += 2;
					if(A_index >= A.size)
					{
						removeLastEntry(&difference);
						break;
					}

					difference.sets[difference.size - 1] = A.sets[A_index];
					difference.sets[difference.size - 2] = A.sets[A_index + 1];

				}
				else if(difference.sets[difference.size - 2] < intersect_begin && intersect_end < difference.sets[difference.size - 1])
				{
					addNewIntervalwMem(&difference, intersect_end + Q, difference.sets[difference.size - 1]);
					difference.sets[difference.size - 3] = intersect_begin - Q;
				}	
				else if(difference.sets[difference.size - 2] < intersect_begin)
				{
					difference.sets[difference.size - 1] = intersect_begin - Q;
					A_index += 2;
					if(A_index >= A.size)
						break;
					addNewIntervalwMem(&difference, A.sets[A_index], A.sets[A_index + 1]);
				}
				else 
				{
					difference.sets[difference.size - 2] = intersect_end + Q;
					B_index += 2;
				}
			}
			else 
			{
				if(B.sets[B_index] < difference.sets[difference.size - 2])
				{
					B_index += 2;
				}
				else 
				{
					A_index += 2;
					if(A_index >= A.size)
						break;
					addNewIntervalwMem(&difference, A.sets[A_index], A.sets[A_index + 1]);
				}
			}
		}
		else if(mod(difference.sets[difference.size - 2]) < mod(B.sets[B_index]))
		{
			A_index += 2;
			if(A_index >= A.size)
				break;
			addNewIntervalwMem(&difference, A.sets[A_index], A.sets[A_index + 1]);
		}
		else 
		{
			B_index += 2;
		}
	}
	
	if(A_index < A.size)
	{
		int* temp = (int*)realloc(difference.sets, sizeof(int) *  (unsigned long)(difference.size + A.size - A_index));
		if(temp != NULL)
		{
			difference.sets = temp;
			memcpy(difference.sets + difference.size, A.sets, (unsigned long)A.size);
			difference.size += (A.size - A_index);
		}
	}

	return difference;
}

bool nalezy(zbior_ary A, int b)
{
	if(A.size == 0)
		return false;
	int low = 0;
	int high = A.size - 1;

	while(low + 1 < high)
	{
		int guess = (low + high)/2;
		
		if(mod(A.sets[guess]) == mod(b))
		{
			if(b < A.sets[guess])
				high = guess - 1;
			else
				low = guess;
		}
		else if(mod(A.sets[guess]) < mod(b))
		{
			low = guess;
		}
		else
			high = guess - 1;
	}
	if(mod(b) == mod(A.sets[low]) && A.sets[low] <= b && b <= A.sets[high])
		return true;
	else
		return false;
}

unsigned moc(zbior_ary A)
{
	if(A.size == 0)
		return 0;

	unsigned int cardinality = 0;
	for(int i = 0; i < A.size; i += 2)
	{
		cardinality += (unsigned int)(1 + ((A.sets[i + 1] - A.sets[i]) / Q));
	}
	return cardinality;
}

unsigned ary(zbior_ary A)
{
	return (unsigned)(A.size / 2);  
}

void printAry(zbior_ary A)
{
	if(A.size == 0)
		return;

	printf("{ ");
	for(int i = 0; i < A.size - 2; i += 2)
	{
		printf("%d %d, ", A.sets[i], A.sets[i + 1]);
	}
	printf("%d %d }\n", A.sets[A.size - 2], A.sets[A.size - 1]);
}


int main()
{
	zbior_ary test = ciag_arytmetyczny(20, 5, 185);
	zbior_ary test1,test2,test3;
	test1 = ciag_arytmetyczny(15, 5, 25);
	test2 = ciag_arytmetyczny(48, 5, 68);
	test3 = ciag_arytmetyczny(120, 5, 180);
	test = suma(test, ciag_arytmetyczny(23, 5, 48));
	test1 = suma(test1, suma(test2, test3));
	test = roznica(test, test1);

	for(int i = -5; i < 0; i++)
	{
		test = suma(test, ciag_arytmetyczny(25 * i + i, 5, i));
	}
	for(int i = 0; i < 15; i++)
	{
		test = suma(test, ciag_arytmetyczny(i, 5, 25 * i + i));
	}
	zbior_ary testie = suma(ciag_arytmetyczny(-15, 5, -10), ciag_arytmetyczny(0, 5, 25));


	zbior_ary intersection = roznica(test, testie);
	printAry(intersection);
}
