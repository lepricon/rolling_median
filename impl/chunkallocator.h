#pragma once
#include "../node.h"

class ChunkAllocator
{
public:
    ChunkAllocator(const uint chunkSizeInNodes);
    ~ChunkAllocator();

    Node* allocateNode(int key, uint level);

private:
    const uint chunkSizeInNodes;
    uint numChunks;
    char** chunks;
    uint firstEmtySlot;
};
