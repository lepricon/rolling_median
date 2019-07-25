#include "multiskiplist.h"
#include <cstdint>
#include <ctime>

namespace pcg32 {
// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)

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

void seed(uint64_t seed, uint64_t seq)
{
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


MultiSkipList::MultiSkipList()
    : head{new Node(0, MAX_LEVEL)}
{
    for (uint i = 0; i < head->level; i++) {
        head->forward[i] = nullptr;
    }
    pcg32::seed(::time(nullptr), reinterpret_cast<uint64_t>(head));
}

MultiSkipList::~MultiSkipList()
{
    Node* p = head;
    while (p != nullptr) {
        Node* next = p->forward[0];
        delete p;
        p = next;
    }
}

void MultiSkipList::insert(double value)
{

}

MultiSkipList::uint MultiSkipList::randomLevel() const
{
    const double probability = 0.5;
    uint l = 1;
    while (static_cast<double>(pcg32::random())/UINT32_MAX < probability and l < MAX_LEVEL) {
        l++;
    }

    return l;
}
