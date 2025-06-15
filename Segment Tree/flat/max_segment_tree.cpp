#include <bits/stdc++.h>
using namespace std;

/**
 * Segment Tree for range maximum queries and point updates.
 */
class MaxSegmentTree 
{
private:
    int n;
    vector<int> tree;
    const int NEG_INF = -1e9 - 5; // Small value for initialization

public:
    // Constructor to build tree from initial values
    MaxSegmentTree(const vector<int>& values) 
    {
        n = values.size();
        tree.resize(2 * n, NEG_INF);

        for (int i = 0; i < n; ++i)
            tree[i + n] = values[i];

        for (int i = n - 1; i > 0; --i)
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }

    // Update a single index to a new value
    void update(int index, int value) 
    {
        index += n;
        tree[index] = value;

        while (index > 1) 
        {
            index /= 2;
            tree[index] = max(tree[2 * index], tree[2 * index + 1]);
        }
    }

    // Query maximum in the range [left, right)
    int rangeMax(int left, int right) 
    {
        int res = NEG_INF;
        left += n;
        right += n;

        while (left < right) 
        {
            if (left & 1)
                res = max(res, tree[left++]);

            if (right & 1)
                res = max(res, tree[--right]);

            left /= 2;
            right /= 2;
        }
        return res;
    }
};

// Test for MaxSegmentTree
int main() 
{
    vector<int> data = {1, 3, 2, 7, 9, 11};
    MaxSegmentTree st(data);

    cout << "Max [1, 5): " << st.rangeMax(1, 5) << endl; // 9

    st.update(4, 0); // Update index 4 to 0

    cout << "After update: Max [1, 5): " << st.rangeMax(1, 5) << endl; // 7
    cout << "Max [3, 6): " << st.rangeMax(3, 6) << endl; // 11
}