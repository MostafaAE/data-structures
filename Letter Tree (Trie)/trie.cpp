#include <bits/stdc++.h>
using namespace std;

class Trie
{
private:
    static const int MAX_CHAR = 26;
    Trie *child[MAX_CHAR];
    bool isLeaf{};

public:
    Trie()
    {
        // set the child array pointers to nullptr
        memset(child, 0, size(child));
    }

    void insert(string str, int idx = 0)
    {

        if (idx == (int)str.size())
            this->isLeaf = true;

        else
        {
            // get the index of the letter
            int cur = str[idx] - 'a';
            if (!child[cur])
                child[cur] = new Trie();

            child[cur]->insert(str, idx + 1);
        }
    }
};

int main()
{
    Trie tr;
    tr.insert("abcdef");
    tr.insert("bcdef");
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}