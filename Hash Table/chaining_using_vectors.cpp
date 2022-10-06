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

class PhoneHashTable
{
private:
    int table_size;
    vector<vector<PhoneEntry>> table;

public:
    PhoneHashTable(int table_size) : table_size(table_size)
    {
        table.resize(table_size);
    }

    void put(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < (int)table[idx].size(); i++)
        {
            // entry exists
            if (table[idx][i].name == phone.name)
            {
                table[idx][i].phone_number = phone.phone_number;
                return;
            }
        }
        // entry does not exist
        table[idx].push_back(phone);
    }

    void print_all()
    {
        for (int hash = 0; hash < table_size; hash++)
        {
            if (table[hash].size() == 0)
                continue;

            cout << "Hash " << hash << ": ";
            for (int i = 0; i < (int)table[hash].size(); i++)
                table[hash][i].print();
            cout << "\n";
        }
    }
};

int main()
{
    PhoneHashTable table(3);
    table.put(PhoneEntry("mostafa", "604-401-120"));
    table.put(PhoneEntry("mostafa", "604-401-777")); // update
    table.put(PhoneEntry("ali", "604-401-343"));
    table.put(PhoneEntry("ziad", "604-401-17"));
    table.put(PhoneEntry("hany", "604-401-758"));
    table.put(PhoneEntry("belal", "604-401-550"));
    table.put(PhoneEntry("john", "604-401-223"));

    table.print_all();
    /*
    Hash 0: (ali, 604-401-343)  (hany, 604-401-758)  (john, 604-401-223)
    Hash 1: (mostafa, 604-401-777)  (ziad, 604-401-17)
    Hash 2: (belal, 604-401-550)
    */

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}