/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  return List<T>::ListIterator(tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode* curr = head_;
  ListNode* next;
  while(curr != nullptr) {
      next = curr->next;
      delete curr;
      curr = next;
  }
  head_ = nullptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  std::cout << "HEAD: " << head_;
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = nullptr;
  
  if (head_ != nullptr) {
    head_ -> prev = newNode;
    head_ = newNode;
  } else {
    head_ = newNode;
  }

  if (tail_ == nullptr) {
    tail_ = newNode;
  }

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
    ListNode * newNode = new ListNode(ndata);
    newNode -> next = NULL;
    newNode -> prev = tail_;

    if(head_ == NULL) {
      head_ = newNode;
    }

    if(tail_ != NULL) {
      tail_ -> next = newNode;
      tail_ = newNode;
    } else {
      tail_ = newNode;
    }
    length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }
  

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  size_t times = length_ / 3;
  ListNode* curr = head_;
  for(size_t count = 0; count < times; count++) {
    if(count == 0) {
      head_ = curr->next;
    } else {
      curr->prev->next = curr->next;
    }
    curr->next->prev = curr->prev;  
    curr->next = curr->next->next->next;
    if(count == times-1 && length_%3 == 0) {
      curr->prev = tail_;
      tail_->next = curr;
      tail_ = curr;
    } else {
      curr->prev = curr->next->prev;
      curr->next->prev->next= curr;
      curr->next->prev = curr;
      curr = curr->next;
    }  
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if(startPoint == endPoint || startPoint == NULL) {
    return;
  }

  bool updateHead = (startPoint == head_);
  bool updateTail = (endPoint == tail_);

  ListNode* previous = startPoint -> prev;
  ListNode* nextNode = endPoint -> next;
 
  ListNode* tempStart = startPoint->next->prev;
  ListNode* tempEnd = endPoint->prev->next;

  ListNode* curr = startPoint;
  ListNode* temp = NULL;
  bool firstRun = true;
  while(curr != endPoint) {
    temp = curr->prev;
    curr->prev = curr->next;
    if(updateTail && firstRun) {
      curr ->next = NULL;
    } else {
      curr->next = temp;
    }
    curr = curr->prev;
    firstRun = false;
  }
  temp = curr->prev;
  curr->prev = curr->next;
  curr->next = temp;
  curr = curr->prev;

  if(temp != NULL && updateHead) {
    head_ = temp->prev;
  }
  if(updateTail) {
    ListNode* newTail = temp;
    while(newTail->next != NULL) {
      newTail = newTail->next;
    }
    tail_ = newTail;
  }

  tempEnd->prev = previous;
  if(previous != NULL) {
    previous->next = tempEnd;
  }

  tempStart->next = nextNode;
  if(startPoint->next != NULL) {
    nextNode->prev = tempStart;
  }

  temp=startPoint;
  startPoint = endPoint;
  endPoint = temp;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if(n == length_ || n==1) {
    reverse();
  }
  if(n < 1) {
    return;
  }
  ListNode* start = head_;
  int times = length_/n;
  for(int i = 0; i < times; i++) {
    ListNode* end = start;
    for(int j = 0; j < n-1; j++) {
      end = end->next;
    }
    reverse(start, end);
    start = end->next;
  }
  if(length_ % n != 0) {
    reverse(start, tail_);
  }
  // ListNode* start = head_;
  // ListNode* end = tail_->prev;
  
  // reverse(start, end);
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  if(first == NULL) {
    return second;
  }
  if(second == NULL) {
    return first;
  }
  ListNode* newHead;
  if(first -> data < second -> data) {
    newHead = first;
    first = first->next;
  } else {
    newHead = second;
    second = second->next;
  }
  ListNode* newTail = newHead;
  while(first != NULL && second != NULL) {
    ListNode* temp;
    if(first -> data < second -> data) {
      temp = first;
      first = first->next;
    } else {
      temp = second;
      second = second->next;
    }
    temp->prev = newTail;
    newTail->next = temp;
    newTail = temp;
  }
  if(first != NULL) {
    first->prev = newTail;
    newTail->next = first;
  } else if(second != NULL) {
    second->prev = newTail;
    newTail->next = second;
  }
  return newHead;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  return NULL;
}
