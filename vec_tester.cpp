// tests (in a non-systematic, non-thorough way) the Vec class defined in vec.h

#include <string>
#include <iostream>
#include "vec.h"

using std::string;
using std::cout;
using std::endl;

int main()
{
    Vec<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    Vec<int> v2 = v;
    v2[0] = 4;

    cout << v[0] << v[1] << v[2] << v2[0] << endl;

    v = v2;
    v2[0] = 1;
    cout << v[0] << endl;

    v2.clear();
    v2.push_back(5);
    cout << v2[0] << " size: " << v2.size() << endl;

    v2.erase(v2.begin());
    cout << v2.size() << endl;

    v.erase(v.begin());
    cout << v[0] << v[1] << " size: " << v.size() << endl;

    return 0;
}
