#include "chunkallocator.h"
#include <new>

ChunkAllocator::ChunkAllocator(const uint chunkSizeInNodes_)
    : chunkSizeInNodes(chunkSizeInNodes_)
{
    numChunks = 1;
    chunks = new char*[numChunks];
    chunks[0] = new char[sizeof (Node) * chunkSizeInNodes_];
    firstEmtySlot = 0;
}

ChunkAllocator::~ChunkAllocator()
{
    for (uint i = 0; i < numChunks; ++i) {
        delete [] chunks[i];
    }
    delete [] chunks;
}

Node* ChunkAllocator::allocateNode(int key, uint level)
{
    if (firstEmtySlot == chunkSizeInNodes) {
        // add another chunk
        char** biggerChunks = new char*[numChunks + 1];
        for (uint i = 0; i < numChunks; ++i) {
            biggerChunks[i] = chunks[i];
        }
        delete chunks;
        numChunks += 1;
        chunks = biggerChunks;
        chunks[numChunks - 1] = new char[sizeof (Node) * chunkSizeInNodes];
        firstEmtySlot = 0;
    }
    // always assing from the last chunk
    char* ptr = chunks[numChunks - 1] + sizeof (Node) * firstEmtySlot;
    firstEmtySlot++;
    return new (ptr) Node(key, level);
}
