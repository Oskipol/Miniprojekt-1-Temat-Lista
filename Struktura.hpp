#ifndef STRUKTURA_HPP
#define STRUKTURA_HPP

class Struktura {
public:
    virtual void dodajPrzod(int v) = 0;
    virtual void dodajTyl(int v) = 0;
    virtual void dodajLos(int v) = 0;
    virtual void usunPrzod() = 0;
    virtual void usunTyl() = 0;
    virtual void usunLos() = 0;
    virtual int szukaj(int v) = 0;
    virtual void wyswietl() = 0;
    virtual void wypelnij(const int* src, int n) = 0;
    virtual int size() = 0;
    virtual ~Struktura() {}
};

// Klasa bazowa, z ktorej dziedzicza pozostale struktury danych.
#endif