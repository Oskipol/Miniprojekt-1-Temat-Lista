#include "ListaJ.hpp"

void ListaJ::dodajPrzod(int v){
    Wezel* w=new Wezel(v);
    w->nast=head;      //metoda tworzy nowy węzeł z wartością v, ustawia jego wskaźnik nast na aktualną głowę listy, a następnie aktualizuje głowę na nowy węzeł. Jeśli lista była pusta, aktualizuje również ogon na nowy węzeł. Na końcu zwiększa rozmiar listy o 1.
    head=w;
    if(!tail) tail=head;
    rozmiar++;
}

void ListaJ::dodajTyl(int v){
    Wezel* w =new Wezel(v);
    if(!tail) {head=tail=w;}
    else{tail->nast=w; tail=w;}  //metoda tworzy nowy węzeł z wartością v, a następnie sprawdza, czy lista jest pusta. Jeśli jest pusta, ustawia zarówno głowę, jak i ogon na nowy węzeł. W przeciwnym razie, ustawia wskaźnik nast aktualnego ogona na nowy węzeł, a następnie aktualizuje ogon na nowy węzeł. Na końcu zwiększa rozmiar listy o 1.
    rozmiar++;
}

void ListaJ::dodajLos(int val){
    if(!head) {dodajPrzod(val); return;}
    int id=rand()%(rozmiar+1);
    if(id==0){dodajPrzod(val); return;}
    Wezel* p=head;
    for(int i=0; i<id-1;i++){p=p->nast;} //metoda losowo wybiera indeks od 0 do rozmiar (włącznie), a następnie dodaje nowy węzeł z wartością val na wybranym indeksie. Jeśli indeks to 0, dodaje na początek listy. W przeciwnym razie, przechodzi do węzła poprzedzającego wybrany indeks i wstawia nowy węzeł za nim. Na końcu zwiększa rozmiar listy o 1.
    Wezel* w=new Wezel(val);
    w->nast=p->nast;
    p->nast=w;
    if(!w->nast) tail=w;
    rozmiar++;
}

void ListaJ::usunPrzod() {
    if (!head) return;
    Wezel* t = head; head = head->nast;
    if (!head) tail = nullptr;  //metoda sprawdza, czy lista jest pusta. Jeśli nie jest, przechowuje wskaźnik na aktualną głowę, aktualizuje głowę na następny węzeł, a następnie usuwa stary węzeł. Jeśli po usunięciu lista jest pusta, ustawia ogon na nullptr. Na końcu zmniejsza rozmiar listy o 1.
    delete t; rozmiar--;
}

void ListaJ::usunTyl() {
    if (!head) return;
    if (head == tail) { delete head; head = tail = nullptr; rozmiar--; return; }
    Wezel* p = head;
    while (p->nast != tail) p = p->nast;  //metoda sprawdza, czy lista jest pusta. Jeśli nie jest, sprawdza, czy lista ma tylko jeden element. Jeśli tak, usuwa ten element i ustawia zarówno głowę, jak i ogon na nullptr. W przeciwnym razie, przechodzi do przedostatniego węzła (tego, którego nast jest ogonem), usuwa ogon, aktualizuje ogon na przedostatni węzeł i ustawia jego wskaźnik nast na nullptr. Na końcu zmniejsza rozmiar listy o 1.
    delete tail; tail = p; tail->nast = nullptr; rozmiar--;
}

void ListaJ::usunLos() {
    if (!head) return;
    int idx = rand() % rozmiar;
    if (idx == 0) { usunPrzod(); return; }
    Wezel* p = head;
    for (int i = 0; i < idx - 1; i++) p = p->nast;  //metoda losowo wybiera indeks od 0 do rozmiar-1, a następnie usuwa węzeł znajdujący się na tym indeksie. Jeśli indeks to 0, usuwa z początku listy. W przeciwnym razie, przechodzi do węzła poprzedzającego wybrany indeks, usuwa węzeł na wybranym indeksie, aktualizuje wskaźnik nast poprzedniego węzła, aby pominąć usunięty węzeł. Jeśli usunięty węzeł był ogonem, aktualizuje ogon na poprzedni węzeł. Na końcu zmniejsza rozmiar listy o 1.
    Wezel* t = p->nast; p->nast = t->nast;
    if (!p->nast) tail = p;
    delete t; rozmiar--;
}

int ListaJ::szukaj(int val) {
    Wezel* c = head; int i = 0;
    while (c) { if (c->val == val) return i; c = c->nast; i++; } //metoda przechodzi przez listę, porównując wartość każdego węzła z podaną wartością val. Jeśli znajdzie węzeł o wartości równej val, zwraca jego indeks. Jeśli przejdzie przez całą listę i nie znajdzie takiego węzła, zwraca -1.
    return -1;
}

void ListaJ::wypelnij(const int* src, int n) {
    while (head) { Wezel* t = head->nast; delete head; head = t; } //metoda usuwa wszystkie istniejące węzły w liście, a następnie dodaje nowe elementy z tablicy src. Na końcu ustawia głowę i ogon na nullptr oraz rozmiar na 0, a następnie dodaje elementy z tablicy src do listy za pomocą metody dodajTyl.
    tail = nullptr; rozmiar = 0;
    for (int i = 0; i < n; i++) dodajTyl(src[i]);
}

void ListaJ::wyswietl() {
    if (!head) { cout << "(pusta)\n"; return; }
    Wezel* c = head;
    int k = 0;
    while (c && k < 20) {
        cout << c->val;
        if (c->nast && k < 19) cout << " -> "; 
        c = c->nast;
        k++;
    }
    if (c) cout << " ...";
    cout << " [rozmiar=" << rozmiar << "]\n";
}
