#pragma once

class MultiSkipList
{
    using uint = unsigned int;
    static constexpr unsigned int MAX_LEVEL = 64;
    struct Node
    {
        Node(double key, uint level) : key(key), repeated(1), level(level)
        {
            forward = new Node*[level];
            for (uint i = 0; i < level; i++) {
                forward[i] = nullptr;
            }
        }

        ~Node()
        {
            delete [] forward;
        }

        double key;
        uint repeated;
        uint level;
        Node** forward;
    };

public:
    MultiSkipList();
    ~MultiSkipList();

    void insert(double value);
    uint size() {
        return len;
    }

private:
    unsigned int randomLevel() const;

    Node* head;
    uint len;
};
