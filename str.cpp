// Implementation of Str

#include "str.h"

using std::istream;
using std::ostream;

// input and output operators
istream& operator>>(istream& is, Str& s) {
    // erase any existing values
    s.data.clear();

    // discard any leading whitespace
    char c;
    while (is.get(c) && isspace(c))
        ; // nothing to do
    // if there is something to read, do so until we hit whitespace
    if (is) {
        do s.data.push_back(c);
        while (is.get(c) && !isspace(c));

        // if we read whitespace, put it back on the stream
        if (is)
            is.unget();
    }
    return is;
}

ostream& operator<<(ostream& os, const Str& s) {
    for (Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}
