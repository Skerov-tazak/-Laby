#include <assert.h>
#include <time.h>
#include<stdlib.h>
#include<stdio.h>
#include <limits.h>
#include <stdbool.h>
#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))
#define debug(x) printf("We are in function %s\n", x); fflush(stdout)


long long N;
long long IDs[1000000];
long long distances[1000000];

long long distance(long long a, long long b)
{
	if(a > b)
		return a - b;
	else 
		return b - a;
}

long long findMinDistance()
{
	long long last;
	long long current = 1;
	long long next;
	long long found_min = LLONG_MAX;

	while(IDs[current] == IDs[current - 1])  
		current++;

	next = current + 1;
	last = current - 1;

	while(next < N)
	{
		if(IDs[next] != IDs[next - 1])
		{
			if(IDs[next] == IDs[last])
			{
				current = next;
				last = current - 1;
				next++;
			}
			else 
			{
				while(current < next)
				{
					found_min = min(max(distance(distances[current], distances[last]), distance(distances[next], distances[current])), found_min);
					current++;
				}
				last = current - 1;
				next++;
			}
		}
		else 
		{
			next++;
		}
	}
	return found_min;
}

void findLastThree(long long last_three[])
{
	last_three[0] = N - 1;
	long long runner = N - 2;

	while(IDs[last_three[0]] == IDs[runner])
		runner--;
	last_three[1] = runner;
	runner--;

	while(IDs[last_three[0]] == IDs[runner] || IDs[last_three[1]] == IDs[runner])
		runner--;	
	last_three[2] = runner;

}

void findFirstThree(long long first_three[])
{
	first_three[0] = 0;
	long long runner = 1;

	while(IDs[first_three[0]] == IDs[runner])
		runner++;
	first_three[1] = runner;
	runner++;
	
	while(IDs[first_three[0]] == IDs[runner] || IDs[first_three[1]] == IDs[runner])
		runner++;
	first_three[2] = runner;
}

long long binFindMiddle(long long low, long long high)
{
	debug("binFindMiddle");
	long long target = distances[low] + ((distances[high] - distances[low]) + 1)/2;
	printf("find between %lld[%lld] %lld[%lld]\n", distances[low], IDs[low], distances[high], IDs[high]);	

	while(low < high)
	{
		long long mid = low + (high - low)/2;

		if(distances[mid] == target){
			printf("TARGET IN SET: %lld\n", target);
			return mid;

		}
		else if(distances[mid] < target)
			low = mid + 1;
		else
			high = mid;
	}



	if(distance(target, distances[low]) < distance(target, distances[low - 1]))
	{
		printf("NOT IN SET: low found %lld, for target: %lld\n", distances[low],target);
		return low;
	}
	else
	{
		printf("NOT IN SET: low found %lld, for target: %lld\n", distances[low - 1],target);
		return low - 1;
	}

}

bool isValid(long long a, long long b, long long c)
{
	if(IDs[a] != IDs[b] && IDs[b] != IDs[c] && IDs[c] != IDs[a])
		return true;
	else 
		return false;
}

long long linearRadiusFindValid(long long at, long long low, long long high)
{
	debug("linearRadiusFindValid");

	if(isValid(low, at, high))
	{
		printf("BEST FOUND: %lld[%lld]\n", distances[at],IDs[at]);
		return at;
	}
	long long right = at + 1;
	long long left = at - 1;
	long long target = distances[low] + ((distances[high] - distances[low]) + 1) / 2;

	while(low < left && right < high)
	{
		if(distance(distances[left], target) > distance(distances[right], target))
		{
			if(isValid(low, right, high))
			{
				printf("BEST FOUND: %lld[%lld]\n", distances[right],IDs[right]);
				return right;
			}
			right++;
		}
		else
		{
			if(isValid(low, left, high))
			{	
				printf("BEST FOUND: %lld[%lld]\n", distances[left],IDs[left]);
				return left;
			}
			left--;
		}
	}
	while(low < left)
	{
		if(isValid(low, left, high))
		{
			printf("BEST FOUND: %lld[%lld]\n", distances[left],IDs[left]);
			return left;
		}
		left--;

	}
	while(right < high)
	{
		if(isValid(low, right, high))
		{	
			printf("BEST FOUND: %lld[%lld]\n", distances[right],IDs[right]);
			return right;
		}
		right++;
	}
	return 0;
}


long long findMaxDistance()
{
	printf("\n\n\n########################");
	debug("findMaxDistance");
	long long current_max = 0;
	long long first_three[3];
	long long last_three[3];
	
	findFirstThree(first_three);
	findLastThree(last_three);
	
	for(int i = 0; i < 3; i++)
	{
		long long low = first_three[i];
		for(int j = 0; j < 3; j++)
		{
			long long high = last_three[j];

			if(IDs[low] != IDs[high] && high > low)
			{
				long long best_third = linearRadiusFindValid(binFindMiddle(low, high), low, high);
				if(best_third)
				{
					current_max = max(current_max, 
							min(distance(distances[low], distances[best_third]),distance(distances[high], distances[best_third])));			
				}
			}
		}
	}
	return current_max;
}


void testie()
{
		(void)!scanf("%lld", &N);

		for(long long i = 0; i < N; i++)
		{
			(void)!scanf("%lld", IDs + i);
			(void)!scanf("%lld", distances + i);
		}

		long long a = IDs[0];
		long long b = 0;
		long long c = 0;
		long long i = 1;
		while(b == 0 && i < N){
			if(IDs[i] != a) 
				b = IDs[i];
			i++;
		}
		while(c == 0 && i < N){
			if(IDs[i] != a && IDs[i] != b) 
				c = IDs[i];
			i++;
		}
		if(c == 0){
			printf("0 0");
			return;
		} 



		printf("%lld ", findMinDistance());		
		printf("%lld", findMaxDistance());
}

int bruteforceCheck(long long a1[], long long a2[], int size, long long min1, long long max1) 
{

	long long best_start = 0;
	long long best_end = N -1;
	long long best_mid = N /2;

    long long minimum = 2147483647;
    long long maximum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            for (int h = j + 1; h < size; h++) {
                if (a1[i] != a1[j] && a1[h] != a1[j] && a1[i] != a1[h]) 
				{
					if(maximum < min(a2[h] - a2[j], a2[j] - a2[i]))
					{
						maximum = min(a2[h] - a2[j], a2[j] - a2[i]);
						best_start = a2[h];
						best_mid = a2[j];
						best_end = a2[i];
					}
                    minimum = min(minimum, max(a2[h] - a2[j], a2[j] - a2[i]));
                }
            }
        }
    }
	if (minimum == 2147483647) 
	{
        minimum = 0;
        maximum = 0;
    }

    if(minimum != min1 || maximum != max1) 
	{
		printf("VALID IS: %lld %lld, FOR %lld, %lld, %lld RECEIVED: %lld %lld\n", minimum, maximum, best_start, best_mid, best_end, min1, max1);
		return 0;
	}
	else 
		return 1;
}

bool existThreeDifferent()
{

		long long a = IDs[0];
		long long b = 0;
		long long c = 0;
		long long i = 1;
		while(b == 0 && i < N){
			if(IDs[i] != a) 
				b = IDs[i];
			i++;
		}
		while(c == 0 && i < N){
			if(IDs[i] != a && IDs[i] != b) 
				c = IDs[i];
			i++;
		}
		if(c == 0){
			return false;
		} 
		return true;
}

void print()
{
	for(int i = 0; i < N; i++)
	{
		printf("%lld %lld\n", IDs[i], distances[i]);
	}
}


int test() {
    int asd = 0;
    while (true) {
        asd++;
        int size = 30;
		N = size;
        int networks = 4;
        int distance = 3;;
        srand((unsigned int)(time(NULL)+asd));
        for (int i = 0; i < size; i++) {
            IDs[i] = rand() % networks + 1;
        }
        distances[0] = 0;
        for (int i = 1; i < size; i++) {
            distances[i] = distances[i - 1] + rand() % distance;
        }

		//insert code here, min is left number in print, max is right
		long long minimum = 0;
		long long maximum = 0;
		if(existThreeDifferent())
		{
			minimum = findMinDistance();
			maximum = findMaxDistance();
		}

       
     	if(bruteforceCheck(IDs, distances, size, minimum, maximum) == 0)
		{
			print();
			break;
		}
    }
    return 0;
}


int main()
{
	test();
}

