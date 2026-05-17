#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <string>
#include <utility> //for std::pair
namespace myds {

class DSException: public std::exception {
public:
    const char* what() const noexcept override;
}; // deklaracija

class DisjointSet {
private:
    class Impl;     // hidden realisation
    Impl* pImpl;    // pointer

public:
    // constructors - destructor
    DisjointSet();
    DisjointSet(const DisjointSet& other); //  copy
    DisjointSet& operator=(const DisjointSet& other);
    ~DisjointSet();
    // CRUD / DAVE
    void makeSet(int x);    // create
    int find(int x) const;     // read
    void unite(int a, int b);  // update
    void remove(int x); // delete

    // operators
    DisjointSet& operator+=(int x);         // add
    DisjointSet& operator-=(int x);     // remove
    DisjointSet& operator*=(const std::pair<int,int>& p); // unite
    int operator[](int x) const;      // find

    DisjointSet& operator!(); // clear

    // comparison
    bool operator==(const DisjointSet& other) const;
    bool operator!=(const DisjointSet& other) const;
    bool operator<(const DisjointSet& other) const;
    bool operator<=(const DisjointSet& other) const;
    bool operator>(const DisjointSet& other) const;
    bool operator>=(const DisjointSet& other) const;

    std::string toString() const;
};

}

#endif
