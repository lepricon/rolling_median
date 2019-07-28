#pragma once
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
