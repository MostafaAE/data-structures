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
    double limit_load_factor;
    int total_elements;
    vector<vector<PhoneEntry>> table;

public:
    PhoneHashTable(int table_size = 10, double limit_load_factor = 0.75) : table_size(table_size), limit_load_factor(limit_load_factor)
    {
        total_elements = 0;
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
        total_elements++;
        table[idx].push_back(phone);
        rehashing();
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

    bool get(PhoneEntry &phone)
    {
        int idx = phone.hash() % table_size;

        for (int i = 0; i < (int)table[idx].size(); i++)
        {
            if (table[idx][i].name == phone.name)
            {
                phone = table[idx][i];
                return true;
            }
        }
        return false;
    }

    bool remove(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < (int)table[idx].size(); i++)
        {
            if (table[idx][i].name == phone.name)
            {
                // Swap with last and remove last in O(1)
                swap(table[idx][i], table[idx].back());
                table[idx].pop_back();
                total_elements--;
                return true;
            }
        }
        return false;
    }

    void rehashing()
    {
        double cur_load_factor = (double)total_elements / table_size;
        // cout << cur_load_factor << "\n";
        if (cur_load_factor < limit_load_factor)
            return;
        cout << "rehashing: new size = " << table_size * 2 << endl;
        int new_table_size = table_size * 2;
        PhoneHashTable new_table(new_table_size, limit_load_factor);

        for (int hash = 0; hash < table_size; hash++)
        {
            if (table[hash].size() == 0)
                continue;

            for (int i = 0; i < (int)table[hash].size(); i++)
                new_table.put(table[hash][i]);
        }

        table_size = new_table_size;
        table = new_table.table;

        print_all();
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
    Hash 1: (mostafa, 604-401-777)  (ziad, 604-4    01-17)
    Hash 2: (belal, 604-401-550)
    */

    PhoneEntry e("mostafa", "");
    if (table.get(e))
        cout << e.phone_number << "\n"; // 604-401-777

    cout << table.remove(PhoneEntry("smith", "")) << "\n"; // 0
    cout << table.remove(PhoneEntry("hany", "")) << "\n";  // 1
    cout << table.remove(PhoneEntry("belal", "")) << "\n"; // 1
    table.print_all();
    // Hash 0: (ali, 604-401-343)  (john, 604-401-223)
    // Hash 1: (mostafa, 604-401-777)  (ziad, 604-401-17)

    cout << "\n*******************************************\n";
    PhoneHashTable table2;
    for (int i = 0; i < 100; ++i)
        table2.put(PhoneEntry(to_string(i), to_string(i * 10)));

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}