/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include "kdtree.h"


using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if(first[curDim] < second[curDim]) {
        return true;
    }
    if(first[curDim] > second[curDim]) {
        return false;
    }
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
     int potentialDistance = 0;
     int currBestDistance = 0;
     for(size_t i = 0; i < Dim; i++) {
         potentialDistance += (target[i] - potential[i])*(target[i] - potential[i]);
         currBestDistance += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
     }

     if(potentialDistance > currBestDistance) {
         return false;
     }
     if(potentialDistance < currBestDistance) {
         return true;
     }
     return potential < currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    size = newPoints.size();
    vector<Point<Dim>> points;
    points.resize(size);
    if(size == 0) {
         return;
     }
     for(size_t i = 0; i < newPoints.size(); i++) {
         points[i] = newPoints[i];
     }
     root = buildTree(points, 0, points.size()-1, 0);
}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>> &points, int start, int end, int currDim) {
    if (start >= end) {
        return nullptr;
    }
    int median = (start+end)/2;
    Point<Dim> point = quickSelect(points, start, end, median, currDim);
    KDTreeNode* n = new KDTreeNode(point);
    n->left = buildTree(points, start, median - 1, (currDim+1) % Dim);
    n->right = buildTree(points,median + 1, end, (currDim+1) % Dim);
    return n;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>> &points, int start, int end, int k, int currDim) {
    if (k > 0 && k <= end-start+1) {
        int index = partition(points, start, end, currDim);
        if (index - start == k - 1) {
            return points[index];
        } else if (index - start > k - 1) {
            return quickSelect(points, start, index - start, k, currDim);
        } else {
            return quickSelect(points, index + 1, end, k - index + 1, currDim);
        }
    }
    return NULL;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> &points, int start, int end, int currDim) {
    Point<Dim> pivot = points[end];
    int curr = start;
    for (int j = start; j <= end-1; j++) {
        if (smallerDimVal(points[j], pivot, currDim)) {
            std::swap(points[curr], points[j]);
            curr++;
        }
    }
    std::swap(points[curr], points[end]);
    return curr;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

