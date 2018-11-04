#ifndef ALGORITHMS_STITCHED_WOOD_H
#define ALGORITHMS_STITCHED_WOOD_H

#include <string>
#include <queue>
#include <string>
#include <fstream>

struct TreeNode
{
    int value;
    TreeNode *left, *right;
    bool rthread;
    TreeNode *parent;
    unsigned depth;

    TreeNode(int data, unsigned depth);
};

std::string readPath(char *argv[]);

std::vector<std::string> readFile(const std::string &path);

TreeNode *addNode(TreeNode *root, TreeNode *parent, std::queue<std::string> &file);

TreeNode *deleteNode(TreeNode *node);

TreeNode *deleteNodeByValue(TreeNode *root, int value);

void showTree(TreeNode *root);

int getIntFromString(std::string str);

#endif //ALGORITHMS_STITCHED_WOOD_H
