#include "big_int.hpp"
using namespace std;

namespace {
void trim_leading_zeros(int* digit, int &length) {
    int i = 0;
    while (i < length - 1 && digit[i] == 0) {
        i++;
    }
    if (i > 0) {
        for (int j = 0; j + i < length; j++) {
            digit[j] = digit[j + i];
        }
        for (int j = length - i; j < length; j++) {
            digit[j] = 0;
        }
        length -= i;
    }
}

bool is_zero_digits(const int* digit, int length) {
    for (int i = 0; i < length; i++) {
        if (digit[i] != 0) return false;
    }
    return true;
}
}

big_int::big_int(const int &length_, int* digit_) {
    length = length_;
    memset(digit, 0, sizeof(digit));
    for (int i = 0; i < length; i++) {
        digit[i] = digit_[i];
    }
    trim_leading_zeros(digit, length);
}

big_int big_int::operator+(const big_int other) {
    int n = length, m = other.length;
    int add[2005] = {};
    const int* x = digit;
    const int* y = other.digit;

    if (n > m) {
        const int* temp = x;
        x = y;
        y = temp;

        int tmp = n;
        n = m;
        m = tmp;
    }

    int step = 0;
    for (int i = 0; i < n; i++) {
        int xt = n - 1 - i;
        int yt = m - 1 - i;
        add[i] = (x[xt] + y[yt] + step) % 10;
        step = (x[xt] + y[yt] + step) / 10;
    }

    int leng;
    if (step == 1 && m == n) {
        add[n] = 1;
        leng = n + 1;
    } else if (step == 1) {
        for (int i = n; i < m; i++) {
            int yt = m - 1 - i;
            add[i] = (step + y[yt]) % 10;
            step = (step + y[yt]) / 10;
        }
        if (step == 1) {
            add[m] = 1;
            leng = m + 1;
        } else {
            leng = m;
        }
    } else {
        for (int i = n; i < m; i++) {
            int yt = m - 1 - i;
            add[i] = y[yt];
        }
        leng = m;
    }

    for (int i = 0; i < leng; i++) {
        if (i > leng - 1 - i)
            break;
        int temp = add[i];
        add[i] = add[leng - 1 - i];
        add[leng - 1 - i] = temp;
    }
    int add_length = leng;
    trim_leading_zeros(add, add_length);

    return big_int(add_length, add);
}

big_int big_int::operator-(const big_int other) {
    int n = length, m = other.length;
    int sub[2005] = {};
    int xcopy[2005] = {0};
    int ycopy[2005] = {0};
    for (int i = 0; i < n; i++) {
        xcopy[i] = digit[i];
    }
    for (int i = 0; i < m; i++) {
        ycopy[i] = other.digit[i];
    }
    int* x = xcopy;
    int* y = ycopy;

    if (n > m) {
        int* temp = x;
        x = y;
        y = temp;

        int tmp = n;
        n = m;
        m = tmp;
    } else if (m == n) {
        for (int i = 0; i < m; i++) {
            if (x[i] > y[i]) {
                int* temp = x;
                x = y;
                y = temp;

                int tmp = n;
                n = m;
                m = tmp;
                break;
            } else if (y[i] > x[i]) {
                break;
            }
        }
    }
    int sublen = m;
    int sx[2005] = {0};
    for (int i = 0; i < n; i++) {
        sx[m - i - 1] = x[n - i - 1];
    }

    for (int i = m - 1; i >= 0; i--) {
        if (y[i] >= sx[i])
            sub[i] = y[i] - sx[i];
        else {
            for (int j = i - 1; j >= 0; j--) {
                if (y[j] > 0) {
                    y[j]--;
                    sub[i] = y[i] - sx[i] + 10;
                    break;
                } else
                    y[j] = 9;
            }
        }
    }

    trim_leading_zeros(sub, sublen);
    return big_int(sublen, sub);
}

big_int big_int::operator*(const big_int other){
    int n = length, m = other.length;
    int result[2005] = {0};
    const int* x = digit;
    const int* y = other.digit;

    if (n > m) {
        const int* temp = x;
        x = y;
        y = temp;

        int tmp = n;
        n = m;
        m = tmp;
    }

    int resn = 1;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < x[i]; j++){
            int temp_y[2005] = {0};
            int temp_len = m + n - i - 1;
            for (int k = 0; k < m; k++) {
                temp_y[k] = y[k];
            }
            big_int temp_res(resn, result);
            big_int temp_mul(temp_len, temp_y);
            big_int add_result = temp_res + temp_mul;
            resn = add_result.length;
            memcpy(result, add_result.digit, 2005 * sizeof(int));
        }
    }
    for(int i = 0; i < x[n - 1]; i++){
        int temp_y[2005] = {0};
        for (int k = 0; k < m; k++) {
            temp_y[k] = y[k];
        }
        big_int temp_res(resn, result);
        big_int temp_mul(m, temp_y);
        big_int add_result = temp_res + temp_mul;
        resn = add_result.length;
        memcpy(result, add_result.digit, 2005 * sizeof(int)); 
    }

    trim_leading_zeros(result, resn);
    return big_int(resn, result);
}

bool big_int::operator>(const big_int other) {
    int n = length, m = other.length;
    const int* x = digit;
    const int* y = other.digit;

    if (n > m) {
        return true;
    } else if (m > n) {
        return false;
    } else {
        for (int i = 0; i < n; i++) {
            if (x[i] > y[i]) {
                return true;
            } else if (y[i] > x[i]) {
                return false;
            }
        }
        return false;
    }
}

bool big_int::operator==(const big_int other) {
    int n = length, m = other.length;
    const int* x = digit;
    const int* y = other.digit;

    if (n != m) {
        return false;
    } else {
        for (int i = 0; i < n; i++) {
            if (x[i] != y[i]) {
                return false;
            }
        }
        return true;
    }
}

bool big_int::operator<(const big_int other) {
    return !(*this > other) && !(*this == other);
}

bool big_int::operator<=(const big_int other) {
    return (*this < other) || (*this == other);
}

bool big_int::operator>=(const big_int other) {
    return (*this > other) || (*this == other);
}

bool big_int::operator!=(const big_int other) {
    return !(*this == other);
}

big_int big_int::operator/(const big_int other){
    int n = length, m = other.length;
    const int* x = digit;
    const int* y = other.digit;

    if (is_zero_digits(y, m)) {
        int zero[2005] = {0};
        return big_int(1, zero);
    }

    int total[2005] = {0};
    memcpy(total, x, 2005 * sizeof(int));
    big_int tot (length, total);
    
    int result[2005] = {0};
    big_int res (1, result);

    int multlen = tot.length - m;

    int temp_plus[2005] = {0};
    temp_plus[0] = 1;
    while(tot >= other){
        while (multlen > 0) {
            int temp_min[2005] = {0};
            int temp_len = m + multlen;
            for (int i = 0; i < m; i++) {
                temp_min[i] = y[i];
            }
            if (!(big_int(temp_len, temp_min) > tot)) {
                break;
            }
            multlen--;
        }

        int temp_min[2005] = {0};
        int temp_len = m + multlen;
        for (int i = 0; i < m; i++) {
            temp_min[i] = y[i];
        }
        big_int temp_minus(temp_len, temp_min);

        while(tot >= temp_minus){
            tot = tot - temp_minus;
            res = res + big_int(multlen + 1, temp_plus);
        }
    }

    return res;
    
}

big_int big_int::operator%(const big_int other){
    big_int div = (*this) / other;
    big_int mul = div * other;
    big_int mod = (*this) - mul;
    return mod;
}

void big_int::print() {
    for (int i = 0; i < length; i++) {
        printf("%d", digit[i]);
    }
    printf("\n");
}
