#include"zbior_ary.h"

static int Q;
#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))

// ADD SINGLETON FUNCTIONALITY TO ALL FUNCTIONS
// TEST THE FUNCTIONS AND WEED OUT THE EDGE CASES
// CHECK THE TIME COMPLEXITY 

void printAry(zbior_ary);

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
	zbior_ary sum;
	sum.size = A.size + B.size;
	printf("%d\n", sum.size);
	sum.sets = (int*)calloc((size_t)sum.size,sizeof(int));
	int i = 0;
	int A_index = 0;
	int B_index = 0;

	printf("to sum:\n");
	printAry(A);
	printAry(B);
	printf("\n");
	printAry(sum);
	while(A_index < A.size && B_index < B.size) // both havent ended
	{
		if(A.sets[A_index] % Q == B.sets[B_index] % Q) // same remainder
		{
			int interval_begin = max(A.sets[A_index], B.sets[B_index]);
			int interval_end = min(A.sets[A_index + 1], B.sets[B_index + 1]);

			if(interval_begin <= interval_end)
			{
				if(sum.sets[i + 1] == 0)
				{
					sum.sets[i] = min(A.sets[A_index],B.sets[B_index]);	
					sum.sets[1 + i] = max(A.sets[A_index + 1],B.sets[B_index + 1]);
				}
				else 
				{
					sum.sets[i + 1] = max(max(A.sets[A_index + 1], B.sets[B_index + 1]), sum.sets[i + 1]); 
				}

				if(A.sets[A_index + 1] < B.sets[B_index + 1])
				{
					A_index += 2;
					if(A_index >= A.size)
					{
						i += 2;
						B_index += 2;
					}
				}
				else 
				{
					B_index += 2;
					if(B_index >= B.size)
					{
						i += 2;
						A_index += 2;
					}
				}
			}
			else if(A.sets[A_index + 1] < B.sets[B_index]) 
			{
				if(A.sets[A_index + 1] + Q == B.sets[B_index])
				{
					if(sum.sets[i] == 0)
						sum.sets[i] = A.sets[A_index];

					sum.sets[i + 1] = B.sets[B_index + 1];
					A_index += 2;
					if(A_index >= A.size)
					{
						i += 2;
						B_index += 2;
					}
				}
				else 
				{
 					sum.sets[i] = A.sets[A_index];
					sum.sets[i + 1] = A.sets[A_index + 1];
					i += 2;
					A_index += 2;
				}

			}
			else
			{
				if(B.sets[B_index + 1] + Q == A.sets[A_index])
				{
					if(sum.sets[i] == 0)
						sum.sets[i] = B.sets[B_index];
				
					sum.sets[i + 1] = A.sets[A_index + 1];
					B_index += 2;
					if(B_index >= B.size)
					{
						A_index += 2;
						i += 2;
					}
				}
				else 
				{
					sum.sets[i] = B.sets[B_index];
					sum.sets[i + 1] = B.sets[B_index + 1];
					i += 2;
					B_index += 2;
				}
			}
		}
		else if(A.sets[A_index] % Q < B.sets[B_index] % Q)
		{
			sum.sets[i] = A.sets[A_index];
			sum.sets[i + 1] = A.sets[A_index + 1];
			i += 2;
			A_index += 2;
		}
		else 
		{
			sum.sets[i] = B.sets[B_index];
			sum.sets[i + 1] = B.sets[B_index + 1];
			i += 2;
			B_index += 2;
		}
		printAry(sum);
	}
	printf("heer");
	while(A_index < A.size)
	{
		printAry(sum);
		sum.sets[i] = A.sets[A_index];
		sum.sets[i + 1] = A.sets[A_index + 1];
		i += 2;
		A_index += 2;
	}
	
	while(B_index < B.size)
	{
		printAry(sum);
		sum.sets[i] = B.sets[B_index];
		sum.sets[i + 1] = B.sets[B_index + 1];
		i += 2;
		B_index += 2;
	}

	printAry(sum);
	printf("%d", i);
	int* temp = (int*)malloc(sizeof(int) * ((size_t)i));
	if(temp != NULL)
	{
		memcpy(temp,sum.sets, ((size_t)i) * sizeof(int));
		free(sum.sets);
		sum.sets = temp;
	}
	sum.size = i;
	return sum;
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B)
{
	zbior_ary intersection;
	intersection.size = 0;
	int A_index = 0;
	int B_index = 0;

	while(A_index < A.size && B_index < B.size)
	{
		if(A.sets[A_index] % Q == B.sets[B_index] % Q)
		{
			int intersect_begin = max(A.sets[A_index], B.sets[B_index]);
			int intersect_end = min(A.sets[A_index + 1], B.sets[B_index + 1]);

			if(intersect_begin < intersect_end)
			{
				int* new_array = (int*)realloc(intersection.sets, sizeof(int) * (unsigned long long)(intersection.size + 2));
				if(new_array != NULL)
					intersection.sets = new_array;

				intersection.sets = new_array;
				intersection.sets[intersection.size] = intersect_begin;
				intersection.sets[intersection.size + 1] = intersect_end;
				intersection.size += 2;
			}

			B_index += 2;
			A_index += 2;
		}
		else if(A.sets[A_index] % Q > B.sets[B_index] % Q)
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

	int A_index = 0;
	int B_index = 0; 
	int i = 0;
	
	while(A_index < A.size)
	{
		if(B_index >= B.size)
		{
			int* temp = (int*)realloc(difference.sets, sizeof(int) * (unsigned long long)(difference.size + A.size - A_index));
			if(temp != NULL)
				difference.sets = temp;
			memcpy(A.sets + A_index, difference.sets + i, (size_t)(A.size - A_index));
			i = i + A.size - A_index;
			A_index = A.size;
		}
		else if(A.sets[A_index] % Q == B.sets[B_index] % Q)
		{

			int intersect_begin = max(A.sets[A_index], B.sets[B_index]);
			int intersect_end = min(A.sets[A_index + 1], B.sets[B_index + 1]);

			if(intersect_begin < intersect_end)
			{	
				if(A.sets[A_index] < intersect_begin && intersect_end < A.sets[A_index + 1])	
				{
					int* temp = (int*)realloc(difference.sets, sizeof(int) * (unsigned long long)(difference.size + 4));
					if(temp != NULL)
						difference.sets = temp;
					difference.sets[i] = A.sets[A_index];
					difference.sets[i + 1] = intersect_begin;
					difference.sets[i + 2] = intersect_end;
					difference.sets[i + 3] = A.sets[A_index + 1];

					i += 4;
					B_index += 2;
				}
				else if(intersect_begin < A.sets[A_index] && A.sets[A_index + 1] < intersect_end)
				{
					A_index += 2;
				}
				else if(A.sets[A_index] < intersect_begin)
				{	
					int* temp = (int*)realloc(difference.sets, sizeof(int) * (unsigned long long)(difference.size + 2));
					if(temp != NULL)
						difference.sets = temp;
					difference.sets[i] = A.sets[A_index];
					difference.sets[i + 1] = intersect_begin;

					i += 2;
					A_index += 2;
				}
				else 
				{
					int* temp = (int*)realloc(difference.sets, sizeof(int) * (unsigned long long)(difference.size + 2));
					if(temp != NULL)
						difference.sets = temp;
					difference.sets[i] = intersect_end;
					difference.sets[i + 1] = A.sets[A_index + 1];
				
					i += 2;
					B_index += 2;
				}
			}	
			else 
			{
				if(A.sets[A_index] < B.sets[B_index])
				{

					if(difference.sets[i - 1] == A.sets[A_index + 1])
					{
						A_index += 2;
					}
					else
					{
						int* temp = (int*)realloc(difference.sets, sizeof(int) * (unsigned long long)(difference.size + 2));
						if(temp != NULL)
							difference.sets = temp;
						difference.sets[i] = A.sets[A_index];
						difference.sets[i  + 1] = A.sets[A_index + 1];
						A_index += 2;
						i += 2;
					}
				}
				else 
				{
					B_index += 2;
				}
			}
		}
		else if(A.sets[A_index] % Q < B.sets[B_index] % Q)
		{
			int* temp = (int*)realloc(difference.sets, sizeof(int) * (unsigned long long)(difference.size + 2));
			if(temp != NULL)
				difference.sets = temp;
			difference.sets[i] = A.sets[A_index];
			difference.sets[i  + 1] = A.sets[A_index + 1];
			A_index += 2;
			i += 2;
		}
		else 
		{
			B_index += 2;
		}
	}
	difference.size = i;
	return difference;
}

bool nalezy(zbior_ary A, int b)
{
	if(A.size == 0)
		return false;
	else if (A.size == 1) 
	{
		if(b == A.sets[0])
			return true;
		else
			return false;
	}

	int low = 0;
	int high = A.size - 1;


	while(low < high)
	{
		int guess = (low + high)/2;
		
		if(A.sets[guess] % Q == b % Q)
		{
			if(b < guess)
				high = guess;
			else
				low = guess;
		}
		else if(A.sets[guess] % Q < b % Q)
		{
			low = guess;
		}
		else
			high = guess;
	}
	if(low % 2 == 1)
		return false;
	else 
		return true;
}

unsigned moc(zbior_ary A)
{
	if(A.size == 0)
		return 0;
	if(A.size == 1)
		return 1;

	unsigned int cardinality = 0;
	for(int i = 0; i < A.size - 1; i++)
	{
		cardinality += (unsigned int)(1 + (A.sets[i + 1] - A.sets[i]) / Q);
	}
	return cardinality;
}

unsigned ary(zbior_ary A)
{
	if(A.size == 1)
		return 1;
	else 
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
	zbior_ary test = ciag_arytmetyczny(20, 5, 35);
	test = suma(test, ciag_arytmetyczny(45, 5, 50));
	test = suma(test, ciag_arytmetyczny(25, 5, 65));
	test = suma(test, ciag_arytmetyczny(37, 5, 47));
	test = suma(test, singleton(15));
	test = suma(test, singleton(70));
	printf("offical: ");

	printAry(test);
}
