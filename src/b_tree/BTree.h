#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef ALGORITHMS_BTREE_H
#define ALGORITHMS_BTREE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>

// A BTree node
class BTreeNode
{
    int *keys;  // An array of keys
    int minimumDegree;      // Minimum degree (defines the range for number of keys)
    BTreeNode **childPointers; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false

public:
    std::string info;

    BTreeNode(int _t, bool _leaf);   // Constructor

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse(int depth);

    // A function to search a key in subtree rooted with this node.
    BTreeNode *search(int k);   // returns NULL if k is not present.

    // A function that returns the index of the first key that is greater
    // or equal to k
    int findKey(int k);

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k);

    // A utility function to split the child y of this node. i is index
    // of y in child array C[].  The Child y must be full when this
    // function is called
    void splitChild(int i, BTreeNode *y);

    // A wrapper function to remove the key k in subtree rooted with
    // this node.
    void remove(int k);

    // A function to remove the key present in idx-th position in
    // this node which is a leaf
    void removeFromLeaf(int idx);

    // A function to remove the key present in idx-th position in
    // this node which is a non-leaf node
    void removeFromNonLeaf(int idx);

    // A function to get the predecessor of the key- where the key
    // is present in the idx-th position in the node
    int getPred(int idx);

    // A function to get the successor of the key- where the key
    // is present in the idx-th position in the node
    int getSucc(int idx);

    // A function to fill up the child node present in the idx-th
    // position in the C[] array if that child has less than minimumDegree-1 keys
    void fill(int idx);

    // A function to borrow a key from the C[idx-1]-th node and place
    // it in C[idx]th node
    void borrowFromPrev(int idx);

    // A function to borrow a key from the C[idx+1]-th node and place it
    // in C[idx]th node
    void borrowFromNext(int idx);

    // A function to merge idx-th child of the node with (idx+1)th child of
    // the node
    void merge(int idx);

    // Make BTree friend of this so that we can access private members of
    // this class in BTree functions
    friend class BTree;
};

class BTree
{
    BTreeNode *root; // Pointer to root node
    int t;  // Minimum degree
public:

    // Constructor (Initializes tree as empty)
    explicit BTree(int _t);

    void traverse();

    // function to search a key in this tree
    BTreeNode* search(int k);

    // The main function that inserts a new key in this B-Tree
    void insert(int k);

    // The main function that removes a new key in thie B-Tree
    void remove(int k);

};

std::string readPath(char *argv[]);

std::vector<std::string> readFile(const std::string &path);

std::vector<std::pair<std::string, std::string>> fill(
    std::vector<std::string> result,
    std::vector<std::pair<std::string, std::string>> &dict);

std::string find(std::string &key, std::vector<std::pair<std::string, std::string>> &dictionary);

void remove(std::string &key, std::vector<std::pair<std::string, std::string>> &dictionary);

void sync(const std::string& path, std::vector<std::pair<std::string, std::string>> &dictionary);

#endif //ALGORITHMS_BTREE_H

#pragma clang diagnostic pop
