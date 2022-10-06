#include <bits/stdc++.h>
using namespace std;

int hash_string(string str, int n_ = 65407)
{
    long long n = n_;
    long long sum = 0;
    int base = 2 * 26 + 10; // lower + upper + digits

    for (int i = 0; i < (int)str.size(); i++)
    {
        // lower [0 - 25], upper [26 - 51], digits [52 - 61]
        int value = 0;
        if (islower(str[i]))
            value = str[i] - 'a';
        else if (isupper(str[i]))
            value = 26 + str[i] - 'A';
        else if (isdigit(str[i]))
            value = 2 * 26 + str[i] - '0';
        else
            assert(false);

        sum = (sum * base + value) % n;
    }

    return sum;
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

class PhoneHashTable
{
private:
    int table_size;
    vector<PhoneEntry *> table;
    // to mark cell as deleted
    PhoneEntry *deleted = new PhoneEntry("", "");

public:
    PhoneHashTable(int table_size) : table_size(table_size)
    {
        table.resize(table_size);
    }
};

int main()
{

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}