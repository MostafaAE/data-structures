// Recursive Segment Tree with Lazy Propagation for Range Sum Queries and Updates
#include <bits/stdc++.h>
using namespace std;

class LazySumSegmentTree 
{
private:
    int n;
    vector<int> tree, lazy;

    // Push pending updates to children
    void push(int node, int left, int right) 
    {
        if (lazy[node] != 0) 
        {
            tree[node] += (right - left + 1) * lazy[node];

            // Propagate to children if not a leaf
            if (left != right) 
            {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }

            lazy[node] = 0;
        }
    }

    // Build the tree from input values
    void build(const vector<int>& values, int node, int left, int right) 
    {
        if (left == right) 
        {
            tree[node] = values[left];
            return;
        }

        int mid = (left + right) / 2;
        build(values, 2 * node, left, mid);
        build(values, 2 * node + 1, mid + 1, right);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Update range [l, r] with value val
    void rangeUpdate(int l, int r, int val, int node, int left, int right) 
    {
        push(node, left, right);

        if (r < left || l > right)
            return; // No overlap

        if (l <= left && right <= r) 
        {
            lazy[node] += val;
            push(node, left, right);
            return;
        }

        int mid = (left + right) / 2;
        rangeUpdate(l, r, val, 2 * node, left, mid);
        rangeUpdate(l, r, val, 2 * node + 1, mid + 1, right);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Query range sum in [l, r]
    int rangeSum(int l, int r, int node, int left, int right) 
    {
        push(node, left, right);

        if (r < left || l > right)
            return 0; // No overlap

        if (l <= left && right <= r)
            return tree[node]; // Total overlap

        int mid = (left + right) / 2;
        return rangeSum(l, r, 2 * node, left, mid) + rangeSum(l, r, 2 * node + 1, mid + 1, right);
    }

public:
    LazySumSegmentTree(const vector<int>& values) 
    {
        n = values.size();
        tree.resize(4 * n);
        lazy.resize(4 * n);
        build(values, 1, 0, n - 1);
    }

    void update(int l, int r, int val) 
    {
        rangeUpdate(l, r, val, 1, 0, n - 1);
    }

    int query(int l, int r) 
    {
        return rangeSum(l, r, 1, 0, n - 1);
    }
};

// Test
int main() 
{
    vector<int> data = {1, 2, 3, 4, 5};
    LazySumSegmentTree st(data);

    cout << "Sum [0, 4]: " << st.query(0, 4) << endl; // 15

    st.update(1, 3, 2); // Add 2 to indices 1 to 3
    cout << "After update, Sum [0, 4]: " << st.query(0, 4) << endl; // 21
    cout << "Sum [2, 4]: " << st.query(2, 4) << endl; // 16

    return 0;
}
