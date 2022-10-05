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
        memset(child, 0, sizeof(child));
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

    void insert_iterative(string str)
    {
        Trie *cur = this;
        for (int i = 0; i < (int)str.size(); i++)
        {
            int ch = str[i] - 'a';

            if (!cur->child[ch])
                cur->child[ch] = new Trie();

            cur = cur->child[ch];
        }
        cur->isLeaf = true;
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

    bool word_exist_iterative(string str)
    {
        Trie *cur = this;
        for (int i = 0; i < (int)str.size(); i++)
        {
            int ch = str[i] - 'a';

            if (!cur->child[ch])
                return false;

            cur = cur->child[ch];
        }
        return cur->isLeaf;
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

    string first_word_prefix(const string &str)
    {
        Trie *cur = this;

        for (int i = 0; i < (int)str.size(); i++)
        {

            int ch = str[i] - 'a';

            if (!cur->child[ch])
                break;

            cur = cur->child[ch];

            if (cur->isLeaf)
                return str.substr(0, i + 1);
        }
        return str;
    }

    // O(NL) where N is the number of words and L is the word length
    void get_all_strings(vector<string> &res, string cur_str = "")
    {
        if (this->isLeaf)
            res.push_back(cur_str);

        for (int i = 0; i < MAX_CHAR; i++)
        {
            if (child[i])
                child[i]->get_all_strings(res, cur_str + (char)('a' + i));
        }
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

    cout << tr.prefix_exist("abc") << endl; // 1
    cout << tr.prefix_exist("def") << endl; // 0
    cout << tr.prefix_exist("bcd") << endl; // 1

    tr.insert("defmosta");
    cout << tr.prefix_exist("def") << endl; // 1
}

void test2()
{
    Trie tr;
    tr.insert_iterative("abcdef");
    tr.insert_iterative("bcdef");

    cout << tr.word_exist_iterative("abcdef") << endl; // 1
    cout << tr.word_exist_iterative("abc") << endl;    // 0
    cout << tr.word_exist_iterative("def") << endl;    // 0
    cout << tr.word_exist_iterative("bcdef") << endl;  // 1
    cout << tr.word_exist_iterative("cdef") << endl;   // 0
}

void test3()
{
    Trie tr;
    tr.insert_iterative("xyz");
    tr.insert_iterative("xyzea");
    tr.insert_iterative("a");
    tr.insert_iterative("bc");

    cout << tr.first_word_prefix("x") << endl;      // x
    cout << tr.first_word_prefix("xyzabc") << endl; // xyz
    cout << tr.first_word_prefix("bcabce") << endl; // bc
    cout << tr.first_word_prefix("xyzq") << endl;   // xyz
    cout << tr.first_word_prefix("azz") << endl;    // a
}

void test4()
{
    Trie tr;
    tr.insert_iterative("abcd");
    tr.insert_iterative("xyz");
    tr.insert_iterative("a");
    tr.insert_iterative("ab");
    tr.insert_iterative("xyzw");
    tr.insert_iterative("bcd");

    vector<string> res;
    tr.get_all_strings(res);

    for (string s : res)
        cout << s << endl;
}

int main()
{

    // test1();
    // test2();
    // test3();
    test4();

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}