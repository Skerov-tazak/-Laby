#include <assert.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include <limits.h>
#include <stdbool.h>
#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))

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
	long long target = distances[low] + (distances[high] - distances[low] + 1)/2;

	while(low < high)
	{
		long long mid = low + (high - low)/2;

		if(distances[mid] == target)
			return mid;
		else if(distances[mid] < target)
			low = mid + 1;
		else
			high = mid;
	}

	if(distance(target, distances[low]) < distance(target, distances[low - 1]))
		return low;
	else
		return low - 1;

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

	if(isValid(low, at, high))
		return at;

	long long right = at + 1;
	long long left = at - 1;
	long long target = distances[low] + (distances[high] - distances[low] + 1) / 2;

	while(low < left && right < high)
	{
		if(distance(distances[left], target) > distance(distances[right], target))
		{
			if(isValid(low, right, high))
				return right;
			right++;
		}
		else
		{
			if(isValid(low, left, high))
				return left;
			left--;
		}
	}
	while(low < left)
	{
		if(isValid(low, left, high))
			return left;
		left--;

	}
	while(right < high)
	{
		if(isValid(low, right, high))
			return right;
		right++;
	}
	return 0;
}


long long findMaxDistance()
{ 
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

bool existThreeDifferent()
{

		long long first = IDs[0];
		long long second = 0;
		long long third = 0;
		long long index = 1;
		
		while(second == 0 && index < N)
		{
			if(IDs[index] != first) 
				second = IDs[index];
			index++;
		}
		while(third == 0 && index < N)
		{
			if(IDs[index] != first && IDs[index] != second) 
				third = IDs[index];
			index++;
		}
	
		if(third == 0)
			return false;
		else 
			return true;
}


void testie()
{
		(void)!scanf("%lld", &N);

		for(long long i = 0; i < N; i++)
		{
			(void)!scanf("%lld", IDs + i);
			(void)!scanf("%lld", distances + i);
		}


		if(existThreeDifferent()){
			printf("%lld ", findMinDistance());		
			printf("%lld", findMaxDistance());
		}
		else 
			printf("0 0");
}


int main()
{
	testie();
}

