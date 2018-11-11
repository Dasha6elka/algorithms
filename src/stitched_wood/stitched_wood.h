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
    bool threads;
    bool hasThread;
    TreeNode *thread;
    TreeNode *parent;
    unsigned depth;

    TreeNode(TreeValue data, unsigned depth);
};

std::string readPath(char *argv[]);

std::vector<std::string> readFile(const std::string &path);

TreeNode *addNode(TreeNode *root, TreeNode *parent, std::queue<std::string> &file);

TreeNode *deleteNode(TreeNode *node);

TreeNode *deleteNodeByValue(TreeNode *root, TreeValue value);

TreeNode *getNodeByValue(TreeNode *root, TreeValue value);

TreeNode *stitch(TreeNode *root);

void trim(std::string &str);

void showTree(TreeNode *root, TreeNode *referenceRoot);

void showThreads(TreeNode *root);

#endif //ALGORITHMS_STITCHED_WOOD_H
