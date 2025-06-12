#include <bits/stdc++.h>
using namespace std;

// Class to represent a Binary Indexed Tree (Fenwick Tree)
class BinaryIndexedTree 
{
public:
    // Constructor to initialize BIT using O(n) time complexity
    BinaryIndexedTree(const vector<int>& inputArray) 
    {
        // Initialize BIT array with one extra size (1-based indexing)
        tree = vector<int>(inputArray.size() + 1, 0);

        // Copy input values to BIT array (1-based indexing)
        for (int i = 0; i < inputArray.size(); i++) 
        {
            tree[i + 1] = inputArray[i];
        }

        // Update BIT array for cumulative sums
        for (int i = 1; i < tree.size(); i++) 
        {
            int parent = i + (i & -i);
            if (parent < tree.size()) 
            {
                tree[parent] += tree[i];
            }
        }
    }

    /* 
    // Alternative Constructor: Initialize BIT using O(n * log(n)) time complexity
    BinaryIndexedTree(const vector<int>& inputArray) {
        // Initialize BIT array with one extra size (1-based indexing)
        tree = vector<int>(inputArray.size() + 1, 0);

        // Build BIT by updating each element individually
        for (int i = 0; i < inputArray.size(); i++) {
            update(i, inputArray[i]);
        }
    }
    */

    // Get prefix sum up to the element at index idx
    int getPrefixSum(int idx) const 
    {
        int sum = 0;
        for (++idx; idx > 0; idx -= idx & -idx) 
        {
            sum += tree[idx];
        }
        return sum;
    }

    // Get the sum of elements in the range [fromIdx, toIdx]
    int getRangeSum(int fromIdx, int toIdx) const 
    {
        return fromIdx == 0 ? getPrefixSum(toIdx) : getPrefixSum(toIdx) - getPrefixSum(fromIdx - 1);
    }

    // Update the value at index idx by adding delta
    void update(int idx, int delta) 
    {
        for (++idx; idx < tree.size(); idx += idx & -idx) 
        {
            tree[idx] += delta;
        }
    }

private:
    vector<int> tree; // BIT array to store cumulative sums
};

// Helper function to display the BIT and test operations
void printBIT(const BinaryIndexedTree& bit, int length) 
{
    cout << "Index:  ";
    for (int i = 0; i < length; ++i)
        cout << setw(3) << i << " ";
    cout << endl;

    cout << "Array:  ";
    for (int i = 0; i < length; ++i)
        cout << setw(3) << bit.getRangeSum(i, i) << " ";
    cout << endl << endl;

    cout << "Prefix sum of first 13 elements: " << bit.getPrefixSum(12) << endl;
    cout << "Prefix sum of first 7 elements:  " << bit.getPrefixSum(6) << endl;
    cout << "Range sum from index 1 to 5:     " << bit.getRangeSum(1, 5) << endl;
    cout << endl;
}

int main() 
{
    // Input array
    vector<int> array{ 1, 7, 3, 0, 5, 8, 3, 2, 6, 2, 1, 1, 4, 5 };
    int length = array.size();

    // Initialize the Binary Indexed Tree
    BinaryIndexedTree bit(array);

    // Display the BIT structure and perform tests
    printBIT(bit, length);

    // Update element at index 4 by adding 2
    bit.update(4, 2);
    cout << "Added 2 to element at index 4\n" << endl;

    // Display the updated BIT
    printBIT(bit, length);

    return 0;
}