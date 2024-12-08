#include"kol.h"
#include <cstddef>
#include <cstdlib>
#include <locale>
// Trzymamy informacje o końcu kolejki i o ilości członków kolejki do okienka w jej pierwszym node
// Kazda kolejka jest w porzadku normalnym (mniejsze liczby blizej poczatku kolejki) 
// lub w porzadku odwroconym - mniejsze liczby blizej konca kolejki. 
// Dla normalnego porzadku mamy fakt, ze "right" jest blizej poczatku,
// dla odwroconego porzadku zato - "left" jest blizej poczatku

typedef struct 
{
	interesant* last;
	interesant* first;

}iter;

std::vector<iter> okienka;
int numerek_glob = 0;


bool isReversed(int k)
{
	return okienka[k].first->left == NULL;
}


interesant *nowy_interesant(int k)
{
	interesant* nowy = (interesant*)malloc(sizeof(interesant));
	nowy->numerek = numerek_glob;
	numerek_glob++;

	if(isReversed(k))
	{
		nowy->right = okienka[k].last;
		nowy->left = okienka[k].last->left;
		okienka[k].last->left = nowy;
	}
	else 
	{
		nowy->left = okienka[k].last;
		nowy->right = okienka[k].last->right;
		okienka[k].last->right = nowy;
	}	
	return nowy;
}

void otwarcie_urzedu(int m)
{	
	for(int i = 0; i < m; i++)
	{
		interesant* pierwszy_kraniec = (interesant*)malloc(sizeof(interesant));
		interesant* ostatni_kraniec = (interesant*)malloc(sizeof(interesant));
		pierwszy_kraniec->left = ostatni_kraniec;
		pierwszy_kraniec->right = NULL;
		ostatni_kraniec->left = NULL;
		ostatni_kraniec->right = pierwszy_kraniec;
		pierwszy_kraniec->numerek = -1;
		ostatni_kraniec->numerek = -2;
	
		okienka.push_back({ostatni_kraniec,pierwszy_kraniec});
	}

}


int numerek(interesant *i)
{
	return i->numerek;
}

interesant *obsluz(int k)
{

	interesant* cur_first;

	if(isReversed(k))
	{
		cur_first = okienka[k].first->right;
		cur_first->right->left = okienka[k].first;
		okienka[k].first->right = cur_first->right;
	}
	else
	{
		cur_first = okienka[k].first->left;
		cur_first->left->right = okienka[k].first;
		okienka[k].first->left = cur_first->left;
	}
	cur_first->right = NULL;
	cur_first->left = NULL;
	return cur_first;
}

void zmiana_okienka(interesant *i, int k)
{
	i->right->left = i->left;
	i->left->right = i->right;
	i->left = NULL;
	i->right = NULL;

	if(isReversed(k))
	{
		i->left = okienka[k].last;
		okienka[k].last->right = i;
		okienka[k].last = i;
	}
	else 
	{
		i->right = okienka[k].last;
		okienka[k].last->left = i;
		okienka[k].last = i;
	}
}

void zamkniecie_okienka(int k1, int k2)
{
	if(isReversed(k1))
	{
		if(isReversed(k2))
		{
			
		}
		else 
		{

		}
	}
	else 
	{
		if(isReversed(k2))
		{
			okienka[k1].first->left->right = okienka[k2].last->right;
		}
		else 
		{
			okienka[k1].first->left->right = okienka[k2].last->right;
			okienka[k2].last->right->left = okienka[k1].first->left;
			okienka[k2].last->right = okienka[k1].last->right;
			okienka[k1].last->right = okienka[k1].first;
			okienka[k1].first->left = okienka[k1].last;
		}

	}
}

std::vector<interesant *> fast_track(interesant *i1, interesant *i2)
{

}

void naczelnik(int k)
{

}

std::vector<interesant *> zamkniecie_urzedu()
{

}

