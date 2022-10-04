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

    bool word_exist(string str, int idx = 0)
    {
        if (idx == (int)str.size())
            return isLeaf; // there is a word marked here

        else
        {
            int cur = str[idx] - 'a';
            if (!child[cur])
                return false; // such path does not exist(word does not exist)

            return child[cur]->word_exist(str, idx + 1);
        }
    }

    bool prefix_exist(string str, int idx = 0)
    {
        if (idx == (int)str.size())
            return true; // all subword covered

        else
        {
            int cur = str[idx] - 'a';
            if (!child[cur])
                return false; // such path does not exist(word does not exist)

            return child[cur]->prefix_exist(str, idx + 1);
        }
    }
};

int main()
{

    Trie tr;
    tr.insert("abcdef");
    tr.insert("bcdef");

    cout << tr.word_exist("abcdef") << endl; // 1
    cout << tr.word_exist("abc") << endl;    // 0
    cout << tr.word_exist("def") << endl;    // 0
    cout << tr.word_exist("bcdef") << endl;  // 1
    cout << tr.word_exist("cdef") << endl;   // 0

    cout << tr.prefix_exist("abc") << endl; // 1
    cout << tr.prefix_exist("def") << endl; // 0
    cout << tr.prefix_exist("bcd") << endl; // 1

    tr.insert("defmosta");
    cout << tr.prefix_exist("def") << endl; // 1
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}