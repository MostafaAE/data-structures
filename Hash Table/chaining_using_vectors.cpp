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

int main()
{
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}