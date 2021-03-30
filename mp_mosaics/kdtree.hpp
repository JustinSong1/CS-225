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
    return first < second;
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
    if (start > end) {
        return nullptr;
    }
    int median = (start + end)/2;
    quickSelect(points, start, end, median, currDim);
    KDTreeNode* n = new KDTreeNode(points[median]);
    n->left = buildTree(points, start, median - 1, (currDim+1) % Dim);
    n->right = buildTree(points, median + 1, end, (currDim+1) % Dim);
    return n;
}

template <int Dim>
void KDTree<Dim>::quickSelect(vector<Point<Dim>> &points, int start, int end, int k, int currDim) {
    if(start>=end) return;
    int index = partition(points, start, end, currDim);
    if (index > k) {
        return quickSelect(points, start, index - 1, k, currDim);
    } 
    if (index < k) {
        return quickSelect(points, index + 1, end, k , currDim);
    }
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> &points, int start, int end, int currDim) {
    Point<Dim> pivot = points[end];
    int curr = start;
    for (int i = start; i < end; i++) {
        if (smallerDimVal(points[i], pivot, currDim)) {
            swap(points[curr], points[i]);
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

