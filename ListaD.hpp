#include "Struktura.hpp"
#include <stdlib.h>
#include <iostream>
using namespace std;

class ListaD:public Struktura{
          
    struct Wezel{int val; Wezel* nast; Wezel* pop; Wezel(int v):val(v),nast(nullptr),pop(nullptr){}}; //struktura reprezentująca pojedynczy węzeł listy dwukierunkowej, zawiera wartość oraz wskaźniki na następny i poprzedni węzeł
    Wezel* head; //wskaźnik na pierwszy węzeł listy
    Wezel* tail; //wskaźnik na ostatni węzeł listy
    int rozmiar; //aktualna liczba elementów w liście

    public:
    ListaD():head(nullptr),tail(nullptr), rozmiar(0){}
    ~ListaD(){
        while(head){
            Wezel* t=head->nast;
            delete head;  //usuwa wszystkie węzły listy po kolei, zaczynając od głowy, aż do momentu, gdy lista będzie pusta
            head=t;
    }
}
int size(){return rozmiar;}


    void wyswietl();
    void dodajPrzod(int v);
    void dodajTyl(int v);
    void dodajLos(int val);
    void usunPrzod();
    void usunTyl();
    void usunLos();
    int szukaj(int val);
    void wypelnij(const int* src, int n);
};