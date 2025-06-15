// Recursive Segment Tree for Range Minimum Query (RMQ)
#include <bits/stdc++.h>
using namespace std;

class MinSegmentTree 
{
private:
    int n;
    vector<int> tree;

    // Build the tree recursively
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

        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    // Query the minimum in the range [queryLeft, queryRight]
    int rangeMin(int queryLeft, int queryRight, int node, int left, int right) 
    {
        if (queryRight < left || queryLeft > right) 
        {
            return INT_MAX; // No overlap
        }

        if (queryLeft <= left && right <= queryRight) 
        {
            return tree[node]; // Total overlap
        }

        // Partial overlap
        int mid = (left + right) / 2;
        int leftMin = rangeMin(queryLeft, queryRight, 2 * node, left, mid);
        int rightMin = rangeMin(queryLeft, queryRight, 2 * node + 1, mid + 1, right);

        return min(leftMin, rightMin);
    }

    // Point update: update index to new value
    void update(int index, int value, int node, int left, int right) 
    {
        if (left == right) 
        {
            tree[node] = value;
            return;
        }

        int mid = (left + right) / 2;
        if (index <= mid) 
        {
            update(index, value, 2 * node, left, mid);
        } 
        else 
        {
            update(index, value, 2 * node + 1, mid + 1, right);
        }

        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

public:
    MinSegmentTree(const vector<int>& values) 
    {
        n = values.size();
        tree.resize(4 * n, INT_MAX);
        build(values, 1, 0, n - 1);
    }

    int rangeMin(int left, int right) 
    {
        return rangeMin(left, right, 1, 0, n - 1);
    }

    void update(int index, int value) 
    {
        update(index, value, 1, 0, n - 1);
    }
};

int main() 
{
    vector<int> data = {5, 2, 6, 1, 4};
    MinSegmentTree st(data);

    cout << "Min [0, 4]: " << st.rangeMin(0, 4) << endl; // Output: 1
    cout << "Min [1, 3]: " << st.rangeMin(1, 3) << endl; // Output: 1

    st.update(3, 10); // Update index 3 from 1 to 10
    cout << "After update, Min [1, 3]: " << st.rangeMin(1, 3) << endl; // Output: 2

    st.update(4, 0); // Update index 4 from 4 to 0
    cout << "After update, Min [0, 4]: " << st.rangeMin(0, 4) << endl; // Output: 0
}
