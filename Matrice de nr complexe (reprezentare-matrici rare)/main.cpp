//#include "numar_complex.cpp"
//#include "lista.cpp"
#include "matrice.cpp"
#include <bits/stdc++.h>
#include <algorithm>
ifstream f("date.in");
int main()
{
    cout<<"\nMATRICE DE NUMERE COMPLEXE REPREZENTATE CA STRUCTURI INLANTUITE (MATRICI RARE)\n\n\n";
    cout<<"==============================OPERATII=CU=MATRICI==============================\n\n";
    matrice_oarecare A,B,C;
    f>>A>>B>>C;

    cout<<"Asociativitatea adunarii:\n";
    if((A+B)+C==A+(B+C))
        cout<<"Are loc egalitatea (A+B)+C = A+(B+C).\n\n";

    cout<<"Distributivitatea inmultirii fata de adunare:\n";
    matrice_oarecare D=A*(B+C);
    if(D==A*B+A*C)
        cout<<"Are loc egalitatea A*(B+C) = A*B + A*C.\n\n\n";

    cout<<"================DETERMINANTUL=SI=INVERSA=UNEI=MATRICI=PATRATICE================\n\n";
    matrice_patratica I3;
    f>>I3;
    matrice_patratica X;
    f>>X;
    cout<<"Matricea X:\n";
    cout<<X;
    matrice_patratica inversa_X=X.inversa();
    cout<<"Inversa matricei X:\n"<<inversa_X;
    if(inversa_X*X==I3)
        cout<<"Are loc egalitatea: X * X^(-1) = I3.\n\n\n";

    cout<<"================SORTAREA=UNUI=VECTOR=DE=MATRICI=DUPA=DIMENSIUNE================\n\n";

    cout<<"Sortare - Matrici oarecare:\n\n";
    vector<matrice_oarecare> v;
    int n;
    f>>n;
    v.resize(n);
    for(int i=0;i<n;++i)
        f>>v[i];
    sort(v.begin(),v.end());
    for(int i=0;i<n;++i)
        cout<<v[i];

    cout<<"Sortare - Matrici patratice:\n\n";
    vector<matrice_patratica> w;
    int m;
    f>>m;
    w.resize(m);
    for(int i=0;i<m;++i)
        f>>w[i];
    sort(w.begin(),w.end());
    for(int i=0;i<m;++i)
        cout<<w[i];
    return 0;
}

//throw std::runtime_error("Matrix must be square! Error occured in SparseMatrix::det()");
