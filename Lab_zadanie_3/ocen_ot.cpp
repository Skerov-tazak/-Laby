// Autor: Olaf Targowski
// Licencja: TODO (jak szerzej roześlę, to public domain)
// Co to: testerka do "Zbiorów arytmetycznych" - zadania I na WPI* na I sem. (2024Z) infy na UW
// Jak odpalić:
// 0. Zaimplementować idk::dealloc i idk::kopiuj (zobacz niżej).
// 1. Umieścić zbior_ary.c w tym samym folderze, co ten plik.
// 2. $ g++ ocen_ot.cpp -o ocen_ot -O3 -fsanitize=undefined -std=c++20 -ggdb3
// 3. $ ./ocen_ot

#include "zbior_ary.c" // Hihihiha

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <set>
#include <random>
using namespace std;

const vector <int> susv={INT_MIN, INT_MAX, 0, int(137114121), int(-5143589), 15, 69, -21};
vector <int> vd; // vd*susv=(3+5)*8=64

static int __mod_ocen(int a){
    a=a%q;
    return a<0 ? a+q : a;
}

struct idk{
    set <int> s;
    zbior_ary z;
    bool czy_zainicjalizowane;
    idk(){
        czy_zainicjalizowane = 0;
    }
    void dealloc(){
        static_assert(0, "ZAIMPLEMENTUJ ocen.cpp:idk::dealloc() !!!!");
        if (czy_zainicjalizowane){
            // NOTE: tu należy dodać logikę zwalniającą pamięć z `z`.
            // Jeżeli `z` jest postaci np. struct{int a,b[100];}, to nie trzeba
            // tu nic robić. Jeżeli zaś jest tam coś pod wskaźnikiem, to trzeba
            // zrobić free(), no chyba że masz za dużo wolnego RAMu :).
        }
    }
    void kopiuj(){
        static_assert(0, "ZAIMPLEMENTUJ ocen.cpp:idk::kopiuj() !!!!");
        if (czy_zainicjalizowane){
            // NOTE: tu należy dodać logikę tworzącą odrębną kopię `z`.
            // Jeżeli `z` jest postaci np. struct{int a,b[100];}, to nie trzeba
            // tu nic robić. Jeżeli zaś jest tam coś pod wskaźnikiem, to trzeba
            // zaalokować nową pamięć i zrobić `memcpy`.
        }
    }
    ~idk(){
        dealloc();
    }
    idk(const idk &i){
        czy_zainicjalizowane = 0;
        *this = i;
    }
    void operator=(const idk &i){
        dealloc();
        s=i.s,z=i.z,czy_zainicjalizowane = i.czy_zainicjalizowane;
        kopiuj();
    }
    void ciag(int a, int _q, int b){
        dealloc();
        czy_zainicjalizowane = 1;
        z=ciag_arytmetyczny(a, _q, b);
        s={};
        while(1){
            s.emplace(a);
            if (a!=b)
                a+=_q;
            else
                break;
        }
    }
    void singiel(int a){
        dealloc();
        czy_zainicjalizowane = 1;
        z=singleton(a);
        s={a};
    }
    void chk(){
        assert(czy_zainicjalizowane);
        assert(moc(z)==s.size());
        unsigned sary=0;
        set <int> s2=s;
        while (!s2.empty()){
            ++sary;
            for (long long a=*s2.begin(); a<=INT_MAX&&s2.contains(int(a)); a+=q)
                s2.erase(int(a));
        }
        assert(sary==ary(z));
        vector <int> v;
        for (const int i : susv)
            v.emplace_back(i);
        for (const int i : s)
            v.emplace_back(i);
        for (const int i : v)
            for (const int d : vd)
                if ((long long)(i)+d>=INT_MIN&&(long long)(i)+d<=INT_MAX)
                    assert(s.contains(i+d)==nalezy(z, i+d));
    }
    idk operator+(const idk &i) const{
        idk r;
        r.z=suma(z, i.z);
        r.s=s;
        for (const int a : i.s)
            r.s.emplace(a);
        r.czy_zainicjalizowane = 1;
        return r;
    }
    idk operator-(const idk &i) const{
        idk r;
        r.z=roznica(z, i.z);
        r.s=s;
        for (const int a : i.s)
            r.s.erase(a);
        r.czy_zainicjalizowane = 1;
        return r;
    }
    idk operator*(const idk &i) const{
        idk r;
        r.z=iloczyn(z, i.z);
        for (const int a : s)
            if (i.s.contains(a))
                r.s.emplace(a);
        r.czy_zainicjalizowane = 1;
        return r;
    }
};

int main() {
    // NOTE: na każdym normalnym linuksie to winno działać.
    // Za windowsa nie ręczę.
    random_device rd;
    mt19937 _r(rd());
    auto r=[&](int p, int k){
        return uniform_int_distribution<int>(p, k)(_r);
    };
    int cnt=0;
    //while (1){
    while (cnt<100){
        // NOTE: Tu i ciut niżej można zmieniać parametry.
        const int qcap=40,cap=200,rounds=cap*cap*10;
        const int ile=2,ileq=2;
        const vector <int> midy={0, 98523, INT_MIN+cap, INT_MAX-cap};
        const int mid=midy[r(0, int(midy.size())-1)];

        // Testujmy też ogromne q.
        const int _q=cnt%5 ? r(1, qcap) : r(INT_MAX-qcap, INT_MAX);
        vd.clear();
        for (int a=-ile; a<=ile; ++a)
            vd.emplace_back(a);
        for (int a=-ileq; a<=ileq; ++a){
            const long long x=(long long)a*q+mid;
            if (a&&x<=INT_MAX&&x>=INT_MIN)
                vd.emplace_back(int(x));
        }
        q=0;
        {
            idk init;
            init.ciag(0, _q, 0);
        }
        assert(_q==q);
        vector <idk> reg;
        for (const int i : susv)
            for (const int d : vd)
                if ((long long)(i)+d>=INT_MIN&&(long long)(i)+d<=INT_MAX){
                    reg.emplace_back();
                    if (_r()&1&&(reg.size()>1))
                        reg.back().singiel(i+d);
                    else
                        reg.back().ciag(i+d, q, i+d);
                }
        const int regnum=int(reg.size())+3;
        while (ssize(reg)<regnum){
            reg.emplace_back();
            reg.back().singiel(0);
        }
        reg.resize(regnum);
        for (int _=0; _<rounds; ++_){
            // czy na dwóch czy na nowym i jednym
            idk *p=&(reg[r(0, regnum-1)]);
            idk *k=&(reg[r(0, regnum-1)]);
            idk *l=&(reg[r(0, regnum-1)]);
            bool czy=_r()&1;
            if (czy){
                k=new idk;
                int a=r(mid-cap, mid+cap),b=r(a, mid+cap);
                b-=__mod_ocen(__mod_ocen(b)-__mod_ocen(a));
                assert(__mod_ocen(a)==__mod_ocen(b)&&a<=b);
                k->ciag(a, q, b);
            }
            idk now;
            int los=r(0, 2);
            switch (los){
                case 0:
                    now=*p+*k;
                    break;
                case 1:
                    now=*p-*k;
                    break;
                case 2:
                    now=(*p)*(*k);
                    break;
            }
            swap(*l, now); // idk
            p->chk(),k->chk(),l->chk();
            if (czy)
                delete k;
        }
        ++cnt;
        if (!(cnt%10))
            fprintf(stderr, "Completed %d passes\n", cnt);
    }
}
