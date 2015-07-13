// Implementation of Str

#include "str.h"

using namespace std;

// input and output operators
//istream& operator>>(istream&, Str&);
ostream& operator<<(ostream& os, const Str& s) {
    for (Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}
