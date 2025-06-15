#include <bits/stdc++.h>
using namespace std;

/**
 * Segment Tree for range minimum queries and point updates.
 */
class MinSegmentTree 
{
private:
    int n;
    vector<int> tree;
    const int INF = 1e9 + 5;  // Large value for initialization

public:
    // Constructor to build tree from initial values
    MinSegmentTree(const vector<int>& values) 
    {
        n = values.size();
        tree.resize(2 * n, INF);

        for (int i = 0; i < n; ++i)
            tree[i + n] = values[i];

        for (int i = n - 1; i > 0; --i)
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }

    // Update a single index to a new value
    void update(int index, int value) 
    {
        index += n;
        tree[index] = value;

        while (index > 1) 
        {
            index /= 2;
            tree[index] = min(tree[2 * index], tree[2 * index + 1]);
        }
    }

    // Query minimum in the range [left, right)
    int rangeMin(int left, int right) 
    {
        int res = INF;
        left += n;
        right += n;

        while (left < right) 
        {
            if (left & 1)
                res = min(res, tree[left++]);

            if (right & 1)
                res = min(res, tree[--right]);

            left /= 2;
            right /= 2;
        }
        return res;
    }
};

// Test for MinSegmentTree
int main() 
{
    vector<int> data = {5, 2, 6, 1, 4};
    MinSegmentTree st(data);

    cout << "Min [0, 5): " << st.rangeMin(0, 5) << endl; // 1
    cout << "Min [1, 4): " << st.rangeMin(1, 4) << endl; // 1

    st.update(3, 10); // Update index 3 to 10

    cout << "After update: Min [1, 4): " << st.rangeMin(1, 4) << endl; // 2
}