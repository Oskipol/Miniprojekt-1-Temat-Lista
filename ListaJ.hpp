#include "Struktura.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

class ListaJ:public Struktura{
    struct Wezel{int val; Wezel* nast; Wezel(int v):val(v),nast(nullptr){}}; //struktura reprezentująca pojedynczy węzeł listy jednokierunkowej, zawiera wartość oraz wskaźnik na następny węzeł
    Wezel* head; //wskaźnik na pierwszy węzeł listy
    Wezel* tail; //wskaźnik na ostatni węzeł listy
    int rozmiar; //aktualna liczba elementów w liście

    public:
    ListaJ():head(nullptr),tail(nullptr), rozmiar(0){}
    ~ListaJ(){
        while(head){
        Wezel* t=head->nast;  //usuwa wszystkie węzły listy po kolei, zaczynając od głowy, aż do momentu, gdy lista będzie pusta
        delete head; head=t;
    }
    }
    int size(){return rozmiar;}

    void dodajPrzod(int v);

    void wyswietl();
    void dodajTyl(int v);
    void dodajLos(int val);
    void usunPrzod();
    void usunTyl();
    void usunLos();
    int szukaj(int val);
    void wypelnij(const int* src, int n);
};