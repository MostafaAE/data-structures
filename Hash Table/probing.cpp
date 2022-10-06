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

    bool put(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;

        for (int step = 0; step < table_size; step++)
        {
            // empty slot
            if (!table[idx] || table[idx] == deleted)
            {
                table[idx] = new PhoneEntry(phone.name, phone.phone_number);
                return true;
            }
            // update
            else if (table[idx]->name == phone.name)
            {
                table[idx]->phone_number = phone.phone_number;
                return true;
            }

            idx = (idx + 1) % table_size; // move next
        }
        return false; // can't insert. full table
    }

    void print_all()
    {
        for (int hash = 0; hash < table_size; hash++)
        {
            cout << hash << " ";
            if (table[hash] == deleted)
                cout << "X";
            else if (!table[hash])
                cout << "E";
            else
                table[hash]->print();

            cout << "\n";
        }
        cout << "****************\n";
    }

    bool remove(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;
        for (int step = 0; step < table_size; step++)
        {
            // empty slot
            if (!table[idx])
                break;

            // found
            else if (table[idx] != deleted && table[idx]->name == phone.name)
            {
                delete table[idx];
                table[idx] = deleted;
                return true;
            }

            idx = (idx + 1) % table_size; // move next
        }
        return false; // can't insert. full table
    }
};

int main()
{
    PhoneHashTable table(11);
    table.put(PhoneEntry("mostafa", "604-401-120"));
    table.put(PhoneEntry("mostafa", "604-401-777"));
    table.put(PhoneEntry("ali", "604-401-343"));
    table.put(PhoneEntry("ziad", "604-401-17"));
    table.put(PhoneEntry("hany", "604-401-758"));
    table.put(PhoneEntry("belal", "604-401-550"));
    table.put(PhoneEntry("john", "604-401-223"));

    table.print_all();
    /*
        0 E
        1 (belal, 604-401-550)
        2 (ziad, 604-401-17)
        3 E
        4 (mostafa, 604-401-777)
        5 (hany, 604-401-758)
        6 E
        7 (john, 604-401-223)
        8 (ali, 604-401-343)
        9 E
        10 E
     */

    cout << table.remove(PhoneEntry("smith", "")) << "\n"; // 0
    cout << table.remove(PhoneEntry("hany", "")) << "\n";  // 1
    cout << table.remove(PhoneEntry("john", "")) << "\n";  // 1
    table.print_all();

    /*
        0 E
        1 (belal, 604-401-550)
        2 (ziad, 604-401-17)
        3 E
        4 (mostafa, 604-401-777)
        5 X
        6 E
        7 X
        8 (ali, 604-401-343)
        9 E
        10 E
    */
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}