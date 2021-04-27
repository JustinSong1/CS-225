#ifndef DSET_H
#define DSET_H

#include <vector>
class DisjointSets {
public:
    //Creates n unconnected root nodes at the end of the vector.
    void addelements(int num);
    //This function should compress paths and works as described in lecture.
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);
private:
    std::vector<int> data;
};

#endif /* DSET_H */
