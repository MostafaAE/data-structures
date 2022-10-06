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

int hash_string_lower_upper_digits(string str, int n)
{
    long long nn = n;
    long long sum = 0;
    int base = 2 * 26 + 10; // lower + upper + digits

    for (int i = 0; i < (int)str.size(); i++)
    {
        // lower [0 - 25], upper [26 - 51], digits [52 - 61]
        int value = 0;
        if (islower[str[i]])
            value = str[i] - 'a';
        else if (isupper(str[i]))
            value = 26 + str[i] - 'A';
        else if (isdigit(str[i]))
            value = 2 * 26 + str[i] - '0';
        else
            assert(false);

        sum = (sum * base + value) % nn;
    }

    return sum % nn;
}

int main()
{

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}