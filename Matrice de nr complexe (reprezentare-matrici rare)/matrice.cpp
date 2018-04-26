#include "matrice.h"

///===================================================================================class matrice==================================================

istream& operator>> (istream& in, matrice& object)
{
    return object.citire(in);
}

ostream& operator<< (ostream& out, const matrice& object)
{
    return object.afisare(out);
}

///===================================================================================class matrice_oarecare=========================================

matrice_oarecare::matrice_oarecare(): matrice()
{
    nr_coloane=0;
    nr_linii=0;
}

matrice_oarecare::matrice_oarecare(int linii,int coloane): matrice()
{
    nr_coloane=coloane;
    nr_linii=linii;
    lista <numar_complex> temp;
    for(int i=0; i<nr_linii; ++i)
        mat.push(temp,i);
}

matrice_oarecare::matrice_oarecare(const matrice_oarecare& other)
{
    nr_coloane=other.nr_coloane;
    nr_linii=other.nr_linii;
    lista <numar_complex> temp;
    for(int i=0; i<nr_linii; ++i)
        mat.push(temp,i);
    for(int i=0; i<nr_linii; ++i)
    {
        for(int j=0; j<other[i].lungime(); ++j)
            (*this)[i].push(other[i][j].info,other[i][j].coloana);
    }
}

matrice_oarecare::~matrice_oarecare()
{
    for(int i=nr_linii-1;i>=0;--i)
    {
        while((*this)[i].lungime())
            (*this)[i].pop();
        mat.pop();
    }
}

//====================================================================================================== operator= ==================================

matrice_oarecare& matrice_oarecare::operator= (const matrice_oarecare& other)
{
    for(int i=nr_linii-1; i>=0; i--)
    {
        while((*this)[i].lungime()!=0)
            (*this)[i].pop();
    }
    nr_coloane=other.nr_coloane;
    nr_linii=other.nr_linii;
    lista <numar_complex> temp;
    for(int i=0; i<nr_linii; ++i)
        mat.push(temp,i);
    for(int i=0; i<nr_linii; ++i)
    {
        for(int j=0; j<other[i].lungime(); ++j)
            (*this)[i].push(other[i][j].info,other[i][j].coloana);
    }
    return *this;
}

//====================================================================================================== operator+ ==================================

matrice_oarecare matrice_oarecare::operator+ (const matrice_oarecare& other) const
{
    if(nr_linii!=other.nr_linii || nr_coloane!=other.nr_coloane)
        throw 1;
    matrice_oarecare temp(nr_linii,nr_coloane);
    for(int i=0; i<nr_linii; ++i)
    {
        if((*this)[i].lungime()!=0 && other[i].lungime()==0)
            for(int j=0; j<(*this)[i].lungime(); ++j)
                temp[i].push((*this)[i][j].info,(*this)[i][j].coloana);
        if((*this)[i].lungime()==0 && other[i].lungime()!=0)
            for(int j=0; j<other[i].lungime(); ++j)
                temp[i].push(other[i][j].info,other[i][j].coloana);
        if((*this)[i].lungime()!=0 && other[i].lungime()!=0)
        {
            int j,k;
            for(j=0,k=0; j<(*this)[i].lungime() && k<other[i].lungime();)
            {
                if((*this)[i][j].coloana<other[i][k].coloana)
                {
                    temp[i].push((*this)[i][j].info,(*this)[i][j].coloana);
                    j++;
                }
                if((*this)[i][j].coloana>other[i][k].coloana)
                {
                    temp[i].push(other[i][k].info,other[i][k].coloana);
                    k++;
                }
                if((*this)[i][j].coloana==other[i][k].coloana)
                {
                    temp[i].push((*this)[i][j].info+other[i][k].info,(*this)[i][j].coloana);
                    j++;
                    k++;
                }
            }

            for(; j<(*this)[i].lungime(); ++j)
                temp[i].push((*this)[i][j].info,(*this)[i][j].coloana);
            for(; k<other[i].lungime(); ++k)
                temp[i].push(other[i][k].info,other[i][k].coloana);
        }
    }
    return temp;
}

//====================================================================================================== operator* ==================================

matrice_oarecare matrice_oarecare::operator* (const matrice_oarecare& other) const
{
    if(nr_coloane!=other.nr_linii)
        throw 2;
    matrice_oarecare temp(nr_linii,other.nr_coloane);

    for(int i=0; i<nr_linii; ++i)
    {
        for(int j=0; j<other.nr_coloane; ++j)
        {
            numar_complex rezultat(0,0);
            for(int k=0; k<(*this)[i].lungime(); ++k)
            {
                int l=(*this)[i][k].coloana;
                for(int m=0; m<other[l].lungime(); ++m)
                    if(other[l][m].coloana==j)
                        rezultat=rezultat+((*this)[i][k].info*other[l][m].info);
            }
            numar_complex zero(0,0);
            if(rezultat!=zero)
                temp[i].push(rezultat,j);
        }
    }
    return temp;
}

//====================================================================================================== citire+afisare ============================

istream& matrice_oarecare::citire(istream& in)
{
    for(int i=nr_linii-1; i>=0; i--)
    {
        while((*this)[i].lungime()>0)
            (*this)[i].pop();
        mat.pop();
    }

    in>>nr_linii>>nr_coloane;
    lista <numar_complex> temp;
    for(int i=0; i<nr_linii; ++i)
    {
        mat.push(temp,i);
        for(int j=0; j<nr_coloane; ++j)
        {
            numar_complex val;
            in>>val;
            numar_complex zero(0,0);
            if(val!=zero)
                (*this)[i].push(val,j);
        }
    }
    return in;
}

ostream& matrice_oarecare::afisare(ostream& out) const
{
    numar_complex zero(0,0);
    for(int i=0; i<nr_linii; ++i)
    {
        if((*this)[i].lungime()==0)
        {
            for(int j=0; j<nr_coloane; ++j)
                out<<zero;
            out<<'\n';
            continue;
        }
        int contor=0;
        int j=0;
        while(contor<(*this)[i].lungime())
        {
            for(; j<(*this)[i][contor].coloana; ++j)
                out<<zero;
            out<<(*this)[i][contor];
            contor++;
            ++j;
        }
        while(j<nr_coloane)
        {

            out<<zero;
            ++j;

        }
        out<<'\n';
    }
    out<<'\n';
    return out;
}

//====================================================================================================== operator==,!=,< ============================

bool matrice_oarecare::operator== (const matrice_oarecare& other) const
{
    if(nr_linii!=other.nr_linii)
        return false;
    if(nr_coloane!=other.nr_coloane)
        return false;
    for(int i=0;i<nr_linii;++i)
        if((*this)[i].lungime()!=other[i].lungime())
            return false;
    for(int i=0;i<nr_linii;++i)
        for(int j=0;j<(*this)[i].lungime();++j)
            if((*this)[i][j].info!=other[i][j].info || (*this)[i][j].coloana!=other[i][j].coloana)
                return false;
    return true;
}

bool matrice_oarecare::operator!= (const matrice_oarecare& other) const
{
    if(*this==other)
        return false;
    return true;
}

bool matrice_oarecare::operator< (const matrice_oarecare& other) const
{
    if(nr_linii<other.nr_linii)
        return true;
    if(nr_linii>other.nr_linii)
        return false;
    if(nr_coloane<other.nr_coloane)
        return true;
    return false;
}

lista <numar_complex>& matrice_oarecare::operator[] (int n) const
{
    int i=0;
    if(n<0)
        n=0;
    else if(n>mat.lungime())
        n=mat.lungime();
    nod<lista<numar_complex> >* p=mat.inceput();
    do
    {
        if(i==n)
            return (*p).info;
        if(p!=NULL)
        {
            p=p->next;
            i++;
        }
    }
    while(p!=NULL);
    return (*p).info;
}

///===================================================================================class matrice_patratica========================================

matrice_patratica::matrice_patratica(): matrice()
{
    dimensiune=0;
}

matrice_patratica::matrice_patratica(int dim): matrice()
{
    dimensiune=dim;
    lista <numar_complex> temp;
    for(int i=0; i<dimensiune; ++i)
        mat.push(temp,i);
}

matrice_patratica::matrice_patratica(const matrice_patratica& other): matrice()
{
    dimensiune=other.dimensiune;
    lista <numar_complex> temp;
    for(int i=0; i<dimensiune; ++i)
        mat.push(temp,i);
    for(int i=0; i<dimensiune; ++i)
    {
        for(int j=0; j<other[i].lungime(); ++j)
            (*this)[i].push(other[i][j].info,other[i][j].coloana);
    }
}


matrice_patratica::~matrice_patratica()
{
    for(int i=dimensiune-1;i>=0;--i)
    {
        while((*this)[i].lungime())
            (*this)[i].pop();
        mat.pop();
    }
}

//====================================================================================================== operator= ==================================

matrice_patratica& matrice_patratica::operator= (const matrice_patratica& other)
{
    for(int i=dimensiune-1; i>=0; i--)
    {
        while((*this)[i].lungime()!=0)
            (*this)[i].pop();
    }
    dimensiune=other.dimensiune;
    lista <numar_complex> temp;
    for(int i=0; i<dimensiune; ++i)
        mat.push(temp,i);
    for(int i=0; i<dimensiune; ++i)
    {
        for(int j=0; j<other[i].lungime(); ++j)
            (*this)[i].push(other[i][j].info,other[i][j].coloana);
    }
    return *this;
}

//====================================================================================================== operator+ ==================================

matrice_patratica matrice_patratica::operator+ (const matrice_patratica& other) const
{
    if(dimensiune!=other.dimensiune)
        throw 1;
    matrice_patratica temp(dimensiune);
    for(int i=0; i<dimensiune; ++i)
    {
        if((*this)[i].lungime()!=0 && other[i].lungime()==0)
            for(int j=0; j<(*this)[i].lungime(); ++j)
                temp[i].push((*this)[i][j].info,(*this)[i][j].coloana);
        if((*this)[i].lungime()==0 && other[i].lungime()!=0)
            for(int j=0; j<other[i].lungime(); ++j)
                temp[i].push(other[i][j].info,other[i][j].coloana);
        if((*this)[i].lungime()!=0 && other[i].lungime()!=0)
        {
            int j,k;
            for(j=0,k=0; j<(*this)[i].lungime() && k<other[i].lungime();)
            {
                if((*this)[i][j].coloana<other[i][k].coloana)
                {
                    temp[i].push((*this)[i][j].info,(*this)[i][j].coloana);
                    j++;
                }
                if((*this)[i][j].coloana>other[i][k].coloana)
                {
                    temp[i].push(other[i][k].info,other[i][k].coloana);
                    k++;
                }
                if((*this)[i][j].coloana==other[i][k].coloana)
                {
                    temp[i].push((*this)[i][j].info+other[i][k].info,(*this)[i][j].coloana);
                    j++;
                    k++;
                }
            }

            for(; j<(*this)[i].lungime(); ++j)
                temp[i].push((*this)[i][j].info,(*this)[i][j].coloana);
            for(; k<other[i].lungime(); ++k)
                temp[i].push(other[i][k].info,other[i][k].coloana);
        }
    }
    return temp;
}

//====================================================================================================== operator* ==================================

matrice_patratica matrice_patratica::operator* (const matrice_patratica& other) const
{
    if(dimensiune!=other.dimensiune)
        throw 2;
    matrice_patratica temp(dimensiune);

    for(int i=0; i<dimensiune; ++i)
    {
        for(int j=0; j<other.dimensiune; ++j)
        {
            numar_complex rezultat(0,0);
            for(int k=0; k<(*this)[i].lungime(); ++k)
            {
                int l=(*this)[i][k].coloana;
                for(int m=0; m<other[l].lungime(); ++m)
                    if(other[l][m].coloana==j)
                        rezultat=rezultat+((*this)[i][k].info*other[l][m].info);
            }
            numar_complex zero(0,0);
            if(rezultat!=zero)
                temp[i].push(rezultat,j);
        }
    }
    return temp;
}

//====================================================================================================== citire+afisare =============================

istream& matrice_patratica::citire(istream& in)
{
    for(int i=dimensiune-1; i>=0; i--)
    {
        while((*this)[i].lungime()>0)
            (*this)[i].pop();
        mat.pop();
    }

    in>>dimensiune;
    lista <numar_complex> temp;
    for(int i=0; i<dimensiune; ++i)
    {
        mat.push(temp,i);
        for(int j=0; j<dimensiune; ++j)
        {
            numar_complex val;
            in>>val;
            numar_complex zero(0,0);
            if(val!=zero)
                (*this)[i].push(val,j);
        }
    }
    return in;
}

ostream& matrice_patratica::afisare(ostream& out) const
{
    numar_complex zero(0,0);
    for(int i=0; i<dimensiune; ++i)
    {
        if((*this)[i].lungime()==0)
        {
            for(int j=0; j<dimensiune; ++j)
                out<<zero;
            out<<'\n';
            continue;
        }
        int contor=0;
        int j=0;
        while(contor<(*this)[i].lungime())
        {
            for(; j<(*this)[i][contor].coloana; ++j)
                out<<zero;
            out<<(*this)[i][contor];
            contor++;
            j++;
        }
        while(j<dimensiune)
        {

            out<<zero;
            ++j;

        }
        out<<'\n';
    }
    //out<<'\n';
    out<<"Determinant: "<<determinant()<<"\n\n";
    return out;
}

//====================================================================================================== check_diagonal =============================

bool matrice_patratica::check_diagonal() const
{
    for(int i=0; i<dimensiune; ++i)
        if((*this)[i].lungime()!=1)
            return false;
    for(int i=0; i<dimensiune; ++i)
        if((*this)[i][0].coloana!=i)
            return false;
    return true;
}

//====================================================================================================== determinant ================================

numar_complex matrice_patratica::determinant() const
{
    numar_complex zero(0,0);
    if(dimensiune==1)
    {
        if((*this)[0].lungime()==1)
            return (*this)[0][0].info;
            else
                return zero;
    }
    numar_complex det(0,0);
    for(int j=0;j<(*this)[0].lungime();++j)
    {
        if((*this)[0][j].coloana%2)
            det=det-((*this)[0][j].info*minor(0,(*this)[0][j].coloana).determinant());
        else
            det=det+((*this)[0][j].info*minor(0,(*this)[0][j].coloana).determinant());
    }
    return det;
}

//====================================================================================================== inversa ====================================

matrice_patratica matrice_patratica::minor(int linie,int coloana) const
{
    matrice_patratica temp(dimensiune-1);

    for(int i=0; i<dimensiune  ; ++i)
    {
        if(i==linie)
            continue;
        for(int j=0; j<(*this)[i].lungime(); ++j)
            if((*this)[i][j].coloana!=coloana)
            {
                int noua_linie=i;
                if(noua_linie>linie)
                    noua_linie--;
                int noua_coloana=(*this)[i][j].coloana;
                if(noua_coloana>coloana)
                    noua_coloana--;
                temp[noua_linie].push((*this)[i][j].info,noua_coloana);
            }

    }

    return temp;
}

matrice_patratica matrice_patratica::transpusa() const
{
    matrice_patratica temp(dimensiune);

    for(int i=0; i<dimensiune; ++i)
    {
        for(int j=0; j<(*this)[i].lungime(); ++j)
            temp[(*this)[i][j].coloana].push((*this)[i][j].info,i);
    }
    return temp;
}

matrice_patratica matrice_patratica::inversa () const
{
    numar_complex zero(0,0);
    numar_complex minus_unu(-1,0);
    numar_complex det=determinant();
    if(det==zero)
        throw 3;

    matrice_patratica temp(dimensiune);

    for(int i=0; i<dimensiune; ++i)
        for(int j=0; j<dimensiune; ++j)
        {
            matrice_patratica minor=transpusa().minor(i,j);
            numar_complex aux=minor.determinant();
            if((i+j)%2)
                aux=aux*minus_unu;
            if(aux!=zero)
                temp[i].push(aux/det,j);
        }
    return temp;
}

//====================================================================================================== operator==,!=,< ============================

bool matrice_patratica::operator== (const matrice_patratica& other) const
{
    if(dimensiune!=other.dimensiune)
        return false;
    for(int i=0;i<dimensiune;++i)
        if((*this)[i].lungime()!=other[i].lungime())
            return false;
    for(int i=0;i<dimensiune;++i)
        for(int j=0;j<(*this)[i].lungime();++j)
            if((*this)[i][j].info!=other[i][j].info || (*this)[i][j].coloana!=other[i][j].coloana)
                return false;
    return true;
}

bool matrice_patratica::operator!= (const matrice_patratica& other) const
{
    if(*this==other)
        return false;
    return true;
}

bool matrice_patratica::operator< (const matrice_patratica& other) const
{
    if(dimensiune<other.dimensiune)
        return true;
    return false;
}


lista <numar_complex>& matrice_patratica::operator[] (int n) const
{
    int i=0;
    if(n<0)
        n=0;
    else if(n>mat.lungime())
        n=mat.lungime();
    nod<lista<numar_complex> >* p=mat.inceput();
    do
    {
        if(i==n)
            return (*p).info;
        if(p!=NULL)
        {
            p=p->next;
            i++;
        }
    }
    while(p!=NULL);
    return (*p).info;
}
