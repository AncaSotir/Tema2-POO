#include "numar_complex.h"
#include <iomanip>

void numar_complex::check_div () const
{
    if(re==0 && im==0)
        throw "Impartire la 0: ";
}

numar_complex::numar_complex ()
{
    re=im=0;
}

numar_complex::numar_complex (float real,float imaginar)
{
    re=real;
    im=imaginar;
}

numar_complex::numar_complex (const numar_complex& other)
{
    re=other.re;
    im=other.im;
}

numar_complex::~numar_complex()
{
    re=im=0;
}

numar_complex& numar_complex::operator= (const numar_complex& other)
{
    re=other.re;
    im=other.im;
    return *this;
}

numar_complex numar_complex::operator+ (const numar_complex& other) const
{
    numar_complex temp(*this);
    temp.re+=other.re;
    temp.im+=other.im;
    return temp;
}

numar_complex numar_complex::operator* (const numar_complex& other) const
{
    numar_complex temp;
    temp.re=(this->re*other.re)-(this->im*other.im);
    temp.im=(this->re*other.im)+(this->im*other.re);
    return temp;
}

numar_complex numar_complex::operator- (const numar_complex& other) const
{
    numar_complex temp(*this);
    temp.re-=other.re;
    temp.im-=other.im;
    return temp;
}

numar_complex numar_complex::operator/ (const numar_complex& other) const
{
    try
    {
        other.numar_complex::check_div();
    }
    catch(const char* mesaj)
    {
        cerr<<mesaj;
        return other;
    }

    numar_complex temp;

    numar_complex other_conjug;
    other_conjug.re=other.re;
    other_conjug.im=-other.im;

    numar_complex numarator= *this*other_conjug;
    float numitor= (other*other_conjug).re+(other*other_conjug).im;

    temp.re=numarator.re/numitor;
    temp.im=numarator.im/numitor;

    return temp;


}

bool numar_complex::operator== (const numar_complex& other) const
{
    if(re==other.re&&im==other.im)
        return true;
    return false;
}

bool numar_complex::operator!= (const numar_complex& other) const
{
    if(*this==other)
        return false;
    return true;
}

bool numar_complex::operator< (const numar_complex& other) const
{
    if(re<other.re)
        return true;
    if(re==other.re && im<other.im)
        return true;
    return false;
}

istream& operator>> (istream &in, numar_complex& object)
{
    in>>object.re>>object.im;
    return in;
}
ostream& operator<< (ostream &out, const numar_complex& object)
{
    cout << fixed << showpoint;
    cout << setprecision(2);
    out<<"( "<<object.re<<" , "<<object.im<<" )   ";
    return out;
}
