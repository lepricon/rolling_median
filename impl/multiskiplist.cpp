#include "../multiskiplist.h"
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

namespace  {
double fabs(double x) {
    *((reinterpret_cast<int *>(&x)) + 1) &= 0x7fffffff;
    return x;
}

bool equal(double a, double b)
{
    constexpr static double EPSILON = 1e-10;
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * EPSILON);
}
} // namespace

MultiSkipList::MultiSkipList()
    : head{new Node(0, MAX_LEVEL)}
{
    len = 0;
    for (uint i = 0; i < head->level; i++) {
        head->forward[i] = nullptr;
    }
    pcg32::seed();
}

MultiSkipList::~MultiSkipList()
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

void MultiSkipList::insert(double value)
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
    if (next != nullptr and equal(next->key, value)) {
        next->repeated++;
        return;
    }

    Node* newNode = new Node(value, randomLevel());
    for (uint i = 0; i < newNode->level; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

uint MultiSkipList::randomLevel() const
{
    constexpr static double PROBABILITY = 0.5;
    uint l = 1;
    while (static_cast<double>(pcg32::random())/UINT32_MAX < PROBABILITY and l < MAX_LEVEL) {
        l++;
    }

    return l;
}
