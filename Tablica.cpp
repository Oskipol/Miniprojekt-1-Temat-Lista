#include "Tablica.hpp"

void Tablica::dodaj(int id, int val){
    if(rozmiar==pojemnosc) resize(pojemnosc*2);
    for(int i=rozmiar; i>id; i--){dane[i]=dane[i-1];} //metoda przesuwa elementy w prawo od id, aby zrobić miejsce dla nowego elementu
    dane[id]=val;
    rozmiar++;
}   
void Tablica::usun(int id){
    for(int i=id; id<rozmiar-1;i++){
        dane[i]=dane[i+1];            //metoda przesuwa elementy w lewo od id, aby usunąć element o indeksie id
    }
    rozmiar--;
    if(rozmiar>0&&rozmiar<=pojemnosc/4) resize(pojemnosc/2);
}
int Tablica::szukaj(int val){
    for(int i=0;i<rozmiar;i++){
        if(dane[i]==val){return i;}
    }
    return -1;
}
void Tablica::wypelnij(const int* src, int n){
    delete[] dane;
    rozmiar=0;
    pojemnosc=1;                                //metoda usuwa istniejące dane, resetuje rozmiar i pojemność, a następnie dodaje elementy z tablicy src do struktury
    dane=new int[1];
    for(int i=0;i<n;i++){
        dodajTyl(src[i]);
    }
}
void Tablica::wyswietl() {
    if (!rozmiar) { cout << "(pusta)\n"; return; }
    int lim = rozmiar < 20 ? rozmiar : 20;  //metoda wyświetla zawartość tablicy. Jeśli tablica jest pusta, wyświetla "(pusta)". W przeciwnym razie, wyświetla pierwsze 20 elementów tablicy (lub wszystkie, jeśli jest ich mniej niż 20), a następnie informację o rozmiarze tablicy.
    for (int i = 0; i < lim; i++) cout << dane[i] << " ";
    if (rozmiar > 20) cout << "...";
    cout << " [rozmiar=" << rozmiar << "]\n";
}