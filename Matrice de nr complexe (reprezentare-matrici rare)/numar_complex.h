#ifndef NUMAR_COMPLEX_H_INCLUDED
#define NUMAR_COMPLEX_H_INCLUDED

#include <iostream>
using namespace std;

class matrice;

class numar_complex
{
    friend class matrice;
    float re,im;
    void check_div () const;
public:
    numar_complex ();
    numar_complex (float real,float imaginar);
    numar_complex (const numar_complex& other);
    ~numar_complex ();
    numar_complex& operator= (const numar_complex& other);
    numar_complex operator+ (const numar_complex& other) const;
    numar_complex operator* (const numar_complex& other) const;
    numar_complex operator- (const numar_complex& other) const;
    numar_complex operator/ (const numar_complex& other) const;
    bool operator== (const numar_complex& other) const;
    bool operator!= (const numar_complex& other) const;
    bool operator< (const numar_complex& other) const;
    friend std::istream& operator>> (std::istream &in, numar_complex& object);
    friend std::ostream& operator<< (std::ostream &out, const numar_complex& object);
};

#endif // NUMAR_COMPLEX_H_INCLUDED
