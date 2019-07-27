#pragma once

using uint = unsigned int;
namespace  {
const uint MAX_LEVEL = 10;
} // namespace

struct Node
{
    Node(double key_, uint level_) : key(key_), repeated(1), level(level_)
    {
        for (uint i = 0; i < level_; i++) {
            forward[i] = nullptr;
        }
    }

    ~Node()
    {
    }

    double key;
    uint repeated;
    uint level;
    Node* forward[MAX_LEVEL];
};

class MultiSkipList
{
public:
    MultiSkipList();
    ~MultiSkipList();

    void insert(double value);

    uint size() {
        return len;
    }

    const Node* getHead() {
        return this->head;
    }

    const Node* getNext(const Node* n) {
        return n->forward[0];
    }

private:
    unsigned int randomLevel() const;

    Node* head;
    uint len;
};
