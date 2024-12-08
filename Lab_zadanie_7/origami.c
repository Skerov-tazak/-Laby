#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<stdbool.h>
#define debug(x,y) printf(" %lf,  %lf\n", (double)x, (double)y); fflush(stdout)
#define max(x,y) ((x) > (y) ? (x) : (y))

// Basic structs which allow for clearer code
typedef struct
{
	double x;
	double y;
}Point;

typedef struct
{
	double dx;
	double dy;

}Vector;

typedef struct
{
	Vector dir;
	Point at;

}Line;

// Rectangle represented as a pair of points, lower left and upper right corners
typedef struct
{
	Point ll_corner;
	Point ur_corner;

}Rectangle;

typedef struct 
{
	double r;
	Point center;

}Circle;

// This struct represents the current Step in constructing the origami. It also knows if it's a circle or a Rectangle
typedef struct
{
	bool isCircle;
	bool isRect;
	int prev;
	Circle c_start;
	Rectangle r_start;
	Line new_line;
}Step;

// comparator fucntion to avoid flaoting point errors in 0 coparisons
double comp(double a, double b)
{
	if(fabs(a - b) < 10E-6)
		return 0;
	else if(a > b)
		return 1;
	else 
		return -1;
}

double dot_product(Vector A, Vector B)
{
	return (A.dx * B.dx + A.dy * B.dy);
}

double cross_product(Vector A, Vector B)
{
	return A.dx * B.dy - A.dy * B.dx;
}

// computes the square of the length
double sqr_length(Vector A)
{
	return (fabs(dot_product(A,A)));
}

// This code uses vector geometry to implement a flip of a point across a line 
// The vector perpendicular to the line from the point to be flipped is found,
// then this vector is scaled to the distance between the line and the points
// at the end, double that vector is added to the point, yielding the flipped image.
Point flipAcrossLine(Point A, Line p)
{
	double plen = sqr_length(p.dir);
	Vector translation_factor;
	double scl_factr1 = dot_product(p.dir, (Vector){p.at.x,p.at.y});
	translation_factor.dx = -(scl_factr1 * p.dir.dx/plen) + p.at.x;
	translation_factor.dy =	-(scl_factr1 * p.dir.dy/plen) + p.at.y;

	Vector A_perp;
	double scl_factr2 = dot_product((Vector){A.x,A.y}, p.dir);
	A_perp.dx = -A.x + (scl_factr2 * p.dir.dx/plen);
	A_perp.dy = -A.y + (scl_factr2 * p.dir.dy/plen); 
	
	return (Point){A.x + 2 * (A_perp.dx + translation_factor.dx), A.y + 2 * (A_perp.dy + translation_factor.dy)};
}	

// Converts two points to a line, in a point-vector form
Line pointsToLine(Point A, Point B)
{
	Line new_line;
	new_line.dir.dx = (B.x - A.x);
	new_line.dir.dy = (B.y - A.y);

	new_line.at = A;
	return new_line;
}

// loads data in the given format
void loadData(Step* head, int n)
{
	for(int i = 0; i < n; i++)
	{
		char temp;
		char flag;
		(void)!scanf("%c %c", &temp, &flag);
		if(flag == 'P')
		{
			(void)!scanf("%lf", &(head[i].r_start.ll_corner.x));
			(void)!scanf("%lf", &(head[i].r_start.ll_corner.y));
			(void)!scanf("%lf", &(head[i].r_start.ur_corner.x));
			(void)!scanf("%lf", &(head[i].r_start.ur_corner.y));
			head[i].prev = 0;
			head[i].isCircle = false;
			head[i].isRect = true;
		}
		else if(flag == 'K')
		{

			(void)!scanf("%lf", &(head[i].c_start.center.x));
			(void)!scanf("%lf", &(head[i].c_start.center.y));
			(void)!scanf("%lf", &(head[i].c_start.r));
			head[i].prev = 0;
			head[i].isCircle = true;
			head[i].isRect = false;
		}
		else if(flag == 'Z')
		{
			(void)!scanf("%d", &(head[i].prev));
			Point A, B;	
			(void)!scanf("%lf", &(A.x));
			(void)!scanf("%lf", &(A.y));
			(void)!scanf("%lf", &(B.x));
			(void)!scanf("%lf", &(B.y));
			head[i].isCircle = false;
			head[i].isRect = false;
			head[i].new_line = pointsToLine(A,B);
		}
	}
}

bool belongsToRectangle(Point A, Rectangle c)
{
	if(comp(A.x,c.ll_corner.x) >= 0 && comp(A.y,c.ll_corner.y) >= 0 && comp(A.x,c.ur_corner.x) <= 0 && comp(A.y, c.ur_corner.y) <= 0)
		return true;
	else 
		return false;
}

bool belongsToCircle(Point A, Circle c)
{
	if(comp((A.x - c.center.x) * (A.x - c.center.x) + (A.y - c.center.y) * (A.y - c.center.y), c.r * c.r) <= 0)
		return true;
	else 
		return false;
}


// This recursively implemented function doubles the number of points every fold (if a certain condition is satisfied)
// and then traces them back to the begining, adding one valid penetration if the traced points do indeed pass throught he initial shape

int checkPenetration(Point A, Step* head, int i)
{
	if(head[i].isCircle)	
	{
		if(belongsToCircle(A, head[i].c_start))
			return 1;
		else 
			return 0;
	}
	else if(head[i].isRect)
	{
		if(belongsToRectangle(A, head[i].r_start))
			return 1;
		else
			return 0;
	}	
	else
	{
		if(comp(cross_product(head[i].new_line.dir,	(Vector){A.x - head[i].new_line.at.x, A.y - head[i].new_line.at.y}), 0) == 0)
		{
			return checkPenetration(A, head, head[i].prev - 1);
		}
		else if(cross_product(head[i].new_line.dir,	(Vector){A.x - head[i].new_line.at.x, A.y - head[i].new_line.at.y}) > 0)
		{
			return (checkPenetration(flipAcrossLine(A, head[i].new_line), head, head[i].prev - 1) +
														checkPenetration(A, head, head[i].prev - 1));
		}
		else 
			return 0;
	}
}

int main()
{
	int n;
	int q;

	(void)!scanf("%d", &n);
	(void)!scanf("%d", &q);
	Step* head = malloc(sizeof(Step) * (size_t)n);
	loadData(head, n);
	

	for(int i = 0; i < q; i++)
	{
		int begin;
		Point to_check;

		(void)!scanf("%d", &begin);
		(void)!scanf("%lf", &to_check.x);
		(void)!scanf("%lf", &to_check.y);

		printf("%d\n", checkPenetration(to_check, head, begin - 1));
	}
}
