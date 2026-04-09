#include "Struktura.hpp"
#include <stdlib.h> 
#include <iostream>
using namespace std;
class Tablica:public Struktura{
    int* dane; //wskaźnik na tablicę dynamiczną
    int rozmiar; //aktualna liczba elementów w tablicy
    int pojemnosc; //aktualna pojemność tablicy, czyli ile elementów może pomieścić bez konieczności rozszerzania
    void resize(int n){
        int* pom=new int[n];
        for(int i=0;i<rozmiar;i++){ //Deklaracja funkcji pomocniczej do zmiany rozmiaru tablicy. Tworzy nową tablicę o pojemności n, kopiuje do niej istniejące dane, a następnie usuwa starą tablicę i aktualizuje wskaźnik oraz pojemność.
            pom[i]=dane[i];
        }
        delete[] dane;
        dane=pom;
        pojemnosc=n;
    }
    public:
    Tablica(): dane(new int[1]), rozmiar(0), pojemnosc(1){}
    ~Tablica(){delete[] dane;}
    int size(){return rozmiar;}

    void dodajPrzod(int v){dodaj(0, v);}
    void dodajTyl(int v){dodaj(rozmiar, v);}
    void dodajLos(int v){dodaj(rozmiar?rand()%(rozmiar+1):0,v);}  //proste metody wykorzystujace dodaj i usun
    void usunPrzod(){usun(0);}
    void usunTyl(){usun(rozmiar-1);}
    void usunLos(){if(rozmiar) usun(rand()%rozmiar);}

    void dodaj(int id, int val);
    void usun(int id);
    void wyswietl();
    int szukaj(int val);
    void wypelnij(const int* src, int n);
};