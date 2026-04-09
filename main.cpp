#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Struktura.hpp"
#include "Tablica.hpp"
#include "ListaJ.hpp"
#include "ListaD.hpp"
using namespace std;

int losuj() { return (rand() << 16) ^ rand(); }                                // Zwraca losową 4-bajtową liczbę całkowitą
long long mikros() { return (long long)clock() * 1000000LL / CLOCKS_PER_SEC; } // zwraca czas w mikrosekundach

void benchmark()
{
    const int ROZMIARY[] = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000}; // Rozmiary do przetestowania
    const int ILE = 8, OPS = 1000, POWT = 5;                                        // Liczba rozmiarów w tablicy ROZMIARY, ile razy wykonać każdą operację podczas pomiaru, ile razy powtórzyć cały pomiar aby uśrednić wyniik
    const char *nazwy[] = {"Tablica", "ListaJ", "ListaD"};

    cout << "\nN ";
    for (int s = 0; s < 3; s++)
        cout << nazwy[s] << "_przod\t" << nazwy[s] << "_tyl\t" << nazwy[s] << "_los\t" << nazwy[s] << "_szukaj\t"; // Nazwy kolumn oddzielone tabem
    cout << "\n";

    for (int s = 0; s < ILE; s++)
    {
        int N = ROZMIARY[s];
        Struktura *str[3] = {new Tablica(), new ListaJ(), new ListaD()};
        long long czasy[3][4] = {}; // 3 struktury x 4 operacje

        for (int r = 0; r < POWT; r++)
        {
            int *src = new int[N]; // Pomiar za każdym razem ma inne dane
            for (int i = 0; i < N; i++)
                src[i] = losuj();
            int szukana = src[rand() % N];
            for (int i = 0; i < 3; i++)
                str[i]->wypelnij(src, N);
            delete[] src;

            long long t0, t1;
            for (int i = 0; i < 3; i++)
            {
                t0 = mikros();
                for (int j = 0; j < OPS; j++)
                    str[i]->dodajPrzod(j);
                t1 = mikros();
                czasy[i][0] += t1 - t0;
                t0 = mikros();
                for (int j = 0; j < OPS; j++)
                    str[i]->dodajTyl(j);
                t1 = mikros();
                czasy[i][1] += t1 - t0; // pomiary
                t0 = mikros();
                for (int j = 0; j < OPS; j++)
                    str[i]->dodajLos(j);
                t1 = mikros();
                czasy[i][2] += t1 - t0;
                t0 = mikros();
                for (int j = 0; j < OPS; j++)
                    str[i]->szukaj(szukana);
                t1 = mikros();
                czasy[i][3] += t1 - t0;
            }
        }

        cout << N << "\t";
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                cout << czasy[i][j] / POWT / OPS << "\t"; // wyświetla wyniki
        cout << "\n";

        for (int i = 0; i < 3; i++)
            delete str[i]; // Zwalnianie pamięci
    }
}

void podmenu(Struktura *s, const char *nazwa)
{
    const char *opcje[] = {
        "1. Utworz losowo",
        "2. Wczytaj z pliku",
        "3. Dodaj element",
        "4. Usun element",
        "5. Znajdz element",
        "6. Wyswietl",
        "0. Powrot"};

    int wybor;
    do
    {
        cout << "\n=== " << nazwa << " ===\n";
        for (const char *o : opcje)
            cout << o << "\n";
        cout << "Wybor: ";
        cin >> wybor;

        if (wybor == 1)
        {
            int n;
            cout << "Ile elementow? ";
            cin >> n;
            int *src = new int[n];
            for (int i = 0; i < n; i++)
                src[i] = losuj();
            s->wypelnij(src, n); // wypelnij usuwa stare dane przed wczytaniem nowych
            delete[] src;
            cout << "Utworzono " << n << " elementow.\n";
        }

        else if (wybor == 2)
        {
            char nazwa_pliku[100];
            cout << "Nazwa pliku: ";
            cin >> nazwa_pliku;
            ifstream plik(nazwa_pliku);
            if (!plik)
            {
                cout << "Nie mozna otworzyc pliku.\n";
                continue;
            }

            // Zlicz elementy, wróć na początek, wczytaj
            int n = 0, x;
            while (plik >> x)
                n++;
            plik.clear();
            plik.seekg(0);
            int *src = new int[n];
            for (int i = 0; i < n; i++)
                plik >> src[i];
            plik.close();

            s->wypelnij(src, n); // wypelnij usuwa stare dane przed wczytaniem nowych
            delete[] src;
            cout << "Wczytano " << n << " elementow.\n";
        }

        else if (wybor == 3)
        {
            cout << "1-Przod  2-Tyl  3-Losowo: ";
            int gdzie;
            cin >> gdzie;
            cout << "Wartosc: ";
            int val;
            cin >> val;
            if (gdzie == 1)
                s->dodajPrzod(val);
            else if (gdzie == 2)
                s->dodajTyl(val);
            else
                s->dodajLos(val);
            cout << "Dodano.\n";
        }

        else if (wybor == 4)
        {
            cout << "1-Przod  2-Tyl  3-Losowo: ";
            int gdzie;
            cin >> gdzie;
            if (gdzie == 1)
                s->usunPrzod();
            else if (gdzie == 2)
                s->usunTyl();
            else
                s->usunLos();
            cout << "Usunieto.\n";
        }

        else if (wybor == 5)
        {
            cout << "Szukana wartosc: ";
            int val;
            cin >> val;
            int idx = s->szukaj(val);
            if (idx >= 0)
                cout << "Znaleziono na indeksie " << idx << ".\n";
            else
                cout << "Nie znaleziono.\n";
        }

        else if (wybor == 6)
        {
            s->wyswietl();
        }

    } while (wybor != 0);
}

int main()
{
    srand(time(NULL));

    const char *opcje[] = {
        "1. Tablica dynamiczna",
        "2. Lista jednokierunkowa",
        "3. Lista dwukierunkowa",
        "4. Benchmark",
        "0. Wyjdz"};

    int wybor;
    do
    {
        cout << "\n=== MENU GLOWNE ===\n";
        for (const char *o : opcje)
            cout << o << "\n";
        cout << "Wybor: ";
        cin >> wybor;

        if (wybor == 1)
        {
            Tablica t;
            podmenu(&t, "Tablica dynamiczna");
        }
        else if (wybor == 2)
        {
            ListaJ j;
            podmenu(&j, "Lista jednokierunkowa");
        }
        else if (wybor == 3)
        {
            ListaD d;
            podmenu(&d, "Lista dwukierunkowa");
        }
        else if (wybor == 4)
        {
            benchmark();
        }

    } while (wybor != 0);

    return 0;
}