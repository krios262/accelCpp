#ifndef __str_h
#define __str_h

// Str class from Accelerated C++
// Evan Thompson

#include <iostream>
#include <cstring>
#include "vec.h"

// This class is a stripeed down version of std::string
// It uses the Vec class to hold the characters
class Str {
    public:
        typedef Vec<char>::size_type size_type;

        // default constructor (empty Str)
        Str() { }
        // create a Str with n copies of c
        Str(size_type n, char c): data(n , c) { }
        // Create a Str from a null-terminated char array
        Str(const char* c) {
            std::copy(c, c + std::strlen(c), std::back_inserter(data));
        }
        // create a Str from the range denoted by the iterators
        template <class In> Str(In b, In e) {
            std::copy(b, e, std::back_inserter(data));
        }

        // index operator
        char& operator[](size_type i) { return data[i]; }
        const char& operator[](size_type i) const { return data[i]; }

        size_type size() const { return data.size(); }

    private:
        Vec<char> data;
};

// input and output operators
//std::istream& operator>>(std::istream&, Str&);
std::ostream& operator<<(std::ostream&, const Str&);

#endif
