#include <bits/stdc++.h>
using namespace std;

int hash_string(string str, int n)
{
    long long nn = n;
    long long sum = 0;
    for (int i = 0; i < (int)str.size(); i++)
        sum = (sum * 26 + str[i] - 'a') % nn;
    return sum % nn;
}

struct PhoneEntry
{
    const static int INTERNAL_LIMIT = 65407;
    string name;         // key
    string phone_number; // data

    int hash()
    {
        return hash_string(name, INTERNAL_LIMIT);
    }

    PhoneEntry(string name, string phone_number) : name(name), phone_number(phone_number) {}

    void print()
    {
        cout << "(" << name << ", " << phone_number << ")  ";
    }
};

int main()
{
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}