
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return currentIdx*2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return currentIdx * 2 < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);
    if (right >= _elems.size()) {
        return left;
    } else {
        if(higherPriority(_elems[left], _elems[right])) {
            return left;
        } else {
            return right;
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (hasAChild(currentIdx)) {
        size_t maxPrio = maxPriorityChild(currentIdx);
        if (higherPriority(_elems[maxPrio], _elems[currentIdx])) {
            std::swap( _elems[maxPrio], _elems[currentIdx]);
            heapifyDown(maxPrio);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
   _elems.push_back(T());
   for(T elem : elems) {
       _elems.push_back(elem);
   }
   for(size_t i = _elems.size() - 1; i > 0; i--) {
       heapifyDown(i);
   }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if(empty()) return T();
    T result = _elems[1];
    std::swap(_elems[1], _elems.back());
    _elems.pop_back();
    heapifyDown(1);
    return result;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
   _elems.push_back(elem);
   heapifyUp(_elems.size() - 1);
   return;
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    _elems[idx] = elem;
    if (higherPriority(elem, _elems[parent(idx)])) {
        heapifyUp(idx);
    } else {
        heapifyDown(idx);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return _elems.size() == 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
