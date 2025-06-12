#include <bits/stdc++.h>
using namespace std;

/**
 * Segment Tree for range sum queries and point updates.
 * Builds the tree in O(n), supports updates and queries in O(log n).
 */
class SumSegmentTree 
{
private:
    int n;                // Original array size
    vector<int> tree;     // Segment tree array (size: 2 * n)

public:
    // Constructor to build the tree from initial values
    SumSegmentTree(const vector<int>& values) 
    {
        n = values.size();
        tree.resize(2 * n, 0);

        // Fill the leaves (second half of tree)
        for (int i = 0; i < n; ++i)
            tree[i + n] = values[i];

        // Build the internal nodes
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    // Update a single index to a new value
    void update(int index, int value) 
    {
        index += n;
        tree[index] = value;

        // Update parent nodes
        while (index > 1) 
        {
            index /= 2;
            tree[index] = tree[2 * index] + tree[2 * index + 1];
        }
    }

    // Query sum in the range [left, right)
    int rangeSum(int left, int right) 
    {
        int sum = 0;
        left += n;
        right += n;

        while (left < right) 
        {
            if (left % 2 == 1)  // If left is a right child
                sum += tree[left++];

            if (right % 2 == 1) // If right is a right child
                sum += tree[--right];

            left /= 2;
            right /= 2;
        }
        return sum;
    }
};

// Test for SumSegmentTree
int main() 
{
    vector<int> data = {1, 2, 3, 4, 5};
    SumSegmentTree st(data);

    cout << "Initial sum [0, 5): " << st.rangeSum(0, 5) << endl; // 15
    cout << "Sum [1, 4): " << st.rangeSum(1, 4) << endl;         // 9

    st.update(2, 10); // Update index 2 to 10

    cout << "After update: sum [1, 4): " << st.rangeSum(1, 4) << endl; // 16
}