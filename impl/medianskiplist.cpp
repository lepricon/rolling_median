#include "../medianskiplist.h"
#include "random.h"

MedianSkipList::MedianSkipList()
    : head{new Node(0, MAX_LEVEL)}, median{head, 0}
{
   len = 0;
    for (uint i = 0; i < head->level; i++) {
        head->forward[i] = nullptr;
    }
    head->prev = nullptr;
    pcg32::seed();
}

MedianSkipList::~MedianSkipList()
{
    Node* p = head;
    while (p != nullptr) {
        Node* next = p->forward[0];
        delete p;
        p = next;
    }
    head = nullptr;
    len = 0;
}

void MedianSkipList::insert(int value)
{
    Node* update[MAX_LEVEL] = {nullptr};
    Node* cur = head;
    len++;

    for (int i = static_cast<int>(head->level-1); i >= 0; i--) {
        while (cur->forward[i] != nullptr and cur->forward[i]->key < value) {
            cur = cur->forward[i];
        }
        update[i] = cur;
    }

    auto next = update[0]->forward[0];
    if (next != nullptr and next->key == value) {
        next->repeated++;
        updateMedian(value);
        return;
    }

    Node* newNode = new Node(value, randomLevel());
    for (uint i = 0; i < newNode->level; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
    newNode->prev = update[0];
    if (newNode->forward[0] != nullptr) {
        newNode->forward[0]->prev = newNode;
    }
    updateMedian(value);
}

uint MedianSkipList::randomLevel() const
{
    constexpr static double PROBABILITY = 0.5;
    uint l = 1;
    while (static_cast<double>(pcg32::random())/UINT32_MAX < PROBABILITY and l < MAX_LEVEL) {
        l++;
    }
    return l;
}

double MedianSkipList::getMedian()
{
    if (len == 0) {
        throw std::runtime_error("error: incorrect input, median request w/o data");
    }

    if (len % 2 == 0) {
        if (median.index == median.p->repeated) {
            return static_cast<double>(median.p->key) / 2.0 + static_cast<double>(getNext(median.p)->key) / 2.0;
        }
        else {
            return static_cast<double>(median.p->key) / 2.0 + static_cast<double>(median.p->key) / 2.0;
        }
    }
    else {
        return static_cast<double>(median.p->key);
    }
}

void MedianSkipList::updateMedian(int newValue)
{
    if (len == 1) {
        median.p = getNext(head);
        median.index = 1;
        return;
    }
    if (newValue == median.p->key) {
        if (len % 2 != 0) {
            median.index++;
        }
    }
    else if (newValue < median.p->key) {
        if (len % 2 == 0) {
            if (median.index == 1) {
                median.p = median.p->prev;
                median.index = median.p->repeated;
            }
            else {
                median.index--;
            }
        }
    }
    else if (newValue > median.p->key) {
        if (len % 2 != 0) {
            if (median.index == median.p->repeated) {
                median.p = getNext(median.p);
                median.index = 1;
            }
            else {
                median.index++;
            }
        }
    }
}


