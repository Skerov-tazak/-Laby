#include "kol.h"
#include<stdlib.h>
#include<stdio.h>
extern void printAll();




void printv(std::vector<interesant*> vect)
{
	printf("{ ");
	for(int i = 0; i < vect.size(); i++)
		printf("%d ", vect[i]->val);
	printf("}\n");
}

int main() {
	
	otwarcie_urzedu(4);

	interesant *i0 = nowy_interesant(0);
	interesant *i1 = nowy_interesant(1);
	interesant *i2 = nowy_interesant(0);
	interesant *i3 = nowy_interesant(0);
	interesant *i4 = nowy_interesant(2);
	interesant *i5 = nowy_interesant(0);
	interesant *i6 = nowy_interesant(2);
	interesant *i7 = nowy_interesant(1);
	interesant *i8 = nowy_interesant(0);
	interesant *i9 = nowy_interesant(0);
	interesant *i10 = nowy_interesant(0);
	interesant *i11 = nowy_interesant(0);
	interesant *i12 = nowy_interesant(0);
	interesant *i13 = nowy_interesant(0);
	interesant *i14 = nowy_interesant(0);
	interesant *i15 = nowy_interesant(0);
	interesant *i16 = nowy_interesant(0);
	interesant *i17 = nowy_interesant(0);
	interesant *i18 = nowy_interesant(0);
	interesant *i19 = nowy_interesant(0);
	interesant *i20 = nowy_interesant(0);
	interesant *i21 = nowy_interesant(0);
	interesant *i22 = nowy_interesant(0);
	printAll();

	naczelnik(0);
	naczelnik(1);
	printAll();

	zamkniecie_okienka(2, 1);
	printAll();

	obsluz(0);
	obsluz(0);
	obsluz(0);
	naczelnik(0);
//	printAll();

	zmiana_okienka(i3, 1);
	zmiana_okienka(i5, 1);
	zmiana_okienka(i8, 1);
//	printAll();

	naczelnik(1);
	zmiana_okienka(i9, 1);
	zmiana_okienka(i13, 1);
//	printAll();

	zamkniecie_okienka(0, 1);
//	printAll();

	printv(fast_track(i6, i12));
	zmiana_okienka(i15, 3);
	zmiana_okienka(i8, 3);
	zmiana_okienka(i19, 3);
	zmiana_okienka(i18, 3);
	zmiana_okienka(i15, 3);
	zmiana_okienka(i5, 3);
	zmiana_okienka(i3, 3);
	zmiana_okienka(i16, 3);
	zmiana_okienka(i17, 3);
	zmiana_okienka(i14, 3);
//	printAll();
	printv(fast_track(i8, i19));
//	printAll();
	printv(fast_track(i16, i14));
//	printAll();
//	printAll();
	printv(zamkniecie_urzedu());

}
