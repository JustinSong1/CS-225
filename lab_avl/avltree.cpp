/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* y = t->right;
    t->right = y->left;
    y->left = t;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = y;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* y = t->left;
    t->left = y->right;
    y->right = t;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = y;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
   if (subtree == nullptr) return;
   int b = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
   if(b < -1) {
       int bl = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
       if(bl < 0) {
           rotateRight(subtree);
       } else {
           rotateLeftRight(subtree);
       }
   } else if (b > 1) {
       int br = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
       if(br > 0) {
           rotateLeft(subtree);
       } else {
           rotateRightLeft(subtree);
       }
   }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == nullptr) {
        subtree = new Node(key, value);
    } else if (key < subtree -> key){
        insert(subtree->left, key, value);
        rebalance(subtree);
    } else if (key > subtree -> key) {
        insert(subtree->right, key, value);
        rebalance(subtree);
    } else {
        subtree->value = value;
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            delete subtree;
            subtree = nullptr;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
           Node* iop = subtree->left;
           while(iop->right != nullptr) {
               iop = iop->right;
           }
           subtree->key = iop->key;
           subtree->value = iop ->value;
           remove(subtree->left, iop->key);
        } else {
           Node* node;
           if(subtree->left != nullptr) {
               node = subtree->left;
           } else {
               node = subtree->right;
           }
           *subtree = *node;
           delete node;
           node = nullptr;
        }
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    rebalance(subtree);
}
