#include <iostream>
#include <fstream>
#include "DisjointSet.h"

using namespace std;
using namespace myds;

void logResult(ofstream& log, const string& testName, bool passed) {
    cout << testName << ": " << (passed ? "PASSED" : "FAILED") << endl;
    log << testName << ": " << (passed ? "PASSED" : "FAILED") << endl;
}

int main() {
    ofstream log("log.txt");
    log << "DisjointSet Test Log " << endl;

    DisjointSet ds1;
    ds1 += 0;
    ds1 += 1;
    ds1 += 2;

    // Test unite
    ds1 *= make_pair(0,1);
    logResult(log, "Union 0-1", ds1[0] == ds1[1]);

    // Test find
    logResult(log, "Find 2", ds1[2] == 2);

    // Test remove
    ds1 -= 2;
    logResult(log, "Remove 2", ds1[2] == -1);

    // Test clear
    !ds1;
    logResult(log, "Clear", ds1.toString() == "Parent array: ");

    // Test deep copy
    ds1 += 5;
    DisjointSet ds2 = ds1;
    logResult(log, "Deep Copy", ds1[5] == ds2[5]);

    log.close();
    return 0;
}