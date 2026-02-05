#include<bits/stdc++.h>
#include "big_int.hpp"
using namespace std;

big_int gcd(big_int A, big_int B){
    if(B > A){
        big_int temp = A;
        A = B;
        B = temp;
    }

    big_int m = A;
    big_int n = B;
    int zeros[2005] = {0};
    big_int zero = big_int(1, zeros);
    
    while(m % n != zero){
        big_int r = m % n;
        m = n;
        n = r;
    }
    return n;
}

int main(){
    int n, m;
    string a, b;
    int numa[2005] = {0};
    int numb[2005] = {0};
    cin>>a;
    cin>>b;
    n = a.length();
    m = b.length();

    for(int i = 0; i < n; i++){
        numa[i] = a[i] - '0';
    }
    for(int i = 0; i < m; i++){
        numb[i] = b[i] - '0';
    }

    big_int A(n, numa);
    big_int B(m, numb);

    big_int C = gcd(A, B);
    C.print();
}
