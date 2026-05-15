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
    class Impl
    {
    private:
        int *parent; //dynamic array
        int size;// logical size
     // realizacija

public:
    // constructors / destructor
    Impl();//empty
    Impl(const Impl& other);          // copy
    Impl& operator=(const Impl& other); // copy‑assign
    ~Impl();
                            
    int find(int x) const;

    }
    Impl* pImpl;    // pointer to implementation
    friend class TestDisjointSet;
    public:
    // lifecycle
    DisjointSet();
    DisjointSet(const DisjointSet& other);
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