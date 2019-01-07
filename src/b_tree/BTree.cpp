#include <utility>
#include "BTree.h"

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

std::vector<std::pair<std::string, std::string>> fill(std::vector<std::string> result,
                                                      std::vector<std::pair<std::string, std::string>> &dict)
{
    while (!result.empty()) {
        std::string line = result.front();
        result.erase(result.begin());
        const std::string &str(line);
        std::string separ(" ");
        std::string::size_type pos = str.find(separ); // Позиция первого символа строки-разделителя.
        std::string key = str.substr(0, pos); // Строка до разделителя.
        std::string info = str.substr(pos + separ.length()); // Строка после разделителя.
        dict.emplace_back(key, info);
    }
    return dict;
}

std::string find(std::string &key, std::vector<std::pair<std::string, std::string>> &dictionary)
{
    for (const auto &item : dictionary) {
        if (key == item.first) {
            return item.second;
        }
    }
    return std::string();
}

void sync(const std::string &path, std::vector<std::pair<std::string, std::string>> &dictionary)
{
    std::ofstream ofs;
    ofs.open(path, std::ofstream::out | std::ofstream::trunc);
    for (const auto& item : dictionary) {
        ofs << item.first << ' ' << item.second << std::endl;
    }
    ofs.close();
}

void remove(std::string &key, std::vector<std::pair<std::string, std::string>> &dictionary)
{
    int index = 0;
    for (const auto &item : dictionary) {
        if (key == item.first) {
            dictionary.erase(dictionary.begin() + index);
        }
        index++;
    }
}

// Инициализация
BTreeNode::BTreeNode(int t1, bool leaf1)
{
    minimumDegree = t1;
    leaf = leaf1;
    keys = new int[2 * minimumDegree - 1];
    childPointers = new BTreeNode *[2 * minimumDegree];
    n = 0;
}

// Удаление
void BTreeNode::remove(int k)
{
    int idx = findKey(k);

    if (idx < n && keys[idx] == k) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            std::cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }
        bool flag = idx == n;
        if (childPointers[idx]->n < minimumDegree)
            fill(idx);
        if (flag && idx > n)
            childPointers[idx - 1]->remove(k);
        else
            childPointers[idx]->remove(k);
    }
}

// Поиск ключа текущеё ноды
int BTreeNode::findKey(int k)
{
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

// Удаление ноды из листа
void BTreeNode::removeFromLeaf(int idx)
{
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    n--;
}

// Удаление не из листа
void BTreeNode::removeFromNonLeaf(int idx)
{

    int k = keys[idx];

    if (childPointers[idx]->n >= minimumDegree) {
        int pred = getPred(idx);
        keys[idx] = pred;
        childPointers[idx]->remove(pred);
    } else if (childPointers[idx + 1]->n >= minimumDegree) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        childPointers[idx + 1]->remove(succ);
    } else {
        merge(idx);
        childPointers[idx]->remove(k);
    }
}

// Взятие ключа предыдущей ноды
int BTreeNode::getPred(int idx)
{
    BTreeNode *cur = childPointers[idx];
    while (!cur->leaf)
        cur = cur->childPointers[cur->n];
    return cur->keys[cur->n - 1];
}

// Нахождение первой левой листовой ноды
int BTreeNode::getSucc(int idx)
{
    BTreeNode *cur = childPointers[idx + 1];
    while (!cur->leaf)
        cur = cur->childPointers[0];
    return cur->keys[0];
}

// Заполнение child, если их мало
void BTreeNode::fill(int idx)
{
    if (idx != 0 && childPointers[idx - 1]->n >= minimumDegree)
        borrowFromPrev(idx);

    else if (idx != n && childPointers[idx + 1]->n >= minimumDegree)
        borrowFromNext(idx);

    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
}

// Сливание нод
void BTreeNode::merge(int idx)
{
    BTreeNode *child = childPointers[idx];
    BTreeNode *sibling = childPointers[idx + 1];

    child->keys[minimumDegree - 1] = keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + minimumDegree] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->childPointers[i + minimumDegree] = sibling->childPointers[i];
    }

    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= n; ++i)
        childPointers[i - 1] = childPointers[i];

    child->n += sibling->n + 1;
    n--;
    delete (sibling);
}

// Взятие child у предыдущей ноды
void BTreeNode::borrowFromPrev(int idx)
{
    BTreeNode *child = childPointers[idx];
    BTreeNode *sibling = childPointers[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->childPointers[i + 1] = child->childPointers[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf)
        child->childPointers[0] = sibling->childPointers[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

// Взятие child у следующей ноды
void BTreeNode::borrowFromNext(int idx)
{

    BTreeNode *child = childPointers[idx];
    BTreeNode *sibling = childPointers[idx + 1];

    child->keys[(child->n)] = keys[idx];

    if (!(child->leaf))
        child->childPointers[(child->n) + 1] = sibling->childPointers[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->childPointers[i - 1] = sibling->childPointers[i];
    }
    child->n += 1;
    sibling->n -= 1;
}

// Сортировка и вывод
void BTreeNode::traverse(int depth)
{
    int index;
    std::cout << std::string(static_cast<unsigned long>(depth * 2), ' ') << "[";
    for (index = 0; index < n; index++) {
        std::cout << keys[index];
        if (index != n - 1) {
            std::cout << " ";
        }
    }
    int nextDepth = ++depth;
    std::cout << "]" << std::endl;
    for (index = 0; index < n; index++) {
        if (!leaf) {
            childPointers[index]->traverse(nextDepth);
        }
    }
    if (!leaf) {
        childPointers[index]->traverse(nextDepth);
    }
}

// Поиск
BTreeNode *BTreeNode::search(int k)
{
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf)
        return nullptr;

    return childPointers[i]->search(k);
}

// Удаление
void BTree::remove(int k)
{
    if (!root) {
        std::cout << "The tree is empty\n";
        return;
    }

    root->remove(k);

    if (root->n == 0) {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->childPointers[0];

        delete tmp;
    }
}

// Добавление
void BTree::insert(int k)
{
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // Insert key
        root->n = 1;  // Update number of keys in root
    } else {
        if (root->n == 2 * t - 1) {
            auto *s = new BTreeNode(t, false);

            s->childPointers[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->childPointers[i]->insertNonFull(k);

            root = s;
        } else root->insertNonFull(k);
    }
}

void BTree::traverse()
{
    if (root != nullptr) root->traverse(0);
}

BTree::BTree(int _t)
{
    root = nullptr;
    t = _t;
}

BTreeNode *BTree::search(int k)
{
    return (root == nullptr)? nullptr : root->search(k);
}

// Вставка, если страница слишком мала
void BTreeNode::insertNonFull(int k)
{
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (childPointers[i + 1]->n == 2 * minimumDegree - 1) {
            splitChild(i + 1, childPointers[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        childPointers[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y)
{
    auto *z = new BTreeNode(y->minimumDegree, y->leaf);
    z->n = minimumDegree - 1;

    for (int j = 0; j < minimumDegree - 1; j++)
        z->keys[j] = y->keys[j + minimumDegree];

    if (!y->leaf) {
        for (int j = 0; j < minimumDegree; j++)
            z->childPointers[j] = y->childPointers[j + minimumDegree];
    }

    y->n = minimumDegree - 1;

    for (int j = n; j >= i + 1; j--)
        childPointers[j + 1] = childPointers[j];

    childPointers[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[minimumDegree - 1];

    n = n + 1;
}
