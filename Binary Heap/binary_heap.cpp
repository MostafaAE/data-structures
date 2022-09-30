#include <bits/stdc++.h>
using namespace std;

class MinHeap
{
private:
    int *array{};
    int size{};
    int capacity{1000};

    int left(int node)
    {
        int pos = 2 * node + 1;

        return pos >= size ? -1 : pos;
    }

    int right(int node)
    {
        int pos = 2 * node + 2;

        return pos >= size ? -1 : pos;
    }

    int parent(int node)
    {
        return node == 0 ? -1 : (node - 1) / 2;
    }

    // O(log(n))
    void heapify_up(int child_pos)
    {

        int parent_pos = parent(child_pos);

        // stop when parent is smaller (or no parent)
        if (child_pos == 0 || array[parent_pos] <= array[child_pos])
            return;

        swap(array[parent_pos], array[child_pos]);
        heapify_up(parent_pos);
    }

public:
    MinHeap()
    {
        array = new int[capacity];
        size = 0;
    }

    ~MinHeap()
    {
        delete[] array;
        array = nullptr;
    }

    void push(int key)
    {
        assert(size + 1 <= capacity);
        array[size++] = key;
        heapify_up(size - 1);
    }

    int top()
    {
        assert(!isempty());
        return array[0];
    }

    bool isempty()
    {
        return size == 0;
    }
};

int main()
{
    MinHeap heap;
    vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

    for (int i = 0; i < v.size(); ++i)
        heap.push(v[i]);

    return 0;
}