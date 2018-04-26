#include "lista.h"

template <class T>
nod<T>::nod() {}

template <class T>
nod<T>::nod(T value)
{
    info=value;
    next=prev=NULL;
}

template <class T>
bool nod<T>::operator== (const nod& other) const
{
    if(this->info==other.info)
        return true;
    return false;
}

template <class T>
bool nod<T>::operator!= (const nod& other) const
{
    if(this->info==other.info)
        return false;
    return true;
}

template <class T>
bool nod<T>::operator< (const nod& other) const
{
    if(this->info<other.info)
        return true;
    return false;
}

template <class T>
istream& operator>> (istream &in, nod<T>& object)
{
    in>>object.info;
    return in;
}

template <class T>
ostream& operator<< (ostream &out, const nod<T>& object)
{
    out<<object.info;
    return out;
}

///===================================================================================class lista====================================================

template <class T>
lista<T>::lista()
{
    first=NULL;
    last=NULL;
    length=0;
}

template <class T>
lista<T>::lista(const lista& other)
{
    nod<T>* p;
    first=last=NULL;
    p=other.first;
    while(p!=NULL)
    {
        push(p->info,p->coloana);
        p=p->next;
    }
    length=other.length;
}

template <class T>
lista<T>::~lista()
{
    while(first!=NULL)
        pop();
}

template <class T>
lista<T>& lista<T>::operator= (const lista &other)
{
    while(first!=NULL)
        pop();

    nod<T>* p;
    first=last=NULL;
    p=other.first;
    while(p!=NULL)
    {
        push(p->info,p->coloana);
        p=p->next;
    }
    length=other.length;
    return *this;
}

template <class T>
void lista<T>::push(T value,int coloana)
{
    if(first==NULL)
    {
        nod<T>* p = new nod<T>;
        p->info=value;
        p->coloana=coloana;
        first=p;
        last=p;
    }
    else
    {
        nod<T>* p = new nod<T>;
        p->info=value;
        p->coloana=coloana;
        last->next=p;
        p->prev=last;
        last=p;
    }
    length++;
}

template <class T>
void lista<T>::pop()
{
    if(last!=NULL)
    {
        nod<T>* p;
        p=last;
        if(p!=first)
            p->prev->next=NULL;
        else
        {
            first=NULL;
        }
        last=p->prev;
        delete p;
    }
    length--;
}

template <class T>
nod<T>& lista<T>::operator[] (int n) const
{
    int i=0;
    if(n<0)
        n=0;
    else if(n>length)
        n=length;
    nod<T>* p=first;
    do
    {
        if(i==n)
            return *p;
        if(p!=NULL)
        {
            p=p->next;
            i++;
        }
    }
    while(p!=NULL);
    return *p;
}

template <class T>
nod<T>* lista<T>::inceput() const
{
    return first;
}

template <class T>
nod<T>* lista<T>::sfarsit() const
{
    return last;
}

template <class T>
int lista<T>::lungime() const
{
    return length;
}
