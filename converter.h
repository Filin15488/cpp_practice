#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

long long toDecimal(const std::string& numQ, int Q);
std::string fromDecimal(long long dec, int P);
std::string convertQtoP(const std::string& numQ, int Q, int P);

#endif
