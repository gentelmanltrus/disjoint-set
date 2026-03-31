#include "DisjointSet.h"
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace myds {

// realisation
class DisjointSet::Impl {
public:
    vector<int> parent;

    int find(int x) const {
        if (x < 0 || x >= parent.size())
            throw out_of_range("Index out of range");

        if (parent[x] == x)
            return x;

        return find(parent[x]);
    }
};
//constructors
DisjointSet::DisjointSet() {
    pImpl = new Impl();
}

DisjointSet::~DisjointSet() {
    delete pImpl;
}
//copy
DisjointSet::DisjointSet(const DisjointSet& other) {
    pImpl = new Impl(*other.pImpl);
}

DisjointSet& DisjointSet::operator=(const DisjointSet& other) {
    if (this != &other) {
        delete pImpl;
        pImpl = new Impl(*other.pImpl);
    }
    return *this;
}
//CRUDE
void DisjointSet::makeSet(int x) {
    if (x < 0) throw invalid_argument("Negative index");

    if (x >= pImpl->parent.size()) {
        pImpl->parent.resize(x + 1);
    }

    pImpl->parent[x] = x;
}
int DisjointSet::find(int x) const {
    return pImpl->find(x);
}
void DisjointSet::unite(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);

    if (rootA != rootB)
        pImpl->parent[rootB] = rootA;
}
void DisjointSet::remove(int x) {
    if (x < 0 || x >= pImpl->parent.size())
        throw out_of_range("Invalid remove");

    pImpl->parent[x] = -1;
}
DisjointSet& DisjointSet::operator+=(int x) {
    makeSet(x);
    return *this;
}
DisjointSet& DisjointSet::operator-=(int x) {
    remove(x);
    return *this;
}
DisjointSet& DisjointSet::operator*=(const pair<int,int>& p) {
    unite(p.first, p.second);
    return *this;
}
int DisjointSet::operator[](int x) const {
    return find(x);
}
DisjointSet& DisjointSet::operator!() {
    pImpl->parent.clear();
    return *this;
}
bool DisjointSet::operator==(const DisjointSet& other) const {
    return pImpl->parent == other.pImpl->parent;
}

bool DisjointSet::operator!=(const DisjointSet& other) const {
    return !(*this == other);
}

bool DisjointSet::operator<(const DisjointSet& other) const {
    return pImpl->parent.size() < other.pImpl->parent.size();
}

bool DisjointSet::operator<=(const DisjointSet& other) const {
    return pImpl->parent.size() <= other.pImpl->parent.size();
}

bool DisjointSet::operator>(const DisjointSet& other) const {
    return pImpl->parent.size() > other.pImpl->parent.size();
}

bool DisjointSet::operator>=(const DisjointSet& other) const {
    return pImpl->parent.size() >= other.pImpl->parent.size();
}
string DisjointSet::toString() const {
    ostringstream oss;
    oss << "Parent array: ";
    for (int i = 0; i < pImpl->parent.size(); i++) {
        oss << pImpl->parent[i] << " ";
    }
    return oss.str();
}   