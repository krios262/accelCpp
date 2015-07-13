// tests (in a non-systematic, non-thorough way) the Str class defined in str.h

#include <iostream>
#include "str.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    Str s = "Testing: enter your name: ";
    cout << s;

    cin >> s;
    cout << s << endl;

    return 0;
}
