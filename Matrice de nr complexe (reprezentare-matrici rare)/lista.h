#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <iostream>
using namespace std;

template <class T>

class lista;
class matrice_oarecare;
class matrice_patratica;

template <class T>

class nod
{
    friend class lista<T>;
    friend class matrice_oarecare;
    friend class matrice_patratica;
    T info;
    int coloana;
    nod* next;
    nod* prev;
public:
    nod();
    nod(T value);
    bool operator== (const nod& other) const;
    bool operator!= (const nod& other) const;
    bool operator< (const nod& other) const;
    template <class U>
    friend std::istream& operator>> (std::istream &in, nod<U>& object);
    template <class U>
    friend std::ostream& operator<< (std::ostream &out, const nod<U>& object);
};

template <class T>

class lista
{
    nod<T>* first;
    nod<T>* last;
    int length;
public:
    lista();
    lista(const lista& other);
    ~lista();
    nod<T>* inceput() const;
    nod<T>* sfarsit() const;
    int lungime() const;
    void push(T value,int coloana);
    void pop();
    lista& operator= (const lista& other);
    nod<T>& operator[] (int n) const;
};

#endif // LISTA_H_INCLUDED
