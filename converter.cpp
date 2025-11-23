#include "converter.h"
#include <algorithm>
#include <stdexcept>

long long toDecimal(const std::string& numQ, int Q) {
    long long dec = 0;
    for (char c : numQ) {
        if (c < '0' || c > '9')
            throw std::invalid_argument("В числе есть недопустимые символы.");

        int digit = c - '0';
        if (digit >= Q)
            throw std::invalid_argument("Цифра не принадлежит системе Q.");

        dec = dec * Q + digit;
    }
    return dec;
}

std::string fromDecimal(long long dec, int P) {
    if (dec == 0) return "0";

    std::string res;
    long long n = dec;
    while (n > 0) {
        int digit = n % P;
        res.push_back(char('0' + digit));
        n /= P;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

std::string convertQtoP(const std::string& numQ, int Q, int P) {
    long long dec = toDecimal(numQ, Q);
    return fromDecimal(dec, P);
}
