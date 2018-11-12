#include <fstream>
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

void showTree(TreeNode *root, TreeNode *referenceRoot)
{
    if (referenceRoot != nullptr) {
        std::string indent(referenceRoot->depth, '-');
        if (root != nullptr) {
            std::cout << indent << ' ' << root->value << std::endl;
        } else {
            std::cout << indent << std::endl;
        }
        if (root != nullptr && root->threads) {
            return;
        }
        if (root != nullptr) {
            showTree(root->left, referenceRoot->left);
            showTree(root->right, referenceRoot->right);
        } else {
            showTree(nullptr, referenceRoot->left);
            showTree(nullptr, referenceRoot->right);
        }
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
    trim(line);
    root = new TreeNode(line.data(), static_cast<unsigned>(depth));
    root->parent = parent;
    root->left = addNode(root->left, root, file);
    root->right = addNode(root->right, root, file);
    return root;
}

TreeNode *deleteNode(TreeNode *node)
{
    TreeNode *root = node;

    while (root != nullptr && root->parent != nullptr) {
        root = root->parent;
    }

    if (node != nullptr) {
        if (node->hasThread && node->thread != nullptr) {
            auto thread = node->thread;
            if (node->threads) {
                thread->right = node->right;
            } else {
                thread->right = nullptr;
                thread->threads = false;
            }
            if (thread->right != nullptr && thread->right->thread != nullptr) {
                thread->right->thread = thread;
            }
            TreeNode *parent = node->parent;
            if (parent->left == node) {
                free(parent->left);
                parent->left = nullptr;
            } else if (parent->right == node) {
                free(parent->right);
                parent->right = nullptr;
            }
            return root;
        }
        if (!node->threads) {
            deleteNode(node->right);
        } else {
            auto right = node->right;
            if (right != nullptr) {
                right->thread = nullptr;
            }
        }
        deleteNode(node->left);
    } else {
        return node;
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

TreeNode *stitch(TreeNode *root)
{
    std::stack<TreeNode *> stack;
    std::vector<TreeNode *> list;
    stack.push(root);

    while (!stack.empty()) {
        auto current = stack.top();
        stack.pop();
        if (current != nullptr) {
            list.push_back(current);
            stack.push(current->right);
            stack.push(current->left);
        }
    }

    for (unsigned long long i = 0; i < list.size() - 1; ++i) {
        auto current = list.at(i);
        auto compare = strcmp(current->value, "");
        if (current->left == nullptr && current->right == nullptr && !current->threads && compare != 0) {
            current->right = list.at(i + 1);
            current->threads = true;
            current->right->thread = current;
            current->right->hasThread = true;
        }
    }

    return root;
}

TreeNode *getNodeByValue(TreeNode *root, TreeValue value)
{
    if (root != nullptr) {
        const auto compare = strcmp(root->value, value);
        if (compare == 0) {
            return root;
        } else {
            getNodeByValue(root->left, value);
            getNodeByValue(root->right, value);
        }
    }
    return root;
}

void trim(std::string &str)
{
    str.erase(std::remove(str.begin(), str.end(), '-'), str.end());
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

void showThreads(TreeNode *root)
{
    if (root != nullptr) {
        if (root->threads) {
            auto right = root->right;
            if (right == nullptr) {
                return;
            }
            std::cout << root->value << " -> " << right->value << std::endl;
        }
        showThreads(root->left);
        if (!root->threads) {
            showThreads(root->right);
        }
    }
}

TreeNode::TreeNode(TreeValue data, unsigned depth) : depth(depth)
{
    std::size_t size = sizeof(TreeValue) / sizeof(char);
    value = static_cast<TreeValue>(malloc(size * sizeof(char)));
    strcpy(value, data);
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    threads = false;
    thread = nullptr;
    hasThread = false;
}

