#include <string>
#include <algorithm>
#include <queue>
#include <sstream>
#include <iostream>

#include "stitched_wood.h"

std::string readPath(char *argv[])
{
    return argv[1];
}

std::vector<std::string> readFile(const std::string &path)
{
    std::vector<std::string> result{};
    std::string line;
    std::ifstream input;
    input.open(path);
    if (!input.is_open()) {
        throw "Cannot open file " + path;
    }
    while (std::getline(input, line)) {
        result.push_back(line);
        line.clear();
    }
    return result;
}

void showTree(TreeNode *root)
{
    if (root != nullptr) {

        std::string indent(root->depth, '-');
        std::cout << indent << ' ' << root->value << std::endl;
        if (root->rthread) {
            return;
        }
        showTree(root->left);
        showTree(root->right);
    }
}

TreeNode *addNode(TreeNode *root, TreeNode *parent, std::queue<std::string> &file)
{
    if (file.empty()) {
        return root;
    }
    if (root != nullptr && root->right != parent) {
        root->rthread = false;
    }
    auto line = file.front();
    auto depth = std::count(line.begin(), line.end(), '-');
    if (parent != nullptr && depth == parent->depth) {
        return root;
    }
    if (parent != nullptr && depth < parent->depth) {
        return root;
    }
    file.pop();
    root = new TreeNode(getIntFromString(line), static_cast<unsigned>(depth));
    root->parent = parent;
    if (parent != nullptr) {
        root->right = parent;
    }
    root->left = addNode(root->left, root, file);
    root->right = addNode(root->right, root, file);
    return root;
}

int getIntFromString(std::string str)
{
    std::stringstream ss;
    ss << str;
    std::string temp;
    int found;
    while (!ss.eof()) {
        ss >> temp;
        if (std::stringstream(temp) >> found) {
            temp = "";
        }
    }
    return found;
}

TreeNode *deleteNode(TreeNode *node)
{
    if (node != nullptr) {
        if (node->rthread) {
            return node;
        }
        deleteNode(node->left);
        deleteNode(node->right);
    } else {
        return node;
    }

    TreeNode *root = node;

    while (root->parent != nullptr) {
        root = root->parent;
    }

    TreeNode *parent = node->parent;

    if (parent == nullptr) {
        return nullptr;
    }

    if (parent->left == node) {
        free(parent->left);
        parent->left = nullptr;
    } else if (parent->right == node) {
        free(parent->right);
        parent->right = nullptr;
    }

    return root;
}

TreeNode *deleteNodeByValue(TreeNode *root, int value)
{
    TreeNode *nextRoot = root;
    if (root != nullptr && root->value == value) {
        nextRoot = deleteNode(root);
    } else {
        if (root) {
            if (root->rthread) {
                return root;
            }
            deleteNodeByValue(root->left, value);
            deleteNodeByValue(root->right, value);
        }
    }
    return nextRoot;
}

TreeNode::TreeNode(int data, unsigned depth) : value(data), depth(depth)
{
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    rthread = true;
}

