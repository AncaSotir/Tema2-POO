#ifndef MATRICE_H_INCLUDED
#define MATRICE_H_INCLUDED

#include "numar_complex.cpp"
#include "lista.cpp"

#include <iostream>
using namespace std;

class matrice
{
protected:
    lista < lista<numar_complex> > mat;
public:
    virtual ~matrice(){}
    virtual istream& citire(istream& in)=0;
    virtual ostream& afisare(ostream& out) const =0;
    friend std::istream& operator>> (std::istream& in, matrice& object);
    friend std::ostream& operator<< (std::ostream& out, const matrice& object);
};

class matrice_oarecare: public matrice
{
    int nr_coloane;
    int nr_linii;
public:
    matrice_oarecare();
    matrice_oarecare(int linii,int coloane);
    matrice_oarecare(const matrice_oarecare& other);
    ~matrice_oarecare();
    matrice_oarecare& operator= (const matrice_oarecare& other);
    matrice_oarecare operator+ (const matrice_oarecare& other) const;
    matrice_oarecare operator* (const matrice_oarecare& other) const;
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    bool operator== (const matrice_oarecare& other) const;
    bool operator!= (const matrice_oarecare& other) const;
    bool operator< (const matrice_oarecare& other) const;
    lista <numar_complex>& operator[] (int n) const;
};

class matrice_patratica: public matrice
{
    int dimensiune;
    matrice_patratica minor (int linie,int coloana) const;
    matrice_patratica transpusa () const;
public:
    matrice_patratica();
    matrice_patratica(int dimensiune);
    matrice_patratica(const matrice_patratica& other);
    ~matrice_patratica();
    matrice_patratica& operator= (const matrice_patratica& other);
    matrice_patratica operator+ (const matrice_patratica& other) const;
    matrice_patratica operator* (const matrice_patratica& other) const;
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    bool check_diagonal () const;
    numar_complex determinant () const;
    matrice_patratica inversa () const;
    bool operator== (const matrice_patratica& other) const;
    bool operator!= (const matrice_patratica& other) const;
    bool operator< (const matrice_patratica& other) const;
    lista <numar_complex>& operator[] (int n) const;
};

#endif // MATRICE_H_INCLUDEDpush_back
