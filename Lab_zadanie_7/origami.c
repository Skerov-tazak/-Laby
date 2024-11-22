#include<stdlib.h>
#include<stdio.h>


typedef enum inequality{smaller, greater} inequality;

typedef struct
{
	double x_factor;
	double y_factor;
	double free_factor;
	inequality sign;

}LnrCondition;

typedef struct
{
	double radius;
	LnrCondition* equalities;
}Set;






int main()
{

}
