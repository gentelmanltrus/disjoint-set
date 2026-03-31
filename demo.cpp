#include <iostream>
#include "DisjointSet.h"

using namespace std;
using namespace myds;

int main() {
    cout << "Disjoint Set Demo" << endl;

    DisjointSet ds;

    // create elemets
    ds += 0;
    ds += 1;
    ds += 2;
    ds += 3;

    cout << ds.toString() << endl;

    // pair elements
    ds *= make_pair(0, 1);
    ds *= make_pair(2, 3);

    cout << "After pairing:" << endl;
    cout << ds.toString() << endl;

    // check find
    cout << "Root 0: " << ds[0] << endl;
    cout << "Root 2: " << ds[2] << endl;

    // delete
    ds -= 3;
    cout << "After delete 3:" << endl;
    cout << ds.toString() << endl;

    // clear
    !ds;
    cout << "After clear:" << endl;
    cout << ds.toString() << endl;

    return 0;
}