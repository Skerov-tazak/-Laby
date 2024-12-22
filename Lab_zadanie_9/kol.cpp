#include"kol.h"
// Trzymamy informacje o końcu kolejki i o ilości członków kolejki do okienka w jej pierwszym node
// Kazda kolejka jest w porzadku normalnym (mniejsze liczby blizej poczatku kolejki) 
// lub w porzadku odwroconym - mniejsze liczby blizej konca kolejki. 
// Dla normalnego porzadku mamy fakt, ze "right" jest blizej poczatku,
// dla odwroconego porzadku zato - "left" jest blizej poczatku

typedef struct 
{
	interesant* tail;
	interesant* head;

}iter;

std::vector<iter> okienka;
int numerek_glob = 0;



interesant* next(interesant* current, interesant* prev)
{
	if(current->v1 == prev)
		return current->v2;
	else
		return current->v1;
}

void printAll()
{
	for(unsigned int i = 0; i < okienka.size(); i++)
	{
		std::cout << "|" << i << ": ";
		interesant* prev = okienka[i].head;
		interesant* current = okienka[i].head->v1;
		while(current != okienka[i].tail)
		{
			std::cout << current->numerek << " ";
			interesant* temp = current;
			current = next(current,prev);
			prev = temp;
		}
	}
	std::fflush(stdout);
	std::cout << std::endl;
}


void link(interesant* at, interesant* to_replace, interesant* replace_with) // potrzebne bo nie wiemy który pointer jest podlaczony
{
	if(at != NULL)
	{
		if(at->v1 == to_replace)
		{
			at->v1 = replace_with;
		}
		else 
		{
			at->v2 = replace_with;
		}
	}
}

interesant* removeIntrs(interesant* to_remove)
{
	link(to_remove->v1, to_remove, to_remove->v2);
	link(to_remove->v2, to_remove, to_remove->v1);
	return to_remove;
}

bool isEmpty(int k)
{
	return okienka[k].tail->v1 == okienka[k].head;
}
	
void pushBack(interesant* to_push, int k)
{
	to_push->v1 = okienka[k].tail;
	to_push->v2 = okienka[k].tail->v1;
	link(okienka[k].tail->v1,okienka[k].tail, to_push);
	okienka[k].tail->v1 = to_push;
}

interesant *nowy_interesant(int k)
{
	interesant* new_intrs = (interesant*)malloc(sizeof(interesant));
	new_intrs->numerek = numerek_glob;
	numerek_glob++;
	pushBack(new_intrs, k);
	return new_intrs;
}

void otwarcie_urzedu(int m)
{	
	for(int i = 0; i < m; i++)
	{
		interesant* head = (interesant*)malloc(sizeof(interesant));
		interesant* tail = (interesant*)malloc(sizeof(interesant));
		head->v1 = tail;
		tail->v1 = head;
		head->v2 = NULL;
		tail->v2 = NULL;
		head->numerek = -1;
		tail->numerek = -1;
		okienka.push_back({tail,head});
	}
}

int numerek(interesant *i)
{
	return i->numerek;
}

interesant *obsluz(int k)
{
	if(isEmpty(k))
		return NULL;
	else
	{
		return removeIntrs(okienka[k].head->v1);
	}
}

void zmiana_okienka(interesant *i, int k)
{
	removeIntrs(i);
	pushBack(i, k);
}

void zamkniecie_okienka(int k1, int k2)
{
	link(okienka[k1].head->v1, okienka[k1].head, okienka[k2].tail->v1);
	link(okienka[k2].tail->v1, okienka[k2].tail, okienka[k1].head->v1);
	link(okienka[k1].tail->v1, okienka[k1].tail, okienka[k2].tail);
	okienka[k2].tail->v1 = okienka[k1].tail->v1;
	okienka[k1].head->v1 = okienka[k1].tail;
	okienka[k1].tail->v1 = okienka[k1].head;
	std::fflush(stdout);
}

std::vector<interesant*> fast_track(interesant *i1, interesant *i2)
{
	interesant* right = i1->v1; // to sie tylko nazywa right, tak naprawde idzie w kierunku v1
	interesant* left = i1->v2; // ten idzie w kierunku v2
	interesant* prev_right = i1;
	interesant* prev_left = i1;
	std::vector<interesant*> right_vector;
	std::vector<interesant*> left_vector;
	right_vector.push_back(i1);
	left_vector.push_back(i1);

	while(right != i2 && left != i2) // znajduje i2 w czasie O(k) i uzupelnia wektor 	
	{
		if(right->numerek != -1) // sprawdza bounds
		{
			interesant* current = right;
			right = next(right, prev_right);
			prev_right = current;
			right_vector.push_back(prev_right);
		}
		if(left->numerek != -1)
		{	
			interesant* current = left;
			left = next(left, prev_left);
			prev_left = current;
			left_vector.push_back(prev_left);
		}
	} // po ukonczeniu petli right == i2 lub left == i2	

	if(right == i2)
	{
		if(right->v1 == prev_right)
		{
			link(i1->v2, i1, right->v2);
			link(i2->v2, i2, i1->v2);
		}
		else 
		{
			link(i1->v2, i1, right->v1);
			link(i2->v1, i2, i1->v2);
		}
		right_vector.push_back(i2);
		return right_vector;
	}
	else 
	{
		if(left->v1 == prev_left)
		{
			link(i1->v1, i1, left->v2);
			link(i2->v2, i2, i1->v1);
		}
		else 
		{
			link(i1->v1, i1, left->v2);
			link(i2->v2, i2, i1->v1);
		}
		left_vector.push_back(i2);
		return left_vector;
	}
}

void naczelnik(int k)
{
	interesant* temp;
	temp = okienka[k].head;
	okienka[k].head = okienka[k].tail;
	okienka[k].tail = temp;
}

std::vector<interesant*> zamkniecie_urzedu()
{
	std::vector<interesant*> answer;
	for(unsigned int i = 0; i < okienka.size(); i++)
	{
		interesant* current = okienka[i].head->v1;
		interesant* prev = okienka[i].head;
		while(current != okienka[i].tail)
		{
			answer.push_back(current);
			interesant* cur_temp = current;
			current = next(cur_temp, prev);
			prev = cur_temp;
		}
	}

	return answer;
}
