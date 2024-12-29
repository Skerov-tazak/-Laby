
#include "kol.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>


struct kolejka {
    interesant *head, *tail;
    int kierunek = 0;
};

int obecnyNumer = 0;
std::pmr::vector<kolejka> kolejki;

interesant* next(interesant *prev, interesant *current) {
	if(current->i1 != prev) return current->i1;
	return current->i2;
}

void printAll()
{
	for(unsigned int i = 0; i < kolejki.size(); i++)
	{
		if(kolejki[i].kierunek == 0)
		{

			std::cout << "|" << i << ": ";
			fflush(stdout);
			interesant* prev = kolejki[i].head;
			interesant* current;

			if(kolejki[i].head->i2 == NULL)
				current = kolejki[i].head->i1;
			else 
				current = kolejki[i].head->i2;

			while(current != kolejki[i].tail)
			{
				std::cout << current->val << " ";
				interesant* temp = current;
				current = next(prev,current);
				prev = temp;
			}
		}
		else 
		{
			std::cout << "|" << i << ": ";
			fflush(stdout);
			interesant* prev = kolejki[i].tail;
			interesant* current;

			if(kolejki[i].tail->i2 == NULL)
				current = kolejki[i].tail->i1;
			else 
				current = kolejki[i].tail->i2;

			while(current != kolejki[i].head)
			{
				std::cout << current->val << " ";
				interesant* temp = current;
				current = next(prev,current);
				prev = temp;
			}
		}
	}
	std::fflush(stdout);
	std::cout << std::endl;
}


interesant* popBack(int k) {
    kolejka* kol = &kolejki[k];
    if(kol->kierunek) {
        if (kol->tail->i1 == kol->head) {
            return nullptr;
        }
        interesant* i = kol->tail->i1;
        if(i->i2 == kol->tail) {
            if(i->i1->i1 == i) i->i1->i1 = kol->tail; else i->i1->i2 = kol->tail;
            kol->tail->i1 = i->i1;
        } else {
            if(i->i2->i1 == i) i->i2->i1 = kol->tail; else i->i2->i2 = kol->tail;
            kol->tail->i1 = i->i2;
        }
        return i;
    }
    if (kol->head->i2 == kol->tail) {
        return nullptr;
    }
    interesant* i = kol->head->i2;
    if(i->i2 == kol->head) {
        if(i->i1->i1 == i) i->i1->i1 = kol->head; else i->i1->i2 = kol->head;
        kol->head->i2 = i->i1;
    } else {
        if(i->i2->i1 == i) i->i2->i1 = kol->head; else i->i2->i2 = kol->head;
        kol->head->i2 = i->i2;
    }
    return i;
}

void pushBack(int k, interesant *i) {
    kolejka *kol = &kolejki[k];
    if(kol->kierunek) {
        i->i2 = kol->head->i2;
        i->i1 = kol->head;
        if(kol->head->i2->i1 == kol->head) kol->head->i2->i1 = i; else kol->head->i2->i2 = i;
        kol->head->i2 = i;
    } else {
        i->i1 = kol->tail->i1;
        i->i2 = kol->tail;
        if(kol->tail->i1->i2 == kol->tail) kol->tail->i1->i2 = i; else kol->tail->i1->i1 = i;
        kol->tail->i1 = i;
    }
}

void otwarcie_urzedu(int m) {
    kolejki.clear();
    kolejki.resize(m);
    for(int i = 0; i < m; i++) {
        kolejka k = {
            .head = (interesant*)malloc(sizeof(interesant)),
            .tail = (interesant*)malloc(sizeof(interesant))
        };
        k.head->val = -1;
        k.tail->val = -1;
        k.head->i1 = nullptr;
        k.head->i2 = k.tail;
        k.tail->i1 = k.head;
        k.tail->i2 = nullptr;
        kolejki[i] = k;
    }
}

interesant *nowy_interesant(int k) {
    interesant *i = (interesant*)malloc(sizeof(interesant));
    i->i1 = i->i2 = nullptr;
    i->val = obecnyNumer++;
    pushBack(k, i);
    return i;
}

int numerek(interesant *i) {
    return i->val;
}

interesant *obsluz(int k) {
        return popBack(k);
}

void zmiana_okienka(interesant *i, int k) {
    if (i->i1) i->i1->i2 = i->i2;
    if (i->i2) i->i2->i1 = i->i1;
    pushBack(k, i);
}

void zamkniecie_okienka(int k1, int k2) {
    kolejka *q1 = &kolejki[k1];
    kolejka *q2 = &kolejki[k2];
    interesant **q1Tail;
    interesant **q1Head;
    interesant **q2Tail;
    interesant **q2Head;
    if(q1->head->i2->i1 == q1 -> head) q1Head = &q1->head->i2->i1; else q1Head = &q1->head->i2->i2;
    if(q2->head->i2->i1 == q2 -> head) q2Head = &q2->head->i2->i1; else q2Head = &q2->head->i2->i2;
    if(q1->tail->i1->i1 == q1 -> tail) q1Tail = &q1->tail->i1->i1; else q1Tail = &q1->tail->i1->i2;
    if(q2->tail->i1->i1 == q2 -> tail) q2Tail = &q2->tail->i1->i1; else q2Tail = &q2->tail->i1->i2;
    // If q1 is empty, there's nothing to move
    if(q1->kierunek) {
        if(q2->kierunek) {
            //link q1 tail el with q2 head el
            *q1Tail = q2->head->i2;
            *q2Head = q1->tail->i1;
            //link q1 head el with q2 head
            *q1Head = q2->head;
            q2->head->i2 = q1->head->i2;
        } else {
            //link q1 tail el with q2 tail el
            *q1Tail = q2->tail->i1;
            *q2Tail = q1->tail->i1;
            //link q1 head el with q2 tail
            *q1Head = q2->tail;
            q2->tail->i1 = q1->head->i2;
        }
    } else {
        if(q2->kierunek) {
            //link q1 head el with q2 head el
            *q1Head = q2->head->i2;
            *q2Head = q1->head->i2;
            //link q1 tail el with q2 head
            *q1Tail = q2->head;
            q2->head->i2 = q1->tail->i1;
        } else {
            //link q1 head el with q2 tail el
            *q1Head = q2->tail->i1;
            *q2Tail = q1->head->i2;
            //link q1 tail el with q2 tail
            *q1Tail = q2->tail;
            q2->tail->i1 = q1->tail->i1;
        }
    }
}

std::vector<interesant*> fast_track(interesant *i1, interesant *i2) {
    std::vector<interesant*> bQueue;
    std::vector<interesant*> fQueue;
    fQueue.push_back(i1);
    bQueue.push_back(i1);
    // Simultaneous forward and backward traversal
    interesant *prevForward = i1;
    interesant *prevBackward = i1;
    interesant *forward = i1->i1;
    interesant *backward = i1->i2;
    while (true) {
        // Check forward direction
        if (forward->val != -1) {
            fQueue.push_back(forward);
            if (forward == i2) {
                interesant *next1 = next(prevForward, forward);
                if(next1->i1 == forward)next1->i1 = i1->i2; else next1->i2 = i1->i2;
                if(i1->i2->i1 == i1) i1->i2->i1 = next1; else i1->i2->i2 = next1;
                return fQueue;
            }
            interesant *tmp = forward;
            forward = next(prevForward,forward);
            prevForward = tmp;
        }
        // Check backward direction
        if (backward->val != -1) {
            bQueue.push_back(backward);
            if (backward == i2) {
                interesant *next1 = next(prevBackward, backward);
                if(next1->i1 == backward)next1->i1 = i1->i1; else next1->i2 = i1->i1;
                if(i1->i1->i1 == i1) i1->i1->i1 = next1; else i1->i1->i2 = next1;
                return bQueue;
            }
            interesant *tmp = backward;
            backward = next(prevBackward, backward);
            prevBackward = tmp;
        }
    }
    return {};
}

void naczelnik(int k) {
    kolejki[k].kierunek = 1 - kolejki[k].kierunek;
}

std::vector<interesant*> zamkniecie_urzedu() {
    std::vector<interesant*> result;
    for (int i = 0; i < kolejki.size(); i++) {
        kolejka k = kolejki[i];
        while(k.head->i2 != k.tail) {
            result.push_back(popBack(i));
        }
        free(k.head);
        free(k.tail);
    }

    kolejki.clear();
    return result;
}



