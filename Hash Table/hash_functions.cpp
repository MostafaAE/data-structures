#include <bits/stdc++.h>
using namespace std;

int hash_num(int value, int n_ = 65407)
{
    long long n = n_;
    return (value % n + n) % n;
}

int hash_string(string str, int n_)
{
    long long n = n_;
    long long sum = 0;
    for (int i = 0; i < (int)str.size(); i++)
        sum = (sum * 26 + str[i] - 'a') % n;
    return sum % n;
}

int hash_string_lower_upper_digits(string str, int n_ = 65407)
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

int hash_string_folding(string str, int n_ = 65407)
{
    long long n = n_;
    long long sum = 0;
    for (int i = 0; i < (int)str.size(); i += 4)
    {
        string block = str.substr(i, 4);
        sum += hash_string_lower_upper_digits(block);
        sum %= n;
    }
    return sum;
}

int main()
{
    cout << hash_string_folding("aabcdefgAxT334gfg"); // 635

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}