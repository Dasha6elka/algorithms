#ifndef ALGORITHMS_STITCHED_WOOD_H
#define ALGORITHMS_STITCHED_WOOD_H

#include <string>
#include <queue>
#include <string>
#include <fstream>

typedef char * TreeValue;

struct TreeNode
{
    TreeValue value;
    TreeNode *left, *right;
    bool rthread;
    TreeNode *parent;
    unsigned depth;

    TreeNode(TreeValue data, unsigned depth);
};

std::string readPath(char *argv[]);

std::vector<std::string> readFile(const std::string &path);

TreeNode *addNode(TreeNode *root, TreeNode *parent, std::queue<std::string> &file);

TreeNode *deleteNode(TreeNode *node);

TreeNode *deleteNodeByValue(TreeNode *root, TreeValue value);

void showTree(TreeNode *root);

#endif //ALGORITHMS_STITCHED_WOOD_H
