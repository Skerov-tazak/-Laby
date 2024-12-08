#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct
{
	double a;
	double b;
}Line;

typedef struct
{
	double x;
	double y;
}Vector;

typedef struct
{
	double p;
	double q;
}Point;
 
typedef struct
{
	Line line;
	Vector direction;
}Condition;

typedef struct
{
	double radius_from;
	Point radius_at;
	Condition* conditions;

}R2subSet;

double dot_product(Vector a, Vector b)
{
	return a.x * b.x + a.y * b.y;
}

double length(Vector a)
{
	return sqrt(dot_product(a,a));
}

Vector flipVector(Vector to_flip, Line flip_across)
{
	Vector line_vect;
	line_vect.x = 1;
	line_vect.y = flip_across.a;

	Vector orthogonal;

	orthogonal.x = to_flip.x - (dot_product(line_vect, to_flip) * (line_vect.x/length(line_vect)));
	orthogonal.y = to_flip.y - (dot_product(line_vect, to_flip) * (line_vect.y/length(line_vect)));
	
	to_flip.x += 2 * orthogonal.x;
	to_flip.y += 2 * orthogonal.y;

	return to_flip;
}

Point flipPoint(Point to_flip, Line flip_across)
{

	Vector offset;
	offset.x = flip_across.b / (flip_across.a + 1/flip_across.a);
	offset.y = flip_across.a * offset.x + flip_across.b;

	Vector to_point;
	to_point.x = to_flip.p;
	to_point.y = to_flip.q;

	to_point = flipVector(to_point, flip_across);
	
	to_point.x += 2 * offset.x;
	to_point.y += 2 * offset.y;
	to_flip.p = to_point.x;
	to_flip.q = to_point.y;
	return to_flip;
}

Line flipLine(Line to_flip, Line flip_across)
{
	double a,b,m,t;
	a = flip_across.a;
	b = flip_across.b;
	m = to_flip.a;
	t = to_flip.b;
	
	if(a == m)
	{
		if(b != t)
		{
			double diff = to_flip.b - flip_across.b;
			to_flip.b -= 2 * diff;
		}

		return 
			to_flip;
	}
	else if(a == INFINITY)
	{
		to_flip.a = -to_flip.a;
		to_flip.b = -to_flip.b;
	}
	else if(m == INFINITY)
	{
		
	}
	
	double x_intersect = (t - b)/(a - m);
	double y_intersect = a * x_intersect + b;

	double flipped_dir = (a - ((m - a) / (1 + m * a))) /
								(1 + (a * ((m - a) / (1 + m * a))));
	
	double flipped_offset = y_intersect - flipped_dir * x_intersect;

	Line to_return;
	to_return.a = flipped_dir;
	to_return.b = flipped_offset;
	return to_return;
}

bool fullfilsCondition(Point point, Condition condition)
{
	if(condition.direction.y == 0)
	{
		if(condition.direction.x > 0)
		{
			if(point.x > condition.line)
		}
		else if(condition.direction.x < 0)
		{

		}
	}
	else if(condition.direction.y < 0)
	{

	}
	else if(condition.direction.y > 0)
	{

	}
}

int main()
{

}
