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

    void auto_complete(const string &str, vector<string> &res)
    {
        Trie *cur = this;
        for (int i = 0; i < (int)str.size(); i++)
        {
            int ch = str[i] - 'a';

            if (!cur->child[ch])
                return;

            cur = cur->child[ch];
        }
        cur->get_all_strings(res, str);
    }

    bool word_exist_with_1_change(string str)
    {
        // O(L * 26 * L)
        for (int i = 0; i < (int)str.size(); i++)
        {
            char cpy = str[i];
            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                str[i] = ch;
                if (ch == cpy)
                    continue;

                if (word_exist(str))
                    return true;
            }
            str[i] = cpy;
        }
        return false;
    }
};

void word_exist_test()
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

void word_exist_iterative_test()
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

void first_word_prefix_test()
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

void get_all_strings_test()
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

void auto_complete_test()
{
    Trie tr;
    tr.insert_iterative("a");
    tr.insert_iterative("abcd");
    tr.insert_iterative("xyz");
    tr.insert_iterative("abx");
    tr.insert_iterative("ab");
    tr.insert_iterative("abyz");
    tr.insert_iterative("bcd");

    vector<string> res;
    tr.auto_complete("ab", res);

    for (string s : res)
        cout << s << endl;
}

void word_exist_with_1_change_test()
{
    Trie tr;
    tr.insert_iterative("hello");
    tr.insert_iterative("leetcode");

    cout << tr.word_exist_with_1_change("xello") << endl;    // 1
    cout << tr.word_exist_with_1_change("xyllo") << endl;    // 0
    cout << tr.word_exist_with_1_change("hello") << endl;    // 0
    cout << tr.word_exist_with_1_change("leatcode") << endl; // 1
}
int main()
{

    // word_exist_test();
    // word_exist_iterative_test();
    // first_word_prefix_test();
    // get_all_strings_test();
    // auto_complete_test();
    word_exist_with_1_change_test();

    // must see it, otherwise RTE
    cout
        << "\n\nNO RTE\n";
    return 0;
}