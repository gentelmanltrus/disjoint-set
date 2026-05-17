#include "DisjointSet.h"
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace myds;

//  declare Impl + define it in the cpp

namespace myds {

class DisjointSet::Impl {
public:
    Impl();                            // empty
    Impl(const Impl& other);          // deep copy
    Impl& operator=(const Impl& other); // copy assign
    ~Impl();                           // cleanup

    int*  parent;  // dynamic array
    int   size;    // logical size

    int find(int x) const;
};

} // namespace myds


//  Impl methods

DisjointSet::Impl::Impl()
    : parent(nullptr), size(0)
{}


DisjointSet::Impl::~Impl() {
    delete[] parent;
}


DisjointSet::Impl::Impl(const Impl& other)
    : parent(other.size > 0 ? new int[other.size] : nullptr), size(other.size)
{
    for (int i = 0; i < size; ++i)
        parent[i] = other.parent[i];
}


DisjointSet::Impl& DisjointSet::Impl::operator=(const Impl& other) {
    if (this == &other) return *this;

    delete[] parent;
    parent = nullptr;
    size   = 0;

    if (other.size > 0) {
        parent = new int[other.size];
        size   = other.size;
        for (int i = 0; i < size; ++i)
            parent[i] = other.parent[i];
    }

    return *this;
}


int DisjointSet::Impl::find(int x) const {
    if (x < 0 || x >= size)
        throw out_of_range("Index out of range");

    if (parent[x] == x)
        return x;

    return find(parent[x]);
}


//DisjointSet public

DisjointSet::DisjointSet()
    : pImpl(new Impl())
{}


DisjointSet::~DisjointSet() {
    delete pImpl;
}


DisjointSet::DisjointSet(const DisjointSet& other)
    : pImpl(new Impl(*other.pImpl))
{}


DisjointSet& DisjointSet::operator=(const DisjointSet& other) {
    if (this != &other) {
        delete pImpl;
        pImpl = new Impl(*other.pImpl);
    }
    return *this;
}


void DisjointSet::makeSet(int x) {
    if (x < 0)
        throw invalid_argument("Negative index");

    if (x >= pImpl->size) {
        Impl* old = pImpl;
        pImpl = new Impl(x + 1);

        // copy old data into new array
        for (int i = 0; i < old->size; ++i)
            pImpl->parent[i] = old->parent[i];

        delete old;
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
    if (x < 0 || x >= pImpl->size)
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


DisjointSet& DisjointSet::operator*=(const std::pair<int,int>& p) {
    unite(p.first, p.second);
    return *this;
}


int DisjointSet::operator[](int x) const {
    return find(x);
}


DisjointSet& DisjointSet::operator!() {
    delete pImpl;
    pImpl = new Impl();
    return *this;
}


bool DisjointSet::operator==(const DisjointSet& other) const {
    if (pImpl->size != other.pImpl->size)
        return false;

    for (int i = 0; i < pImpl->size; ++i)
        if (pImpl->parent[i] != other.pImpl->parent[i])
            return false;

    return true;
}


bool DisjointSet::operator!=(const DisjointSet& other) const {
    return !(*this == other);
}


bool DisjointSet::operator<(const DisjointSet& other) const {
    return pImpl->size < other.pImpl->size;
}


bool DisjointSet::operator<=(const DisjointSet& other) const {
    return pImpl->size <= other.pImpl->size;
}


bool DisjointSet::operator>(const DisjointSet& other) const {
    return pImpl->size > other.pImpl->size;
}


bool DisjointSet::operator>=(const DisjointSet& other) const {
    return pImpl->size >= other.pImpl->size;
}


std::string DisjointSet::toString() const {
    ostringstream oss;
    oss << "Parent array: ";
    for (int i = 0; i < pImpl->size; ++i) {
        oss << pImpl->parent[i] << " ";
    }
    return oss.str();
}