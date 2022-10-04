#include <bits/stdc++.h>
using namespace std;

class trie
{
private:
    static const int MAX_CHAR = 26;
    trie *child[MAX_CHAR];
    bool isLeaf{};

public:
    trie()
    {
        // set the child array pointers to nullptr
        memset(child, 0, size(child));
    }
};

int main()
{

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}