#pragma once

using uint = unsigned int;
namespace  {
const uint MAX_LEVEL = 20;
} // namespace

struct Node
{
    Node(int key_, uint level_) : key(key_), repeated(1), level(level_)
    {
        for (uint i = 0; i < level_; i++) {
            forward[i] = nullptr;
        }
        prev = nullptr;
    }

    ~Node()
    {
    }

    int key;
    uint repeated;
    uint level;
    Node* forward[MAX_LEVEL];
    Node* prev;
};

class MedianSkipList
{
struct Median
{
    const Node* p;
    uint index; // starting from 1
};

public:
    MedianSkipList();
    ~MedianSkipList();

    void insert(int value);

    uint size() const {
        return len;
    }

    double getMedian();

    const Node* getHead() const {
        return this->head;
    }

    const Node* getNext(const Node* n) const {
        return n->forward[0];
    }

private:
    unsigned int randomLevel() const;
    void updateMedian(int newValue);

    Node* head;
    uint len;
    Median median;
};
