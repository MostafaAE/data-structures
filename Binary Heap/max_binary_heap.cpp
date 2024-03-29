#include <bits/stdc++.h>
using namespace std;

class MaxHeap
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
        if (child_pos == 0 || array[parent_pos] >= array[child_pos])
            return;

        swap(array[parent_pos], array[child_pos]);
        heapify_up(parent_pos);
    }

    void heapify_down(int node = 0)
    {
        int child_pos = left(node);
        int right_child = right(node);

        // the node is a leaf node (no children)
        if (child_pos == -1)
            return;

        // if the node have left and right children
        // get the maximum of them
        if (right_child != -1 && array[right_child] > array[child_pos])
            child_pos = right_child;

        // if the node is greater than the minimum of its children
        // swap it with the minimum and repeat
        if (array[child_pos] > array[node])
        {
            swap(array[node], array[child_pos]);
            heapify_down(child_pos);
        }
    }

    // O(n)
    void heapify()
    {
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify_down(i);
    }

public:
    MaxHeap()
    {
        array = new int[capacity]{};
        size = 0;
    }

    MaxHeap(vector<int> &elements)
    {
        assert((int)elements.size() <= capacity);
        array = new int[capacity]{};
        size = elements.size();

        for (int i = 0; i < (int)elements.size(); i++)
            array[i] = elements[i];

        heapify();
    }

    ~MaxHeap()
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

    void pop()
    {
        assert(!isempty());
        array[0] = array[--size];
        heapify_down(0);
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

// O(nlogn)
void heap_sort(vector<int> &elements)
{
    MaxHeap heap;
    for (int i = 0; i < elements.size(); ++i)
        heap.push(elements[i]);

    for (int i = 0; i < elements.size(); ++i)
    {
        elements[i] = heap.top();
        heap.pop();
    }
}
int main()
{
    vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};
    MaxHeap heap(v);

    while (!heap.isempty()) // 2 5 6 7 8 10 12 14 17 19 22 25 30 37
    {
        cout << heap.top() << " ";
        heap.pop();
    }

    // vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};
    // heap_sort(v);
    // for (int i = 0; i < v.size(); ++i) // 2 5 6 7 8 10 12 14 17 19 22 25 30 37
    //     cout << v[i] << " ";

    // MaxHeap heap;
    // vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

    // for (int i = 0; i < v.size(); ++i)
    //     heap.push(v[i]);

    // while (!heap.isempty()) // 2 5 6 7 8 10 12 14 17 19 22 25 30 37
    // {
    //     cout << heap.top() << " ";
    //     heap.pop();
    // }

    cout << "\n\nNO RTE\n";

    return 0;
}