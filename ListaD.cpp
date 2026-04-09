#include "ListaD.hpp"

    void ListaD::dodajPrzod(int v) {
        Wezel* w = new Wezel(v);
        if (!head) { head = tail = w; }
        else { w->nast = head; head->pop = w; head = w; } //metoda tworzy nowy węzeł z wartością v, a następnie sprawdza, czy lista jest pusta. Jeśli jest pusta, ustawia zarówno głowę, jak i ogon na nowy węzeł. W przeciwnym razie, ustawia wskaźnik nast nowego węzła na aktualną głowę, aktualizuje wskaźnik pop aktualnej głowy na nowy węzeł, a następnie aktualizuje głowę na nowy węzeł. Na końcu zwiększa rozmiar listy o 1.
        rozmiar++;
    }
    void ListaD::dodajTyl(int v) {
        Wezel* w = new Wezel(v);
        if (!tail) { head = tail = w; }
        else { w->pop = tail; tail->nast = w; tail = w; } //metoda tworzy nowy węzeł z wartością v, a następnie sprawdza, czy lista jest pusta. Jeśli jest pusta, ustawia zarówno głowę, jak i ogon na nowy węzeł. W przeciwnym razie, ustawia wskaźnik pop nowego węzła na aktualny ogon, aktualizuje wskaźnik nast aktualnego ogona na nowy węzeł, a następnie aktualizuje ogon na nowy węzeł. Na końcu zwiększa rozmiar listy o 1.
        rozmiar++;
    }
    void ListaD::dodajLos(int v) {
        if (!head) { dodajPrzod(v); return; }
        int idx = rand() % (rozmiar + 1);
        if (idx == 0)       { dodajPrzod(v); return; }
        if (idx == rozmiar) { dodajTyl(v);   return; }
        Wezel* c = head;    //metoda losowo wybiera indeks od 0 do rozmiar (włącznie), a następnie dodaje nowy węzeł z wartością v na wybranym indeksie. Jeśli indeks to 0, dodaje na początek listy. Jeśli indeks to rozmiar, dodaje na koniec listy. W przeciwnym razie, przechodzi do węzła znajdującego się na wybranym indeksie, wstawia nowy węzeł przed nim, aktualizując odpowiednio wskaźniki nast i pop sąsiednich węzłów. Na końcu zwiększa rozmiar listy o 1.
        for (int i = 0; i < idx; i++) c = c->nast;
        Wezel* w = new Wezel(v);
        w->nast = c; w->pop = c->pop;
        c->pop->nast = w; c->pop = w;
        rozmiar++;
    }
    void ListaD::usunPrzod() {
        if (!head) return;
        Wezel* t = head; head = head->nast;
        if (head) head->pop = nullptr; else tail = nullptr; //metoda sprawdza, czy lista jest pusta. Jeśli nie jest, przechowuje wskaźnik na aktualną głowę, aktualizuje głowę na następny węzeł, a następnie usuwa stary węzeł. Jeśli po usunięciu lista jest pusta, ustawia ogon na nullptr. Na końcu zmniejsza rozmiar listy o 1.
        delete t; rozmiar--;
    }
    void ListaD::usunTyl() {
        if (!tail) return;
        Wezel* t = tail; tail = tail->pop;
        if (tail) tail->nast = nullptr; else head = nullptr; //metoda sprawdza, czy lista jest pusta. Jeśli nie jest, przechowuje wskaźnik na aktualny ogon, aktualizuje ogon na poprzedni węzeł, a następnie usuwa stary ogon. Jeśli po usunięciu lista jest pusta, ustawia głowę na nullptr. Na końcu zmniejsza rozmiar listy o 1.
        delete t; rozmiar--;
    }
    void ListaD::usunLos() {
        if (!head) return;
        int idx = rand() % rozmiar;
        if (idx == 0)         { usunPrzod(); return; }  //metoda losowo wybiera indeks od 0 do rozmiar-1, a następnie usuwa węzeł znajdujący się na tym indeksie. Jeśli indeks to 0, usuwa z początku listy. Jeśli indeks to rozmiar-1, usuwa z końca listy. W przeciwnym razie, przechodzi do węzła znajdującego się na wybranym indeksie, usuwa go, aktualizując odpowiednio wskaźniki nast i pop sąsiednich węzłów. Na końcu zmniejsza rozmiar listy o 1.
        if (idx == rozmiar-1) { usunTyl();   return; }
        Wezel* c = head;
        for (int i = 0; i < idx; i++) c = c->nast;
        c->pop->nast = c->nast; c->nast->pop = c->pop;
        delete c; rozmiar--;
    }
    int ListaD::szukaj(int val) {
        Wezel* c = head; int i = 0;
        while (c) { if (c->val == val) return i; c = c->nast; i++; }  //metoda przechodzi przez listę, porównując wartość każdego węzła z podaną wartością val. Jeśli znajdzie węzeł o wartości równej val, zwraca jego indeks. Jeśli przejdzie przez całą listę i nie znajdzie takiego węzła, zwraca -1.
        return -1;
    }
    void ListaD::wypelnij(const int* src, int n) {
        while (head) { Wezel* t = head->nast; delete head; head = t; } //metoda usuwa istniejące dane, resetuje rozmiar i pojemność, a następnie dodaje elementy z tablicy src do struktury
        tail = nullptr; rozmiar = 0;
        for (int i = 0; i < n; i++) dodajTyl(src[i]);
    }

    void ListaD::wyswietl() {
    if (!head) { cout << "(pusta)\n"; return; }
    Wezel* c = head;
    int k = 0;
    while (c && k < 20) {
        cout << c->val;
        if (c->nast && k < 19) cout << " <-> ";  
        c = c->nast;
        k++;
    }
    if (c) cout << " ...";
    cout << " [rozmiar=" << rozmiar << "]\n";
}