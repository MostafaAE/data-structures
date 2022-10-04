#include <bits/stdc++.h>
using namespace std;

class Trie
{
private:
    map<int, Trie *> child;
    bool isLeaf{};

public:
    void insert(string str)
    {
        Trie *cur = this;
        for (int i = 0; i < (int)str.size(); i++)
        {
            int ch = str[i] - 'a';
            if (!cur->child.count(ch))
                cur->child[ch] = new Trie();

            cur = cur->child[ch];
        }
        cur->isLeaf = true;
    }

    bool word_exist(string str)
    {
        Trie *cur = this;
        for (int i = 0; i < (int)str.size(); i++)
        {
            int ch = str[i] - 'a';
            if (!cur->child.count(ch))
                return false;

            cur = cur->child[ch];
        }
        return cur->isLeaf;
    }
};

void test1()
{
    Trie tr;
    tr.insert("abcdef");
    tr.insert("bcdef");

    cout << tr.word_exist("abcdef") << endl; // 1
    cout << tr.word_exist("abc") << endl;    // 0
    cout << tr.word_exist("def") << endl;    // 0
    cout << tr.word_exist("bcdef") << endl;  // 1
    cout << tr.word_exist("cdef") << endl;   // 0
}

int main()
{
    test1();
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}