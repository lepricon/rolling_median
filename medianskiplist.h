#pragma once
#include "node.h"

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
