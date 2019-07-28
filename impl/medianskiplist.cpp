#include "../medianskiplist.h"
#include <cstdint>
#include <fstream>

namespace pcg32 {
// based on *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
static struct RandomState
{
    uint64_t state;
    uint64_t inc;
} globalState = { 0x853c49e6748fea9bULL, 0xda3e39cb94b95bdbULL };

uint32_t random_r(RandomState& rng)
{
    uint64_t oldstate = rng.state;
    // Advance internal state
    rng.state = oldstate * 6364136223846793005ULL + (rng.inc | 1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

void seed()
{
    uint64_t seed{5260921825093978833ULL};
    uint64_t seq{18270956999296599992ULL};
    std::ifstream randomDevice("/dev/urandom", std::ios::in|std::ios::binary);
    if (randomDevice) {
        randomDevice.read(reinterpret_cast<char*>(&seed), sizeof (seed));
        randomDevice.read(reinterpret_cast<char*>(&seq), sizeof (seq));
    }
    globalState.state = 0U;
    globalState.inc = (seq << 1u) | 1u;
    random_r(globalState);
    globalState.state += seed;
    random_r(globalState);
}

uint32_t random()
{
    return random_r(globalState);
}
} // namespace pcg32

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
        throw std::runtime_error("error: no input yet");
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
