#include"zbior_ary.h"
#include <stdio.h>

static int Q; // Keep Q in global var
#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))

extern void print(zbior_ary A);

int mod(int a) // This modulo function retruns the positive remainder for all integers
{
	int mod = a % Q;
	if(mod < 0){
		mod += Q;
	}
	return mod;
}

void intervalMemAlloc(zbior_ary* add_to, int start, int end) // constructs a new interval at the end of zbior_ary array, enlarging the allocated memory as needed
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

void removeLastEntry(zbior_ary* to_remove) // removes the last two elements (one interval) in the array and deallocs the memory 
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

void copyInterval(int* add_to, int to_index, int* add_from, int from_index) // copies interval in-place
{
	add_to[to_index] = add_from[from_index];
	add_to[to_index + 1] = add_from[from_index + 1];
}

void mergeOverlapIntervals(int* merge_at, int at_index, int* merge_with, int with_index) // sums overlapping intervals
{
	merge_at[at_index + 1] = max(merge_at[at_index + 1], merge_with[with_index + 1]);
}

zbior_ary ciag_arytmetyczny(int a, int q, int b) // the constructor as required 
{
	zbior_ary new_set;
	new_set.sets = (int*)malloc(sizeof(int) * 2);
	new_set.sets[0] = a;
	new_set.sets[1] = b;
	new_set.size = 2;
	Q = q;
	return new_set;
}

zbior_ary singleton(int a) // the second required constructor
{
	zbior_ary singleton;
	singleton.sets = (int*)malloc(sizeof(int) * 2);
	singleton.sets[0] = a;
	singleton.sets[1] = a;
	singleton.size = 2;
	return singleton;
}


zbior_ary suma(zbior_ary A, zbior_ary B) // calculates the sum of two zbior_ary
{
	if(A.size == 0) // Base conditions for null arrays
		return B;
	if(B.size == 0)
		return A;

	zbior_ary sum;
	sum.sets = (int*)calloc((unsigned long)(A.size + B.size), sizeof(int)); // allocate overboard memory for performance
	sum.size = 0;
	int i = 0;
	int A_index = 0;
	int B_index = 0;
	
	if(mod(A.sets[0]) == mod(B.sets[0])) // Initialise the first interval
	{
		if(A.sets[0] < B.sets[0])
		{
			copyInterval(sum.sets, 0, A.sets, 0);
			A_index += 2;
		}
		else
		{
			copyInterval(sum.sets, 0, B.sets, 0);
			B_index += 2;
		}
	}
	else if(mod(A.sets[0]) < mod(B.sets[0]))
	{	
		copyInterval(sum.sets, 0, A.sets, 0);
		A_index += 2;
	}
	else 
	{
		copyInterval(sum.sets, 0, B.sets, 0);
		B_index += 2;
	}
	sum.size = 2;
	

	while(A_index < A.size || B_index < B.size) // zipper merge intervals if the same Q remainder
	{
		if(A_index < A.size && B_index < B.size && mod(A.sets[A_index]) == mod(B.sets[B_index]))
		{
			if(A.sets[A_index] < B.sets[B_index])
			{
				if(mod(A.sets[A_index]) == mod(sum.sets[i]) && A.sets[A_index] <= sum.sets[i + 1] + Q) // takes care of overlapping intervals
				{
					mergeOverlapIntervals(sum.sets, i, A.sets, A_index);
					A_index += 2;
				}
				else 
				{
					i += 2;
					copyInterval(sum.sets, i, A.sets, A_index);
					sum.size += 2;
					A_index += 2;
				}
			}
			else if(B.sets[B_index] < A.sets[A_index])
			{	
				if(mod(B.sets[B_index]) == mod(sum.sets[i]) && B.sets[B_index] <= sum.sets[i + 1] + Q) // overlapping for B;
				{
					mergeOverlapIntervals(sum.sets, i, B.sets, B_index);
					B_index += 2;
				}
				else 
				{
					i += 2;
					copyInterval(sum.sets, i, B.sets, B_index);
					sum.size += 2;
					B_index += 2;
				}
			}
			else if(A.sets[A_index] == B.sets[B_index])
			{
				if(A.sets[A_index + 1] > B.sets[B_index + 1])
				{
					if(mod(B.sets[B_index]) == mod(sum.sets[i]) && B.sets[B_index] <= sum.sets[i + 1] + Q) // overlapping for B;
					{
						mergeOverlapIntervals(sum.sets, i, A.sets, A_index);
						A_index += 2;
						B_index += 2;
					}
					else 
					{
						i += 2;
						copyInterval(sum.sets, i, A.sets, A_index);
						sum.size += 2;
						B_index += 2;
						A_index += 2;
					}

				}
				else 
				{
					if(mod(B.sets[B_index]) == mod(sum.sets[i]) && B.sets[B_index] <= sum.sets[i + 1] + Q) // overlapping for B;
					{
						mergeOverlapIntervals(sum.sets, i, B.sets, B_index);
						B_index += 2;
						A_index += 2;
					}
					else 
					{
						i += 2;
						copyInterval(sum.sets, i, B.sets, B_index);
						sum.size += 2;
						B_index += 2;
						A_index += 2;
					}
				}
			}
		}
		else if(A_index < A.size && (B_index >= B.size || mod(A.sets[A_index]) < mod(B.sets[B_index]))) // if no more in B to process
		{
			if(mod(A.sets[A_index]) == mod(sum.sets[i])) // checks for overlaps
			{
				if(A.sets[A_index] <= sum.sets[i + 1] + Q) // merges overlaping intervals
				{
					mergeOverlapIntervals(sum.sets, i, A.sets, A_index);
					A_index += 2;
				}
				else // or copies the new non-overlaping interval 
				{
					i += 2;
					copyInterval(sum.sets, i, A.sets, A_index);
					sum.size += 2;
					A_index += 2;
				}

			}
			else 
			{	
				i += 2;
				copyInterval(sum.sets, i, A.sets, A_index);
				sum.size += 2;
				A_index += 2;
			}
		}
		else if(A_index >= A.size || mod(B.sets[B_index]) < mod(A.sets[A_index])) // if no more in A to process
		{
			if(mod(B.sets[B_index]) == mod(sum.sets[i])) // check for overlaps
			{
				if(B.sets[B_index] <= sum.sets[i + 1] + Q)
				{
					mergeOverlapIntervals(sum.sets, i, B.sets, B_index);
					B_index += 2;
				}
				else 
				{
					i += 2;
					copyInterval(sum.sets, i, B.sets, B_index);
					sum.size += 2;
					B_index += 2;
				}

			}
			else 
			{	
				i += 2;
				copyInterval(sum.sets, i, B.sets, B_index);
				sum.size += 2;
				B_index += 2;
			}
		}
	}

	int* new_array = (int*)realloc(sum.sets, (unsigned long)(sum.size) * sizeof(int)); // truncate unnecessary memory
	if(new_array != NULL)
		sum.sets = new_array;
	return sum;
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B) // calculates the intersection of two zbior_ary
{
	zbior_ary intersection;
	intersection.size = 0;
	int A_index = 0;
	int B_index = 0;

	while(A_index < A.size && B_index < B.size)
	{

		if(mod(A.sets[A_index]) == mod(B.sets[B_index]))
		{
			int intersect_begin = max(A.sets[A_index], B.sets[B_index]);
			int intersect_end = min(A.sets[A_index + 1], B.sets[B_index + 1]);

			if(intersect_begin <= intersect_end)
			{
				intervalMemAlloc(&intersection,	intersect_begin, intersect_end);
			}

			if(A.sets[A_index + 1] == B.sets[B_index + 1]) // Increments the index for the interval that ends earlier
			{
				A_index += 2;
				B_index += 2;
			}
			else if(A.sets[A_index + 1] < B.sets[B_index + 1])
				A_index += 2;
			else
				B_index += 2;
		}
		else if(mod(A.sets[A_index]) > mod(B.sets[B_index])) // this operation only makes sense for intervals with the same remainder
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

	// The algo works 'hot' on difference array, so it needs to allocate the first value
	intervalMemAlloc(&difference, A.sets[0], A.sets[1]); 

	int A_index = 0;
	int B_index = 0; 

	// difference.size - 2 means "index of start of most recent interval in array"
	// difference.size - 1 means "index of end of most recent interval in array"

	while(B_index < B.size)
	{	
		if(mod(difference.sets[difference.size - 2]) == mod(B.sets[B_index]))
		{
			int intersect_begin = max(B.sets[B_index], difference.sets[difference.size - 2]);
			int intersect_end = min(B.sets[B_index + 1], difference.sets[difference.size - 1]);
			
			if(intersect_begin <= intersect_end) // check if there is any intersection to subtract
			{
				if(difference.sets[difference.size - 2] == intersect_begin && difference.sets[difference.size - 1] == intersect_end) 
				{
					// this case is when the entire interval needs to be dropped
					A_index += 2;
					if(A_index >= A.size)
					{
						removeLastEntry(&difference);
						break;
					}

					difference.sets[difference.size - 2] = A.sets[A_index];
					difference.sets[difference.size - 1] = A.sets[A_index + 1];

				}
				else if(difference.sets[difference.size - 2] < intersect_begin && intersect_end < difference.sets[difference.size - 1])
				{
					// this case chops current interval in two parts
					intervalMemAlloc(&difference, intersect_end + Q, difference.sets[difference.size - 1]);
					difference.sets[difference.size - 3] = intersect_begin - Q;
				}	
				else if(difference.sets[difference.size - 2] < intersect_begin)
				{
					// this chops the end of this interval off
					difference.sets[difference.size - 1] = intersect_begin - Q;
					A_index += 2;
					if(A_index >= A.size)
						break;
					intervalMemAlloc(&difference, A.sets[A_index], A.sets[A_index + 1]);
				}
				else 
				{
					// chops the begining of this interval off
					difference.sets[difference.size - 2] = intersect_end + Q;
					B_index += 2;
				}
			}
			else 
			{
				// If there is no intersection, because B is before this interval
				if(B.sets[B_index + 1] < difference.sets[difference.size - 2])
				{
					B_index += 2;
				}
				else // or because the last in difference is before B
				{
					A_index += 2;
					if(A_index >= A.size)
						break;
					intervalMemAlloc(&difference, A.sets[A_index], A.sets[A_index + 1]);
				}
			}
		}
		else if(mod(difference.sets[difference.size - 2]) < mod(B.sets[B_index]))
		{
			A_index += 2;
			if(A_index >= A.size)
				break;
			intervalMemAlloc(&difference, A.sets[A_index], A.sets[A_index + 1]);
		}
		else 
		{
			B_index += 2;
		}
	}
	// why +2? why so many breaks? Basically, the counter needs to increase ONLY after we are done with the processing of the current 
	// interval. It also shouldn't load the next one after the last increase. Too lazy to rewrite this decently (and this works just fine).
	if(A_index + 2 < A.size) // copy all the entries in A, when we are already exhausted with B
	{
		int* temp = (int*)realloc(difference.sets, sizeof(int) *  (unsigned long)(difference.size + A.size - A_index - 2));
		if(temp != NULL)
		{
			difference.sets = temp;
			memcpy(difference.sets + difference.size, A.sets + A_index + 2, (unsigned long)(A.size - A_index - 2) * sizeof(int));
			difference.size += (A.size - A_index - 2);
		}
	}

	return difference;
}

bool nalezy(zbior_ary A, int b)
{
	if(A.size == 0) 
		return false;

	int low = 0;
	int high = (int)ary(A) - 1;

	while(low <= high) // binsearches through intervals until it finds the right one
	{
		int guess = low + (high - low)/2;
		if(mod(b) == mod(A.sets[guess * 2]))
		{
			if(A.sets[guess * 2] <= b && b <= A.sets[guess * 2 + 1])
			{
				return true;
			}
			else if(b < A.sets[guess * 2])
			{
				high = guess - 1;
			}
			else if(b > A.sets[guess * 2 + 1])
			{
				low = guess + 1;
			}
			
		}
		else if(mod(b) < mod(A.sets[guess * 2]))
		{
			high = guess - 1;
		}
		else
		{
			low = guess + 1;
		}
	}
	return false;
}

unsigned moc(zbior_ary A)
{
	if(A.size == 0)
		return 0;

	unsigned int cardinality = 0;
	for(int i = 0; i < A.size; i += 2) // Ary(A) iterations
	{
		cardinality += (unsigned int)(1 + ((A.sets[i + 1] - A.sets[i]) / Q));
	}
	return cardinality;
}

unsigned ary(zbior_ary A)
{
	return (unsigned)(A.size / 2);  
}

