#pragma once

using uint = unsigned int;
namespace  {
const uint MAX_LEVEL = 20; // the list should be fast up to 2^MAX_LEVEL elements
} // namespace

struct Node
{
    Node(int key_, uint level_) : key(key_), repeated(1), level(level_)
    {
        for (uint i = 0; i < level; i++) {
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
