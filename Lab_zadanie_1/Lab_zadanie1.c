#include<stdio.h>
#include<stdlib.h>
int max_divisor_sequence(int, int[]);


int main()
{

	int n;
	(void)!scanf("%d",  &n);
	int *nums = (int*)malloc((long unsigned int)n * sizeof(int));
	int *cur = nums;

	for(int i = 0; i < n; i++)
	{
		(void)!scanf("%d", cur);
		cur++;
	}
	printf("%d", max_divisor_sequence(n,nums));
}


int max_divisor_sequence(int n, int nums[])
{
	int curr_max = 1;
	for(int i = n-1; i > 0; i--)
	{
		int cur_len = 1;
		int j = i - 1;
		if(nums[j] == 0)
			continue;
		while( j >= 0 && (nums[i] % nums[j] == 0 ))
		{
			j--;
			cur_len++;
			if(nums[j] == 0)
				break;
		}

		if(cur_len > curr_max)
			curr_max = cur_len;
		if(curr_max > i)
			return curr_max;
		i = j;
	}

	return curr_max;
}
