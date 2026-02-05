#include<bits/stdc++.h>
using namespace std;

class big_int{
    public:
        int digit[2005];
        int length;
    
    public:
        big_int(const int & length, int* digit);

        big_int operator+(const big_int other);

        big_int operator-(const big_int other);

        big_int operator*(const big_int other);

        big_int operator/(const big_int other);

        big_int operator%(const big_int other);

        bool operator>(const big_int other);
        
        bool operator==(const big_int other);

        bool operator<(const big_int other);

        bool operator<=(const big_int other);

        bool operator>=(const big_int other);

        bool operator!=(const big_int other);

        void print();
        
};
