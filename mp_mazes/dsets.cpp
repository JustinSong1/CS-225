#include "dsets.h"

void DisjointSets::addelements(int num) {
    for(int i = 0; i < num; i++) {
        data.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if(data[elem] < 0) {
        return elem;
    } else {
        data[elem] = find(data[elem]);
        return data[elem];
    }
}

void DisjointSets::setunion(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    int newSize = data[rootA] + data[rootB];
    if(rootA == rootB) return;
    if(data[rootA] > data[rootB]) {
        data[rootA] = rootB;
        data[rootB] = newSize;
    } else {
        data[rootB] = rootA;
        data[rootA] = newSize;
    }
}

int DisjointSets::size(int elem) {
    return -1*data[find(elem)];
}

