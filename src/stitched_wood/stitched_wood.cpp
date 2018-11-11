#include <string>
#include <algorithm>
#include <queue>
#include <sstream>
#include <iostream>
#include <cstring>

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
        showTree(root->left);
        showTree(root->right);
    }
}

TreeNode *addNode(TreeNode *root, TreeNode *parent, std::queue<std::string> &file)
{
    if (file.empty()) {
        return root;
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
    line.erase(std::remove(line.begin(), line.end(), '-'), line.end());
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    root = new TreeNode(line.data(), static_cast<unsigned>(depth));
    root->parent = parent;
    root->left = addNode(root->left, root, file);
    root->right = addNode(root->right, root, file);
    return root;
}

TreeNode *deleteNode(TreeNode *node)
{
    if (node != nullptr) {
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

TreeNode *deleteNodeByValue(TreeNode *root, TreeValue value)
{
    TreeNode *nextRoot = root;
    if (root != nullptr) {
        const auto compare = strcmp(root->value, value);
        if (compare == 0) {
            nextRoot = deleteNode(root);
        } else {
            deleteNodeByValue(root->left, value);
            deleteNodeByValue(root->right, value);
        }
    }
    return nextRoot;
}

TreeNode::TreeNode(TreeValue data, unsigned depth) : depth(depth)
{
    std::size_t size = sizeof(TreeValue) / sizeof(char);
    value = static_cast<TreeValue>(malloc(size * sizeof(char)));
    strcpy(value, data);
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    rthread = false;
}

